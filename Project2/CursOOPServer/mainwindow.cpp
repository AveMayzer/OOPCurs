#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("Перекрёсток - Модель");
    setMinimumSize(400, 500);
}

MainWindow::~MainWindow()
{
}
void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    tabWidget = new QTabWidget();

    statusDisplay = new StatusDisplayWindow();
    parametersWindow = new ParametersWindow();

    tabWidget->addTab(statusDisplay, "Состояние");
    tabWidget->addTab(parametersWindow, "Параметры");

    mainLayout->addWidget(tabWidget);
}

void MainWindow::updateStatus(int panelState, const QString& status)
{
    statusDisplay->updateStatus(panelState, status);
    parametersWindow->updateMode(panelState);
}

void MainWindow::updateTimings(int greenTime, int yellowTime)
{
    parametersWindow->updateTimings(greenTime, yellowTime);
}
