/********************************************************************************
** Form generated from reading UI file 'heapswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef HEAPSWIDGET_UI_H
#define HEAPSWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HeapsWidget
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *HeapsWidget)
    {
        if (HeapsWidget->objectName().isEmpty())
            HeapsWidget->setObjectName(QStringLiteral("HeapsWidget"));
        HeapsWidget->resize(302, 316);
        gridLayout = new QGridLayout(HeapsWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(HeapsWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setFocusPolicy(Qt::NoFocus);
        treeWidget->setColumnCount(2);
        treeWidget->header()->setDefaultSectionSize(100);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);


        retranslateUi(HeapsWidget);

        QMetaObject::connectSlotsByName(HeapsWidget);
    } // setupUi

    void retranslateUi(QWidget *HeapsWidget)
    {
        HeapsWidget->setWindowTitle(QApplication::translate("HeapsWidget", "Form", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("HeapsWidget", "Name", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("HeapsWidget", "Handle", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HeapsWidget: public Ui_HeapsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // HEAPSWIDGET_UI_H
