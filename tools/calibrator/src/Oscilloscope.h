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

private:
    Ui::Oscilloscope * d_ui;
};


