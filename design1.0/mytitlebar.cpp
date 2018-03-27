#include "mytitlebar.h"
#include <QtGui/QMouseEvent>
//#include <QtGui/QApplication>

char styleSheetLabel[] = "QLabel {  color: rgb(120,120,120);border-style: none;  "
									" font: 10pt \"����\" ;} ";
myTitleBar::myTitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);



	//setBaseSize(120, 50);
	resize(parent->width(), 40);
	setMaximumHeight(80);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setSizePolicy(sizePolicy);

	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(204, 204, 191));//61, 62, 68
	setAutoFillBackground(true);
	setPalette(pal);
	

	logo = new QWidget(this);
	logo->setMinimumHeight(80);
	logo->setMinimumWidth(129);
	logo->setMaximumWidth(160);
	logo->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(251, 85, 78));
	logo->setPalette(pal);
	sizePolicy.setHorizontalStretch(1);
	logo->setSizePolicy(sizePolicy);

	logoText = new QLabel(logo);
	logoText->setText(QStringLiteral("V2.15"));
	logoLayout = new  QHBoxLayout(logo);
	logoLayout->addStretch();
	logoLayout->addWidget(logoText);
	logoLayout->addStretch();
	QFont ft;
	ft.setBold(true);
	//ft.setFamily(QStringLiteral("����"));
	ft.setPointSize(18);
	logoText->setFont(ft);
	pal.setColor(QPalette::WindowText, Qt::white);
	logoText->setPalette(pal);

	//�������Ŀհ�
	blank = new QWidget(this);
	blank->setMinimumHeight(80);
	blank->setMinimumWidth(129);
	blank->setAutoFillBackground(true);

	//QLinearGradient linear(QPointF(80, 80), QPointF(150, 150));
	//QLinearGradient linear(blank->rect().topLeft(), blank->rect().bottomRight());
	//QLinearGradient linear(QPoint(blank->rect().left()+80, blank->rect().top()), blank->rect().bottomRight());
	QLinearGradient linear(QPointF(0, 0), QPointF(700, 0));
	linear.setColorAt(1, QColor(204,205, 191));
	linear.setColorAt(0.7, QColor(215, 217, 215));
	linear.setColorAt(0.4, QColor(193, 195, 198));
	linear.setColorAt(0.2, QColor(215, 217, 215));
	linear.setColorAt(0, QColor(185, 183, 176));
	pal.setBrush(backgroundRole(),QBrush(linear));
	//pal.setColor(QPalette::Window, QColor(204, 204, 191));

	blank->setPalette(pal);
	sizePolicy.setHorizontalStretch(5);
	blank->setSizePolicy(sizePolicy);

	layout = new QHBoxLayout(this);
	layout->addWidget(logo);
	layout->addWidget(blank);
	layout->setMargin(0);
	layout->setSpacing(0);

	//button
	QSizePolicy sizeFixed(QSizePolicy::Fixed, QSizePolicy::Fixed);
	//button
	CloseButt = new QPushButton();
	CloseButt->setText(QStringLiteral("�ر�"));
	CloseButt->setSizePolicy(sizeFixed);
	CloseButt->setMinimumHeight(30);
	CloseButt->setMaximumWidth(45);
	//	CloseButt->setStyleSheet(styleSheet1);



	MinimazeButt = new QPushButton();
	MinimazeButt->setText(QStringLiteral("��С��"));
	MinimazeButt->setSizePolicy(sizeFixed);
	MinimazeButt->setMinimumHeight(30);
	MinimazeButt->setMaximumWidth(45);
	//	MinimazeButt->setStyleSheet(styleSheet2);

	MaximizeButt = new QPushButton();
	MaximizeButt->setText(QString::fromLocal8Bit("���"));
	MaximizeButt->setSizePolicy(sizeFixed);
	MaximizeButt->setMinimumHeight(30);
	MaximizeButt->setMaximumWidth(45);
	//	MaximizeButt->setStyleSheet(styleSheet2);

	//connect(CloseButt, SIGNAL(clicked()), this, SLOT(test()));
	QObject::connect(CloseButt, SIGNAL(clicked()), this->parent(), SLOT(close()));
	QObject::connect(MaximizeButt, SIGNAL(clicked()), this->parent(), SLOT(showWindowSized()));
	QObject::connect(MinimazeButt, SIGNAL(clicked()), this->parent(), SLOT(showMinimized()));

	//ip
	ipLabel = new QLabel();
	ipLabel->setText(QStringLiteral("��������ַ"));
	ipLabel->setStyleSheet(styleSheetLabel);
	hostIpEdit = new QComboBox();
	hostIpEdit->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	hostIpEdit->setMaximumHeight(23);
	hostIpEdit->setMinimumWidth(150);
	hostIpEdit->setEditable(true);
	hostIpList = new QListWidget();
	hostIpList->setFocusPolicy(Qt::NoFocus);

	ifstream file("ip.txt", ios::in | ios::binary); 
	if (!file.is_open()){
		ipNum = 1;
		ip = new string("192.168.231.142");
	}
	else {
		file >> ipNum;
		ip = new string[ipNum];
		for (int i = 0;i < ipNum;i++) {
			file >> ip[i];
		}
	}
	file.close();

	//QFile qfile("ip.txt");
	//QString *qIp;
	//if (!qfile.isOpen()) {
	//	ipNum = 1;
	//	qIp = new QString("192.168.231.142");
	//}
	//else {
	//	QByteArray file_bytearr=qfile.readAll();
	//	file_bytearr.t
	//	ip = new string[ipNum];
	//	for (int i = 0; i < ipNum; i++) {
	//		file >> ip[i];
	//	}
	//}

	pHostIpListItem = new QListWidgetItem*[MAXIPSIZE];
	for (int i = 0;i < ipNum;i++) {
		pHostIpListItem[i] = new QListWidgetItem(hostIpList);
		pHostIpListItem[i]->setText(ip[i].data());
	}
	hostIpList->setItemWidget(pHostIpListItem[0], hostIpEdit);
	//connect(hostIpEdit, SIGNAL(currenTextChanged(QString)), parent, SLOT(addip(QString)));

	hostIpEdit->setModel(hostIpList->model());
	//hostIpEdit->setFocusProxy(hostIpList);

	connectButton = new QPushButton(this);
	connectButton->setText(QStringLiteral("��������"));
	connectButton->setMaximumWidth(50);
	connectButton->setMinimumHeight(30);
	connect(connectButton, SIGNAL(clicked()), parent, SLOT(connectTCP()));

	//�������ڿհ׵ķֲ�
	buttLayout = new QHBoxLayout(blank);
	buttLayout->addWidget(ipLabel);
	buttLayout->addWidget(hostIpEdit);
	buttLayout->addWidget(connectButton);
	buttLayout->addStretch();
	buttLayout->addWidget(CloseButt);
	buttLayout->addWidget(MinimazeButt);
	buttLayout->addWidget(MaximizeButt);
	buttLayout->setContentsMargins(60, 0, 10, 0);
}

