#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <glog/logging.h> 

MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, d_ui(new Ui::MainWindow) {
    d_ui->setupUi(this);
    
    d_ui->toolButton->setDefaultAction(d_ui->actionSave_in_EEPROM);


    on_actionRefresh_triggered();
    
}

void MainWindow::Close() {
	LOG(INFO) << "Cleaning up application";
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
	
	//Do Job

	d_ui->statusbar->showMessage(tr("List of device refreshed"));
}
