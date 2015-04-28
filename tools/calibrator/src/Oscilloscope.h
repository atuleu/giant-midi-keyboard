#pragma once

#include <QWidget>

class QwtPlotGrid;

namespace Ui {
	class Oscilloscope;
}

class Oscilloscope : public QWidget {
    Q_OBJECT
public:
    explicit Oscilloscope(QWidget *parent = 0);
    virtual ~Oscilloscope();

public slots :
	void addData(double x, double y);
	void setData(const double * x, const double * y, size_t size);

	void on_timeEntry_valueChanged(double v);
	void on_minEntry_valueChanged(int v);
	void on_maxEntry_valueChanged(int v);

private:

    Ui::Oscilloscope * d_ui;
	QwtPlotGrid      * d_grid;
};


