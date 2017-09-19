/********************************************************************************
** Form generated from reading UI file 'tagtree.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TAGTREE_UI_H
#define TAGTREE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tagTree
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeWidget;

    void setupUi(QWidget *tagTree)
    {
        if (tagTree->objectName().isEmpty())
            tagTree->setObjectName(QStringLiteral("tagTree"));
        tagTree->resize(1032, 660);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/StackTree64.png"), QSize(), QIcon::Normal, QIcon::Off);
        tagTree->setWindowIcon(icon);
        gridLayout = new QGridLayout(tagTree);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeView(tagTree);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);


        retranslateUi(tagTree);

        QMetaObject::connectSlotsByName(tagTree);
    } // setupUi

    void retranslateUi(QWidget *tagTree)
    {
        tagTree->setWindowTitle(QApplication::translate("tagTree", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class tagTree: public Ui_tagTree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TAGTREE_UI_H
