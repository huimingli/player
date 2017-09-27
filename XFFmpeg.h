#pragma once
extern "C" {
#include<libavcodec\avcodec.h>
#include<libavformat\avformat.h>
#include<libswscale\swscale.h>
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
	AVFrame *Decode(const AVPacket *pkt);
	std::string GetError();
	bool ToRGB(char *out, int outWidth, int outHeight);
	virtual ~XFFmpeg();
	int totalMs = 0;
	int fps = 0;
	int videoStream = 0;
protected:
	AVFormatContext *ic = NULL;
	char errorbuf[1024];
	QMutex mutex;
	AVFrame *yuv = NULL;
	XFFmpeg();
	SwsContext *cCtx = NULL;//转换器
};

