/********************************************************************************
** Form generated from reading UI file 'symbolstore.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SYMBOLSTORE_UI_H
#define SYMBOLSTORE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SymbolStoreDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *textPublicStore;
    QToolButton *buttonDefault;
    QHBoxLayout *horizontalLayout;
    QLineEdit *textLocalStore;
    QToolButton *buttonBrowse;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QCheckBox *checkRegistry;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_OK;

    void setupUi(QDialog *SymbolStoreDialog)
    {
        if (SymbolStoreDialog->objectName().isEmpty())
            SymbolStoreDialog->setObjectName(QStringLiteral("SymbolStoreDialog"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Symbol64.png"), QSize(), QIcon::Normal, QIcon::Off);
        SymbolStoreDialog->setWindowIcon(icon);
        SymbolStoreDialog->setModal(true);
        verticalLayout_3 = new QVBoxLayout(SymbolStoreDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_2 = new QGroupBox(SymbolStoreDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textPublicStore = new QLineEdit(groupBox_2);
        textPublicStore->setObjectName(QStringLiteral("textPublicStore"));
        textPublicStore->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(textPublicStore);

        buttonDefault = new QToolButton(groupBox_2);
        buttonDefault->setObjectName(QStringLiteral("buttonDefault"));

        horizontalLayout_2->addWidget(buttonDefault);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textLocalStore = new QLineEdit(groupBox_2);
        textLocalStore->setObjectName(QStringLiteral("textLocalStore"));
        textLocalStore->setClearButtonEnabled(true);

        horizontalLayout->addWidget(textLocalStore);

        buttonBrowse = new QToolButton(groupBox_2);
        buttonBrowse->setObjectName(QStringLiteral("buttonBrowse"));

        horizontalLayout->addWidget(buttonBrowse);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(SymbolStoreDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        checkRegistry = new QCheckBox(groupBox_3);
        checkRegistry->setObjectName(QStringLiteral("checkRegistry"));

        gridLayout_4->addWidget(checkRegistry, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        toolButton = new QToolButton(SymbolStoreDialog);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout_4->addWidget(toolButton);

        horizontalSpacer = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_Cancel = new QPushButton(SymbolStoreDialog);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));

        horizontalLayout_4->addWidget(pushButton_Cancel);

        pushButton_OK = new QPushButton(SymbolStoreDialog);
        pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));

        horizontalLayout_4->addWidget(pushButton_OK);


        verticalLayout_3->addLayout(horizontalLayout_4);


        retranslateUi(SymbolStoreDialog);
        QObject::connect(buttonDefault, SIGNAL(clicked()), SymbolStoreDialog, SLOT(defaultSymbolServer()));
        QObject::connect(buttonBrowse, SIGNAL(clicked()), SymbolStoreDialog, SLOT(selectLocalStore()));
        QObject::connect(toolButton, SIGNAL(clicked()), SymbolStoreDialog, SLOT(visitMSDN()));
        QObject::connect(pushButton_Cancel, SIGNAL(clicked()), SymbolStoreDialog, SLOT(reject()));
        QObject::connect(pushButton_OK, SIGNAL(clicked()), SymbolStoreDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(SymbolStoreDialog);
    } // setupUi

    void retranslateUi(QDialog *SymbolStoreDialog)
    {
        SymbolStoreDialog->setWindowTitle(QApplication::translate("SymbolStoreDialog", "Symbol store setup", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SymbolStoreDialog", "User defined", Q_NULLPTR));
        label->setText(QApplication::translate("SymbolStoreDialog", "Public store", Q_NULLPTR));
        label_2->setText(QApplication::translate("SymbolStoreDialog", "Local store", Q_NULLPTR));
        buttonDefault->setText(QApplication::translate("SymbolStoreDialog", "Default", Q_NULLPTR));
        buttonBrowse->setText(QApplication::translate("SymbolStoreDialog", "...", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("SymbolStoreDialog", "Environment", Q_NULLPTR));
        checkRegistry->setText(QApplication::translate("SymbolStoreDialog", "_NT_SYMBOL_PATH", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButton->setToolTip(QApplication::translate("SymbolStoreDialog", "Visit MSDN page explaining in depth how to set up symbol store paths", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButton->setText(QApplication::translate("SymbolStoreDialog", "MSDN info", Q_NULLPTR));
        pushButton_Cancel->setText(QApplication::translate("SymbolStoreDialog", "Cancel", Q_NULLPTR));
        pushButton_OK->setText(QApplication::translate("SymbolStoreDialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SymbolStoreDialog: public Ui_SymbolStoreDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SYMBOLSTORE_UI_H
