/********************************************************************************
** Form generated from reading UI file 'qttest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTEST_H
#define UI_QTTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qttestClass
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *TestButt;
    QPushButton *MaximizeButt;
    QPushButton *MinimazeButt;
    QTextEdit *myout;
    QFrame *frame;
    QWidget *widget;
    QFrame *frame_2;

    void setupUi(QWidget *qttestClass)
    {
        if (qttestClass->objectName().isEmpty())
            qttestClass->setObjectName(QStringLiteral("qttestClass"));
        qttestClass->setWindowModality(Qt::NonModal);
        qttestClass->resize(600, 511);
        qttestClass->setMouseTracking(false);
        gridLayoutWidget = new QWidget(qttestClass);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(90, 160, 401, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        TestButt = new QPushButton(gridLayoutWidget);
        TestButt->setObjectName(QStringLiteral("TestButt"));

        horizontalLayout->addWidget(TestButt);

        MaximizeButt = new QPushButton(gridLayoutWidget);
        MaximizeButt->setObjectName(QStringLiteral("MaximizeButt"));

        horizontalLayout->addWidget(MaximizeButt);

        MinimazeButt = new QPushButton(gridLayoutWidget);
        MinimazeButt->setObjectName(QStringLiteral("MinimazeButt"));

        horizontalLayout->addWidget(MinimazeButt);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        myout = new QTextEdit(gridLayoutWidget);
        myout->setObjectName(QStringLiteral("myout"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(myout->sizePolicy().hasHeightForWidth());
        myout->setSizePolicy(sizePolicy);
        myout->setReadOnly(false);

        gridLayout->addWidget(myout, 1, 0, 1, 1);

        frame = new QFrame(gridLayoutWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 0, 0, 1, 1);

        widget = new QWidget(qttestClass);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(140, 40, 120, 80));
        frame_2 = new QFrame(qttestClass);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(320, 40, 120, 80));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);

        retranslateUi(qttestClass);
        QObject::connect(TestButt, SIGNAL(clicked()), qttestClass, SLOT(close()));
        QObject::connect(MaximizeButt, SIGNAL(clicked()), qttestClass, SLOT(showWindowSized()));
        QObject::connect(MinimazeButt, SIGNAL(clicked(bool)), qttestClass, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(qttestClass);
    } // setupUi

    void retranslateUi(QWidget *qttestClass)
    {
        qttestClass->setWindowTitle(QApplication::translate("qttestClass", "qttest", Q_NULLPTR));
        TestButt->setText(QApplication::translate("qttestClass", "Test", Q_NULLPTR));
        MaximizeButt->setText(QApplication::translate("qttestClass", "Test2", Q_NULLPTR));
        MinimazeButt->setText(QApplication::translate("qttestClass", "\346\234\200\345\260\217\345\214\226", Q_NULLPTR));
        myout->setPlaceholderText(QApplication::translate("qttestClass", "abc", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qttestClass: public Ui_qttestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST_H
