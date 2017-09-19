/********************************************************************************
** Form generated from reading UI file 'hotspot.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef HOTSPOT_UI_H
#define HOTSPOT_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hotspotWidget
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTableWidget *tablePeak;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QTableWidget *tablePeakCount;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableUsage;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTableWidget *tableLeaks;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *hotspotWidget)
    {
        if (hotspotWidget->objectName().isEmpty())
            hotspotWidget->setObjectName(QStringLiteral("hotspotWidget"));
        hotspotWidget->resize(1176, 957);
        verticalLayout_5 = new QVBoxLayout(hotspotWidget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(hotspotWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        tablePeak = new QTableWidget(hotspotWidget);
        if (tablePeak->columnCount() < 5)
            tablePeak->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablePeak->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablePeak->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablePeak->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablePeak->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablePeak->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tablePeak->setObjectName(QStringLiteral("tablePeak"));
        tablePeak->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablePeak->setSelectionMode(QAbstractItemView::SingleSelection);
        tablePeak->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePeak->setShowGrid(false);
        tablePeak->verticalHeader()->setVisible(false);
        tablePeak->verticalHeader()->setDefaultSectionSize(21);

        verticalLayout_2->addWidget(tablePeak);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_4 = new QLabel(hotspotWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout_4->addWidget(label_4);

        tablePeakCount = new QTableWidget(hotspotWidget);
        if (tablePeakCount->columnCount() < 5)
            tablePeakCount->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tablePeakCount->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tablePeakCount->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tablePeakCount->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tablePeakCount->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tablePeakCount->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tablePeakCount->setObjectName(QStringLiteral("tablePeakCount"));
        tablePeakCount->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablePeakCount->setSelectionMode(QAbstractItemView::SingleSelection);
        tablePeakCount->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePeakCount->setShowGrid(false);
        tablePeakCount->verticalHeader()->setVisible(false);
        tablePeakCount->verticalHeader()->setDefaultSectionSize(21);

        verticalLayout_4->addWidget(tablePeakCount);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(hotspotWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        verticalLayout->addWidget(label);

        tableUsage = new QTableWidget(hotspotWidget);
        if (tableUsage->columnCount() < 5)
            tableUsage->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableUsage->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableUsage->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableUsage->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableUsage->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableUsage->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        tableUsage->setObjectName(QStringLiteral("tableUsage"));
        tableUsage->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableUsage->setSelectionMode(QAbstractItemView::SingleSelection);
        tableUsage->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableUsage->setShowGrid(false);
        tableUsage->verticalHeader()->setVisible(false);
        tableUsage->verticalHeader()->setDefaultSectionSize(21);

        verticalLayout->addWidget(tableUsage);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(hotspotWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout_3->addWidget(label_3);

        tableLeaks = new QTableWidget(hotspotWidget);
        if (tableLeaks->columnCount() < 5)
            tableLeaks->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableLeaks->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableLeaks->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableLeaks->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableLeaks->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableLeaks->setHorizontalHeaderItem(4, __qtablewidgetitem19);
        tableLeaks->setObjectName(QStringLiteral("tableLeaks"));
        tableLeaks->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableLeaks->setSelectionMode(QAbstractItemView::SingleSelection);
        tableLeaks->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableLeaks->setShowGrid(false);
        tableLeaks->verticalHeader()->setVisible(false);
        tableLeaks->verticalHeader()->setDefaultSectionSize(21);

        verticalLayout_3->addWidget(tableLeaks);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 72, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        retranslateUi(hotspotWidget);

        QMetaObject::connectSlotsByName(hotspotWidget);
    } // setupUi

    void retranslateUi(QWidget *hotspotWidget)
    {
        hotspotWidget->setWindowTitle(QApplication::translate("hotspotWidget", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("hotspotWidget", "Peak memory usage", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tablePeak->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("hotspotWidget", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tablePeak->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("hotspotWidget", "Block size", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tablePeak->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("hotspotWidget", "Alignment", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tablePeak->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("hotspotWidget", "Peak count", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tablePeak->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("hotspotWidget", "Peak size", Q_NULLPTR));
        label_4->setText(QApplication::translate("hotspotWidget", "Peak live memory blocks", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tablePeakCount->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("hotspotWidget", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tablePeakCount->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("hotspotWidget", "Block size", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tablePeakCount->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("hotspotWidget", "Alignment", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tablePeakCount->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("hotspotWidget", "Peak count", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tablePeakCount->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("hotspotWidget", "Peak size", Q_NULLPTR));
        label->setText(QApplication::translate("hotspotWidget", "Leaked memory by size", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableUsage->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("hotspotWidget", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableUsage->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("hotspotWidget", "Block size", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableUsage->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("hotspotWidget", "Alignment", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableUsage->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("hotspotWidget", "Count", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableUsage->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QApplication::translate("hotspotWidget", "Size", Q_NULLPTR));
        label_3->setText(QApplication::translate("hotspotWidget", "Leaked memory by count", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tableLeaks->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("hotspotWidget", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tableLeaks->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("hotspotWidget", "Block size", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tableLeaks->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QApplication::translate("hotspotWidget", "Alignment", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tableLeaks->horizontalHeaderItem(3);
        ___qtablewidgetitem18->setText(QApplication::translate("hotspotWidget", "Leaked count", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tableLeaks->horizontalHeaderItem(4);
        ___qtablewidgetitem19->setText(QApplication::translate("hotspotWidget", "Leaked size", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class hotspotWidget: public Ui_hotspotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // HOTSPOT_UI_H
