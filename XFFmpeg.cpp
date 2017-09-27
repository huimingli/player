#include "XFFmpeg.h"

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"swscale.lib")
static double r2d(AVRational r) {
	return r.num == 0 || r.den == 0 ?
		0. : (double)r.num / (double)r.den;
}
int XFFmpeg::Open(const char*path) {
	Close();//不能保证上次的已经关闭
	mutex.lock();
	int re = avformat_open_input(&ic, path, 0, 0);
	if (re != 0) {
		mutex.unlock();
		av_strerror(re, errorbuf, sizeof(errorbuf));//util库
		printf("open fail %s\n", errorbuf);
		return 0;
	}
	totalMs = ((ic->duration / AV_TIME_BASE) * 1000);

	//打开解码器
	for (int i = 0;i < ic->nb_streams;i++) {
		AVCodecContext *enc = ic->streams[i]->codec;//解码器
		
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
		
			fps = r2d(ic->streams[i]->avg_frame_rate);
			AVCodec * codec = avcodec_find_decoder(
				enc->codec_id);
			if (!codec) {
				mutex.lock();
				printf("video code not found\n");
				return 0;
			}
			int err = avcodec_open2(enc, codec, NULL);
			if (err != 0) {
				mutex.lock();
				char *buf = { 0 };
				av_strerror(err, buf, sizeof(buf));
				printf(buf);
				return 0;
			}
			printf("open success\n");
		}
	}
	mutex.unlock();
	return totalMs;
}

void XFFmpeg::Close() {
	mutex.lock();
	if (ic) {
		avformat_close_input(&ic);
	}
	if (yuv) {
		av_frame_free(&yuv);
	}
	if (cCtx) {
		sws_freeContext(cCtx);
		cCtx = NULL;
	}
	mutex.unlock();
}

std::string XFFmpeg::GetError() {
	mutex.lock();
	std::string re = this->errorbuf;
	mutex.unlock();
	return re;
}

AVPacket XFFmpeg::Read() {
	AVPacket pkt;
	memset(&pkt, 0, sizeof(AVPacket));
	mutex.lock();
	if (!ic) {
		mutex.unlock();
		return pkt;
	}
	int err = av_read_frame(ic, &pkt);
	if (err != 0)
	{
		av_strerror(err, errorbuf, sizeof(errorbuf));
	}
	mutex.unlock();
	return pkt;
}

XFFmpeg::XFFmpeg()
{
	errorbuf[0] = '\0';
	av_register_all();//构造函数只执行一次，单例
}

AVFrame *XFFmpeg::Decode(const AVPacket *pkt) {
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return NULL;
	}
	if (yuv == NULL)
	{
		yuv = av_frame_alloc();
	}
	int re = avcodec_send_packet(
		ic->streams[pkt->stream_index]->codec, pkt);

	if (re != 0) {
		mutex.unlock();
		return NULL;
	}
	re = avcodec_receive_frame(
		ic->streams[pkt->stream_index]->codec, yuv);
	if (re != 0) {
		mutex.unlock();
		return NULL;
	}
	mutex.unlock();
	pts = yuv->pts * r2d(ic->
		streams[pkt->stream_index]->time_base) * 1000;
	return yuv;
}

bool XFFmpeg::ToRGB(char *out, int outWidth, int outHeight) {
	mutex.lock();
	if (!ic || !yuv) {
		mutex.unlock();
		return false;
	}
	AVCodecContext *videoCtx = ic->streams[this->videoStream]->codec;
		cCtx = sws_getCachedContext(NULL,
			videoCtx->width,
			videoCtx->height,
			videoCtx->pix_fmt,
			outWidth, outHeight,
			AV_PIX_FMT_BGRA,
			SWS_BICUBIC,
			NULL, NULL, NULL
		);
		if (!cCtx)
		{
			mutex.unlock();
			printf("sws_getCachecontext fail \n");
			return false;
		}
		uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
		data[0] = (uint8_t*)out;
		int linesize[AV_NUM_DATA_POINTERS] = { 0 };
		linesize[0] = outWidth * 4;
		int h = sws_scale(cCtx, yuv->data,
			yuv->linesize,0,
			videoCtx->height,data,linesize);

		if (h>0)
		{
			printf("(%d)", h);
		}
		
	mutex.unlock();
	return true;
}

bool XFFmpeg::Seek(float pos) {
	mutex.lock();
	if (!ic) {
		mutex.unlock();
		return false;
	}
	int64_t stamp = 0;//时间戳
	stamp = pos * ic->streams[videoStream]->duration;
	int re = av_seek_frame(ic, videoStream, stamp,
		AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
	avcodec_flush_buffers(ic->streams[videoStream]->codec);//清除缓冲帧
	pts = stamp * r2d(ic->streams[videoStream]->time_base) * 1000;

	mutex.unlock();
	if (re >= 0) {
		return true;
	}
	return false;
}

XFFmpeg::~XFFmpeg()
{
}
