#pragma once

#include <QWidget>
#include <functional>
#include <map>


class QwtPlotGrid;
class QwtPlotCurve;
class QwtSymbol;
namespace Ui {
	class Oscilloscope;
}

class Oscilloscope : public QWidget {
    Q_OBJECT
public:
    explicit Oscilloscope(QWidget *parent = 0);
    virtual ~Oscilloscope();

public slots :
	void addDatum(double x, double y);
	void resetData();

	void on_timeEntry_valueChanged(double v);
	void on_minEntry_valueChanged(int v);
	void on_maxEntry_valueChanged(int v);

private:
	enum State {
		WAITING_TRIGGER_EMPTY = 0,
		TRIGGERED_FILLING = 1,
		WAITING_TRIGGER = 2
	};

	typedef std::function<State()> ProcessFunction;
	typedef std::map<State,ProcessFunction> ProcessByState;

	void ShrinkBuffers();
	void FlushTriggered();

	State ProcessWaitingEmpty();
	State ProcessFilling();
	State ProcessWaiting();
		

    Ui::Oscilloscope * d_ui;
	QwtPlotGrid      * d_grid;
	QwtPlotCurve     * d_curve;
	QwtSymbol        * d_symbol;

	std::vector<double> d_xData,d_yData,d_xDisplayData,d_yDisplayData;
	std::vector<double>::size_type d_startIdx;

	State d_state;
	ProcessByState d_processes;
};


