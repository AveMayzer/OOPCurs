#pragma once

#ifndef COMMON_H
#define COMMON_H

#include <QString>

const QChar separator(';');

QString& operator<< (QString& m, const QString& s);

// Состояния пульта управления
enum PanelState {
    PANEL_OFF = 0,          // Пульт выключен
    PANEL_AUTONOMOUS = 1,   // Автономный режим (мигание желтым)
    PANEL_MANUAL = 2,       // Ручное управление
    PANEL_AUTO = 3          // Автоматическое управление
};

// Состояния светофора
enum LightState {
    LIGHT_OFF = 0,          // Выключен
    LIGHT_RED = 1,          // Красный
    LIGHT_YELLOW = 2,       // Желтый
    LIGHT_GREEN = 3,        // Зеленый
    LIGHT_YELLOW_BLINK = 4  // Мигающий желтый
};

// Типы сообщений
enum Messages {
    // Запросы от Пульта
    MSG_TURN_ON_PANEL,           // Включить пульт
    MSG_TURN_OFF_PANEL,          // Выключить пульт
    MSG_SET_AUTONOMOUS,          // Установить автономный режим
    MSG_SET_MANUAL,              // Установить ручной режим
    MSG_SET_AUTO,                // Установить автоматический режим
    MSG_MANUAL_SET_STATE,        // Ручная установка состояния светофоров
    MSG_SET_TIMINGS,             // Установить временные параметры
    MSG_GET_STATUS,              // Запросить текущий статус

    // Ответы от Перекрестка
    MSG_STATUS_UPDATE,           // Обновление статуса светофоров
    MSG_PANEL_STATE_CHANGED,     // Состояние пульта изменилось
    MSG_ERROR                    // Ошибка
};

// Направления движения на перекрестке
enum Direction {
    DIRECTION_NORTH_SOUTH = 0,   // Север-Юг
    DIRECTION_EAST_WEST = 1      // Восток-Запад
};

#endif // COMMON_H
