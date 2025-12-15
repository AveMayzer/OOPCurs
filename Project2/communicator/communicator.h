#pragma once

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QByteArray>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QDebug>

struct TCommParams
{
    QHostAddress rHost;
    quint16      rPort;
    QHostAddress sHost;
    quint16      sPort;
};

class TCommunicator : public QUdpSocket
{
    Q_OBJECT

    bool         ready;
    TCommParams  params;

public:
    TCommunicator(TCommParams& pars, QObject *parent = nullptr);
    bool isReady() { return ready; }

signals:
    void recieved(QByteArray msg);

public slots:
    void send(QByteArray msg);

private slots:
    void recieve();
};

#endif // COMMUNICATOR_H
