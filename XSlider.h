#pragma once
#include<qslider.h>
class XSlider:public QSlider
{
	Q_OBJECT
	
public:
	void mousePressEvent(QMouseEvent *e);
	XSlider(QWidget *p = NULL);
	~XSlider();
};

