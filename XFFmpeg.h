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
	///����Ƶ�ļ�������ϴ��Ѿ��򿪻��ȹر�
	///@param path ��Ƶ·��
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
	int pts = 0;//��ǰ����
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
	SwsContext *cCtx = NULL;//ת����
	SwrContext *aCtx = NULL;//��Ƶ�ز���
};

