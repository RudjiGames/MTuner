/********************************************************************************
** Form generated from reading UI file 'grouplist.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GROUPLIST_UI_H
#define GROUPLIST_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "../src/bigtable.h"

QT_BEGIN_NAMESPACE

class Ui_GroupListWidget
{
public:
    QGridLayout *gridLayout;
    BigTable *bigTableWidget;

    void setupUi(QWidget *GroupListWidget)
    {
        if (GroupListWidget->objectName().isEmpty())
            GroupListWidget->setObjectName(QStringLiteral("GroupListWidget"));
        GroupListWidget->resize(897, 614);
        gridLayout = new QGridLayout(GroupListWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        bigTableWidget = new BigTable(GroupListWidget);
        bigTableWidget->setObjectName(QStringLiteral("bigTableWidget"));

        gridLayout->addWidget(bigTableWidget, 0, 0, 1, 1);


        retranslateUi(GroupListWidget);

        QMetaObject::connectSlotsByName(GroupListWidget);
    } // setupUi

    void retranslateUi(QWidget *GroupListWidget)
    {
        GroupListWidget->setWindowTitle(QApplication::translate("GroupListWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GroupListWidget: public Ui_GroupListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GROUPLIST_UI_H
