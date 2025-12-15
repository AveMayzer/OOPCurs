#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include "../communicator/common.h"

// Виджет светофора (3 лампы в вертикальном прямоугольнике)
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

class TInterface : public QWidget
{
    Q_OBJECT

private:
    // Кнопки управления пультом
    QPushButton* btnTurnOn;
    QPushButton* btnTurnOff;

    // Кнопки режимов
    QPushButton* btnAutonomous;
    QPushButton* btnManual;
    QPushButton* btnAuto;

    // Элементы ручного управления
    QGroupBox* manualGroup;
    QComboBox* comboNS;
    QComboBox* comboEW;
    QPushButton* btnApplyManual;

    // Элементы настройки времени
    QGroupBox* timingsGroup;
    QSpinBox* spinGreen;
    QSpinBox* spinYellow;
    QPushButton* btnApplyTimings;

    // Индикаторы состояния
    QLabel* lblPanelState;

    // Виджеты светофоров
    TrafficLightWidget* lightNorth;
    TrafficLightWidget* lightSouth;
    TrafficLightWidget* lightEast;
    TrafficLightWidget* lightWest;

    // Текущее состояние пульта
    int currentPanelState;

    void setupUI();
    void updateControlsState();

public:
    TInterface(QWidget* parent = nullptr);
    void updateStatus(int panelState, const QString& status);
    void showError(const QString& error);

signals:
    void request(QString msg);

private slots:
    void onTurnOn();
    void onTurnOff();
    void onSetAutonomous();
    void onSetManual();
    void onSetAuto();
    void onApplyManual();
    void onApplyTimings();
};

#endif // INTERFACE_H
