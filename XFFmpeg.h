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
	///����Ƶ�ļ�������ϴ��Ѿ��򿪻��ȹر�
	///@param path ��Ƶ·��
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
	SwsContext *cCtx = NULL;//ת����
};

