/********************************************************************************
** Form generated from reading UI file 'binloaderview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BINLOADERVIEW_UI_H
#define BINLOADERVIEW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../src/grouplistwidget.h"
#include "../src/hotspots.h"
#include "../src/operationslist.h"
#include "../src/stacktreewidget.h"
#include "../src/treemap.h"

QT_BEGIN_NAMESPACE

class Ui_BinLoaderView
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *Operations;
    QGridLayout *gridLayout;
    OperationsList *operationsListWidget;
    QWidget *GroupedView;
    QGridLayout *gridLayout_4;
    GroupList *groupListWidget;
    QWidget *CallStackTree;
    QGridLayout *gridLayout_3;
    StackTreeWidget *stackTree;
    QWidget *TreeMap;
    QGridLayout *gridLayout_2;
    TreeMapWidget *treeMapWidget;
    QWidget *Hotspots;
    QGridLayout *gridLayout_5;
    HotspotsWidget *hotspotsWidget;

    void setupUi(QWidget *BinLoaderView)
    {
        if (BinLoaderView->objectName().isEmpty())
            BinLoaderView->setObjectName(QStringLiteral("BinLoaderView"));
        BinLoaderView->resize(979, 702);
        verticalLayout = new QVBoxLayout(BinLoaderView);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(BinLoaderView);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Operations = new QWidget();
        Operations->setObjectName(QStringLiteral("Operations"));
        gridLayout = new QGridLayout(Operations);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        operationsListWidget = new OperationsList(Operations);
        operationsListWidget->setObjectName(QStringLiteral("operationsListWidget"));

        gridLayout->addWidget(operationsListWidget, 0, 0, 1, 1);

        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/List64.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/MTuner/resources/images/ListSelected64.png"), QSize(), QIcon::Active, QIcon::On);
        tabWidget->addTab(Operations, icon, QString());
        GroupedView = new QWidget();
        GroupedView->setObjectName(QStringLiteral("GroupedView"));
        gridLayout_4 = new QGridLayout(GroupedView);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupListWidget = new GroupList(GroupedView);
        groupListWidget->setObjectName(QStringLiteral("groupListWidget"));

        gridLayout_4->addWidget(groupListWidget, 0, 0, 1, 1);

        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MTuner/resources/images/Group64.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/MTuner/resources/images/GroupSelected64.png"), QSize(), QIcon::Active, QIcon::On);
        tabWidget->addTab(GroupedView, icon1, QString());
        CallStackTree = new QWidget();
        CallStackTree->setObjectName(QStringLiteral("CallStackTree"));
        gridLayout_3 = new QGridLayout(CallStackTree);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        stackTree = new StackTreeWidget(CallStackTree);
        stackTree->setObjectName(QStringLiteral("stackTree"));

        gridLayout_3->addWidget(stackTree, 0, 0, 1, 1);

        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MTuner/resources/images/StackTree64.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":/MTuner/resources/images/StackTreeSelected64.png"), QSize(), QIcon::Active, QIcon::On);
        tabWidget->addTab(CallStackTree, icon2, QString());
        TreeMap = new QWidget();
        TreeMap->setObjectName(QStringLiteral("TreeMap"));
        gridLayout_2 = new QGridLayout(TreeMap);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        treeMapWidget = new TreeMapWidget(TreeMap);
        treeMapWidget->setObjectName(QStringLiteral("treeMapWidget"));

        gridLayout_2->addWidget(treeMapWidget, 0, 0, 1, 1);

        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MTuner/resources/images/TreeMap64.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QStringLiteral(":/MTuner/resources/images/TreeMapSelected64.png"), QSize(), QIcon::Active, QIcon::On);
        tabWidget->addTab(TreeMap, icon3, QString());
        Hotspots = new QWidget();
        Hotspots->setObjectName(QStringLiteral("Hotspots"));
        gridLayout_5 = new QGridLayout(Hotspots);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        hotspotsWidget = new HotspotsWidget(Hotspots);
        hotspotsWidget->setObjectName(QStringLiteral("hotspotsWidget"));

        gridLayout_5->addWidget(hotspotsWidget, 0, 0, 1, 1);

        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MTuner/resources/images/Flame64.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QStringLiteral(":/MTuner/resources/images/FlameSelected64.png"), QSize(), QIcon::Active, QIcon::On);
        tabWidget->addTab(Hotspots, icon4, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(BinLoaderView);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(BinLoaderView);
    } // setupUi

    void retranslateUi(QWidget *BinLoaderView)
    {
        BinLoaderView->setWindowTitle(QApplication::translate("BinLoaderView", "Form", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Operations), QApplication::translate("BinLoaderView", "Operations", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(GroupedView), QApplication::translate("BinLoaderView", "Grouped view", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(CallStackTree), QApplication::translate("BinLoaderView", "Call Stack Tree", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(TreeMap), QApplication::translate("BinLoaderView", "Tree Map", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Hotspots), QApplication::translate("BinLoaderView", "Hotspots", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BinLoaderView: public Ui_BinLoaderView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BINLOADERVIEW_UI_H
