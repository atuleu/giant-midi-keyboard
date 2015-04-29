#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <sstream>

#include <QTimer>

#include <glog/logging.h> 

#include "lusb.h"
#include "common.h"


MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, d_ui(new Ui::MainWindow) 
	, d_selectorGuard(false) 
	, d_plotTimer(new QTimer(this)) 
	, d_time(0) {

	d_plotTimer->setObjectName("plotTimer");
	d_plotTimer->setSingleShot(false);
	d_plotTimer->setInterval(10);
    d_ui->setupUi(this);
    
    LOG(INFO) << "Initializing libusb context";
    lusb_call(libusb_init,NULL);

    d_ui->toolButton->setDefaultAction(d_ui->actionSave_in_EEPROM);

    LOG(INFO) << "device is not initialized: " << d_device;
    UnselectCell();



}

void MainWindow::Close() {
	LOG(INFO) << "Cleaning up application";

	LOG(INFO) << "Cleaning up libusb";
	libusb_exit(NULL);
}

MainWindow::~MainWindow() {
	CloseDevice();
	Close();
    delete d_ui;
}


void MainWindow::on_actionQuit_triggered() {
	this->close();
}

void MainWindow::on_actionSave_in_EEPROM_triggered() {
	if(!d_device) {
		LOG(WARNING) << "User interface should not let save in EEPROM if no device is opened";
	}

	try {
		d_device->SaveInEEPROM();
	} catch ( const std::exception & e) {
		LOG(ERROR) << "Could not save in EEPROM of device: " << e.what();
		CloseDevice();
		d_ui->statusbar->showMessage(tr("Could not save data in EEPROM, device Closed"));
		d_ui->comboBox->setCurrentIndex(-1);
	}
}


void MainWindow::on_actionRefresh_triggered() {
	LOG(INFO) << "Refreshing list of devices";

	GMKDevice::List list;
	GMKDevice::ListDevices(list);
	d_ui->statusbar->showMessage(tr("List of device refreshed"));
   
	d_selectorGuard = true;
	d_ui->comboBox->clear();
	d_selectorGuard = false;
	d_devicesDescriptors.clear();
	for ( size_t i = 0; i < list.size(); ++i) {
		GMKDevice::Descriptor::Ptr desc = list[i];
		d_devicesDescriptors[desc->BusAndAddress()] = desc;
		std::ostringstream oss;
		oss << *desc << " " << desc->Product();

		d_ui->comboBox->addItem(QString(oss.str().c_str()),QVariant(desc->BusAndAddress()));
		d_selectorGuard = true;
		if (d_device && d_device->BusAndAddress() == desc->BusAndAddress() ) {
			d_selectorGuard = false;
			d_ui->comboBox->setCurrentIndex(i);
			d_selectorGuard = true;
				
		}
	}
	d_selectorGuard = false;

}

void MainWindow::Open(const GMKDevice::Descriptor::Ptr & desc) {
	d_device = GMKDevice::Open(desc);
	d_ui->actionSave_in_EEPROM->setEnabled(true);

	//sets the display widget
	d_ui->tableWidget->setColumnCount(4);
	d_ui->tableWidget->setRowCount(25);

	QString labels[12] = { tr("C"), tr("C#") ,tr("D"), tr("D#") , tr("E"), tr("F") , tr("F#"), tr("G"), tr("G#"), tr("A") , tr("A#"), tr("B") };

	for ( unsigned int i = 0 ; i < 25; ++i ) {
		int labelIdx = i % 12;
		int nb = (i - labelIdx) / 12 + 1;
		d_ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1 %2").arg(labels[labelIdx]).arg(nb)));
		d_ui->tableWidget->setItem(i,1,new QTableWidgetItem("0"));
		d_ui->tableWidget->setItem(i,2,new QTableWidgetItem("0"));
		d_ui->tableWidget->setItem(i,3,new QTableWidgetItem("0"));
	}

	QStringList headers;
	headers << tr("Note") << tr("Value") << tr("Press Count") << tr("Velocity");
	d_ui->tableWidget->setHorizontalHeaderLabels(headers);

	d_plotTimer->start();
	d_selectedCell = -1;
	d_ui->statusbar->showMessage(tr("Opened device at %1:%2")
	                             .arg(desc->BusAndAddress() >> 8)
	                             .arg(desc->BusAndAddress() & 0xff));
}

void MainWindow::CloseDevice() {
	if( !d_device ) {
		return;
	}
	d_ui->actionSave_in_EEPROM->setEnabled(false);
	d_plotTimer->stop();
	// cannot edit cell anymore
	UnselectCell();
	// clear the display widget
	d_ui->tableWidget->setColumnCount(0);
	d_ui->tableWidget->setRowCount(0);
	
	d_ui->statusbar->showMessage(tr("Closed device at %1:%2")
	                             .arg(d_device->BusAndAddress() >> 8)
	                             .arg(d_device->BusAndAddress() & 0xff));
	d_device = GMKDevice::Ptr();

}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
	if ( d_selectorGuard ) {
		return;
	}
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

void MainWindow::on_tableWidget_cellClicked(int row, int col) {
	SelectCell(row);
}


void MainWindow::SelectCell(int index) {
	if ( index >= 25 || index < 0) {
		throw std::out_of_range("Index of cell is out of range");
	}
	
	QString note =  d_ui->tableWidget->item(index,0)->text();
	d_ui->cellBox->setTitle(tr("Cell: %1").arg(note));	
	d_ui->statusbar->showMessage(tr("Selected Cell for %1").arg(note));
	//TODO fetch values 

	d_ui->spinBoxMinimum->setEnabled(true);
	d_ui->spinBoxMaximum->setEnabled(true);
	d_ui->plotWidget->resetData();
	d_ui->plotWidget->setEnabled(true);
	d_selectedCell = index;
	d_timeSync = false;
};


void MainWindow::UnselectCell() {
	d_ui->cellBox->setTitle(tr("Cell: None"));
	d_ui->spinBoxMinimum->setEnabled(false);
	d_ui->spinBoxMaximum->setEnabled(false);
	d_ui->plotWidget->setEnabled(false);
	d_selectedCell = -1;
}


void MainWindow::on_plotTimer_timeout() {
	if(!d_device || d_selectedCell == -1) {
		return;
	}
	CellStatus_t status;
	d_device->FetchCellStatus(d_selectedCell,status);
	//display data in table

	d_ui->tableWidget->item(d_selectedCell,1)->setText(QString::number(status.value));

	if ( d_timeSync == false ) {
		d_time = 0.0;
		d_lastTime = status.systime;
		d_timeSync = true;
	} else {
		d_time += 1e-3 * ( status.systime - d_lastTime);
		d_lastTime = status.systime;
	}
	
	d_ui->plotWidget->addDatum(d_time,status.value);
}
