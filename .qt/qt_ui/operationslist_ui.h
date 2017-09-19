/********************************************************************************
** Form generated from reading UI file 'operationslist.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef OPERATIONSLIST_UI_H
#define OPERATIONSLIST_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../src/bigtable.h"
#include "../src/operationsearch.h"

QT_BEGIN_NAMESPACE

class Ui_OperationsListWidget
{
public:
    QVBoxLayout *verticalLayout;
    OperationSearch *operationSearchWidget;
    BigTable *bigTableWidget;

    void setupUi(QWidget *OperationsListWidget)
    {
        if (OperationsListWidget->objectName().isEmpty())
            OperationsListWidget->setObjectName(QStringLiteral("OperationsListWidget"));
        OperationsListWidget->resize(1211, 798);
        verticalLayout = new QVBoxLayout(OperationsListWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        operationSearchWidget = new OperationSearch(OperationsListWidget);
        operationSearchWidget->setObjectName(QStringLiteral("operationSearchWidget"));

        verticalLayout->addWidget(operationSearchWidget);

        bigTableWidget = new BigTable(OperationsListWidget);
        bigTableWidget->setObjectName(QStringLiteral("bigTableWidget"));

        verticalLayout->addWidget(bigTableWidget);


        retranslateUi(OperationsListWidget);

        QMetaObject::connectSlotsByName(OperationsListWidget);
    } // setupUi

    void retranslateUi(QWidget *OperationsListWidget)
    {
        OperationsListWidget->setWindowTitle(QApplication::translate("OperationsListWidget", "Operations", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OperationsListWidget: public Ui_OperationsListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // OPERATIONSLIST_UI_H
