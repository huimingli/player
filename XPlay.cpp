#include "XPlay.h"
#include"XFFmpeg.h"
#include<qfiledialog.h>
#include<qmessagebox.h>
void XPlay::open() {
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("选择视频文件"));
	if (name.isEmpty()) {
		return;
	}
	this->setWindowTitle(name);
	int totalMs = XFFmpeg::Get()->Open(name.toLocal8Bit());
	if (totalMs<=0) {
		QMessageBox::information(this, "error", "file open failed");
		return;
	}
	char buf[1024] = { 0 };
	int min = (totalMs / 1000) /60;
	int sec = (totalMs / 1000)%60;
	sprintf(buf, "%d" ,sec);
	ui.totalTime->setText(buf);
	ui.playTime->setText(buf);
}
XPlay::XPlay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
