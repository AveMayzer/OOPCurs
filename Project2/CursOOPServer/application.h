#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <QApplication>
#include "../communicator/communicator.h"
#include "../communicator/common.h"
#include "intersection.h"
#include "mainwindow.h"

class ServerApplication : public QApplication
{
    Q_OBJECT

private:
    TCommunicator* comm;
    Intersection* intersection;
    MainWindow* mainWindow;

    QString processRequest(int messageType, const QStringList& params);

public:
    ServerApplication(int argc, char* argv[]);
    ~ServerApplication();

public slots:
    void onMessageReceived(QByteArray msg);
    void onIntersectionStatusChanged(QString status);
};

#endif // SERVER_APPLICATION_H
