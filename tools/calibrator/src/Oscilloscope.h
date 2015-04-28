#pragma once

#include <QWidget>

class QwtPlotGrid;
class QwtPlotCurve;

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
	void setData(const double * x, const double * y, size_t size);

	void on_timeEntry_valueChanged(double v);
	void on_minEntry_valueChanged(int v);
	void on_maxEntry_valueChanged(int v);

private:

	void SetXAxisScale();

    Ui::Oscilloscope * d_ui;
	QwtPlotGrid      * d_grid;
	QwtPlotCurve     * d_curve;

	std::vector<double> d_xData,d_yData;

	std::vector<double>::size_type d_startIdx;
};


