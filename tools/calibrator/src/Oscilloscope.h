#pragma once

#include <QWidget>

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

private:
    Ui::Oscilloscope * d_ui;
};


