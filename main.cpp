#include "XPlay.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	 
	///*ad->write*/
	QApplication a(argc, argv);
	XPlay w;
	w.show();
	return a.exec();
}
