/********************************************************************************
** Form generated from reading UI file 'centralwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CENTRALWIDGET_UI_H
#define CENTRALWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CentralWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *CentralWidget)
    {
        if (CentralWidget->objectName().isEmpty())
            CentralWidget->setObjectName(QStringLiteral("CentralWidget"));
        CentralWidget->resize(1084, 732);
        gridLayout = new QGridLayout(CentralWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(CentralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(true);

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(CentralWidget);

        QMetaObject::connectSlotsByName(CentralWidget);
    } // setupUi

    void retranslateUi(QWidget *CentralWidget)
    {
        CentralWidget->setWindowTitle(QApplication::translate("CentralWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CentralWidget: public Ui_CentralWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CENTRALWIDGET_UI_H
