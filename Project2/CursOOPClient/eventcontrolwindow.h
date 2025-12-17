#ifndef EVENTCONTROLWINDOW_H
#define EVENTCONTROLWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QTabWidget>
#include "../communicator/common.h"

class EventControlWindow : public QWidget
{
    Q_OBJECT

private:
    // Управление пультом
    QPushButton* btnTurnOn;
    QPushButton* btnTurnOff;
    QLabel* lblPanelState;

    // Режимы работы
    QPushButton* btnAutonomous;
    QPushButton* btnManual;
    QPushButton* btnAuto;

    // Ручное управление
    QGroupBox* manualGroup;
    QComboBox* comboNS;
    QComboBox* comboEW;
    QPushButton* btnApplyManual;

    QComboBox* comboNorth;
    QComboBox* comboSouth;
    QComboBox* comboEast;
    QComboBox* comboWest;
    QPushButton* btnApplyIndividual;

    int currentPanelState;

    void setupUI();
    void updateControlsState();
    void setupLightCombo(QComboBox* combo);

public:
    EventControlWindow(QWidget* parent = nullptr);
    void updatePanelState(int panelState);
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
    void onApplyIndividual();
};

#endif // EVENTCONTROLWINDOW_H
