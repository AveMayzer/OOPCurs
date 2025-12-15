#ifndef CLIENT_APPLICATION_H
#define CLIENT_APPLICATION_H

#include <QApplication>
#include "interface.h"
#include "../communicator/communicator.h"
#include "../communicator/common.h"

class ClientApplication : public QApplication
{
    Q_OBJECT

private:
    TCommunicator* comm;
    TInterface* interface;

public:
    ClientApplication(int argc, char** argv);

public slots:
    void fromCommunicator(QByteArray msg);
    void toCommunicator(QString msg);
};

#endif // CLIENT_APPLICATION_H
