#include "MainWindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include <stdexcept>

#include <glog/logging.h>


int main(int argc, char ** argv) {
	FLAGS_logtostderr = true;
	FLAGS_colorlogtostderr = true;

	google::InitGoogleLogging(argv[0]);


	QApplication application(argc,argv);
	application.setOrganizationName("Balelec");
	application.setApplicationName("giant-MIDI-keyboard-calibrator");

	QString locale = QLocale::system().name();
	QTranslator translator;
	LOG(INFO) << "Detected Locale is: " << locale.toUtf8().data();
	translator.load(":/ts/calibrator_" + locale);
	
	application.installTranslator(&translator);
	MainWindow main;
	main.show();
	int retValue = 0;
	try {
		main.on_actionRefresh_triggered();
		retValue = application.exec();
	} catch ( const std::exception & e) {
		LOG(INFO) << "Got unhandled error: " << e.what();
		retValue = 255;
	}

	return retValue;

}
