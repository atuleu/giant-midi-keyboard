#include "MainWindow.h"

#include <QApplication>

int main(int argc, char ** argv) {
	QApplication application(argc,argv);

	MainWindow main;
	main.show();


	return application.exec();
}
