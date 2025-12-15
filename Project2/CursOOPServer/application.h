#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <QCoreApplication>
#include "../communicator/communicator.h"
#include "../communicator/common.h"
#include "intersection.h"

class ServerApplication : public QCoreApplication
{
    Q_OBJECT

private:
    TCommunicator* comm;
    Intersection* intersection;

    QString processRequest(int messageType, const QStringList& params);
    void sendStatusUpdate();

public:
    ServerApplication(int argc, char* argv[]);
    ~ServerApplication();

public slots:
    void onMessageReceived(QByteArray msg);
    void onIntersectionStatusChanged(QString status);
};

#endif // SERVER_APPLICATION_H
