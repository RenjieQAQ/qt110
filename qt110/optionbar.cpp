#include "optionbar.hpp"
QString title1 = title1.fromLocal8Bit("关于工程领袖");
QString title2 = title2.fromLocal8Bit("3D建模");
QString title3 = title3.fromLocal8Bit("3D还原");
QString title4 = title4.fromLocal8Bit("图像组");
optionBar::optionBar(QWidget * parent) : QWidget(parent) {
	setFixedHeight(parent->height()-50);//30
	setFixedWidth(120);
	QPalette pal(palette()); pal.setColor(QPalette::Window, QColor(42, 45, 76));//(241, 241, 241));
	setAutoFillBackground(true);
	setPalette(pal);
	setMouseTracking(true);

	maxButtonNum=10;
	buttonList=new MyButton*[maxButtonNum];
	idList = new int[maxButtonNum];
	buttonNum=0;
	selectedId=0;

	addButton(title1);
	addButton(title2);
	addButton(title3);
	addButton(title4);

	//pMyButton = new  MyButton(this);
	//MyButton *pMyButton2 = new  MyButton(this);
	//pMyButton2->move(0, 50);
	//connect(pMyButton, SIGNAL(clicked()), this, SLOT(onClicked()));
}

optionBar::~optionBar() {
	
}

bool optionBar::addButton(QString & name)
{
	if (buttonNum >= maxButtonNum) { return false; }
	buttonList[buttonNum] = new  MyButton(this, name);
	MyButton *pButton = buttonList[buttonNum];
	installEventFilter(pButton);
	setWindowTitle(name);
	idList[buttonNum] = pButton->getId();//映射
	pButton->move(0, buttonNum * pButton->height());
	connect(pButton, SIGNAL(clicked()), this, SLOT(onClicked()));
	connect(pButton, SIGNAL(clicked()), this->window(), SLOT(onClicked()));
	buttonNum++;
}

const int * const & optionBar::getIdList()
{
	return idList;
}
const MyButton * const optionBar::getButton(int i)
{
	return buttonList[i];
}
int optionBar::getButtonNum()
{
	return buttonNum;
}
void optionBar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	// 反走样
	painter.setRenderHint(QPainter::Antialiasing, true);
	// 设置画笔颜色、宽度
	painter.setPen(QPen(QColor(61, 62, 68), 1));
	//painter.drawRect(0, 0, this->width(), this->height());
	painter.drawLine(0, 0, 0, this->height());
	painter.drawLine(0, this->height(), this->width(), this->height());
}

void optionBar::onClicked()
{
	MyButton *pButton = qobject_cast<MyButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{

		selectedId = pButton->getId();
		updateSelect(selectedId);		
		emit selected(selectedId);
	}
}
/*void optionBar::mouseMoveEvent(QMouseEvent * event)
{
	if ((event->x()<width() - 1) && (event->x()>0) && (event->y()<50 ) && (event->y()>0))
		emit selected(true);
	else
		emit selected(false);
}*/ 

