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
	, d_curve(new QwtPlotCurve("value")) 
	, d_state(WAITING_TRIGGER_EMPTY) {

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


	d_processes[WAITING_TRIGGER_EMPTY] = [this]() -> State {
		return ProcessWaitingEmpty();
	};
	d_processes[TRIGGERED_FILLING] = [this]() -> State {
		return ProcessFilling();
	};
	d_processes[WAITING_TRIGGER] = [this]() -> State {
		return ProcessWaiting();
	};
}

Oscilloscope::~Oscilloscope() {
    delete d_ui;
    delete d_grid;
}


void Oscilloscope::resetData() {
	d_xData.clear();
	d_yData.clear();
	d_startIdx = 0;
	d_xDisplayData.clear();
	d_yDisplayData.clear();
	d_ui->plot->setAxisScale(QwtPlot::xBottom,0,d_ui->timeEntry->value());
	d_curve->setRawSamples(NULL,NULL,0);
	
	d_ui->plot->replot();
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

	auto p = d_processes.find(d_state);
	if ( p == d_processes.end() ) {
		throw std::logic_error("Invalid state machine state");
	}
	
	d_state = p->second();
		
}


void Oscilloscope::on_timeEntry_valueChanged(double v) {
	if(d_xData.empty()) {
		d_ui->plot->setAxisScale(QwtPlot::xBottom,0,v);
	} else {
		
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

void Oscilloscope::ShrinkBuffers() {
	//we only should keep the minimal amount of data
	double maxTime = d_ui->timeEntry->value(); 
	while(d_startIdx < d_xData.size() - 1) {
		double spent = d_xData.back() - d_xData[d_startIdx + 1];
		if (spent <= maxTime) {
			break;
		}

		++d_startIdx;
	}

	if ( d_startIdx > d_xData.size() / 2) {
		d_xData.assign(d_xData.begin() + d_startIdx, d_xData.end());
		d_yData.assign(d_yData.begin() + d_startIdx, d_yData.end());
		d_startIdx = 0;
	}
}

void Oscilloscope::FlushTriggered() {
	double maxTime = d_ui->timeEntry->value() / 2;
	for( std::vector<double>::iterator it = d_xData.begin() + d_startIdx; 
	     it != d_xData.end();
	     ++it ) {
		if ( (d_xData.back() - *it) <= maxTime) {
			d_xDisplayData.assign(it,d_xData.end());
			d_yDisplayData.assign(d_yData.begin() + (it - d_xData.begin()), d_yData.end());
			break;
		}
	}
	d_ui->plot->setAxisScale(QwtPlot::xBottom,
	                         d_xDisplayData[0],
	                         d_xDisplayData[0] + d_ui->timeEntry->value());	                         
	d_curve->setRawSamples(&(d_xDisplayData[0]),
	                       &(d_yDisplayData[0]),
	                       d_xDisplayData.size());
	d_ui->plot->replot();
}

Oscilloscope::State Oscilloscope::ProcessWaitingEmpty() {

	ShrinkBuffers();
	
	if (d_yData.back() >= d_ui->triggerEntry->value()) {
		//we search the first index where we are time / 2
		FlushTriggered();
		return TRIGGERED_FILLING;
	}

	//display current data
	d_ui->plot->setAxisScale(QwtPlot::xBottom,
	                         d_xData[d_startIdx],
	                         d_xData[d_startIdx] + d_ui->timeEntry->value());
	d_curve->setRawSamples(&(d_xData[d_startIdx]),
	                       &(d_yData[d_startIdx]),
	                       d_xData.size() - d_startIdx);

	d_ui->plot->replot();
		

	return WAITING_TRIGGER_EMPTY;
}

Oscilloscope::State Oscilloscope::ProcessWaiting() {
	ShrinkBuffers();

	if (d_yData.back() >= d_ui->triggerEntry->value()) {
		//we search the first index where we are time / 2
		FlushTriggered();
		return TRIGGERED_FILLING;
	}
	
	return WAITING_TRIGGER;
}

Oscilloscope::State Oscilloscope::ProcessFilling() {
	ShrinkBuffers();

	d_xDisplayData.push_back(d_xData.back());
	d_yDisplayData.push_back(d_yData.back());
	d_curve->setRawSamples(&(d_xDisplayData[0]),
	                       &(d_yDisplayData[0]),
	                       d_xDisplayData.size());
	d_ui->plot->replot();

	if ( (d_xDisplayData.back() - d_xDisplayData.front()) >= d_ui->timeEntry->value() ) {
		return WAITING_TRIGGER;
	}

	return TRIGGERED_FILLING;
}
