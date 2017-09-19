/********************************************************************************
** Form generated from reading UI file 'bigtable.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BIGTABLE_UI_H
#define BIGTABLE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>
#include "../src/bigtabletablewidget.h"

QT_BEGIN_NAMESPACE

class Ui_BigTableWidget
{
public:
    QHBoxLayout *horizontalLayout;
    BigTableTableWidget *tableWidget;
    QScrollBar *verticalScrollBar;

    void setupUi(QWidget *BigTableWidget)
    {
        if (BigTableWidget->objectName().isEmpty())
            BigTableWidget->setObjectName(QStringLiteral("BigTableWidget"));
        BigTableWidget->resize(400, 300);
        BigTableWidget->setFocusPolicy(Qt::StrongFocus);
        horizontalLayout = new QHBoxLayout(BigTableWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new BigTableTableWidget(BigTableWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setTabKeyNavigation(false);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setShowGrid(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(21);
        tableWidget->verticalHeader()->setMinimumSectionSize(21);

        horizontalLayout->addWidget(tableWidget);

        verticalScrollBar = new QScrollBar(BigTableWidget);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalScrollBar);


        retranslateUi(BigTableWidget);

        QMetaObject::connectSlotsByName(BigTableWidget);
    } // setupUi

    void retranslateUi(QWidget *BigTableWidget)
    {
        BigTableWidget->setWindowTitle(QApplication::translate("BigTableWidget", "BigTable", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BigTableWidget: public Ui_BigTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BIGTABLE_UI_H
