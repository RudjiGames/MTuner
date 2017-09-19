/********************************************************************************
** Form generated from reading UI file 'stats.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STATS_UI_H
#define STATS_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Stats
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *Stats)
    {
        if (Stats->objectName().isEmpty())
            Stats->setObjectName(QStringLiteral("Stats"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Stats->sizePolicy().hasHeightForWidth());
        Stats->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        Stats->setWindowIcon(icon);
        gridLayout = new QGridLayout(Stats);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(Stats);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(0, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(0, 1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        __qtablewidgetitem13->setFlags(Qt::ItemIsEnabled);
        tableWidget->setItem(1, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(1, 1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(2, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(2, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(3, 0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(3, 1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(4, 0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(4, 1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(5, 0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(5, 1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(6, 0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(6, 1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        __qtablewidgetitem25->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(7, 0, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(7, 1, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(8, 0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableWidget->setItem(8, 1, __qtablewidgetitem28);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(276, 232));
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setGridStyle(Qt::DotLine);
        tableWidget->verticalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);
        tableWidget->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(Stats);

        QMetaObject::connectSlotsByName(Stats);
    } // setupUi

    void retranslateUi(QWidget *Stats)
    {
        Stats->setWindowTitle(QApplication::translate("Stats", "Form", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Stats", "Global", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Stats", "Snapshot", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("Stats", "Usage", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("Stats", "Usage peak", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("Stats", "Operations", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("Stats", "Allocations", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("Stats", "Reallocations", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QApplication::translate("Stats", "Frees", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem8->setText(QApplication::translate("Stats", "Live blocks", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem9->setText(QApplication::translate("Stats", "Overhead", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem10->setText(QApplication::translate("Stats", "Overhead peak", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(0, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem11->setToolTip(QApplication::translate("Stats", "Total memory usage, in bytes, at process termination", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(0, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem12->setToolTip(QApplication::translate("Stats", "Total memory usage, in bytes, at the end of selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(1, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem13->setToolTip(QApplication::translate("Stats", "Peak memory usage, in bytes", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(1, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem14->setToolTip(QApplication::translate("Stats", "Peak memory usage, in bytes, inside the selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(2, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem15->setToolTip(QApplication::translate("Stats", "Number of memory operations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(2, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem16->setToolTip(QApplication::translate("Stats", "Number of memory operations in selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(3, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem17->setToolTip(QApplication::translate("Stats", "Number of allocations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(3, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem18->setToolTip(QApplication::translate("Stats", "Number of allocations in selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(4, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem19->setToolTip(QApplication::translate("Stats", "Number of reallocations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(4, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem20->setToolTip(QApplication::translate("Stats", "Number of reallocations in selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(5, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem21->setToolTip(QApplication::translate("Stats", "Number of free operations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(5, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem22->setToolTip(QApplication::translate("Stats", "Number of free operations in selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(6, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem23->setToolTip(QApplication::translate("Stats", "Number of memory leaks", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(6, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem24->setToolTip(QApplication::translate("Stats", "Number of memory leaks in selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(7, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem25->setToolTip(QApplication::translate("Stats", "Total allocation overhead, in bytes", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(7, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem26->setToolTip(QApplication::translate("Stats", "Total allocation overhead, in bytes, in selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->item(8, 0);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem27->setToolTip(QApplication::translate("Stats", "Peak allocation overhead, in bytes", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->item(8, 1);
#endif
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem28->setToolTip(QApplication::translate("Stats", "Peak overhead, in bytes, in selected time slice", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        tableWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class Stats: public Ui_Stats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // STATS_UI_H
