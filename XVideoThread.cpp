#include "XVideoThread.h"
#include"XFFmpeg.h"
bool isExit = false;
void XVideoThread::run() {
	while (!isExit) {

		AVPacket pkt = XFFmpeg::Get()->Read();
		if (pkt.size <= 0) {
			msleep(10);//释放cpu资源
			continue;
		}
		if (pkt.stream_index != XFFmpeg::Get()->videoStream) {
			av_packet_unref(&pkt);
			continue;
		}
		XFFmpeg::Get()->Decode(&pkt);
		av_packet_unref(&pkt);
		if (XFFmpeg::Get()->fps > 0)//每一帧的毫秒数
		{
            msleep(1000 / XFFmpeg::Get()->fps);//释放cpu资源
		}
		
	}
}


XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{
	
}
