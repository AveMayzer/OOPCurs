#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include "../communicator/common.h"

class ParametersWindow : public QWidget
{
    Q_OBJECT

private:
    QGroupBox* timingsGroup;
    QSpinBox* spinGreen;
    QSpinBox* spinYellow;
    QPushButton* btnApplyTimings;
    QLabel* lblCurrentParams;

    int currentPanelState;

    void setupUI();
    void updateControlsState();

public:
    ParametersWindow(QWidget* parent = nullptr);
    void updatePanelState(int panelState);
    ~ParametersWindow();

signals:
    void request(QString msg);

private slots:
    void onApplyTimings();
};

#endif // PARAMETERSWINDOW_H
