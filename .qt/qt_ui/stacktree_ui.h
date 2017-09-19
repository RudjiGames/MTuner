/********************************************************************************
** Form generated from reading UI file 'stacktree.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STACKTREE_UI_H
#define STACKTREE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stackTree
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeWidget;

    void setupUi(QWidget *stackTree)
    {
        if (stackTree->objectName().isEmpty())
            stackTree->setObjectName(QStringLiteral("stackTree"));
        stackTree->resize(1032, 660);
        gridLayout = new QGridLayout(stackTree);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeView(stackTree);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);


        retranslateUi(stackTree);

        QMetaObject::connectSlotsByName(stackTree);
    } // setupUi

    void retranslateUi(QWidget *stackTree)
    {
        stackTree->setWindowTitle(QApplication::translate("stackTree", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class stackTree: public Ui_stackTree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // STACKTREE_UI_H
