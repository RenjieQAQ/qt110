/********************************************************************************
** Form generated from reading UI file 'playerbar.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERBAR_H
#define UI_PLAYERBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playerBar
{
public:

    void setupUi(QWidget *playerBar)
    {
        if (playerBar->objectName().isEmpty())
            playerBar->setObjectName(QStringLiteral("playerBar"));
        playerBar->resize(400, 300);

        retranslateUi(playerBar);

        QMetaObject::connectSlotsByName(playerBar);
    } // setupUi

    void retranslateUi(QWidget *playerBar)
    {
        playerBar->setWindowTitle(QApplication::translate("playerBar", "playerBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class playerBar: public Ui_playerBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERBAR_H
