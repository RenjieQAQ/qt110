#include "qt110.h"
#include "titlebar.hpp"
QString s1 = s1.fromLocal8Bit("图像所小组成员：\n\n    刘仁杰\n\n    高菁汐\n\n    毕雪洁\n\n    拂晓\n\n指导老师：\n\n    卿鳞波");
qt110::qt110(QWidget *parent)
	: QWidget(parent)
{

	playerStatus = 2;
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());
	TitleBar *pTitleBar = new TitleBar(this);
	installEventFilter(pTitleBar);

//	resize(400, 300);
//	setWindowTitle("Custom Window");
	setWindowIcon(QIcon("scu.png"));
	
	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setAutoFillBackground(true);
	setPalette(pal);
	
	pLayout=new QVBoxLayout();
	pLayout->addWidget(pTitleBar);
	pLayout->addStretch();
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	ui.setupUi(this);
	pOptionBar = new optionBar(this);
	installEventFilter(pOptionBar);
	pLayout->addWidget(pOptionBar);
	setLayout(pLayout);
	setMouseTracking(true);

	pPlayBar = new playerBar(this);
	pPlayBar->setFixedWidth(width() - pOptionBar->width());
	pPlayBar->move(pOptionBar->width(), height() - 60);
	pPlayBar->setVisible(false);

	int x = pOptionBar->width(), y = pTitleBar->height();
	int w= (width()- pOptionBar->width()), h=height()- pTitleBar->height();
	//QSize size((w-14)/2,(h-14)/2);
	QSize size(250, 200);

	QImage image;  
	setQImage(image, 0, 0, 0,Size(200,200));

	/*threeD1 = new QLabel(this);
	threeD1->resize(size.width(), size.height());
	threeD1->move(x+ 5, y+5);
	threeD1->setPixmap( QPixmap::fromImage( image.scaled(size) ) );
	threeD1->setVisible(false);

	threeD2 = new QLabel(this);
	threeD2->resize(size.width(), size.height());
	threeD2->move(x + w/2+2, y+5);
	threeD2->setPixmap(QPixmap::fromImage(image.scaled(size)));
	threeD2->setVisible(false);*/
	
	threeD1 = new QLabel(this);
	threeD1->resize(size.width(), size.height());
	threeD1->move(x + 50, y + 5);
	threeD1->setPixmap(QPixmap::fromImage(image.scaled(size)));
	threeD1->setVisible(false);

	threeD2 = new QLabel(this);
	threeD2->resize(size.width(), size.height());
	threeD2->move(x + w / 2 + 2, y + 5);
	threeD2->setPixmap(QPixmap::fromImage(image.scaled(size)));
	threeD2->setVisible(false);

	//QGridLayout gridLayout(this);
	//gridLayout.addWidget(threeD1);
	//gridLayout.addWidget(threeD2);
	ptext=new QTextBrowser(this);
	ptext->setGeometry(x+100, y+100, 600, 300);
	ptext->setText(s1);
	ptext->setVisible(false);
	QFont ft;
	ft.setPointSize(12);
	ptext->setFont(ft);
}

qt110::~qt110()
{

}
bool qt110::isPlaying()
{
	return pPlayBar->playFlag;
}
bool qt110::isStoped()
{
	return pPlayBar->stopFlag;
}
void qt110::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	// 反走样
	painter.setRenderHint(QPainter::Antialiasing, true);
	// 设置画笔颜色、宽度
	painter.setPen(QPen(QColor(61, 62, 68), 1));
	painter.drawRect(0, 0, this->width(), this->height());


}
void qt110::closeButton()
{
	this->close();
}
void qt110::mouseMoveEvent(QMouseEvent * event)
{
	static int status = -2;
	int temp;
	if ((event->x() > pOptionBar->width()) || (event->x() < 0)|| ((event->y() - 50)<0))
	{
		temp = -1;
		if(temp!=status)
			emit selected(temp);
		status = temp;
	}
	else 
	{
		//emit selected( (event->y()-50) / pOptionBar->height());
		temp = (event->y() - 50) / 50;		
		if (temp >= pOptionBar->getButtonNum())
			temp = -1;
		else
			temp=pOptionBar->getIdList()[temp];

		if (temp != status)	emit selected(temp);
		status = temp;

	}
}
void setQImage(QImage &image,int r, int g, int b,Size size)
{
	int w, h;
	w = size.width;
	h = size.height;
	unsigned char *s;
	s = new unsigned char[w*h * 3];
	for (int i = 0; i < (w*h); i++)
	{
		s[3 * i + 0] = b;
		s[3 * i + 1] = g;
		s[3 * i + 2] = r;
	}
	Mat img(h, w, CV_8UC3, s);
	//imshow("df", img);
	//waitKey(0);
	Mat temp;
	cv::cvtColor(img, temp, CV_RGB2RGBA);
	image = QImage((temp.data),
		temp.cols, temp.rows, QImage::Format_RGB32);
	delete[]s;
}
void showImg(int r, int g, int b, QLabel * pLabel)
{
	int w, h;
	w = pLabel->width();
	h = pLabel->height();
	unsigned char *s;
	s = new unsigned char[w*h*3];
	for (int i = 0; i < (w*h); i++)
	{
		s[3 * i + 0] = b;
		s[3 * i + 1] = g;
		s[3 * i + 2] = r;
	}
	Mat img(h, w, CV_8UC3,s);
	//imshow("df", img);
	//waitKey(0);
	Mat temp;
	cv::cvtColor(img, temp, CV_RGB2RGBA);
	QImage image = QImage((temp.data),
		temp.cols, temp.rows, QImage::Format_RGB32);
	pLabel->setPixmap(QPixmap::fromImage(image));
	pLabel->show();
	delete[]s;
}