myTitleBar::~myTitleBar()
{

}

void myTitleBar:: addip(QString ip) {
	/*int res = 0;
	for (int i = 0; i < hostIpList->count(); i++) {
		if (hostIpList->item(i)->text() == ip) {
			res = 1;
		}
	}
	if (res == 0) {
		pHostIpListItem[ipNum]= new QListWidgetItem(hostIpList);
		pHostIpListItem[ipNum]->setText(ip);
		ipNum++;
	}*/
}

void myTitleBar::add(string & ip) {
	ipNum++;
	ofstream file("ip.txt", ios::out | ios::binary);
	if (!file.is_open()) {
		ipNum = 1;
	}
	else {
		file << ip;
	}
	file.close();
	
}


void myTitleBar::mousePressEvent(QMouseEvent *event)
{
	isMoving = true;
	movePosition = event->globalPos() - this->window()->pos();
	return QWidget::mousePressEvent(event);
}

void myTitleBar::mouseReleaseEvent(QMouseEvent *event) {
	isMoving = false;
}

void myTitleBar::mouseMoveEvent(QMouseEvent *event) {
	//����ƶ��¼���Ҫ�ƶ����ڣ������ƶ��������أ�����Ҫ��ȡ����ƶ��У�������������Ļ�����꣬Ȼ��move��������꣬��ô��ȡ���ꣿ  
	//ͨ���¼�event->globalPos()֪��������꣬��������ȥ�������ڴ���λ�ã����Ǵ�����������Ļ������  
	if (isMoving && (event->buttons() && Qt::LeftButton)//����������
		&& (event->globalPos() - movePosition).manhattanLength() > QApplication::startDragDistance())
	{
		this->window()->move(event->globalPos() - movePosition);
		movePosition = event->globalPos() - this->window()-> pos();
	}
	return QWidget::mouseMoveEvent(event);
}

void myTitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
	if (Qt::WindowState::WindowMaximized == window()->windowState())
		window()->setWindowState(Qt::WindowState::WindowNoState);
	else
		window()->setWindowState(Qt::WindowState::WindowMaximized);
	return QWidget::mouseDoubleClickEvent(event);
}



void myTitleBar::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	//QPainter painter(this);// ������
	//painter.setRenderHint(QPainter::Antialiasing, true);

	//// ���ý���ɫ
	//QLinearGradient linear(QPointF(80, 80), QPointF(150, 150));
	//linear.setColorAt(0, Qt::black);
	//linear.setColorAt(1, Qt::white);

	//// ������ʾģʽ
	////linear.setSpread(QGradient::PadSpread);

	//// ���û�����ɫ�����
	//painter.setPen(QPen(QColor(0, 160, 230), 2));

	//// ���û�ˢ���
	//painter.setBrush(linear);

	//// ������Բ
	//painter.drawRect(QRect(40, 0, 40, 60));

}

void myTitleBar::test() {
	close();
}
