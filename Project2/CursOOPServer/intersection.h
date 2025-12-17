#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QObject>
#include <QTimer>
#include "../communicator/common.h"

class Intersection : public QObject
{
    Q_OBJECT

private:
    PanelState panelState;
    LightState lights[4];

    int greenTime;
    int yellowTime;
    int redTime;

    QTimer* autoTimer;
    QTimer* blinkTimer;
    int currentPhase;
    bool blinkState;

    void setDirectionState(Direction dir, LightState state);

public:
    Intersection(QObject* parent = nullptr);
    ~Intersection();

    void turnOn();
    void turnOff();
    void setAutonomous();
    void setManual();
    void setAutomatic();
    void setManualState(LightState nsState, LightState ewState);
    void setIndividualState(LightState north, LightState south, LightState east, LightState west);
    void setTimings(int green, int yellow, int red);

    PanelState getPanelState() const;
    QString getStatusString() const;

signals:
    void statusChanged(QString status);

private slots:
    void onAutoTimerTick();
    void onBlinkTimerTick();
};

#endif // INTERSECTION_H
