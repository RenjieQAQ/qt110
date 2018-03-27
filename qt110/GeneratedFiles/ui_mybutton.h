/********************************************************************************
** Form generated from reading UI file 'mybutton.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYBUTTON_H
#define UI_MYBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyButton
{
public:

    void setupUi(QWidget *MyButton)
    {
        if (MyButton->objectName().isEmpty())
            MyButton->setObjectName(QStringLiteral("MyButton"));
        MyButton->resize(94, 25);
        QFont font;
        font.setFamily(QStringLiteral("Roman"));
        MyButton->setFont(font);

        retranslateUi(MyButton);

        QMetaObject::connectSlotsByName(MyButton);
    } // setupUi

    void retranslateUi(QWidget *MyButton)
    {
        MyButton->setWindowTitle(QApplication::translate("MyButton", "MyButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyButton: public Ui_MyButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYBUTTON_H
