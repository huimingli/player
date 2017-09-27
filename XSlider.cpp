#include "XSlider.h"
#include<QMouseEvent>
void XSlider::mousePressEvent(QMouseEvent *e) {
	int value = ((float)e->pos().x() /
		(float)this->width())*this->maximum() + 1;
	this->setValue(value);
	QSlider::mousePressEvent(e);
}

XSlider::XSlider(QWidget *p):QSlider(p)
{

}


XSlider::~XSlider()
{
}
