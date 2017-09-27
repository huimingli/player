#include "XVideoThread.h"
#include"XFFmpeg.h"
bool isExit = false;
void XVideoThread::run() {
	while (!isExit) {

		AVPacket pkt = XFFmpeg::Get()->Read();
		if (pkt.size <= 0) {
			msleep(10);//�ͷ�cpu��Դ
			continue;
		}
		if (pkt.stream_index != XFFmpeg::Get()->videoStream) {
			av_packet_unref(&pkt);
			continue;
		}
		XFFmpeg::Get()->Decode(&pkt);
		av_packet_unref(&pkt);
		if (XFFmpeg::Get()->fps > 0)//ÿһ֡�ĺ�����
		{
            msleep(1000 / XFFmpeg::Get()->fps);//�ͷ�cpu��Դ
		}
		
	}
}


XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{
	
}
