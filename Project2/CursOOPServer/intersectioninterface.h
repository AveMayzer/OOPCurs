#ifndef INTERSECTIONINTERFACE_H
#define INTERSECTIONINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QFrame>
#include "../communicator/common.h"

// Виджет светофора
class TrafficLightWidget : public QFrame
{
    Q_OBJECT

private:
    QLabel* redLight;
    QLabel* yellowLight;
    QLabel* greenLight;
    QLabel* titleLabel;

public:
    TrafficLightWidget(const QString& title, QWidget* parent = nullptr);
    void setState(LightState state);
};

// Окно перекрёстка (только GUI)
class IntersectionInterface : public QWidget
{
    Q_OBJECT

private:
    QLabel* lblStatus;
    TrafficLightWidget* lightNorth;
    TrafficLightWidget* lightSouth;
    TrafficLightWidget* lightEast;
    TrafficLightWidget* lightWest;

    void setupUI();

public:
    IntersectionInterface(QWidget* parent = nullptr);
    void updateStatus(int panelState, const QString& status);
};

#endif // INTERSECTIONINTERFACE_H
