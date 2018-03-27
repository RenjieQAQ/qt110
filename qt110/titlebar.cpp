#include "titlebar.hpp"


#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	setFixedHeight(50);//30

	m_pIconLabel = new QLabel(this);
	m_pTitleLabel = new QLabel(this);
	m_pMinimizeButton = new QPushButton(this);
//	m_pMaximizeButton = new QPushButton(this);
	m_pCloseButton = new QPushButton(this);

	m_pIconLabel->setFixedSize(50, 50);
	m_pIconLabel->setScaledContents(true);

	m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	//m_pTitleLabel->setWindowTitle("2017年工程领袖计划项目----图像所");

	m_pMinimizeButton->setFixedSize(27, 22);
//	m_pMaximizeButton->setFixedSize(27, 22);
	m_pCloseButton->setFixedSize(27, 22);

	m_pTitleLabel->setObjectName("whiteLabel");
	m_pMinimizeButton->setObjectName("minimizeButton");
//	m_pMaximizeButton->setObjectName("maximizeButton");
	m_pCloseButton->setObjectName("closeButton");

	m_pMinimizeButton->setToolTip("Minimize");
//	m_pMaximizeButton->setToolTip("Maximize");
	m_pCloseButton->setToolTip("Close");

	QPixmap pm;   
	QPixmap pmClose;
	pm.load("min.png");
	pmClose.load("close.png");
//	m_pMinimizeButton->setMask(pm.createHeuristicMask());
	m_pMinimizeButton->setIcon(pm);
	m_pMinimizeButton->setIconSize(QSize(pm.width(), pm.height()));
//	m_pCloseButton->setMask(pmClose.createHeuristicMask());
	m_pCloseButton->setIcon(pmClose);
	m_pCloseButton->setIconSize(QSize(pmClose.width(), pmClose.height()));

	QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(29, 34, 62));//61, 62, 68
	setAutoFillBackground(true);
	setPalette(pal);

	pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pIconLabel);
	pLayout->addSpacing(5);
	pLayout->addWidget(m_pTitleLabel);
	pLayout->addWidget(m_pMinimizeButton);
//	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);/**/
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(5, 0, 5, 0);

	setLayout(pLayout); 
//	this->setWindowTitle("2017年工程领袖计划项目----图像所");
	connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
//	connect(this, SIGNAL(move()), this, SLOT(changeIcon()));
//	connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	setMouseTracking(true);
	m_pMinimizeButton->setMouseTracking(true);
	m_pCloseButton->setMouseTracking(true);
}

TitleBar::~TitleBar()
{
//	delete m_pIconLabel;
//	delete m_pTitleLabel;
//	delete m_pMinimizeButton;
////	delete m_pMaximizeButton;
//	delete m_pCloseButton;
	//	delete pLayout;
}

void TitleBar::mouseMoveEvent(QMouseEvent * event)
{
	//emit move();
	QPushButton * pButton = m_pMinimizeButton;
	QRect rec(pButton->x(), pButton->y(), pButton->width(), pButton->height());
	if (rec.contains(event->pos()))
	{
		QPixmap pm;
		pm.load("min_s.png");
		pButton->setIcon(pm);
		pButton->setIconSize(QSize(pm.width(), pm.height()));

	}
	else
	{
		QPixmap pm;
		pm.load("min.png");
		pButton->setIcon(pm);
		pButton->setIconSize(QSize(pm.width(), pm.height()));

	}
	pButton = m_pCloseButton;
	rec.setRect(pButton->x(), pButton->y(), pButton->width(), pButton->height());
	if (rec.contains(event->pos()))
	{
		QPixmap pm;
		pm.load("close_s.png");
		pButton->setIcon(pm);
		pButton->setIconSize(QSize(pm.width(), pm.height()));
//		QMessageBox::information(this, ("close"), ("close!!"));
	}
	else
	{
		QPixmap pm;
		pm.load("close.png");
		pButton->setIcon(pm);
		pButton->setIconSize(QSize(pm.width(), pm.height()));
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);

//	emit m_pMaximizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
	if (ReleaseCapture())
	{
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
#else
#endif
}

QString title = title.fromLocal8Bit("2016年工程领袖计划项目----图像所");
bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::WindowTitleChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			m_pTitleLabel->setText(title);
			QPalette pal;
			pal.setColor(QPalette::WindowText, QColor(255, 255, 255));
			m_pTitleLabel->setPalette(pal);
			return true;
		}
	}
	case QEvent::WindowIconChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			QIcon icon = pWidget->windowIcon();
			m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
			return true;
		}
	}
	case QEvent::WindowStateChange:
	case QEvent::Resize:
//		updateMaximize();
		return true;
	}
	return QWidget::eventFilter(obj, event);
}

void TitleBar::changeIcon()
{
	//QPushButton *pButton = qobject_cast<QPushButton *>(sender());
	if (1)
	{
		QPixmap pm;
		pm.load("min_s.png");
		m_pMinimizeButton->setIcon(pm);
		m_pMinimizeButton->setIconSize(QSize(pm.width(), pm.height()));
		QMessageBox::information(this, ("close"), ("close!!"));
	}
	else
	{
		QPixmap pm;
		pm.load("min.png");
		m_pMinimizeButton->setIcon(pm);
		m_pMinimizeButton->setIconSize(QSize(pm.width(), pm.height()));
		QMessageBox::information(this, ("close"), ("123!!"));
	}
}
void TitleBar::onClicked()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == m_pMinimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pButton == m_pMaximizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pButton == m_pCloseButton)
		{
			//Sleep(1000); QMessageBox::information(this, ("close"), ("close!!"));
			pWindow->close();
		}
	}
}

//void TitleBar::updateMaximize()
//{
//	QWidget *pWindow = this->window();
//	if (pWindow->isTopLevel())
//	{
//		bool bMaximize = pWindow->isMaximized();
//		if (bMaximize)
//		{
//			m_pMaximizeButton->setToolTip(tr("Restore"));
//			m_pMaximizeButton->setProperty("maximizeProperty", "restore");
//		}
//		else
//		{
//			m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
//			m_pMaximizeButton->setToolTip(tr("Maximize"));
//		}
//
//		m_pMaximizeButton->setStyle(QApplication::style());
//	}
//}