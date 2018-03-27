#include "myclass.h"

char guideStyleSheet[] = "QListWidget { background-color: rgb(61, 74, 83); "
										"color: rgb(255, 255, 255);border-style: none;  "
										" font: 14pt \"������\" ; "
										" }"
						"QListWidget::Item {min-height: 80px;border-left-color: rgb(255, 255, 255)}"
						"QListWidget::item:selected{color:rgb(251, 85, 78);border-style: none;  }"
						"QListWidget::item:hover{background: rgb(80, 90, 100);color:rgb(176, 233, 72);  }";

MyClass::MyClass(QWidget *parent)
	: QWidget(parent), frame_writer(&socket)
{
	ui.setupUi(this);	//��������
	setWindowIcon(QIcon("icon/money.ico"));
	setMinimumSize(1100, 1100*0.618+30);
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());
	titleBar = new myTitleBar(this); //�Զ��������

    //network
	socket = NULL;

	//������
	window = new QWidget(this);		
	window->resize(width(), height() - titleBar->height());
	QPalette pal(palette());
	pal.setColor(QPalette::Window, QColor(255, 255, 255));//61, 62, 68
	window->setAutoFillBackground(true);
	window->setPalette(pal);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setSizePolicy(sizePolicy);



	//������
	blank = new QWidget(window);
	sizePolicy.setHorizontalStretch(5);
	blank->setSizePolicy(sizePolicy);
	blank->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(254, 255, 255));
	blank->setPalette(pal);

	debugWidget = new MyDebugWidget(this);	//�Ҳ�Ŀհ�������������
	sizePolicy.setHorizontalStretch(5);
	debugWidget->setSizePolicy(sizePolicy);
	debugWidget->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(254, 255, 255));
	debugWidget->setPalette(pal);

	//������
	function = new QWidget(window);	//���Ĺ���ѡ����
	function->setMaximumWidth(160);
	sizePolicy.setHorizontalStretch(1);
	function->setSizePolicy(sizePolicy);
	function->setAutoFillBackground(true);
	pal.setColor(QPalette::Window, QColor(61, 74, 83));
	function->setPalette(pal);
	//����������
	guideLayout =new QVBoxLayout(function);
	guideList = new QListWidget;
	debugListItem = new QListWidgetItem(QStringLiteral("ͨ�������"), guideList);
	debugListItem->setTextAlignment(Qt::AlignCenter);
	fsnListItem = new QListWidgetItem(QStringLiteral("FSNϵͳ"), guideList);
	fsnListItem->setTextAlignment(Qt::AlignCenter);
	cisListItem = new QListWidgetItem(QStringLiteral("CIS����"), guideList);

	cisListItem->setTextAlignment(Qt::AlignCenter);
	guideList->insertItem(1, debugListItem);
	guideList->insertItem(2, fsnListItem);
	guideList->insertItem(3, cisListItem);

	guideList->setItemSelected(debugListItem, true);//����Ĭ��ѡ��
	guideList->setStyleSheet(guideStyleSheet);
	guideList->setFocusPolicy(Qt::NoFocus);
	currentItem = debugListItem;	//ͬ��Ĭ��ѡ��
	connect(guideList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(guidItemChanged(QListWidgetItem*)));
	guideLayout->addWidget(guideList);
	guideLayout->setMargin(0);

    setupLayout();

	/*connect(this, SIGNAL(fsnPkg(const TCP_FSN_Msg*)), fsnWidget, SLOT(updateTable(const TCP_FSN_Msg*)));
	connect(this, SIGNAL(fsnPkg(const TCP_FSN_Msg_Sml*)), fsnWidget, SLOT(updateTable(const TCP_FSN_Msg_Sml*)));*/
	connect(this, SIGNAL(billPkg(billInf&)), fsnWidget, SLOT(updateTable(billInf&)));


	//debugWidget->print("%d",sizeof(MoneyResult));
	//billInf bill;
	//bill.moneyResult.width = 100;
	//emit billPkg(billInf());
	//emit billPkg(bill);
	//emit billPkg(billInf(50));
	//emit billPkg(billInf(20));
}

MyClass::~MyClass()
{

}


void MyClass::setupLayout() {

	mainLayout = new QVBoxLayout(this);		//�������壺��������������
	windowLayout = new QHBoxLayout(window); //���������ڣ������������Ĵ�
	stackLayout = new QStackedLayout(blank);

	//���ñ������봰�ڽṹ
	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(titleBar);
	mainLayout->addWidget(window);

	windowLayout->addWidget(function);
	windowLayout->addWidget(blank);
	windowLayout->setMargin(0);
	windowLayout->setSpacing(0);

	//tmpwidget = new QWidget();
	//tmpwidget->setAutoFillBackground(true);
	//QPalette pal(palette());
	//pal.setColor(QPalette::Window, QColor(0, 255, 255));
	//tmpwidget->setPalette(pal);

	fsnWidget = new MyFsnWidget(this);
	cisWidget= new cisDebugWidget(this,&socket);

	stackLayout->addWidget(debugWidget);
	stackLayout->addWidget(fsnWidget);
	stackLayout->addWidget(cisWidget);



}









/*
��󻯰�����Ӧ�Ĳۺ���
*/
void MyClass::showWindowSized() {
	if (Qt::WindowState::WindowMaximized == this->windowState())
		this->setWindowState(Qt::WindowState::WindowNoState);
	else
		this->setWindowState(Qt::WindowState::WindowMaximized);
}

