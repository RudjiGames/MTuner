/********************************************************************************
** Form generated from reading UI file 'operationsearch.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef OPERATIONSEARCH_UI_H
#define OPERATIONSEARCH_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperationSearchWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditAddress;
    QPushButton *buttonPrev;
    QPushButton *buttonNext;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *comboBox;
    QLineEdit *lineEditSearch;
    QToolButton *buttonSearch;

    void setupUi(QWidget *OperationSearchWidget)
    {
        if (OperationSearchWidget->objectName().isEmpty())
            OperationSearchWidget->setObjectName(QStringLiteral("OperationSearchWidget"));
        OperationSearchWidget->resize(824, 24);
        OperationSearchWidget->setMinimumSize(QSize(0, 24));
        OperationSearchWidget->setMaximumSize(QSize(16777215, 24));
        horizontalLayout_2 = new QHBoxLayout(OperationSearchWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 0, 6, 0);
        label_2 = new QLabel(OperationSearchWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEditAddress = new QLineEdit(OperationSearchWidget);
        lineEditAddress->setObjectName(QStringLiteral("lineEditAddress"));
        lineEditAddress->setEnabled(false);
        lineEditAddress->setMinimumSize(QSize(120, 0));
        lineEditAddress->setMaximumSize(QSize(120, 16777215));
        lineEditAddress->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditAddress->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditAddress);

        buttonPrev = new QPushButton(OperationSearchWidget);
        buttonPrev->setObjectName(QStringLiteral("buttonPrev"));
        buttonPrev->setEnabled(false);

        horizontalLayout_2->addWidget(buttonPrev);

        buttonNext = new QPushButton(OperationSearchWidget);
        buttonNext->setObjectName(QStringLiteral("buttonNext"));
        buttonNext->setEnabled(false);

        horizontalLayout_2->addWidget(buttonNext);

        horizontalSpacer = new QSpacerItem(216, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(OperationSearchWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(OperationSearchWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        lineEditSearch = new QLineEdit(OperationSearchWidget);
        lineEditSearch->setObjectName(QStringLiteral("lineEditSearch"));
        lineEditSearch->setMinimumSize(QSize(120, 0));
        lineEditSearch->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_2->addWidget(lineEditSearch);

        buttonSearch = new QToolButton(OperationSearchWidget);
        buttonSearch->setObjectName(QStringLiteral("buttonSearch"));
        buttonSearch->setEnabled(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Lupa16.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSearch->setIcon(icon);

        horizontalLayout_2->addWidget(buttonSearch);


        retranslateUi(OperationSearchWidget);

        QMetaObject::connectSlotsByName(OperationSearchWidget);
    } // setupUi

    void retranslateUi(QWidget *OperationSearchWidget)
    {
        OperationSearchWidget->setWindowTitle(QApplication::translate("OperationSearchWidget", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("OperationSearchWidget", "Address:", Q_NULLPTR));
        lineEditAddress->setText(QString());
#ifndef QT_NO_TOOLTIP
        buttonPrev->setToolTip(QApplication::translate("OperationSearchWidget", "Find previous operation on the same memory block", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonPrev->setText(QApplication::translate("OperationSearchWidget", "Prev", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonNext->setToolTip(QApplication::translate("OperationSearchWidget", "Find next operation on the same memory block", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonNext->setText(QApplication::translate("OperationSearchWidget", "Next", Q_NULLPTR));
        label->setText(QApplication::translate("OperationSearchWidget", "Find next by", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("OperationSearchWidget", "address", Q_NULLPTR)
         << QApplication::translate("OperationSearchWidget", "size", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        buttonSearch->setToolTip(QApplication::translate("OperationSearchWidget", "Finds next memory operaton with given address or size", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonSearch->setText(QApplication::translate("OperationSearchWidget", "Find memory operation on a memory block with given address", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OperationSearchWidget: public Ui_OperationSearchWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // OPERATIONSEARCH_UI_H
