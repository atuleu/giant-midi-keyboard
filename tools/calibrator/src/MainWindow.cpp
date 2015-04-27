#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <sstream>

#include <glog/logging.h> 

#include "lusb.h"
#include "common.h"


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
   

	d_ui->comboBox->clear();
	d_devicesDescriptors.clear();
	for ( size_t i = 0; i < list.size(); ++i) {
		GMKDevice::Descriptor::Ptr desc = list[i];
		d_devicesDescriptors[desc->BusAndAddress()] = desc;
		std::ostringstream oss;
		oss << *desc << " " << desc->Product();

		d_ui->comboBox->addItem(QString(oss.str().c_str()),QVariant(desc->BusAndAddress()));

		if ( d_device && d_device->BusAndAddress() == desc->BusAndAddress() ) {
			d_ui->comboBox->setCurrentIndex(i);
		}
	}

	//Do Job
	d_ui->statusbar->showMessage(tr("List of device refreshed"));

	if ( d_device ) {
		return;
	}

	if( d_ui->comboBox->count() == 0) {
		return;
	}

	d_ui->comboBox->setCurrentIndex(0);
}


void MainWindow::Open(const GMKDevice::Descriptor::Ptr & desc) {
	throw_nyi();
}

void MainWindow::CloseDevice() {
	if( !d_device ) {
		return;
	}
	throw_nyi();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
	if (index < 0 ) {
		CloseDevice();
		return;
	}
	

	uint16_t busAndAddress = d_ui->comboBox->itemData(index).toInt();
	if ( d_device ) {
		if ( d_device->BusAndAddress() == busAndAddress) {
			return;
		}
		CloseDevice();
	}

	auto fi = d_devicesDescriptors.find(busAndAddress);
	if ( fi == d_devicesDescriptors.end() ) {
		std::ostringstream oss;
		oss << "Internal error: invalid bus and address " 
		    << std::dec << (busAndAddress >> 8)
		    << ":" << (busAndAddress && 0xff);
		throw std::out_of_range(oss.str());
	}
	
	Open(fi->second);

}
