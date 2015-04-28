#include "Oscilloscope.h"
#include "ui_Oscilloscope.h"

#include <stdexcept>

#include <QPen>

#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"


#include <glog/logging.h>

Oscilloscope::Oscilloscope(QWidget *parent) 
	: QWidget(parent)
	, d_ui(new Ui::Oscilloscope) 
	, d_grid(new QwtPlotGrid())
	, d_curve(new QwtPlotCurve("value")) {

	d_ui->setupUi(this);

	
	d_grid->setPen(QPen(Qt::gray,1,Qt::DotLine));
	d_grid->attach(d_ui->plot);

	d_curve->attach(d_ui->plot);

	d_ui->plot->setAxisTitle(QwtPlot::xBottom,"time (s)");
	
	d_ui->plot->setAxisScale(QwtPlot::xBottom,0,d_ui->timeEntry->value());
	d_ui->plot->setAxisScale(QwtPlot::yLeft,d_ui->minEntry->value(),d_ui->maxEntry->value());

	LOG(INFO) << "X Autoscale :" << (d_ui->plot->axisAutoScale(QwtPlot::xBottom) ? "yes" : "no")
	          << " X ScaleEngine :" << d_ui->plot->axisScaleEngine(QwtPlot::xBottom)
	          << " Y ScaleEngine :" << d_ui->plot->axisScaleEngine(QwtPlot::yLeft);


	d_ui->minEntry->setMaximum(d_ui->maxEntry->value() - d_ui->minEntry->singleStep());
	d_ui->maxEntry->setMinimum(d_ui->minEntry->value() + d_ui->maxEntry->singleStep());

	

}

Oscilloscope::~Oscilloscope() {
    delete d_ui;
    delete d_grid;
}

void Oscilloscope::setData(const double * x, const double * y, size_t size) {
	if (size == 0 || x == NULL || y == NULL) {
		d_xData.clear();
		d_yData.clear();
		d_ui->plot->setAxisScale(QwtPlot::xBottom,0,d_ui->timeEntry->value());
		d_curve->setRawSamples(NULL,NULL,0);
		d_ui->plot->replot();
		return;
	}

	d_xData.reserve(size * 2);
	d_yData.reserve(size * 2);

	//check growing xData;
	for (size_t i = 0; i < size; ++i ) {
		if (i > 0 && x[i - 1] >= x[i]) {
			throw std::domain_error("XData should be growing");
		}
		d_xData.push_back(x[i]);
		d_yData.push_back(y[i]);
	}
	d_startIdx = 0;
	ComputeXAxisScale();

	d_curve->setRawSamples(&(d_xData[d_startIdx]),
	                       &(d_yData[d_startIdx]),
	                       d_xData.size() - d_startIdx);

	SetXAxisScale();

	d_ui->plot->replot();
}

void Oscilloscope::ComputeXAxisScale() {
	double maxTime = d_ui->timeEntry->value();
	//now we check the new start index 
	while(d_startIdx < d_xData.size() - 1) {
		double spent = d_xData.back() - d_xData[d_startIdx + 1];
		if ( spent <= maxTime) {
			break;
		}
		++d_startIdx;
	}
	
	//check if we should reshape the data
	if ( d_startIdx > (d_xData.size() / 2) ) {
		//simply copy end of vector at the beginning;
		d_xData.assign(d_xData.begin() + d_startIdx, d_xData.end());
		d_yData.assign(d_yData.begin() + d_startIdx, d_yData.end());
		d_startIdx = 0;
	}

}

void Oscilloscope::SetXAxisScale() {
	double timeEntry = d_ui->timeEntry->value();
	double startX = d_xData.back() - std::fmod(d_xData.back(),timeEntry);
	d_ui->plot->setAxisScale(QwtPlot::xBottom,
	                         startX,
	                         startX + timeEntry);
}

void Oscilloscope::addDatum(double x, double y) {
	if ( d_xData.size() == 0 ){
		d_xData.push_back(x);
		d_yData.push_back(y);	  
		d_startIdx = 0;
		return;
	}
	
	if ( x <= d_xData.back() ) {
		throw std::domain_error("Data should be X growing !");
	}

	d_xData.push_back(x);
	d_yData.push_back(y);	  

	ComputeXAxisScale();

	d_curve->setRawSamples(&(d_xData[d_startIdx]),
	                       &(d_yData[d_startIdx]),
	                       d_xData.size() - d_startIdx);
	
	SetXAxisScale();

	d_ui->plot->replot();

}


void Oscilloscope::on_timeEntry_valueChanged(double v) {
	if(d_xData.empty()) {
		d_ui->plot->setAxisScale(QwtPlot::xBottom,0,v);
	} else {
		SetXAxisScale();
	}
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

