/********************************************************************************
** Form generated from reading UI file 'stacktrace.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STACKTRACE_UI_H
#define STACKTRACE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StackTrace
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QToolButton *button_dec;
    QSpinBox *spinBox;
    QToolButton *button_inc;
    QLabel *label_total;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *StackTrace)
    {
        if (StackTrace->objectName().isEmpty())
            StackTrace->setObjectName(QStringLiteral("StackTrace"));
        StackTrace->resize(404, 642);
        verticalLayout = new QVBoxLayout(StackTrace);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(StackTrace);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->horizontalHeader()->setDefaultSectionSize(99);
        tableWidget->horizontalHeader()->setMinimumSectionSize(21);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(21);
        tableWidget->verticalHeader()->setMinimumSectionSize(21);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(StackTrace);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        button_dec = new QToolButton(StackTrace);
        button_dec->setObjectName(QStringLiteral("button_dec"));

        horizontalLayout->addWidget(button_dec);

        spinBox = new QSpinBox(StackTrace);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setAlignment(Qt::AlignCenter);
        spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout->addWidget(spinBox);

        button_inc = new QToolButton(StackTrace);
        button_inc->setObjectName(QStringLiteral("button_inc"));

        horizontalLayout->addWidget(button_inc);


        horizontalLayout_2->addLayout(horizontalLayout);

        label_total = new QLabel(StackTrace);
        label_total->setObjectName(QStringLiteral("label_total"));

        horizontalLayout_2->addWidget(label_total);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(StackTrace);
        QObject::connect(button_inc, SIGNAL(clicked()), StackTrace, SLOT(incClicked()));
        QObject::connect(button_dec, SIGNAL(clicked()), StackTrace, SLOT(decClicked()));

        QMetaObject::connectSlotsByName(StackTrace);
    } // setupUi

    void retranslateUi(QWidget *StackTrace)
    {
        StackTrace->setWindowTitle(QApplication::translate("StackTrace", "Form", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("StackTrace", "Module", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("StackTrace", "File", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("StackTrace", "Line", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("StackTrace", "Function", Q_NULLPTR));
        label->setText(QApplication::translate("StackTrace", "Stack trace", Q_NULLPTR));
        button_dec->setText(QApplication::translate("StackTrace", "<", Q_NULLPTR));
        button_inc->setText(QApplication::translate("StackTrace", ">", Q_NULLPTR));
        label_total->setText(QApplication::translate("StackTrace", "of 100", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StackTrace: public Ui_StackTrace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // STACKTRACE_UI_H
