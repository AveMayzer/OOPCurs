#include "intersection.h"

Intersection::Intersection(QObject* parent)
    : QObject(parent),
    panelState(PANEL_OFF),
    greenTime(5000),
    yellowTime(2000),
    redTime(5000),
    currentPhase(0),
    blinkState(false)
{
    for (int i = 0; i < 4; i++) {
        lights[i] = LIGHT_OFF;
    }

    autoTimer = new QTimer(this);
    blinkTimer = new QTimer(this);

    connect(autoTimer, SIGNAL(timeout()), this, SLOT(onAutoTimerTick()));
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(onBlinkTimerTick()));
}

Intersection::~Intersection()
{
    autoTimer->stop();
    blinkTimer->stop();
}

void Intersection::setDirectionState(Direction dir, LightState state)
{
    if (dir == DIRECTION_NORTH_SOUTH) {
        lights[0] = state;
        lights[1] = state;
    } else {
        lights[2] = state;
        lights[3] = state;
    }
}

void Intersection::turnOn()
{
    if (panelState == PANEL_OFF) {
        setAutonomous();
    }
}

void Intersection::turnOff()
{
    autoTimer->stop();
    blinkTimer->stop();
    panelState = PANEL_OFF;

    for (int i = 0; i < 4; i++) {
        lights[i] = LIGHT_OFF;
    }

    emit statusChanged(getStatusString());
}

void Intersection::setAutonomous()
{
    autoTimer->stop();
    blinkTimer->stop();

    panelState = PANEL_AUTONOMOUS;
    blinkState = true;

    for (int i = 0; i < 4; i++) {
        lights[i] = LIGHT_YELLOW;
    }

    blinkTimer->start(500);
    emit statusChanged(getStatusString());
}

void Intersection::setManual()
{
    autoTimer->stop();
    blinkTimer->stop();

    panelState = PANEL_MANUAL;

    setDirectionState(DIRECTION_NORTH_SOUTH, LIGHT_YELLOW);
    setDirectionState(DIRECTION_EAST_WEST, LIGHT_YELLOW);

    emit statusChanged(getStatusString());
}

void Intersection::setAutomatic()
{
    blinkTimer->stop();

    panelState = PANEL_AUTO;
    currentPhase = 0;

    setDirectionState(DIRECTION_NORTH_SOUTH, LIGHT_GREEN);
    setDirectionState(DIRECTION_EAST_WEST, LIGHT_RED);

    autoTimer->start(greenTime);
    emit statusChanged(getStatusString());
}

void Intersection::setManualState(LightState nsState, LightState ewState)
{
    if (panelState != PANEL_MANUAL) return;

    setDirectionState(DIRECTION_NORTH_SOUTH, nsState);
    setDirectionState(DIRECTION_EAST_WEST, ewState);

    emit statusChanged(getStatusString());
}

void Intersection::setTimings(int green, int yellow, int red)
{
    greenTime = green;
    yellowTime = yellow;
    redTime = red;
}

void Intersection::onAutoTimerTick()
{
    currentPhase = (currentPhase + 1) % 6;

    switch (currentPhase) {
    case 0:
        // Север-Юг: Зелёный, Восток-Запад: Красный
        setDirectionState(DIRECTION_NORTH_SOUTH, LIGHT_GREEN);
        setDirectionState(DIRECTION_EAST_WEST, LIGHT_RED);
        autoTimer->setInterval(redTime);  // Время красного для Восток-Запад
        break;
    case 1:
        // Север-Юг: Жёлтый, Восток-Запад: Красный
        setDirectionState(DIRECTION_NORTH_SOUTH, LIGHT_YELLOW);
        autoTimer->setInterval(yellowTime);
        break;
    case 2:
        // Север-Юг: Красный, Восток-Запад: Жёлтый (переход к зелёному)
        setDirectionState(DIRECTION_NORTH_SOUTH, LIGHT_RED);
        setDirectionState(DIRECTION_EAST_WEST, LIGHT_YELLOW);
        autoTimer->setInterval(yellowTime);
        break;
    case 3:
        // Север-Юг: Красный, Восток-Запад: Зелёный
        setDirectionState(DIRECTION_EAST_WEST, LIGHT_GREEN);
        autoTimer->setInterval(redTime);  // Время красного для Север-Юг
        break;
    case 4:
        // Север-Юг: Красный, Восток-Запад: Жёлтый
        setDirectionState(DIRECTION_EAST_WEST, LIGHT_YELLOW);
        autoTimer->setInterval(yellowTime);
        break;
    case 5:
        // Север-Юг: Жёлтый (переход к зелёному), Восток-Запад: Красный
        setDirectionState(DIRECTION_NORTH_SOUTH, LIGHT_YELLOW);
        setDirectionState(DIRECTION_EAST_WEST, LIGHT_RED);
        autoTimer->setInterval(yellowTime);
        break;
    }

    emit statusChanged(getStatusString());
}

void Intersection::onBlinkTimerTick()
{
    blinkState = !blinkState;
    LightState state = blinkState ? LIGHT_YELLOW : LIGHT_OFF;

    for (int i = 0; i < 4; i++) {
        lights[i] = state;
    }

    emit statusChanged(getStatusString());
}

PanelState Intersection::getPanelState() const
{
    return panelState;
}

QString Intersection::getStatusString() const
{
    static const char* positions[] = {"Северный", "Южный", "Восточный", "Западный"};
    static const char* states[] = {"Выключен", "Красный", "Желтый", "Зеленый", "Желтый"};

    QString status;
    for (int i = 0; i < 4; i++) {
        status += QString("Светофор %1 (%2): %3\n")
                      .arg(i)
                      .arg(positions[i])
                      .arg(states[lights[i]]);
    }
    return status;
}

void Intersection::setIndividualState(LightState north, LightState south, LightState east, LightState west)
{
    if (panelState != PANEL_MANUAL) return;

    lights[0] = north;
    lights[1] = south;
    lights[2] = east;
    lights[3] = west;

    emit statusChanged(getStatusString());
}
