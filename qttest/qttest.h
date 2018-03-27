#ifndef QTTEST_H
#define QTTEST_H

#include <QtWidgets/QWidget>
#include "ui_qttest.h"

class qttest : public QWidget
{
	Q_OBJECT

public:
	qttest(QWidget *parent = 0);
	~qttest();
public slots:
	void showWindowSized();
private:
	Ui::qttestClass ui;
};

#endif // QTTEST_H
