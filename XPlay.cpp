#include "XPlay.h"
#include"XFFmpeg.h"
#include<qfiledialog.h>
#include<qmessagebox.h>
#include"XAudioPlay.h"
#define PAUSE "QPushButton\
{border-image: url\
(:/XPlay/Resources/pause_normal.png);}"

#define PLAY "QPushButton\
{border-image: url\
(:/XPlay/Resources/play_normal.png);}"
static bool isPressSlider = false;
static bool isPlay = true;
void XPlay::openFile(QString name) {
	if (name.isEmpty()) {
		return;
	}
	this->setWindowTitle(name);
	int totalMs = XFFmpeg::Get()->Open(name.toLocal8Bit());
	if (totalMs <= 0) {
		QMessageBox::information(this, "error", "file open failed");
		return;
	}

	XAudioPlay::Get()->sampleRate = XFFmpeg::Get()->sampleRate;
	XAudioPlay::Get()->channel = XFFmpeg::Get()->channel;
	XAudioPlay::Get()->sampleSize = 16;
	XAudioPlay::Get()->Start();
	char buf[1024] = { 0 };
	int min = (totalMs / 1000) / 60;
	int sec = (totalMs / 1000) % 60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.totalTime->setText(buf);
	isPlay = false;
	play();
}
void XPlay::open() {
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("选择视频文件"));
	openFile(name);
}

void XPlay::resizeEvent(QResizeEvent *e) {
	ui.openGLWidget->resize(size());
	ui.playButton->move(this->width() / 2 + 50,this->height() -80);
	ui.openButton->move(this->width() / 2 - 50, this->height() - 80);
	ui.playLine->move(25, this->height() - 120);
	ui.playLine->resize(this->width() - 50, ui.playLine->height());
	ui.playTime->move(25, ui.playButton->y());
	ui.sp->move(ui.playTime->x() + ui.playTime->width() + 5, ui.playButton->y());
	ui.totalTime->move(ui.sp->x() + ui.sp->width(), ui.playButton->y());
}

void XPlay::play() {
	isPlay = !isPlay;
	XFFmpeg::Get()->isPlay = isPlay;
	if (isPlay) {
		ui.playButton->setStyleSheet(PAUSE);
	}
	else {
		ui.playButton->setStyleSheet(PLAY);
	}
}

void XPlay::sliderPress() {
	isPressSlider = true;
}

void XPlay::sliderRelease() {
	isPressSlider = false;
	float pos = 0;
	pos = (float)ui.playLine->value() / (float)(ui.playLine->maximum() + 1);
	if (XFFmpeg::Get()->Seek(pos)) {
     	printf("seek success");
	}
	else {
		printf("seek failed");
	}
}

void XPlay::timerEvent(QTimerEvent *e) {
	char buf[1024] = { 0 };
	int min = XFFmpeg::Get()->pts / 1000/60;
	int sec = XFFmpeg::Get()->pts / 1000 % 60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playTime->setText(buf);
	if (XFFmpeg::Get()->totalMs > 0) {
		float rate = (float)XFFmpeg::Get()->pts / (float)XFFmpeg::Get()->totalMs;
		if(!isPressSlider)
		    ui.playLine->setValue(rate * 1000);
	
	}
 
}

XPlay::XPlay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	startTimer(40);
	openFile("video.mp4");
}
XPlay::~XPlay()
{
	
}