void showImg(const char * filename, QLabel * pLabel,int showMethod=0)
{
	Mat img = imread(filename);
	int w, h;
	if (showMethod)//根据图片大小显示
	{
		w = img.cols;
		h = img.rows;
		pLabel->resize(w, h);
	}
	else //根据控件大小显示
	{	
		resize(img, img, Size(pLabel->width(), pLabel->height()), 0, 0, CV_INTER_LINEAR);
	}
	cv::cvtColor(img, img, CV_RGB2RGBA);
	QImage image = QImage((img.data),
		img.cols, img.rows, QImage::Format_RGB32);
	pLabel->setPixmap(QPixmap::fromImage(image));
	pLabel->show();
}
void showMat(Mat & img, QLabel * pLabel)
{
	Mat tmp;
	//static QImage image;
	resize(img, tmp, Size(250, 250), 0, 0, CV_INTER_LINEAR);
	cv::cvtColor(tmp, tmp, CV_RGB2RGBA);
	QImage image = QImage((tmp.data),
		tmp.cols, tmp.rows, QImage::Format_RGB32);
	pLabel->resize(250, 250);
	pLabel->setPixmap( QPixmap::fromImage(image));
	pLabel->show();
}
void showMat(QImage & img, QLabel * pLabel)
{
	QImage temp;
	temp =img.scaled(250, 250);
	pLabel->resize(250, 250);
//	pLabel->setPixmap(QPixmap::fromImage(temp));
	pLabel->show();
}
void showVal(int x, QTextBrowser * pt)
{
	pt->setText(QString::number(x));
}
//void * qtPlay(void * p)
//{
//	qt110 * widget = (qt110 *)p;
//	VideoCapture capture;
//	capture.open("D:/vlc/test.mp4");
//	while (!capture.isOpened())//判断是否打开视频文件  
//	{
//		QMessageBox::information(widget, ("cannot open"), ("234!!"));
//		return NULL;
//	}
//	Mat img(1280,780, CV_8UC3);;
//	Mat* pimg = &img;
//	Mat img_r;
//	double rate = capture.get(CV_CAP_PROP_FPS);//获取视频文件的帧率  
//	int delay = cvRound(1000.000 / rate);
//	while (1)
//	{
//		if (widget->pPlayBar->playFlag==1)
//		{
//			capture >> img;
//			if (img.empty())return NULL;
//			showMat(*pimg, widget->threeD1);
//			_sleep(delay);
//		}
//	}
//	return NULL;
//}
unsigned  char zero[10000] = { 0 };
void * qtPlay(void * p)
{
	cVedio *vedio = (cVedio *)p;
	qt110 * widget = vedio->pQtWidget;
	/*Mat * x = new Mat();
	*x= imread("kid.png");*/
	while (1)
	{
		if ( (IsLock()) && (widget->pPlayBar->playFlag == 1) )
		{
			if (vedio->img->empty())continue;
			//showMat(*(vedio->img), vedio->pLabel);
			showMat(*(vedio->qImg), vedio->pLabel);
			_sleep(1000 / 25);
	
		}
	}
	return NULL;
}


void qt110::onClicked()
{
	static MyButton * pLastButton= NULL;
	MyButton *pButton = qobject_cast<MyButton *>(sender());
	QWidget *pWindow = this->window();
	if (pButton != pLastButton)
	{
		if (pWindow->isTopLevel())
		{
			if (pButton == pOptionBar->getButton(0))
			{
				pPlayBar->close();
				threeD1->close();
				threeD2->close();
				ptext->close();
			}
			else if (pButton == pOptionBar->getButton(1))
			{
				pPlayBar->show();
				threeD1->show();
				threeD2->show();
				ptext->close();
				//showImg(0, 0, 0, threeD1);
				//showImg(Mat(100,100, CV_8UC3, zero), threeD1);
				/*threeD1->setPixmap(QPixmap("kid.png"));
				threeD1->show();*/
			}
			else if (pButton == pOptionBar->getButton(2))
			{
				ptext->close();
				//Mat img;
				//img = imread("kid.png");//读取图像                                                      
				//cv::cvtColor(img, img, CV_RGB2RGBA);
				//QImage image = QImage((img.data),
				//	img.cols, img.rows, QImage::Format_RGB32);
				////	threeD1->setGeometry(pOptionBar->width(), 50, 500, 500);
				//threeD1->resize(img.cols, img.rows);
				//threeD1->setPixmap(QPixmap::fromImage(image));
				//threeD1->show();

				//MyThread show1(qtPlay, this);
			}
			else if (pButton == pOptionBar->getButton(3))
			{
				pPlayBar->close();
				threeD1->close();
				threeD2->close();
				ptext->show();
			}
		}
	}
	pLastButton = pButton;
}


