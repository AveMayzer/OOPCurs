#include "parameterswindow.h"

ParametersWindow::ParametersWindow(QWidget* parent)
    : QWidget(parent),
    currentPanelState(PANEL_OFF)
{
    setupUI();
    updateControlsState();
}

ParametersWindow::~ParametersWindow(){

}
void ParametersWindow::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QGroupBox* infoGroup = new QGroupBox("Текущие параметры");
    QVBoxLayout* infoLayout = new QVBoxLayout(infoGroup);
    lblCurrentParams = new QLabel("Зеленый: 5000 мс\nЖелтый: 2000 мс\nКрасный: 5000 мс");
    lblCurrentParams->setStyleSheet("font-size: 14px;");
    infoLayout->addWidget(lblCurrentParams);

    timingsGroup = new QGroupBox("Настройка времени (мс)");
    QGridLayout* timingsLayout = new QGridLayout(timingsGroup);

    timingsLayout->addWidget(new QLabel("Время зелёного сигнала:"), 0, 0);
    spinGreen = new QSpinBox();
    spinGreen->setRange(1000, 30000);
    spinGreen->setValue(5000);
    spinGreen->setSingleStep(500);
    spinGreen->setSuffix(" мс");
    timingsLayout->addWidget(spinGreen, 0, 1);

    timingsLayout->addWidget(new QLabel("Время жёлтого сигнала:"), 1, 0);
    spinYellow = new QSpinBox();
    spinYellow->setRange(500, 5000);
    spinYellow->setValue(2000);
    spinYellow->setSingleStep(500);
    spinYellow->setSuffix(" мс");
    timingsLayout->addWidget(spinYellow, 1, 1);

    timingsLayout->addWidget(new QLabel("Время красного сигнала:"), 2, 0);
    spinRed = new QSpinBox();
    spinRed->setRange(1000, 30000);
    spinRed->setValue(5000);
    spinRed->setSingleStep(500);
    spinRed->setSuffix(" мс");
    timingsLayout->addWidget(spinRed, 2, 1);

    btnApplyTimings = new QPushButton("Применить параметры");
    timingsLayout->addWidget(btnApplyTimings, 3, 0, 1, 2);

    connect(btnApplyTimings, SIGNAL(clicked()), this, SLOT(onApplyTimings()));

    QLabel* lblHint = new QLabel("Параметры времени доступны только в автоматическом режиме");
    lblHint->setStyleSheet("color: gray; font-style: italic;");
    lblHint->setWordWrap(true);

    mainLayout->addWidget(infoGroup);
    mainLayout->addWidget(timingsGroup);
    mainLayout->addWidget(lblHint);
    mainLayout->addStretch();
}

void ParametersWindow::updateControlsState()
{
    bool isAuto = (currentPanelState == PANEL_AUTO);
    timingsGroup->setEnabled(isAuto);
}

void ParametersWindow::updatePanelState(int panelState)
{
    currentPanelState = panelState;
    updateControlsState();
}

void ParametersWindow::onApplyTimings()
{
    QString msg;
    msg << QString::number(MSG_SET_TIMINGS)
        << QString::number(spinGreen->value())
        << QString::number(spinYellow->value())
        << QString::number(spinRed->value());
    emit request(msg);

    lblCurrentParams->setText(QString("Зеленый: %1 мс\nЖелтый: %2 мс\nКрасный: %3 мс")
                                  .arg(spinGreen->value())
                                  .arg(spinYellow->value())
                                  .arg(spinRed->value()));
}
