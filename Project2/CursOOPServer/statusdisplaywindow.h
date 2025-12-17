#ifndef STATUSDISPLAYWINDOW_H
#define STATUSDISPLAYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QFrame>
#include "../communicator/common.h"

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
    ~TrafficLightWidget();
};

class StatusDisplayWindow : public QWidget
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
    StatusDisplayWindow(QWidget* parent = nullptr);
    void updateStatus(int panelState, const QString& status);
};

#endif // STATUSDISPLAYWINDOW_H
