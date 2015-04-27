#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
	void on_actionQuit_triggered();
	void on_actionRefresh_triggered();
private:
	void Close();

    Ui::MainWindow * d_ui;
};

#endif // MAINWINDOW_H
