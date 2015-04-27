#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, d_ui(new Ui::MainWindow) {
    d_ui->setupUi(this);
    
    d_ui->toolButton->setDefaultAction(d_ui->actionSave_in_EEPROM);



    
}

MainWindow::~MainWindow() {
    delete d_ui;
}


void MainWindow::on_actionQuit_triggered() {
	this->close();
}
