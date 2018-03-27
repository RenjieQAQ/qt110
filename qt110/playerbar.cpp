#include "playerbar.hpp"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

playerBar::playerBar(QWidget * parent) : QWidget(parent) {
	setFixedHeight(60);
	QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(42, 45, 76));//61, 62, 68
	setAutoFillBackground(true);
	setPalette(pal);
	setMouseTracking(true);

	stopFlag = 1;
	playFlag=0;
	saveFlag=0;

	pButtonPlay = new QPushButton(this);
	pButtonStop = new QPushButton(this);
	pButtonSave = new QPushButton(this);
	pButtonPlay->setFixedSize(50, 50);
	pButtonStop->setFixedSize(50, 50);
	pButtonSave->setFixedSize(50, 50);
	QHBoxLayout* pLayout = new QHBoxLayout(this);
	pLayout->addWidget(pButtonPlay);
	pLayout->addWidget(pButtonStop);
	pLayout->addWidget(pButtonSave);
	pLayout->setContentsMargins(5, 0, 5, 0);
	setLayout(pLayout);
	QPixmap pmPlay;
	QPixmap pmStop;
	QPixmap pmSave;
	pmPlay.load("play.png");
	pmStop.load("stop.png");
	pmSave.load("save.png");

	pButtonPlay->setMask(pmPlay.createHeuristicMask());
	pButtonPlay->setIcon(pmPlay);
	pButtonPlay->setIconSize(QSize(50,50));

	pButtonStop->setMask(pmStop.createHeuristicMask());
	pButtonStop->setIcon(pmStop);
	pButtonStop->setIconSize(QSize(50, 50));

	pButtonSave->setMask(pmSave.createHeuristicMask());
	pButtonSave->setIcon(pmSave);
	pButtonSave->setIconSize(QSize(50, 50));

	connect(pButtonStop, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(pButtonSave, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(pButtonPlay, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

playerBar::~playerBar() {
	
}
//void playerBar::mousePressEvent(QMouseEvent *event)
//{
//	QMessageBox::information(this, ("close"), ("123!!"));
//	emit clicked();
//}
void playerBar::onClicked()
{
	//QMessageBox::information(this, ("close"), ("123!!"));
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == pButtonPlay)
		{
			if (playFlag == 0)
			{
				QPixmap pm;
				pm.load("pause_s");
				pButton->setMask(pm.createHeuristicMask());
				pButton->setIcon(pm);
				pButton->setIconSize(QSize(pm.width(), pm.height()));
				pm.load("stop_s");
				pButtonStop->setMask(pm.createHeuristicMask());
				pButtonStop->setIcon(pm);
				pButtonStop->setIconSize(QSize(pm.width(), pm.height()));
				playFlag = 1;
				stopFlag = 0;
			}
			else
			{
				QPixmap pm;
				pm.load("play_s");
				pButton->setMask(pm.createHeuristicMask());
				pButton->setIcon(pm);
				pButton->setIconSize(QSize(pm.width(), pm.height()));
				playFlag = 0;
			}
			
		}
		else if (pButton == pButtonStop)
		{
			stopFlag = 1;
			playFlag = 0;
			QPixmap pm;
			pm.load("stop");
			pButton->setMask(pm.createHeuristicMask());
			pButton->setIcon(pm);
			pButton->setIconSize(QSize(pm.width(), pm.height()));
			pm.load("play");
			pButtonPlay->setMask(pm.createHeuristicMask());
			pButtonPlay->setIcon(pm);
			pButtonPlay->setIconSize(QSize(pm.width(), pm.height()));
		}
		else if (pButton == pButtonSave)
		{
			if (saveFlag == 0)
			{
				QPixmap pm;
				pm.load("save_r");
				pButton->setMask(pm.createHeuristicMask());
				pButton->setIcon(pm);
				pButton->setIconSize(QSize(pm.width(), pm.height()));
				saveFlag = 1;
			}
			else
			{
				QPixmap pm;
				pm.load("save_s");
				pButton->setMask(pm.createHeuristicMask());
				pButton->setIcon(pm);
				pButton->setIconSize(QSize(pm.width(), pm.height()));
				saveFlag = 0;
			}
		}
		
	}
}
void playerBar::mouseMoveEvent(QMouseEvent * event)
{
	QPushButton * pButton = pButtonPlay;
	QRect rec(pButton->x(), pButton->y(), pButton->width(), pButton->height());
	QString ico;
	if (playFlag == 0)
	{
		if (rec.contains(event->pos()))
			ico = "play_s.png";
		else ico = "play.png";
	}
	else
	{
		if (rec.contains(event->pos()))
			ico = "pause_s.png";
		else ico = "pause.png";
	}		
	QPixmap pm;
	pm.load(ico);
	pButton->setMask(pm.createHeuristicMask());
	pButton->setIcon(pm);
	pButton->setIconSize(QSize(pm.width(), pm.height()));

	pButton = pButtonSave;
	rec.setRect(pButton->x(), pButton->y(), pButton->width(), pButton->height());
	if (saveFlag == 0)
	{
		if (rec.contains(event->pos()))
			ico = "save_s.png";
		else ico = "save.png";
	}
	else
	{
		ico = "save_r.png";
	}
	pm.load(ico);
	pButton->setMask(pm.createHeuristicMask());
	pButton->setIcon(pm);
	pButton->setIconSize(QSize(pm.width(), pm.height()));

	/*pButton = pButtonStop;
	rec.setRect(pButton->x(), pButton->y(), pButton->width(), pButton->height());
	if (stopFlag == 0)
	{
		ico = "stop_s.png";
	}
	else
	{
		ico = "stop.png";
	}
	pm.load(ico);
	pButton->setMask(pm.createHeuristicMask());
	pButton->setIcon(pm);
	pButton->setIconSize(QSize(pm.width(), pm.height()));*/


}
