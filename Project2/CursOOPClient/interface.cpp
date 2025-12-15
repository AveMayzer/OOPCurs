#include "interface.h"
#include <QMessageBox>

// === TrafficLightWidget ===

TrafficLightWidget::TrafficLightWidget(const QString& title, QWidget* parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(2);
    setFixedSize(60, 140);
    setStyleSheet("background-color: #333; border: 2px solid #555; border-radius: 5px;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);

    titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white; font-size: 10px; background: transparent; border: none;");

    redLight = new QLabel();
    yellowLight = new QLabel();
    greenLight = new QLabel();

    QString lightOffStyle = "background-color: #444; border-radius: 15px; border: 1px solid #222;";

    redLight->setFixedSize(30, 30);
    yellowLight->setFixedSize(30, 30);
    greenLight->setFixedSize(30, 30);

    redLight->setStyleSheet(lightOffStyle);
    yellowLight->setStyleSheet(lightOffStyle);
    greenLight->setStyleSheet(lightOffStyle);

    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addWidget(redLight, 0, Qt::AlignCenter);
    layout->addWidget(yellowLight, 0, Qt::AlignCenter);
    layout->addWidget(greenLight, 0, Qt::AlignCenter);
}

void TrafficLightWidget::setState(LightState state)
{
    QString offStyle = "background-color: #444; border-radius: 15px; border: 1px solid #222;";
    QString redOn = "background-color: #ff0000; border-radius: 15px; border: 2px solid #cc0000;";
    QString yellowOn = "background-color: #ffaa00; border-radius: 15px; border: 2px solid #cc8800;";
    QString greenOn = "background-color: #00ff00; border-radius: 15px; border: 2px solid #00cc00;";

    redLight->setStyleSheet(offStyle);
    yellowLight->setStyleSheet(offStyle);
    greenLight->setStyleSheet(offStyle);

    switch (state) {
    case LIGHT_RED:
        redLight->setStyleSheet(redOn);
        break;
    case LIGHT_YELLOW:
    case LIGHT_YELLOW_BLINK:
        yellowLight->setStyleSheet(yellowOn);
        break;
    case LIGHT_GREEN:
        greenLight->setStyleSheet(greenOn);
        break;
    case LIGHT_OFF:
    default:
        break;
    }
}

// === TInterface ===

TInterface::TInterface(QWidget* parent)
    : QWidget(parent),
    currentPanelState(PANEL_OFF)
{
    setupUI();
    setWindowTitle("Пульт управления светофорами");
    setMinimumSize(550, 550);
    updateControlsState();
}

void TInterface::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // === Группа управления пультом ===
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

    // === Группа выбора режима ===
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

    // === Группа настройки времени ===
    timingsGroup = new QGroupBox("Настройка времени (мс) — только в автоматическом режиме");
    QGridLayout* timingsLayout = new QGridLayout(timingsGroup);

    timingsLayout->addWidget(new QLabel("Зеленый:"), 0, 0);
    spinGreen = new QSpinBox();
    spinGreen->setRange(1000, 30000);
    spinGreen->setValue(5000);
    spinGreen->setSingleStep(500);
    timingsLayout->addWidget(spinGreen, 0, 1);

    timingsLayout->addWidget(new QLabel("Желтый:"), 1, 0);
    spinYellow = new QSpinBox();
    spinYellow->setRange(500, 5000);
    spinYellow->setValue(2000);
    spinYellow->setSingleStep(500);
    timingsLayout->addWidget(spinYellow, 1, 1);

    btnApplyTimings = new QPushButton("Установить");
    timingsLayout->addWidget(btnApplyTimings, 2, 0, 1, 2);

    connect(btnApplyTimings, SIGNAL(clicked()), this, SLOT(onApplyTimings()));

    // === Группа ручного управления ===
    manualGroup = new QGroupBox("Ручное управление — только в ручном режиме");
    QGridLayout* manualLayout = new QGridLayout(manualGroup);

    manualLayout->addWidget(new QLabel("Север-Юг:"), 0, 0);
    comboNS = new QComboBox();
    comboNS->addItem("Красный", LIGHT_RED);
    comboNS->addItem("Желтый", LIGHT_YELLOW);
    comboNS->addItem("Зеленый", LIGHT_GREEN);
    manualLayout->addWidget(comboNS, 0, 1);

    manualLayout->addWidget(new QLabel("Восток-Запад:"), 1, 0);
    comboEW = new QComboBox();
    comboEW->addItem("Красный", LIGHT_RED);
    comboEW->addItem("Желтый", LIGHT_YELLOW);
    comboEW->addItem("Зеленый", LIGHT_GREEN);
    manualLayout->addWidget(comboEW, 1, 1);

    btnApplyManual = new QPushButton("Применить");
    manualLayout->addWidget(btnApplyManual, 2, 0, 1, 2);

    connect(btnApplyManual, SIGNAL(clicked()), this, SLOT(onApplyManual()));

    // === Группа визуализации перекрёстка ===
    QGroupBox* intersectionGroup = new QGroupBox("Перекрёсток");
    QGridLayout* intersectionLayout = new QGridLayout(intersectionGroup);
    intersectionLayout->setSpacing(10);

    lightNorth = new TrafficLightWidget("С");
    lightSouth = new TrafficLightWidget("Ю");
    lightEast = new TrafficLightWidget("В");
    lightWest = new TrafficLightWidget("З");

    QLabel* crossLabel = new QLabel("╋");
    crossLabel->setStyleSheet("font-size: 40px; color: #888;");
    crossLabel->setAlignment(Qt::AlignCenter);

    intersectionLayout->addWidget(lightNorth, 0, 1, Qt::AlignCenter);
    intersectionLayout->addWidget(lightWest, 1, 0, Qt::AlignCenter);
    intersectionLayout->addWidget(crossLabel, 1, 1, Qt::AlignCenter);
    intersectionLayout->addWidget(lightEast, 1, 2, Qt::AlignCenter);
    intersectionLayout->addWidget(lightSouth, 2, 1, Qt::AlignCenter);

    // Добавляем все группы в основной layout
    mainLayout->addWidget(panelGroup);
    mainLayout->addWidget(modeGroup);
    mainLayout->addWidget(timingsGroup);
    mainLayout->addWidget(manualGroup);
    mainLayout->addWidget(intersectionGroup);
    mainLayout->addStretch();
}

