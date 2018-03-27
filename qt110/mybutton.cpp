#include "mybutton.hpp"
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif
QString fonts = fonts.fromLocal8Bit("黑体");
int MyButton::buttonNum=0;
MyButton::MyButton(QWidget * parent, QString & buttonName) : QWidget(parent),name(buttonName){
	//ui.setupUi(this);
	id = buttonNum;
	buttonNum++;
	flagSelected = 0;
	setFixedHeight(50);
	setFixedWidth(parent->width());
	QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(42, 45, 76));
	setAutoFillBackground(true);
	setPalette(pal);
	setMouseTracking(true);
	connect(parent->window(), SIGNAL(selected(int)), this, SLOT(changeUI(int)));
	connect(parent, SIGNAL(selected(int)), this, SLOT(changeUI(int)));
	m_pTitleLabel = new QLabel(this);
	m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout  * pLayout = new QHBoxLayout(this);
	pLayout->addStretch();
	pLayout->addWidget(m_pTitleLabel);
	pLayout->addStretch();
	setLayout(pLayout);
}

MyButton::~MyButton() {
}

int MyButton::getId()
{
	return id;
}
void MyButton::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	// 反走样
	painter.setRenderHint(QPainter::Antialiasing, true);
	// 设置画笔颜色、宽度
	painter.setPen(QPen(QColor(61, 62, 68), 1));
	painter.drawLine(0, 0, 0, height());
	//painter.setPen(QPen(QColor(231, 231, 231), 2));
	//painter.drawLine(0, height(), width(),height());
}

bool MyButton::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
		case QEvent::WindowTitleChange:
		{
			QWidget *pWidget = qobject_cast<QWidget *>(obj);
			if (pWidget)
			{
				m_pTitleLabel->setText(name);
				QPalette pal;
				pal.setColor(QPalette::WindowText, QColor(255, 255, 255));
				m_pTitleLabel->setPalette(pal);
				QFont ft;
				ft.setPointSize(12);
				ft.setFamily(fonts);
				m_pTitleLabel->setFont(ft);
				return true;
			}
		}
	}
	return QWidget::eventFilter(obj, event);
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
//#ifdef Q_OS_WIN
//	if (ReleaseCapture())
//	{
//		QWidget *pWindow = this->window();
//		if (pWindow->isTopLevel())
//		{
//			//SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
//			QMessageBox::information(this, ("button"), ("button!!"));
//		
//		}
//	}
//	event->ignore();
//#else
//#endif
	flagSelected = 1;
	emit clicked();

}
bool MyButton::isSelected()
{
	return flagSelected;
}
//void MyButton::mouseMoveEvent(QMouseEvent * event)
//{
//	if ( (event->x()<width()-1)&& (event->x()>0)&&(event->y()<height() - 1) && (event->y()>0))
//	{
//		QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(255, 200, 200));
//		setPalette(pal);
//	}
//	else
//	{
//		QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(255, 234, 234));
//		setPalette(pal);
//	}
//}

//id:按键的ID
void MyButton::changeUI(int id)
{
	if (id == this->id)//选中
	{
		QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(31, 33, 54));
		setPalette(pal);
	}
	else
	{
		if (!flagSelected)
		{
			QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(42,45,76));//29, 34, 62
			setPalette(pal);
		}
	}
}


