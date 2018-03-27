#pragma once

#include <QWidget>
#include "ui_MyDebugWidget.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QTNetwork/Qtnetwork>
#include <QComboBox>
#include <QListWidget>
#include "MyFsnWidget.h"

class MyDebugWidget : public QWidget
{
	Q_OBJECT
public:
	//text edit
	QTextEdit *myout;
	QTextEdit *myin;
	QComboBox  *hostIpEdit;
	QListWidget *hostIpList;
	QListWidgetItem *hostIpListItem;

	/* window element below*/
	//button
	QPushButton *sendButton;
	QPushButton *textClearButton;
	QPushButton *connectButton;


	QGridLayout *blankLayout;


	QTcpSocket * socket;


public slots:
	void sendText();
	void autoScroll();
	void clearText();
//	void connected();
//	void readyread();
//	void connectTCP();

	void test();
public:
	MyDebugWidget(QWidget *parent = Q_NULLPTR);
	~MyDebugWidget();
	void print(char * s);
	void print(QString  s);
	void print(char * s, uint32_t i);
	void print(char * fmt, QString  s);

private:
	void setupWidget();

private:
	Ui::MyDebugWidget ui;
};

