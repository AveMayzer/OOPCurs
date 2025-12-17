#include "eventcontrolwindow.h"
#include <QMessageBox>

EventControlWindow::EventControlWindow(QWidget* parent)
    : QWidget(parent),
    currentPanelState(PANEL_OFF)
{
    setupUI();
    updateControlsState();
}



void EventControlWindow::setupLightCombo(QComboBox* combo)
{
    combo->addItem("Красный", LIGHT_RED);
    combo->addItem("Желтый", LIGHT_YELLOW);
    combo->addItem("Зеленый", LIGHT_GREEN);
}

void EventControlWindow::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QGroupBox* panelGroup = new QGroupBox("Управление пультом");
    QHBoxLayout* panelLayout = new QHBoxLayout(panelGroup);

    btnTurnOn = new QPushButton("Включить");
    btnTurnOff = new QPushButton("Выключить");
    lblPanelState = new QLabel("Состояние: Выключен");
    lblPanelState->setStyleSheet("font-weight: bold; font-size: 14px;");

    panelLayout->addWidget(btnTurnOn);
    panelLayout->addWidget(btnTurnOff);
    panelLayout->addWidget(lblPanelState);
    panelLayout->addStretch();

    connect(btnTurnOn, SIGNAL(clicked()), this, SLOT(onTurnOn()));
    connect(btnTurnOff, SIGNAL(clicked()), this, SLOT(onTurnOff()));

    QGroupBox* modeGroup = new QGroupBox("Режим работы");
    QHBoxLayout* modeLayout = new QHBoxLayout(modeGroup);

    btnAutonomous = new QPushButton("Автономный");
    btnManual = new QPushButton("Ручной");
    btnAuto = new QPushButton("Автоматический");

    modeLayout->addWidget(btnAutonomous);
    modeLayout->addWidget(btnManual);
    modeLayout->addWidget(btnAuto);

    connect(btnAutonomous, SIGNAL(clicked()), this, SLOT(onSetAutonomous()));
    connect(btnManual, SIGNAL(clicked()), this, SLOT(onSetManual()));
    connect(btnAuto, SIGNAL(clicked()), this, SLOT(onSetAuto()));

    manualGroup = new QGroupBox("Ручное управление светофорами");
    QVBoxLayout* manualMainLayout = new QVBoxLayout(manualGroup);

    QTabWidget* manualTabs = new QTabWidget();

    QWidget* tabDirections = new QWidget();
    QGridLayout* dirLayout = new QGridLayout(tabDirections);

    dirLayout->addWidget(new QLabel("Север-Юг:"), 0, 0);
    comboNS = new QComboBox();
    setupLightCombo(comboNS);
    dirLayout->addWidget(comboNS, 0, 1);

    dirLayout->addWidget(new QLabel("Восток-Запад:"), 1, 0);
    comboEW = new QComboBox();
    setupLightCombo(comboEW);
    dirLayout->addWidget(comboEW, 1, 1);

    btnApplyManual = new QPushButton("Применить");
    dirLayout->addWidget(btnApplyManual, 2, 0, 1, 2);
    connect(btnApplyManual, SIGNAL(clicked()), this, SLOT(onApplyManual()));

    QWidget* tabIndividual = new QWidget();
    QGridLayout* indLayout = new QGridLayout(tabIndividual);

    indLayout->addWidget(new QLabel("Север:"), 0, 0);
    comboNorth = new QComboBox();
    setupLightCombo(comboNorth);
    indLayout->addWidget(comboNorth, 0, 1);

    indLayout->addWidget(new QLabel("Юг:"), 1, 0);
    comboSouth = new QComboBox();
    setupLightCombo(comboSouth);
    indLayout->addWidget(comboSouth, 1, 1);

    indLayout->addWidget(new QLabel("Восток:"), 2, 0);
    comboEast = new QComboBox();
    setupLightCombo(comboEast);
    indLayout->addWidget(comboEast, 2, 1);

    indLayout->addWidget(new QLabel("Запад:"), 3, 0);
    comboWest = new QComboBox();
    setupLightCombo(comboWest);
    indLayout->addWidget(comboWest, 3, 1);

    btnApplyIndividual = new QPushButton("Применить");
    indLayout->addWidget(btnApplyIndividual, 4, 0, 1, 2);
    connect(btnApplyIndividual, SIGNAL(clicked()), this, SLOT(onApplyIndividual()));

    manualTabs->addTab(tabDirections, "По направлениям");
    manualTabs->addTab(tabIndividual, "Индивидуально");

    manualMainLayout->addWidget(manualTabs);

    mainLayout->addWidget(panelGroup);
    mainLayout->addWidget(modeGroup);
    mainLayout->addWidget(manualGroup);
    mainLayout->addStretch();
}

void EventControlWindow::updateControlsState()
{
    btnTurnOn->setEnabled(currentPanelState == PANEL_OFF);
    btnTurnOff->setEnabled(currentPanelState != PANEL_OFF);

    bool panelOn = (currentPanelState != PANEL_OFF);
    btnAutonomous->setEnabled(panelOn);
    btnManual->setEnabled(panelOn);
    btnAuto->setEnabled(panelOn);

    bool isManual = (currentPanelState == PANEL_MANUAL);
    manualGroup->setEnabled(isManual);
}

void EventControlWindow::updatePanelState(int panelState)
{
    currentPanelState = panelState;

    QString stateStr;
    switch (panelState) {
    case PANEL_OFF:        stateStr = "Выключен"; break;
    case PANEL_AUTONOMOUS: stateStr = "Автономный"; break;
    case PANEL_MANUAL:     stateStr = "Ручной"; break;
    case PANEL_AUTO:       stateStr = "Автоматический"; break;
    }
    lblPanelState->setText(QString("Состояние: %1").arg(stateStr));

    updateControlsState();
}

void EventControlWindow::showError(const QString& error)
{
    QMessageBox::warning(this, "Ошибка", error);
}

void EventControlWindow::onTurnOn() {
    QString msg;
    msg << QString::number(MSG_TURN_ON_PANEL);
    emit request(msg);
}

void EventControlWindow::onTurnOff() {
    QString msg;
    msg << QString::number(MSG_TURN_OFF_PANEL);
    emit request(msg);
}

void EventControlWindow::onSetAutonomous() {
    QString msg;
    msg << QString::number(MSG_SET_AUTONOMOUS);
    emit request(msg);
}

void EventControlWindow::onSetManual() {
    QString msg;
    msg << QString::number(MSG_SET_MANUAL);
    emit request(msg);
}

void EventControlWindow::onSetAuto() {
    QString msg;
    msg << QString::number(MSG_SET_AUTO);
    emit request(msg);
}

void EventControlWindow::onApplyManual() {
    QString msg;
    msg << QString::number(MSG_MANUAL_SET_STATE)
        << QString::number(comboNS->currentData().toInt())
        << QString::number(comboEW->currentData().toInt());
    emit request(msg);
}

void EventControlWindow::onApplyIndividual() {
    QString msg;
    msg << QString::number(MSG_MANUAL_SET_INDIVIDUAL)
        << QString::number(comboNorth->currentData().toInt())
        << QString::number(comboSouth->currentData().toInt())
        << QString::number(comboEast->currentData().toInt())
        << QString::number(comboWest->currentData().toInt());
    emit request(msg);
}
