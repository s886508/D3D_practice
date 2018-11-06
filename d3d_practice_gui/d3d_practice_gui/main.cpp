#include "d3d_practice_gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	d3d_practice_gui w;
	w.show();
	return a.exec();
}
