/********************************************************************************
** Form generated from reading UI file 'histogram.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef HISTOGRAM_UI_H
#define HISTOGRAM_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../src/histogramview.h"

QT_BEGIN_NAMESPACE

class Ui_HistogramWidgetClass
{
public:
    QVBoxLayout *verticalLayout;
    HistogramView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboType;
    QComboBox *comboHistogram;
    QCheckBox *checkBoxPeaks;

    void setupUi(QWidget *HistogramWidgetClass)
    {
        if (HistogramWidgetClass->objectName().isEmpty())
            HistogramWidgetClass->setObjectName(QStringLiteral("HistogramWidgetClass"));
        HistogramWidgetClass->resize(391, 149);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HistogramWidgetClass->sizePolicy().hasHeightForWidth());
        HistogramWidgetClass->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Histogram64.png"), QSize(), QIcon::Normal, QIcon::Off);
        HistogramWidgetClass->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(HistogramWidgetClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        graphicsView = new HistogramView(HistogramWidgetClass);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setCacheMode(QGraphicsView::CacheBackground);

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        comboType = new QComboBox(HistogramWidgetClass);
        comboType->setObjectName(QStringLiteral("comboType"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboType->sizePolicy().hasHeightForWidth());
        comboType->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(comboType);

        comboHistogram = new QComboBox(HistogramWidgetClass);
        comboHistogram->setObjectName(QStringLiteral("comboHistogram"));
        sizePolicy2.setHeightForWidth(comboHistogram->sizePolicy().hasHeightForWidth());
        comboHistogram->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(comboHistogram);

        checkBoxPeaks = new QCheckBox(HistogramWidgetClass);
        checkBoxPeaks->setObjectName(QStringLiteral("checkBoxPeaks"));

        horizontalLayout->addWidget(checkBoxPeaks);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(HistogramWidgetClass);

        QMetaObject::connectSlotsByName(HistogramWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *HistogramWidgetClass)
    {
        HistogramWidgetClass->setWindowTitle(QApplication::translate("HistogramWidgetClass", "Form", Q_NULLPTR));
        comboType->clear();
        comboType->insertItems(0, QStringList()
         << QApplication::translate("HistogramWidgetClass", "Memory usage", Q_NULLPTR)
         << QApplication::translate("HistogramWidgetClass", "Allocation overhead", Q_NULLPTR)
         << QApplication::translate("HistogramWidgetClass", "Number of allocations", Q_NULLPTR)
        );
        comboHistogram->clear();
        comboHistogram->insertItems(0, QStringList()
         << QApplication::translate("HistogramWidgetClass", "Global histogram", Q_NULLPTR)
         << QApplication::translate("HistogramWidgetClass", "Snapshot histogram", Q_NULLPTR)
         << QApplication::translate("HistogramWidgetClass", "Global and snapshot histogram", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        comboHistogram->setToolTip(QApplication::translate("HistogramWidgetClass", "Select which time range to show histograms for", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        checkBoxPeaks->setToolTip(QApplication::translate("HistogramWidgetClass", "Shows peak values alongside current values", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBoxPeaks->setText(QApplication::translate("HistogramWidgetClass", "Show peaks", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HistogramWidgetClass: public Ui_HistogramWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // HISTOGRAM_UI_H
