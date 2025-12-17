#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "eventcontrolwindow.h"
#include "parameterswindow.h"
#include "statusdisplaywindow.h"
#include "../communicator/common.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTabWidget* tabWidget;
    EventControlWindow* eventControl;
    ParametersWindow* parameters;
    StatusDisplayWindow* statusDisplay;

    void setupUI();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void updateStatus(int panelState, const QString& status);
    void showError(const QString& error);

signals:
    void request(QString msg);
};

#endif // MAINWINDOW_H
