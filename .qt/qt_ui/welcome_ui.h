/********************************************************************************
** Form generated from reading UI file 'welcome.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef WELCOME_UI_H
#define WELCOME_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Welcome
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *buttonSymbols;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *buttonDocumentation;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *buttonClose;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *Welcome)
    {
        if (Welcome->objectName().isEmpty())
            Welcome->setObjectName(QStringLiteral("Welcome"));
        Welcome->resize(730, 449);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Welcome->sizePolicy().hasHeightForWidth());
        Welcome->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Icon64.png"), QSize(), QIcon::Normal, QIcon::Off);
        Welcome->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(Welcome);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Welcome);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(Welcome);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QStringLiteral("Maven Pro"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        label_5 = new QLabel(Welcome);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_4->addWidget(label_5);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget = new QListWidget(Welcome);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 2, 2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        buttonSymbols = new QPushButton(Welcome);
        buttonSymbols->setObjectName(QStringLiteral("buttonSymbols"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MTuner/resources/images/Symbol64.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSymbols->setIcon(icon1);
        buttonSymbols->setIconSize(QSize(64, 64));
        buttonSymbols->setFlat(true);

        horizontalLayout_3->addWidget(buttonSymbols);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        buttonDocumentation = new QPushButton(Welcome);
        buttonDocumentation->setObjectName(QStringLiteral("buttonDocumentation"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MTuner/resources/images/Documentation.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDocumentation->setIcon(icon2);
        buttonDocumentation->setIconSize(QSize(64, 64));
        buttonDocumentation->setFlat(true);

        horizontalLayout_3->addWidget(buttonDocumentation);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_3 = new QLabel(Welcome);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_4 = new QLabel(Welcome);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_3, 1, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout);

        checkBox = new QCheckBox(Welcome);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        verticalLayout_4->addWidget(checkBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        buttonClose = new QPushButton(Welcome);
        buttonClose->setObjectName(QStringLiteral("buttonClose"));

        horizontalLayout_4->addWidget(buttonClose);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);


        verticalLayout_4->addLayout(horizontalLayout_4);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(Welcome);
        QObject::connect(buttonClose, SIGNAL(clicked()), Welcome, SLOT(reject()));

        buttonClose->setDefault(true);


        QMetaObject::connectSlotsByName(Welcome);
    } // setupUi

    void retranslateUi(QDialog *Welcome)
    {
        Welcome->setWindowTitle(QApplication::translate("Welcome", "Welcome to MTuner!", Q_NULLPTR));
        label->setText(QApplication::translate("Welcome", "<html><head/><body><p><img src=\":/MTuner/resources/images/Icon64.png\"/></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("Welcome", "<html><head/><body><p><span style=\" font-size:24pt; color:#5a5a78;\">Welcome to M</span><span style=\" font-size:24pt; color:#787896;\">Tuner</span><span style=\" font-size:24pt; color:#5a5a78;\">!</span></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("Welcome", "<html><head/><body><p><span style=\" font-size:9pt;\">Thank you for choosing MTuner!</span></p><p><span style=\" font-size:9pt;\">Before starting to profile MSVC based applications it is important to setup PDB symbol servers.<br/>For more information please visit MTuner website, just click the Documentation button below.</span></p></body></html>", Q_NULLPTR));
        buttonSymbols->setText(QString());
        buttonDocumentation->setText(QString());
        label_3->setText(QApplication::translate("Welcome", "<html><head/><body><p align=\"center\">Setup PDB<br/>symbol servers</p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("Welcome", "<html><head/><body><p align=\"center\">Read MTuner<br/>documentation</p></body></html>", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Welcome", "Always show on startup", Q_NULLPTR));
        buttonClose->setText(QApplication::translate("Welcome", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Welcome: public Ui_Welcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // WELCOME_UI_H
