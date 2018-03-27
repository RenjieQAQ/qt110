#pragma once
#include <QWidget>
#include "ui_playerbar.h"
#include<qlabel.h>
#include<QMessageBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QtGui/QMouseEvent>
#include <QPushButton>
#include <QPainter>
#include <qbitmap.h>
class playerBar : public QWidget {
	Q_OBJECT

public:
	playerBar(QWidget * parent = Q_NULLPTR);
	~playerBar();
	bool stopFlag;
	bool playFlag;
	bool saveFlag;
//signals:
//	void clicked(bool);
protected slots:
	void mouseMoveEvent(QMouseEvent * event);
//	void mousePressEvent(QMouseEvent *event);
	void onClicked();

private:
	Ui::playerBar ui;
	QPushButton *pButtonPlay;
	QPushButton *pButtonStop;
	QPushButton *pButtonSave;
};
