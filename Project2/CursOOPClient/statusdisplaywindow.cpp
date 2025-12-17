#include "statusdisplaywindow.h"

StatusDisplayWindow::StatusDisplayWindow(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

StatusDisplayWindow::~StatusDisplayWindow(){

}

void StatusDisplayWindow::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QGroupBox* connectionGroup = new QGroupBox("Связь с перекрёстком");
    QVBoxLayout* connLayout = new QVBoxLayout(connectionGroup);

    lblConnectionStatus = new QLabel("Статус: Ожидание ответа...");
    lblConnectionStatus->setStyleSheet("font-size: 16px; font-weight: bold;");
    connLayout->addWidget(lblConnectionStatus);

    lblCurrentMode = new QLabel("Режим: Не определён");
    lblCurrentMode->setStyleSheet("font-size: 14px;");
    connLayout->addWidget(lblCurrentMode);

    mainLayout->addWidget(connectionGroup);
    mainLayout->addStretch();
}

void StatusDisplayWindow::updateStatus(int panelState, const QString& status)
{
    Q_UNUSED(status);

    lblConnectionStatus->setText("Статус: Подключено");
    lblConnectionStatus->setStyleSheet("font-size: 16px; font-weight: bold; color: green;");

    QString modeStr;
    switch (panelState) {
    case PANEL_OFF:        modeStr = "Выключен"; break;
    case PANEL_AUTONOMOUS: modeStr = "Автономный"; break;
    case PANEL_MANUAL:     modeStr = "Ручной"; break;
    case PANEL_AUTO:       modeStr = "Автоматический"; break;
    default:               modeStr = "Неизвестно"; break;
    }
    lblCurrentMode->setText(QString("Режим: %1").arg(modeStr));
}
