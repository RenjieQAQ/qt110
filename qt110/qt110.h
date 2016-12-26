#ifndef QT110_H
#define QT110_H

#include <QtWidgets/QWidget>
#include "ui_qt110.h"

class qt110 : public QWidget
{
	Q_OBJECT

public:
	qt110(QWidget *parent = 0);
	~qt110();

private:
	Ui::qt110Class ui;
};

#endif // QT110_H
