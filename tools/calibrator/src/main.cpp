#include "MainWindow.h"

#include <QApplication>

#include <glog/logging.h>

int main(int argc, char ** argv) {
	FLAGS_logtostderr = true;
	FLAGS_colorlogtostderr = true;

	google::InitGoogleLogging(argv[0]);


	QApplication application(argc,argv);

	MainWindow main;
	main.show();


	return application.exec();
}
