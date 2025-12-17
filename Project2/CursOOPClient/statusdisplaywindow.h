#ifndef STATUSDISPLAYWINDOW_H
#define STATUSDISPLAYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include "../communicator/common.h"

class StatusDisplayWindow : public QWidget
{
    Q_OBJECT

private:
    QLabel* lblConnectionStatus;
    QLabel* lblCurrentMode;

    void setupUI();

public:
    StatusDisplayWindow(QWidget* parent = nullptr);
    ~StatusDisplayWindow();
    void updateStatus(int panelState, const QString& status);
};

#endif // STATUSDISPLAYWINDOW_H
