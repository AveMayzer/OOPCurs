#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("Пульт управления светофорами");
    setMinimumSize(450, 400);
}

MainWindow::~MainWindow(){

}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    tabWidget = new QTabWidget();

    eventControl = new EventControlWindow();
    parameters = new ParametersWindow();
    statusDisplay = new StatusDisplayWindow();

    tabWidget->addTab(eventControl, "Управление");
    tabWidget->addTab(parameters, "Параметры");
    tabWidget->addTab(statusDisplay, "Статус");

    mainLayout->addWidget(tabWidget);

    connect(eventControl, SIGNAL(request(QString)), this, SIGNAL(request(QString)));
    connect(parameters, SIGNAL(request(QString)), this, SIGNAL(request(QString)));
}

void MainWindow::updateStatus(int panelState, const QString& status)
{
    eventControl->updatePanelState(panelState);
    parameters->updatePanelState(panelState);
    statusDisplay->updateStatus(panelState, status);
}

void MainWindow::showError(const QString& error)
{
    eventControl->showError(error);
}
