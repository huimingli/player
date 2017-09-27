#pragma once
extern "C" {
#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<libswscale/swscale.h>
#include<libswresample/swresample.h>
}
#include<string>
#include<qmutex.h>
class XFFmpeg
{
public:
	static XFFmpeg *Get() {
		static XFFmpeg ff;
		return &ff;
	}
	///////////////////////////////////////////
	///打开视频文件，如果上次已经打开会先关闭
	///@param path 视频路径
	///@return total ms  
	int Open(const char*path);
	void Close();
	AVPacket Read();
	int GetPts(const AVPacket *pkt);
	int Decode(const AVPacket *pkt);
	std::string GetError();
	bool ToRGB(char *out, int outWidth, int outHeight);
	int ToPCM(char *out);
	bool Seek(float pos);
	virtual ~XFFmpeg();
	bool isPlay = false;
	int totalMs = 0;
	int fps = 0;
	int pts = 0;//当前进度
	int videoStream = 0;


	int audioStream = 1;
	int sampleRate = 48000;
	int sampleSize = 16;
	int channel = 2;

protected:
	AVFormatContext *ic = NULL;
	char errorbuf[1024];
	QMutex mutex;
	AVFrame *yuv = NULL;
	AVFrame *pcm = NULL;
	XFFmpeg();
	SwsContext *cCtx = NULL;//转换器
	SwrContext *aCtx = NULL;//音频重采样
};

