#include "XPlay.h"
#include <QtWidgets/QApplication>
#include"XFFmpeg.h"
#include<qaudiooutput.h>
int main(int argc, char *argv[])
{
	QAudioOutput *out;
	QAudioFormat fmt;
	fmt.setSampleRate(48000);///һ��ɼ������ǧ����Ƶ
	fmt.setSampleSize(16);//16λ��һ��ɼ�65535������
	fmt.setChannelCount(2);
	fmt.setCodec("audio/pcm");
	fmt.setByteOrder(QAudioFormat::LittleEndian);
	fmt.setSampleType(QAudioFormat::UnSignedInt);
	out = new QAudioOutput(fmt);
	QIODevice *ad = out->start();
	/*ad->write*/
	QApplication a(argc, argv);
	XPlay w;
	w.show();
	return a.exec();
}
