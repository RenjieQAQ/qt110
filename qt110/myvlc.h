#pragma once
#include <pthread.h>
#include <Windows.h>  
#include "vlc/vlc.h" 
#include <opencv2/opencv.hpp>
#include <QWidget>
#include "ui_playerbar.h"
#include<qlabel.h>
#include<QMessageBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QtGui/QMouseEvent>
#include <QPushButton>
#include <QPainter>
#include <qbitmap.h>
#include <iostream>
#include <qt110.h>
using namespace std;
using namespace cv;


void saveImage(Mat& img, int id, int iFrame);
void buffer2RBG(uint8_t * buff, Mat& img);
void buffer2img(Mat&img, uint8_t *buff);
void *libvlc_video_lock_cb_callback(void *opaque, void **planes);
void libvlc_video_unlock_cb_callback(void *opaque, void *picture,void *const *planes);

void libvlc_video_display_cb_callback(void *opaque, void *picture);

void Lock();
void DisLock();
BOOL IsLock();
class qt110;
class cVedio
{

public:
	const char * url;
	qt110 * pQtWidget;
	QLabel* pLabel;
	int width;
	int height;
	int iFrame;
	int cnt;
	int bufSize;
	uint8_t* buffer;
	Mat *img;
	QImage *qImg;
	int id;
	int getID();
	bool isEnd;
	cVedio(char * filename, qt110 *  p, QLabel* plabel)
	{
		url = filename;
		this->pQtWidget = p;
		pLabel = plabel;
		id=getID();
		width = 704;
		height = 480;
		iFrame = 0;
		cnt = 0;
		bufSize = 1280 * 720 * 3;
		buffer = new uint8_t[bufSize];
		isEnd = 0;
	}

	~cVedio()
	{
		delete buffer;
	}
};


void * getVedio(void* Param);

void showImg(Mat& img, QLabel * pLabel, int showMethod);
//void getVedio(cVedio* vedio, int x);
