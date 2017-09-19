/********************************************************************************
** Form generated from reading UI file 'treemap.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TREEMAP_UI_H
#define TREEMAP_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../src/treemapview.h"

QT_BEGIN_NAMESPACE

class Ui_TreeMap
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    TreeMapView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBoxType;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *TreeMap)
    {
        if (TreeMap->objectName().isEmpty())
            TreeMap->setObjectName(QStringLiteral("TreeMap"));
        TreeMap->resize(844, 678);
        TreeMap->setMouseTracking(true);
        gridLayout = new QGridLayout(TreeMap);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new TreeMapView(TreeMap);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(208, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        comboBoxType = new QComboBox(TreeMap);
        comboBoxType->setObjectName(QStringLiteral("comboBoxType"));
        comboBoxType->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(comboBoxType);

        horizontalSpacer = new QSpacerItem(208, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(TreeMap);

        QMetaObject::connectSlotsByName(TreeMap);
    } // setupUi

    void retranslateUi(QWidget *TreeMap)
    {
        TreeMap->setWindowTitle(QApplication::translate("TreeMap", "Form", Q_NULLPTR));
        comboBoxType->clear();
        comboBoxType->insertItems(0, QStringList()
         << QApplication::translate("TreeMap", "Memory usage", Q_NULLPTR)
         << QApplication::translate("TreeMap", "Memory usage peak", Q_NULLPTR)
         << QApplication::translate("TreeMap", "Allocation overhead", Q_NULLPTR)
         << QApplication::translate("TreeMap", "Allocation overhead peak", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class TreeMap: public Ui_TreeMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TREEMAP_UI_H
