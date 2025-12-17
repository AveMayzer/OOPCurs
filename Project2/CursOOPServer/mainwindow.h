#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "statusdisplaywindow.h"
#include "parameterswindow.h"
#include "../communicator/common.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTabWidget* tabWidget;
    StatusDisplayWindow* statusDisplay;
    ParametersWindow* parametersWindow;

    void setupUI();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void updateStatus(int panelState, const QString& status);
    void updateTimings(int greenTime, int yellowTime);
};

#endif // MAINWINDOW_H
