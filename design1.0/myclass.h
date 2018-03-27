#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtWidgets/QWidget>
#include "ui_myclass.h"
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QTNetwork/Qtnetwork>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedLayout>
#include "MyDebugWidget.h"
#include "MyFsnWidget.h"
#include "cisDebugWidget.h"
#include "fsnMsg.h"
#include "decodeFrame.h"

QT_BEGIN_NAMESPACE

#include "mytitlebar.h"

QString &fomatData(QByteArray &arr);
class MyClass : public QWidget
{
	Q_OBJECT
	QListWidgetItem * currentItem;
public:
	MyClass(QWidget *parent = 0);
	~MyClass();

public:
	//title and window
	myTitleBar* titleBar;
	QWidget * window;
	QWidget * function;
	QWidget * blank;
	QVBoxLayout *mainLayout;
	QHBoxLayout *windowLayout;


	MyDebugWidget * debugWidget;
	MyFsnWidget * fsnWidget;
	cisDebugWidget * cisWidget;
	QWidget * tmpwidget;

	//guide
	QListWidget* guideList;
	QListWidgetItem * debugListItem;
	QListWidgetItem * fsnListItem;
	QListWidgetItem * cisListItem;


	//layout
	QStackedLayout *stackLayout;
	QHBoxLayout *textLayout;
	QVBoxLayout * guideLayout;

	QTcpSocket * socket;
	decodeFrame de_frame;
	frameWriter frame_writer;

private:
	Ui::MyClassClass ui;
	void setupLayout();
	void processsBuf(QByteArray& qarray);
	void carryOutCmd(netFrame & frame);
public slots:
	void showWindowSized();
	void guidItemChanged(QListWidgetItem* item);
	//void connectTcp(QString ip);
	void connectTCP();
	//void disconnectTcp();
	void connected();
	void readyread();
	void debugPrint(QString str);
//пе╨е
signals:
	void fsnPkg(const TCP_FSN_Msg* msg);
	void fsnPkg(const TCP_FSN_Msg_Sml* msg);
	void billPkg(billInf& msg);
	void debug(QString str);

};

#endif // MYCLASS_H


