#include "parameterswindow.h"

ParametersWindow::ParametersWindow(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

void ParametersWindow::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QGroupBox* modeGroup = new QGroupBox("Текущий режим работы");
    QVBoxLayout* modeLayout = new QVBoxLayout(modeGroup);

    lblMode = new QLabel("Режим: Выключен");
    lblMode->setStyleSheet("font-size: 18px; font-weight: bold;");
    modeLayout->addWidget(lblMode);

    QGroupBox* timingsGroup = new QGroupBox("Параметры времени сигналов");
    QVBoxLayout* timingsLayout = new QVBoxLayout(timingsGroup);

    lblGreenTime = new QLabel("Время зелёного сигнала: 5000 мс");
    lblGreenTime->setStyleSheet("font-size: 14px;");
    timingsLayout->addWidget(lblGreenTime);

    lblYellowTime = new QLabel("Время жёлтого сигнала: 2000 мс");
    lblYellowTime->setStyleSheet("font-size: 14px;");
    timingsLayout->addWidget(lblYellowTime);

    QLabel* lblHint = new QLabel("Параметры управляются с пульта");
    lblHint->setStyleSheet("color: gray; font-style: italic;");

    mainLayout->addWidget(modeGroup);
    mainLayout->addWidget(timingsGroup);
    mainLayout->addWidget(lblHint);
    mainLayout->addStretch();
}

void ParametersWindow::updateTimings(int greenTime, int yellowTime)
{
    lblGreenTime->setText(QString("Время зелёного сигнала: %1 мс").arg(greenTime));
    lblYellowTime->setText(QString("Время жёлтого сигнала: %1 мс").arg(yellowTime));
}

void ParametersWindow::updateMode(int panelState)
{
    QString modeStr;
    switch (panelState) {
    case PANEL_OFF:        modeStr = "Выключен"; break;
    case PANEL_AUTONOMOUS: modeStr = "Автономный"; break;
    case PANEL_MANUAL:     modeStr = "Ручной"; break;
    case PANEL_AUTO:       modeStr = "Автоматический"; break;
    default:               modeStr = "Неизвестно"; break;
    }
    lblMode->setText(QString("Режим: %1").arg(modeStr));
}
