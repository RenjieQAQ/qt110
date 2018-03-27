/********************************************************************************
** Form generated from reading UI file 'optionbar.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONBAR_H
#define UI_OPTIONBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optionBar
{
public:

    void setupUi(QWidget *optionBar)
    {
        if (optionBar->objectName().isEmpty())
            optionBar->setObjectName(QStringLiteral("optionBar"));
        optionBar->resize(400, 300);

        retranslateUi(optionBar);

        QMetaObject::connectSlotsByName(optionBar);
    } // setupUi

    void retranslateUi(QWidget *optionBar)
    {
        optionBar->setWindowTitle(QApplication::translate("optionBar", "optionBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class optionBar: public Ui_optionBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONBAR_H