/*
������ѡ��ı�-�ۺ���
*/
void MyClass::guidItemChanged(QListWidgetItem* item) {
	if (item != currentItem) {//�Լ�
		currentItem = item;
		//debugWidget-> print(QStringLiteral("\"") + item->text() + QStringLiteral("\"ѡ��\n"));
		if (debugListItem == item) {
			stackLayout->setCurrentWidget(debugWidget);
		}
		if (fsnListItem == item) {
			stackLayout->setCurrentWidget(fsnWidget);
		}
		if (cisListItem == item) {
			stackLayout->setCurrentWidget(cisWidget);
		}
	}
}


/*
��������
*/
void MyClass::processsBuf(QByteArray& qarray) {
	//print(QString().sprintf("receive %d char", qarray.length()));

}
/*
TCP����/�Ͽ���ť�Ĳۺ���
*/
void MyClass::connectTCP() {
	if (socket == NULL) {
		titleBar->connectButton->setText(QStringLiteral("�Ͽ�����"));
		debugWidget->print("ip:" + titleBar->hostIpEdit->currentText());
		debugWidget->print("������������...\n");
		//emit connectNet(hostIpListItem->text());
		socket = new QTcpSocket(this);
		socket->connectToHost(titleBar->hostIpEdit->currentText(), 11910, QTcpSocket::ReadWrite);//80100
		QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	}
	else if (socket->isOpen()) {
		titleBar->hostIpEdit->setEditable(true);
		titleBar->hostIpEdit->setDisabled(false);
		titleBar->hostIpEdit->setFocusPolicy(Qt::StrongFocus);
		titleBar->connectButton->setText(QStringLiteral("��������"));
		socket->disconnectFromHost();
		socket->waitForDisconnected(400);
		socket->close();
		//emit disconnectNet();
		debugWidget->print("�����ѶϿ�...\n");
		delete socket;
		socket = NULL;
	}
}

/*
�ɹ�������TCP�������Ĳۺ��������ڴ�ӡ�ɹ��Լ���������
*/
void MyClass::connected() {
	//debugWidget->myout->setText(myout->toPlainText() + QStringLiteral("���ӳɹ�\n"));
	debugWidget->print("���ӳɹ�\n");
	titleBar->hostIpEdit->setEditable(false);
	titleBar->hostIpEdit->setDisabled(true);
	titleBar->hostIpEdit->setFocusPolicy(Qt::NoFocus);
	de_frame.clear();
//	titleBar->addip(titleBar->hostIpEdit->currentText());
	socket->write("hello linux\n");
	connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyread()));
}


/*
���յ�TCP���ݵĲۺ���
*/
void MyClass::readyread()
{
	QByteArray arr = this->socket->readAll();

//	debugWidget->print(fomatData(arr));

	de_frame.inputs((arr.data()), arr.size()) ;
	while (!de_frame.isEmpty()) {
		if (de_frame.decode() == 0) {
		/*	if((de_frame.getFrame().cmd>>8)==0x00)
				emit billPkg(*(billInf*)(uint8_t *)(de_frame.getFrame().data));
			if ((de_frame.getFrame().cmd >> 8) == 0x02) {
				debugWidget->print("0x%x\n", de_frame.getFrame().cmd);
				frame_writer.cmdFix(0x01);
			}
			if ((de_frame.getFrame().cmd >> 8) == 0xa0) {
				titleBar->hostIpEdit->setEditable(true);
				titleBar->hostIpEdit->setDisabled(false);
				titleBar->hostIpEdit->setFocusPolicy(Qt::StrongFocus);
				titleBar->connectButton->setText(QStringLiteral("��������"));
				socket->disconnectFromHost();
				socket->waitForDisconnected(400);
				socket->close();
				debugWidget->print("�����ѶϿ�...\n");
				delete socket;
				socket = NULL;
			}*/
			carryOutCmd(de_frame.getFrame());
		}
		else {

		}
	}
}

void MyClass::carryOutCmd(netFrame & frame) {
	switch (frame.cmd >> 8) {
	case CMD_BILLINF:
		emit billPkg(*(billInf*)(uint8_t *)(de_frame.getFrame().data));
		break;
	case CMD_FPGA:
		break;
	case CMD_FIX:

		break;
	case CMD_IMG:
		break; 
	case CMD_CLOSENET:
		titleBar->hostIpEdit->setEditable(true);
		titleBar->hostIpEdit->setDisabled(false);
		titleBar->hostIpEdit->setFocusPolicy(Qt::StrongFocus);
		titleBar->connectButton->setText(QStringLiteral("��������"));
		socket->disconnectFromHost();
		socket->waitForDisconnected(400);
		socket->close();
		debugWidget->print("�����ѶϿ�...\n");
		delete socket;
		socket = NULL;
		break;
	default:
		break;

	}
}

void MyClass::debugPrint(QString str) {
	debugWidget->print(str+"\n");
}

QString str = "";
QString &fomatData(QByteArray &arr) {
	str.clear();
	for (int i = 0; i < arr.length(); i++) {
		if (i % 10 == 0) {
			str += "[";
			str += QString("%1").arg(i / 10, 2, 10, QLatin1Char('0'));
			str += "]:";
		}
		str += QString("%1").arg((unsigned char)arr.at(i), 2, 16, QLatin1Char('0'));
		str += " ";
		if (i % 10 == 9)
			str += "\n";
	}
	return str;
}