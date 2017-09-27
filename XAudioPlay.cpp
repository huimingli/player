#include "XAudioPlay.h"
#include<qaudiooutput.h>
#include<qmutex.h>
class CXAudioPlay :public XAudioPlay {
public:
	QAudioOutput *output = NULL;
	QIODevice *io = NULL;
	QMutex mutex;
	void Stop() {
		mutex.lock();
		if (output) {
			output->stop();
			delete output;
			output = NULL;
			io = NULL;
		}
		mutex.unlock();
	}
	bool Start() {
		Stop();
		mutex.lock();
		QAudioFormat fmt;
		fmt.setSampleRate(this->sampleRate);///一秒采集四万八千个音频
		fmt.setSampleSize(this->sampleSize);//16位，一秒采集65535种声音
		fmt.setChannelCount(this->channel);
		fmt.setCodec("audio/pcm");
		fmt.setByteOrder(QAudioFormat::LittleEndian);
		fmt.setSampleType(QAudioFormat::UnSignedInt);
		output = new QAudioOutput(fmt);
		io = output->start();
		mutex.unlock();
		return true;
	}

	void Play(bool isPlay) {
		mutex.lock();
		if (!output) {
			mutex.unlock();
			return;
		}
		if (isPlay) {
			output->resume();
		}
		else {
			output->suspend();
		}
		mutex.unlock();
	}
	int GetFree() {
		mutex.lock();
		if (!output) {
			mutex.unlock();
			return 0;
		}
		int free = output->bytesFree();
		mutex.unlock();
		return free;
	}

	bool Write(const char *data, int datasize) {
		mutex.lock();
		if (io) {
		    io->write(data, datasize);
		}
		mutex.unlock();
		return true;
	}
};


XAudioPlay::XAudioPlay()
{

}


XAudioPlay::~XAudioPlay()
{
}

XAudioPlay *XAudioPlay::Get()
{
	static CXAudioPlay ap;
	return &ap;
}