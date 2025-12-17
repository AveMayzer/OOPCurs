#include "application.h"

ServerApplication::ServerApplication(int argc, char* argv[])
    : QApplication(argc, argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10001,
                        QHostAddress("127.0.0.1"), 10000 };
    comm = new TCommunicator(pars, this);

    intersection = new Intersection(this);

    mainWindow = new MainWindow();
    mainWindow->show();

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(onMessageReceived(QByteArray)));
    connect(intersection, SIGNAL(statusChanged(QString)), this, SLOT(onIntersectionStatusChanged(QString)));
}

ServerApplication::~ServerApplication()
{
    delete intersection;
    delete mainWindow;
}

void ServerApplication::onMessageReceived(QByteArray msg)
{
    QString message = QString::fromUtf8(msg);
    QStringList parts = message.split(separator, Qt::SkipEmptyParts);

    if (parts.isEmpty()) {
        QString response;
        response << QString::number(MSG_ERROR) << "Пустое сообщение";
        comm->send(response.toUtf8());
        return;
    }

    int messageType = parts[0].toInt();
    QStringList params = parts.mid(1);

    QString response = processRequest(messageType, params);
    comm->send(response.toUtf8());
}

QString ServerApplication::processRequest(int messageType, const QStringList& params)
{
    QString response;

    switch (messageType) {
    case MSG_TURN_ON_PANEL:
        intersection->turnOn();
        response << QString::number(MSG_PANEL_STATE_CHANGED)
                 << QString::number(intersection->getPanelState())
                 << "Пульт включен";
        break;

    case MSG_TURN_OFF_PANEL:
        intersection->turnOff();
        response << QString::number(MSG_PANEL_STATE_CHANGED)
                 << QString::number(intersection->getPanelState())
                 << "Пульт выключен";
        break;

    case MSG_SET_AUTONOMOUS:
        if (intersection->getPanelState() == PANEL_OFF) {
            response << QString::number(MSG_ERROR) << "Пульт выключен";
        } else {
            intersection->setAutonomous();
            response << QString::number(MSG_PANEL_STATE_CHANGED)
                     << QString::number(PANEL_AUTONOMOUS)
                     << "Автономный режим";
        }
        break;

    case MSG_SET_MANUAL:
        if (intersection->getPanelState() == PANEL_OFF) {
            response << QString::number(MSG_ERROR) << "Пульт выключен";
        } else {
            intersection->setManual();
            response << QString::number(MSG_PANEL_STATE_CHANGED)
                     << QString::number(PANEL_MANUAL)
                     << "Ручное управление";
        }
        break;

    case MSG_SET_AUTO:
        if (intersection->getPanelState() == PANEL_OFF) {
            response << QString::number(MSG_ERROR) << "Пульт выключен";
        } else {
            intersection->setAutomatic();
            response << QString::number(MSG_PANEL_STATE_CHANGED)
                     << QString::number(PANEL_AUTO)
                     << "Автоматическое управление";
        }
        break;

    case MSG_MANUAL_SET_STATE:
        if (intersection->getPanelState() != PANEL_MANUAL) {
            response << QString::number(MSG_ERROR) << "Не в режиме ручного управления";
        } else if (params.size() < 2) {
            response << QString::number(MSG_ERROR) << "Недостаточно параметров";
        } else {
            LightState nsState = static_cast<LightState>(params[0].toInt());
            LightState ewState = static_cast<LightState>(params[1].toInt());
            intersection->setManualState(nsState, ewState);
            response << QString::number(MSG_STATUS_UPDATE)
                     << QString::number(intersection->getPanelState())
                     << intersection->getStatusString();
        }
        break;

    case MSG_SET_TIMINGS:
        if (params.size() < 2) {
            response << QString::number(MSG_ERROR) << "Недостаточно параметров";
        } else {
            int greenTime = params[0].toInt();
            int yellowTime = params[1].toInt();
            intersection->setTimings(greenTime, yellowTime);
            mainWindow->updateTimings(greenTime, yellowTime);
            response << QString::number(MSG_PANEL_STATE_CHANGED)
                     << QString::number(intersection->getPanelState())
                     << QString("Время: зеленый=%1мс, желтый=%2мс")
                            .arg(greenTime).arg(yellowTime);
        }
        break;

    case MSG_GET_STATUS:
        response << QString::number(MSG_STATUS_UPDATE)
                 << QString::number(intersection->getPanelState())
                 << intersection->getStatusString();
        break;

    case MSG_MANUAL_SET_INDIVIDUAL:
        if (intersection->getPanelState() != PANEL_MANUAL) {
            response << QString::number(MSG_ERROR) << "Не в режиме ручного управления";
        } else if (params.size() < 4) {
            response << QString::number(MSG_ERROR) << "Недостаточно параметров";
        } else {
            LightState north = static_cast<LightState>(params[0].toInt());
            LightState south = static_cast<LightState>(params[1].toInt());
            LightState east = static_cast<LightState>(params[2].toInt());
            LightState west = static_cast<LightState>(params[3].toInt());
            intersection->setIndividualState(north, south, east, west);
            response << QString::number(MSG_STATUS_UPDATE)
                     << QString::number(intersection->getPanelState())
                     << intersection->getStatusString();
        }
        break;

    default:
        response << QString::number(MSG_ERROR) << "Неизвестная команда";
    }

    return response;
}

void ServerApplication::onIntersectionStatusChanged(QString status)
{
    mainWindow->updateStatus(intersection->getPanelState(), status);

    QString response;
    response << QString::number(MSG_STATUS_UPDATE)
             << QString::number(intersection->getPanelState())
             << status;
    comm->send(response.toUtf8());
}