void TInterface::updateControlsState()
{
    // Кнопки включения/выключения
    btnTurnOn->setEnabled(currentPanelState == PANEL_OFF);
    btnTurnOff->setEnabled(currentPanelState != PANEL_OFF);

    // Кнопки режимов — доступны только если пульт включен
    bool panelOn = (currentPanelState != PANEL_OFF);
    btnAutonomous->setEnabled(panelOn);
    btnManual->setEnabled(panelOn);
    btnAuto->setEnabled(panelOn);

    // Настройка времени — только в автоматическом режиме
    bool isAuto = (currentPanelState == PANEL_AUTO);
    timingsGroup->setEnabled(isAuto);
    spinGreen->setEnabled(isAuto);
    spinYellow->setEnabled(isAuto);
    btnApplyTimings->setEnabled(isAuto);

    // Ручное управление — только в ручном режиме
    bool isManual = (currentPanelState == PANEL_MANUAL);
    manualGroup->setEnabled(isManual);
    comboNS->setEnabled(isManual);
    comboEW->setEnabled(isManual);
    btnApplyManual->setEnabled(isManual);
}

void TInterface::updateStatus(int panelState, const QString& status)
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

    // Обновляем доступность элементов управления
    updateControlsState();

    // Парсинг статуса для обновления светофоров
    QStringList lines = status.split('\n', Qt::SkipEmptyParts);
    for (const QString& line : lines) {
        LightState state = LIGHT_OFF;
        if (line.contains("Красный")) state = LIGHT_RED;
        else if (line.contains("Мигающий желтый") || line.contains("Желтый")) state = LIGHT_YELLOW;
        else if (line.contains("Зеленый")) state = LIGHT_GREEN;

        if (line.contains("Северный")) lightNorth->setState(state);
        else if (line.contains("Южный")) lightSouth->setState(state);
        else if (line.contains("Восточный")) lightEast->setState(state);
        else if (line.contains("Западный")) lightWest->setState(state);
    }
}

void TInterface::showError(const QString& error)
{
    QMessageBox::warning(this, "Ошибка", error);
}

void TInterface::onTurnOn() {
    QString msg;
    msg << QString::number(MSG_TURN_ON_PANEL);
    emit request(msg);
}

void TInterface::onTurnOff() {
    QString msg;
    msg << QString::number(MSG_TURN_OFF_PANEL);
    emit request(msg);
}

void TInterface::onSetAutonomous() {
    QString msg;
    msg << QString::number(MSG_SET_AUTONOMOUS);
    emit request(msg);
}

void TInterface::onSetManual() {
    QString msg;
    msg << QString::number(MSG_SET_MANUAL);
    emit request(msg);
}

void TInterface::onSetAuto() {
    QString msg;
    msg << QString::number(MSG_SET_AUTO);
    emit request(msg);
}

void TInterface::onApplyManual() {
    QString msg;
    msg << QString::number(MSG_MANUAL_SET_STATE)
        << QString::number(comboNS->currentData().toInt())
        << QString::number(comboEW->currentData().toInt());
    emit request(msg);
}

void TInterface::onApplyTimings() {
    QString msg;
    msg << QString::number(MSG_SET_TIMINGS)
        << QString::number(spinGreen->value())
        << QString::number(spinYellow->value());
    emit request(msg);
}
