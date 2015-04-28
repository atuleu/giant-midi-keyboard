#include "Oscilloscope.h"
#include "ui_Oscilloscope.h"

#include "qwt_plot_grid.h"
#include <QPen>

Oscilloscope::Oscilloscope(QWidget *parent) 
	: QWidget(parent)
	, d_ui(new Ui::Oscilloscope) 
	, d_grid(new QwtPlotGrid()) {

	d_ui->setupUi(this);

	
	d_grid->setPen(QPen(Qt::gray,1,Qt::DotLine));
	d_grid->attach(d_ui->plot);

	d_ui->plot->setAxisTitle(QwtPlot::xBottom,"time (s)");
	
	
	d_ui->plot->setAxisScale(QwtPlot::xBottom,0,d_ui->timeEntry->value());
	d_ui->plot->setAxisScale(QwtPlot::yLeft,d_ui->minEntry->value(),d_ui->maxEntry->value());

	d_ui->minEntry->setMaximum(d_ui->maxEntry->value() - d_ui->minEntry->singleStep());
	d_ui->maxEntry->setMinimum(d_ui->minEntry->value() + d_ui->maxEntry->singleStep());

}

Oscilloscope::~Oscilloscope() {
    delete d_ui;
    delete d_grid;
}

void Oscilloscope::setData(const double * x, const double * y, size_t size) {

}

void Oscilloscope::addData(double x, double y) {

}


void Oscilloscope::on_timeEntry_valueChanged(double v) {
	d_ui->plot->setAxisScale(QwtPlot::xBottom,0,v);
	d_ui->plot->replot();
}

void Oscilloscope::on_minEntry_valueChanged(int v) {
	d_ui->maxEntry->setMinimum(v + d_ui->maxEntry->singleStep());
	d_ui->plot->setAxisScale(QwtPlot::yLeft,v,d_ui->maxEntry->value());
	d_ui->plot->replot();
}

void Oscilloscope::on_maxEntry_valueChanged(int v) {
	d_ui->minEntry->setMaximum(v - d_ui->minEntry->singleStep());
	d_ui->plot->setAxisScale(QwtPlot::yLeft,d_ui->minEntry->value(),v);
	d_ui->plot->replot();
}

