#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include "../communicator/common.h"

class ParametersWindow : public QWidget
{
    Q_OBJECT

private:
    QLabel* lblGreenTime;
    QLabel* lblYellowTime;
    QLabel* lblRedTime;
    QLabel* lblMode;

    void setupUI();

public:
    ParametersWindow(QWidget* parent = nullptr);
    ~ParametersWindow();
    void updateTimings(int greenTime, int yellowTime, int redTime);
    void updateMode(int panelState);
};

#endif // PARAMETERSWINDOW_H
