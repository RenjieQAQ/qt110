#include "qt110.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <Windows.h>
#include <shellapi.h>
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	qt110 w;
	/*cVedio ch1("file:///D:/vlc/good.mp4",&w,w.threeD1);
	cVedio ch2("file:///D:/vlc/test.mp4", &w, w.threeD2);*/
	cVedio ch1("rtsp://admin:aa123456@192.168.1.65:554/h264/ch1/main/av_stream", &w, w.threeD1);
	cVedio ch2("rtsp://admin:a1234567@192.168.1.64:554/h264/ch1/main/av_stream", &w, w.threeD2);
	MyThread open1(getVedio, &ch1);
	_sleep(2000);
	MyThread open2(getVedio, &ch2);
	w.show();
	return a.exec();
}
