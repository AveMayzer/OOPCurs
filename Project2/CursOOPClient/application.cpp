#include "application.h"

ClientApplication::ClientApplication(int argc, char* argv[])
    : QApplication(argc, argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001 };
    comm = new TCommunicator(pars, this);

    mainWindow = new MainWindow();
    mainWindow->show();

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(fromCommunicator(QByteArray)));
    connect(mainWindow, SIGNAL(request(QString)), this, SLOT(toCommunicator(QString)));
}

ClientApplication::~ClientApplication(){

}

void ClientApplication::fromCommunicator(QByteArray msg)
{
    QString message = QString::fromUtf8(msg);
    QStringList parts = message.split(separator, Qt::SkipEmptyParts);

    if (parts.isEmpty()) return;

    int messageType = parts[0].toInt();

    switch (messageType) {
    case MSG_STATUS_UPDATE:
    case MSG_PANEL_STATE_CHANGED:
        if (parts.size() >= 2) {
            int panelState = parts[1].toInt();
            QString status = parts.size() >= 3 ? parts.mid(2).join("\n") : "";
            mainWindow->updateStatus(panelState, status);
        }
        break;

    case MSG_ERROR:
        if (parts.size() >= 2) {
            mainWindow->showError(parts[1]);
        }
        break;
    }
}

void ClientApplication::toCommunicator(QString msg)
{
    comm->send(msg.toUtf8());
}
