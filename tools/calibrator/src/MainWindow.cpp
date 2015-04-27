#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <glog/logging.h> 
#include "lusb.h"


MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, d_ui(new Ui::MainWindow) {
    d_ui->setupUi(this);
    
    LOG(INFO) << "Initializing libusb context";
    lusb_call(libusb_init,NULL);

    d_ui->toolButton->setDefaultAction(d_ui->actionSave_in_EEPROM);
    
}

void MainWindow::Close() {
	LOG(INFO) << "Cleaning up application";

	LOG(INFO) << "Cleaning up libusb";
	libusb_exit(NULL);
}

MainWindow::~MainWindow() {
	Close();
    delete d_ui;
}


void MainWindow::on_actionQuit_triggered() {
	this->close();
}


void MainWindow::on_actionRefresh_triggered() {
	LOG(INFO) << "Refreshing list of devices";

	GMKDevice::List list;
	GMKDevice::ListDevices(list);
	//Do Job
	d_ui->statusbar->showMessage(tr("List of device refreshed"));
}
