#include "VideoWidget.h"
#include<qpainter.h>
#include<XFFmpeg.h>
#include"XVideoThread.h"


VideoWidget::VideoWidget(QWidget *p):QOpenGLWidget(p)
{
	startTimer(20);
	this->videoThread->start();
}

void VideoWidget::paintEvent(QPaintEvent *e) {
	static QImage *image = NULL;

	//���ʱ �ı��˴�С������Ŀռ䲻������
	//��Ҫ���·���ռ䣬��˻���image�Ŀռ�
	static int w = 0;
	static int h = 0;
	if (w != width() || h != height()) {
		if (image) {
		    delete image->bits();
		    delete image;
		    image = NULL;
		}
	}
	if (image == NULL) {
		uchar * buf = new uchar[width() * height() * 4];//������ɫһ��͸��ͨ���������ĸ��ֽ�
		image = new QImage(buf,width(),height(),QImage::Format_ARGB32);
	}
 
	XFFmpeg::Get()->ToRGB((char*)image->bits(), width(), height());

	QPainter painter;
	painter.begin(this);
	painter.drawImage(QPoint(0, 0), *image);
	painter.end();
}

void VideoWidget::timerEvent(QTimerEvent *e) {
	this->update();
}

VideoWidget::~VideoWidget()
{
	delete videoThread;
	videoThread = NULL;
}
