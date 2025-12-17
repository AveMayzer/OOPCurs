#include "intersectioninterface.h"

// === TrafficLightWidget ===

TrafficLightWidget::TrafficLightWidget(const QString& title, QWidget* parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(2);
    setFixedSize(70, 160);
    setStyleSheet("background-color: #333; border: 2px solid #555; border-radius: 5px;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);

    titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white; font-size: 12px; font-weight: bold; background: transparent; border: none;");

    redLight = new QLabel();
    yellowLight = new QLabel();
    greenLight = new QLabel();

    QString lightOffStyle = "background-color: #444; border-radius: 17px; border: 1px solid #222;";

    redLight->setFixedSize(35, 35);
    yellowLight->setFixedSize(35, 35);
    greenLight->setFixedSize(35, 35);

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
    QString offStyle = "background-color: #444; border-radius: 17px; border: 1px solid #222;";
    QString redOn = "background-color: #ff0000; border-radius: 17px; border: 2px solid #cc0000;";
    QString yellowOn = "background-color: #ffaa00; border-radius: 17px; border: 2px solid #cc8800;";
    QString greenOn = "background-color: #00ff00; border-radius: 17px; border: 2px solid #00cc00;";

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

// === IntersectionInterface ===

IntersectionInterface::IntersectionInterface(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    setWindowTitle("Перекрёсток");
    setMinimumSize(350, 450);
}

void IntersectionInterface::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QGroupBox* statusGroup = new QGroupBox("Состояние системы");
    QVBoxLayout* statusLayout = new QVBoxLayout(statusGroup);
    lblStatus = new QLabel("Ожидание команд от пульта...");
    lblStatus->setStyleSheet("font-size: 16px; font-weight: bold;");
    lblStatus->setAlignment(Qt::AlignCenter);
    statusLayout->addWidget(lblStatus);

    QGroupBox* intersectionGroup = new QGroupBox("Светофоры на перекрёстке");
    QGridLayout* gridLayout = new QGridLayout(intersectionGroup);
    gridLayout->setSpacing(15);

    lightNorth = new TrafficLightWidget("Север");
    lightSouth = new TrafficLightWidget("Юг");
    lightEast = new TrafficLightWidget("Восток");
    lightWest = new TrafficLightWidget("Запад");

    QLabel* crossLabel = new QLabel("╋");
    crossLabel->setStyleSheet("font-size: 50px; color: #555;");
    crossLabel->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(lightNorth, 0, 1, Qt::AlignCenter);
    gridLayout->addWidget(lightWest, 1, 0, Qt::AlignCenter);
    gridLayout->addWidget(crossLabel, 1, 1, Qt::AlignCenter);
    gridLayout->addWidget(lightEast, 1, 2, Qt::AlignCenter);
    gridLayout->addWidget(lightSouth, 2, 1, Qt::AlignCenter);

    mainLayout->addWidget(statusGroup);
    mainLayout->addWidget(intersectionGroup);
    mainLayout->addStretch();
}

void IntersectionInterface::updateStatus(int panelState, const QString& status)
{
    QString stateStr;
    switch (panelState) {
    case PANEL_OFF:        stateStr = "Пульт выключен"; break;
    case PANEL_AUTONOMOUS: stateStr = "Автономный режим"; break;
    case PANEL_MANUAL:     stateStr = "Ручное управление"; break;
    case PANEL_AUTO:       stateStr = "Автоматический режим"; break;
    }
    lblStatus->setText(stateStr);

    QStringList lines = status.split('\n', Qt::SkipEmptyParts);
    for (const QString& line : lines) {
        LightState state = LIGHT_OFF;
        if (line.contains("Красный")) state = LIGHT_RED;
        else if (line.contains("Желтый")) state = LIGHT_YELLOW;
        else if (line.contains("Зеленый")) state = LIGHT_GREEN;

        if (line.contains("Северный")) lightNorth->setState(state);
        else if (line.contains("Южный")) lightSouth->setState(state);
        else if (line.contains("Восточный")) lightEast->setState(state);
        else if (line.contains("Западный")) lightWest->setState(state);
    }
}
