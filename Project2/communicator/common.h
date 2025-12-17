#pragma once

#ifndef COMMON_H
#define COMMON_H

#include <QString>

const QChar separator(';');

QString& operator<< (QString& m, const QString& s);

// Состояния пульта управления
enum PanelState {
    PANEL_OFF = 0,
    PANEL_AUTONOMOUS = 1,
    PANEL_MANUAL = 2,
    PANEL_AUTO = 3
};

// Состояния светофора
enum LightState {
    LIGHT_OFF = 0,
    LIGHT_RED = 1,
    LIGHT_YELLOW = 2,
    LIGHT_GREEN = 3,
    LIGHT_YELLOW_BLINK = 4
};

// Типы сообщений
enum Messages {
    MSG_TURN_ON_PANEL,
    MSG_TURN_OFF_PANEL,
    MSG_SET_AUTONOMOUS,
    MSG_SET_MANUAL,
    MSG_SET_AUTO,
    MSG_MANUAL_SET_STATE,           // По направлениям (Север-Юг, Восток-Запад)
    MSG_MANUAL_SET_INDIVIDUAL,      // По каждому светофору отдельно
    MSG_SET_TIMINGS,
    MSG_GET_STATUS,

    MSG_STATUS_UPDATE,
    MSG_PANEL_STATE_CHANGED,
    MSG_ERROR
};

// Направления движения
enum Direction {
    DIRECTION_NORTH_SOUTH = 0,
    DIRECTION_EAST_WEST = 1
};

#endif // COMMON_H
