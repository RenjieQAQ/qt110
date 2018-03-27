#include "qttest.h"
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTableWidget>

using namespace Qt;
qttest::qttest(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());
	ui.setupUi(this);
	QFrame * pFrame = new QFrame(this);
	QVBoxLayout *pVBoxPlayout = new QVBoxLayout();
	pVBoxPlayout->addWidget(pFrame);
	//setLayout(pVBoxPlayout);
	/*
	QTreeWidget * pTreeWidget = new QTreeWidget(this);
	QTableWidget * pTableWidget = new QTableWidget(this);
	QHBoxLayout *playout = new QHBoxLayout();
	playout->addWidget(pTreeWidget);
	playout->addWidget(pTableWidget);
	playout->setSpacing(10);
	playout->setContentsMargins(10, 10, 10, 10);
	setLayout(playout);
	QSizePolicy treeSizePolicy = pTreeWidget->sizePolicy();
	QSizePolicy tableSizePolicy = pTableWidget->sizePolicy();
	treeSizePolicy.setHorizontalStretch(2);
	tableSizePolicy.setHorizontalStretch(4);
	pTreeWidget->setSizePolicy(treeSizePolicy);
	pTableWidget->setSizePolicy(tableSizePolicy);*/

}

qttest::~qttest()
{

}

//slot function

void qttest::showWindowSized() {
	if(WindowMaximized==this->windowState())
		this->setWindowState(WindowNoState);
	else
		this->setWindowState(WindowMaximized);
}
