#pragma once
#include <QWidget>
#include "ui_optionbar.h"
#include<qlabel.h>
#include<QMessageBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QtGui/QMouseEvent>
#include <QPushButton>
#include <QPainter>

#include "mybutton.hpp"
class optionBar : public QWidget {
	Q_OBJECT

public:
	optionBar(QWidget * parent = Q_NULLPTR);
	~optionBar();
	const int * const &getIdList();
	int getButtonNum();
	const MyButton * const getButton(int i);
signals:
	void selected(int);
private:
	Ui::optionBar ui;
	QVBoxLayout *pLayout;
	QPushButton *pb1;
	QPushButton *pb2;
	MyButton *pMyButton;
//	void mouseMoveEvent(QMouseEvent * event);
	void paintEvent(QPaintEvent *event);
private slots:
	void onClicked();
private:
	MyButton** buttonList;
	int * idList;
	int maxButtonNum;
	int buttonNum;
	int selectedId;
	bool addButton(QString & name);
	void updateSelect(int selectedId)
	{
		for (int i = 0; i < buttonNum; i++)
		{
			if(buttonList[i]->getId() != selectedId)buttonList[i]->flagSelected = 0;
		}
	}

};
