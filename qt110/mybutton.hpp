#pragma once
#include <QWidget>
#include<qlabel.h>
#include<QMessageBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QtGui/QMouseEvent>
#include <QPushButton>
#include <QPainter>
#include<qstring.h>

#include "GeneratedFiles/ui_mybutton.h"

class MyButton : public QWidget {
	Q_OBJECT

public:
	MyButton(QWidget * parent = Q_NULLPTR, QString & buttonName= QString("button"));
	~MyButton();
	int getId();
	bool isSelected();
	bool flagSelected;
signals:
	void clicked();
private:
	Ui::MyButton ui;
	void paintEvent(QPaintEvent *event);
protected:
	void mousePressEvent(QMouseEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
//	void mouseMoveEvent(QMouseEvent * event);
private slots:
	void changeUI(int id);
private:
	static int buttonNum;
	QLabel *m_pTitleLabel;
	QString name;
	int id;
};
