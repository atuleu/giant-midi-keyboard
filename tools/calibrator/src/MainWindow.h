#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>

#include "GMKDevice.h"

class QTimer;

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
	void on_actionSave_in_EEPROM_triggered();
	void on_comboBox_currentIndexChanged(int index);
	void on_tableWidget_cellClicked(int count, int index);
	void on_plotTimer_timeout();

	void on_spinBoxMinimum_valueChanged( int value);
	void on_spinBoxMaximum_valueChanged( int value);
private:
	void Open(const GMKDevice::Descriptor::Ptr &);
	void CloseDevice();
	void Close();
	
	void SelectCell(int index);
	void UnselectCell();

	typedef std::map<uint16_t,GMKDevice::Descriptor::Ptr> DevicesByBusAddress;

    Ui::MainWindow * d_ui;

	GMKDevice::Ptr d_device;
	DevicesByBusAddress d_devicesDescriptors;
	bool d_selectorGuard;

	QTimer * d_plotTimer;
	double d_time;
	int    d_selectedCell;
	uint16_t d_lastTime;
	bool     d_timeSync;
	double   d_frameRate;
};

#endif // MAINWINDOW_H
