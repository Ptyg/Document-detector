#include "App.h"

#include <QByteArray>
#include <QString>
#include <QtWidgets/QApplication>

#include <opencv2/opencv.hpp>

int main(int argc, char* argv[])
{
	qputenv("QT_SCALE_FACTOR", QByteArray("1"));
	QApplication a(argc, argv);
	App w;
	w.show();
	return a.exec();
}