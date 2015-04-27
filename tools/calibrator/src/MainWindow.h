#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>

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
	void on_comboBox_currentIndexChanged(int index);

private:
	void Open(const GMKDevice::Descriptor::Ptr &);
	void CloseDevice();
	void Close();
	
	typedef std::map<uint16_t,GMKDevice::Descriptor::Ptr> DevicesByBusAddress;

    Ui::MainWindow * d_ui;

	GMKDevice::Ptr d_device;
	DevicesByBusAddress d_devicesDescriptors;
};

#endif // MAINWINDOW_H
