#include "XPlay.h"
#include <QtWidgets/QApplication>
#include"XFFmpeg.h"


//static double r2d(AVRational r) {
//	return r.num == 0 || r.den == 0 ?
//		0. : (double)r.num / (double)r.den;
//}
int main(int argc, char *argv[])
{
	/*if (XFFmpeg::Get()->Open("video.mp4")) {
		printf("open success\n");
	}
	else {
		printf("open failed\n",
			XFFmpeg::Get()->GetError().c_str());
		return -1;
	}
	char *rgb = new char[800 * 600 * 4];
	while (true) {
        AVPacket pkt = XFFmpeg::Get()->Read();
	    if (pkt.size == 0) {
		    break;
	    }
	    printf("pts=%11d\n", pkt.pts);
		printf("ptsend\n");
		if (pkt.stream_index != XFFmpeg::Get()->videoStream) {
			av_packet_unref(&pkt);
			continue;
		}
		AVFrame *yuv = XFFmpeg::Get()->Decode(&pkt);
		if (yuv) {
			printf("[D]");
			XFFmpeg::Get()->ToRGB(yuv, rgb, 800, 600);
		}
		
		av_packet_unref(&pkt);
	}
	delete rgb;
	XFFmpeg::Get()->XFFmpeg::Close();
	*/
	QApplication a(argc, argv);
	XPlay w;
	w.show();
	return a.exec();
}
