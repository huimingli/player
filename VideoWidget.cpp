#include "VideoWidget.h"
#include<qpainter.h>
#include<XFFmpeg.h>
#include"XVideoThread.h"


VideoWidget::VideoWidget(QWidget *p):QOpenGLWidget(p)
{
	startTimer(20);
	XVideoThread::Get()->start();
}

void VideoWidget::paintEvent(QPaintEvent *e) {
	static QImage *image = NULL;

	//最大化时 改变了大小，申请的空间不够用了
	//需要重新分配空间，因此回收image的空间
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
		uchar * buf = new uchar[width() * height() * 4];//三种颜色一种透明通道，用了四个字节
		image = new QImage(buf,width(),height(),QImage::Format_ARGB32);
	}
	/*AVPacket pkt = XFFmpeg::Get()->Read();
	if (pkt.stream_index != XFFmpeg::Get()->videoStream) {
		av_packet_unref(&pkt);
		return;
	}
	if (pkt.size == 0) {
		return;
	}
	AVFrame *yuv = XFFmpeg::Get()->Decode(&pkt);
	av_packet_unref(&pkt);
	if (yuv == NULL) {
		return;
	}*/
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
}
