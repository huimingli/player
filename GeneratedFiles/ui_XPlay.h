/********************************************************************************
** Form generated from reading UI file 'XPlay.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPLAY_H
#define UI_XPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "videowidget.h"
#include "xslider.h"

QT_BEGIN_NAMESPACE

class Ui_XPlayClass
{
public:
    VideoWidget *openGLWidget;
    QPushButton *openButton;
    QPushButton *playButton;
    QLabel *totalTime;
    QLabel *playTime;
    QLabel *sp;
    XSlider *playLine;

    void setupUi(QWidget *XPlayClass)
    {
        if (XPlayClass->objectName().isEmpty())
            XPlayClass->setObjectName(QStringLiteral("XPlayClass"));
        XPlayClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/XPlay/Resources/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        XPlayClass->setWindowIcon(icon);
        openGLWidget = new VideoWidget(XPlayClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 800, 600));
        openButton = new QPushButton(XPlayClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(290, 490, 51, 71));
        openButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/XPlay/Resources/open_normal.png);}\n"
"QPushButton:hover{border-image: url(:/XPlay/Resources/open_hot.png);}"));
        playButton = new QPushButton(XPlayClass);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(410, 500, 61, 61));
        playButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/XPlay/Resources/play_normal.png);}\n"
"QPushButton:hover{border-image: url(:/XPlay/Resources/play_hot.png);}"));
        totalTime = new QLabel(XPlayClass);
        totalTime->setObjectName(QStringLiteral("totalTime"));
        totalTime->setGeometry(QRect(180, 520, 71, 31));
        totalTime->setStyleSheet(QString::fromUtf8(" \n"
"color: rgb(13, 13, 13);\n"
"font: 14pt \"\351\273\221\344\275\223\";"));
        playTime = new QLabel(XPlayClass);
        playTime->setObjectName(QStringLiteral("playTime"));
        playTime->setGeometry(QRect(70, 520, 71, 31));
        playTime->setStyleSheet(QString::fromUtf8("color: rgb(13, 13, 13);\n"
"font: 14pt \"\351\273\221\344\275\223\";"));
        sp = new QLabel(XPlayClass);
        sp->setObjectName(QStringLiteral("sp"));
        sp->setGeometry(QRect(150, 530, 16, 31));
        sp->setStyleSheet(QStringLiteral("color: rgb(13, 13, 13);"));
        playLine = new XSlider(XPlayClass);
        playLine->setObjectName(QStringLiteral("playLine"));
        playLine->setGeometry(QRect(0, 470, 800, 22));
        playLine->setMaximum(999);
        playLine->setOrientation(Qt::Horizontal);

        retranslateUi(XPlayClass);
        QObject::connect(openButton, SIGNAL(clicked()), XPlayClass, SLOT(open()));
        QObject::connect(playLine, SIGNAL(sliderPressed()), XPlayClass, SLOT(sliderPress()));
        QObject::connect(playLine, SIGNAL(sliderReleased()), XPlayClass, SLOT(sliderRelease()));
        QObject::connect(playButton, SIGNAL(clicked()), XPlayClass, SLOT(play()));

        QMetaObject::connectSlotsByName(XPlayClass);
    } // setupUi

    void retranslateUi(QWidget *XPlayClass)
    {
        XPlayClass->setWindowTitle(QApplication::translate("XPlayClass", "XPlay", Q_NULLPTR));
        openButton->setText(QString());
        playButton->setText(QString());
        totalTime->setText(QApplication::translate("XPlayClass", "000:00", Q_NULLPTR));
        playTime->setText(QApplication::translate("XPlayClass", "000:00", Q_NULLPTR));
        sp->setText(QApplication::translate("XPlayClass", "/", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XPlayClass: public Ui_XPlayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPLAY_H
