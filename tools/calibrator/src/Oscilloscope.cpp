#include "Oscilloscope.h"
#include "ui_Oscilloscope.h"

Oscilloscope::Oscilloscope(QWidget *parent) 
	: QWidget(parent)
	, d_ui(new Ui::Oscilloscope) {
	d_ui->setupUi(this);
}

Oscilloscope::~Oscilloscope() {
    delete d_ui;
}




