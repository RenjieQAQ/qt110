#ifndef QT110_H
#define QT110_H

#include "vlc/vlc.h" 
#include "myvlc.h"
#include "MyThread.h"
#include "ui_qt110.h"
#include <QtWidgets/QWidget>
#include <QLabel>
#include<qfont.h>
#include <QIcon>
#include<QMessageBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QtGui/QMouseEvent>
#include "titlebar.hpp"
#include <QPushButton>
#include <QPainter>
#include "pthread.h"
#include "playerbar.hpp"
#include <opencv2\opencv.hpp>
#include <QTextBrowser>
using namespace cv;
class qt110 : public QWidget
{
	Q_OBJECT

public:
	qt110(QWidget *parent = 0);
	~qt110();
//	Mat *img_r;
	friend void * qtPlay(void * p);
	int playerStatus;
	bool isPlaying();
	bool isStoped();
	QLabel *threeD1;
	QLabel *threeD2;
	QLabel *threeD3;
	QLabel *threeD4;
	playerBar *pPlayBar;
signals:
	void selected(int);
	void getImg();
private:
	Ui::qt110Class ui;
	QVBoxLayout * pLayout;
	optionBar *pOptionBar;
	QTextBrowser *ptext;
	void mouseMoveEvent(QMouseEvent * event);
private slots:
	void closeButton();
	void paintEvent(QPaintEvent *event);
	void onClicked();
};
void showMat(Mat & img, QLabel * pLabel);
void showVal(int x, QTextBrowser * pt);
void setQImage(QImage &image, int r, int g, int b, Size size);
//void showImg(const char * filename, QLabel * pLabel, int showMethod = 0);
//void showImg(int r, int g, int b, QLabel * pLabel);
//void showImg(Mat img, QLabel * pLabel, int showMethod = 0);
//void showImg(const char * filename, QLabel * pLabel, int showMethod = 0);

#endif // QT110_H
