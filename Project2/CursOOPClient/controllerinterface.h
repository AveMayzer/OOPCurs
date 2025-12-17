#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include "../communicator/common.h"

class ControllerInterface : public QWidget
{
    Q_OBJECT

private:
    QPushButton* btnTurnOn;
    QPushButton* btnTurnOff;

    QPushButton* btnAutonomous;
    QPushButton* btnManual;
    QPushButton* btnAuto;

    // Ручное управление — по направлениям
    QGroupBox* manualGroup;
    QComboBox* comboNS;
    QComboBox* comboEW;
    QPushButton* btnApplyManual;

    // Ручное управление — индивидуально
    QComboBox* comboNorth;
    QComboBox* comboSouth;
    QComboBox* comboEast;
    QComboBox* comboWest;
    QPushButton* btnApplyIndividual;

    QGroupBox* timingsGroup;
    QSpinBox* spinGreen;
    QSpinBox* spinYellow;
    QPushButton* btnApplyTimings;

    QLabel* lblPanelState;

    int currentPanelState;

    void setupUI();
    void updateControlsState();
    void setupLightCombo(QComboBox* combo);

public:
    ControllerInterface(QWidget* parent = nullptr);
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
    void onApplyIndividual();
    void onApplyTimings();
};

#endif // CONTROLLERINTERFACE_H
