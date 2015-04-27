#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GMKDevice.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void on_actionQuit_triggered();
	void on_actionRefresh_triggered();
private:
	void Close();

    Ui::MainWindow * d_ui;

	GMKDevice::Ptr d_device;
};

#endif // MAINWINDOW_H
