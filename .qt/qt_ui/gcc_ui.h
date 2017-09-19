/********************************************************************************
** Form generated from reading UI file 'gcc.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GCC_UI_H
#define GCC_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GCCSetup
{
public:
    QHBoxLayout *horizontalLayout_13;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QComboBox *toolchainCombo;
    QHBoxLayout *horizontalLayout;
    QLabel *labelToolchainName;
    QLineEdit *lineEditToolchainName;
    QGroupBox *groupBox64;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *lineEditEnv64;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditBinutils64;
    QToolButton *browseButton64;
    QLineEdit *lineEditPrefix64;
    QHBoxLayout *horizontalLayout_9;
    QLabel *isOkLabel64;
    QLabel *labelFound64;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox32;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_4;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditEnv32;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEditBinutils32;
    QToolButton *browseButton32;
    QLineEdit *lineEditPrefix32;
    QHBoxLayout *horizontalLayout_7;
    QLabel *isOkLabel32;
    QLabel *labelFound32;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBoxProDGps3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_15;
    QLabel *label_16;
    QVBoxLayout *verticalLayout_9;
    QLineEdit *lineEditEnvProDGps3;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEditBinutilsProDGps3;
    QToolButton *browseButtonProDGps3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *isOkLabelProDGps3;
    QLabel *labelFoundProDGps3;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GCCSetup)
    {
        if (GCCSetup->objectName().isEmpty())
            GCCSetup->setObjectName(QStringLiteral("GCCSetup"));
        GCCSetup->resize(632, 417);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/gnu64.png"), QSize(), QIcon::Normal, QIcon::Off);
        GCCSetup->setWindowIcon(icon);
        GCCSetup->setModal(true);
        horizontalLayout_13 = new QHBoxLayout(GCCSetup);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_13->setContentsMargins(-1, 13, -1, -1);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        toolchainCombo = new QComboBox(GCCSetup);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MTuner/resources/images/toolchain_mingw.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolchainCombo->addItem(icon1, QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MTuner/resources/images/toolchain_ps3.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolchainCombo->addItem(icon2, QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MTuner/resources/images/toolchain_ps4.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolchainCombo->addItem(icon3, QStringLiteral(""));
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->addItem(QString());
        toolchainCombo->setObjectName(QStringLiteral("toolchainCombo"));
        QFont font;
        font.setPointSize(9);
        toolchainCombo->setFont(font);
        toolchainCombo->setMaxVisibleItems(18);
        toolchainCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        toolchainCombo->setIconSize(QSize(112, 16));

        verticalLayout_10->addWidget(toolchainCombo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelToolchainName = new QLabel(GCCSetup);
        labelToolchainName->setObjectName(QStringLiteral("labelToolchainName"));

        horizontalLayout->addWidget(labelToolchainName);

        lineEditToolchainName = new QLineEdit(GCCSetup);
        lineEditToolchainName->setObjectName(QStringLiteral("lineEditToolchainName"));

        horizontalLayout->addWidget(lineEditToolchainName);


        verticalLayout_10->addLayout(horizontalLayout);


        verticalLayout_11->addLayout(verticalLayout_10);

        groupBox64 = new QGroupBox(GCCSetup);
        groupBox64->setObjectName(QStringLiteral("groupBox64"));
        groupBox64->setFlat(true);
        gridLayout_2 = new QGridLayout(groupBox64);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_13 = new QLabel(groupBox64);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_5->addWidget(label_13);

        label_14 = new QLabel(groupBox64);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_5->addWidget(label_14);

        label_6 = new QLabel(groupBox64);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_5->addWidget(label_6);


        horizontalLayout_8->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        lineEditEnv64 = new QLineEdit(groupBox64);
        lineEditEnv64->setObjectName(QStringLiteral("lineEditEnv64"));

        verticalLayout_6->addWidget(lineEditEnv64);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lineEditBinutils64 = new QLineEdit(groupBox64);
        lineEditBinutils64->setObjectName(QStringLiteral("lineEditBinutils64"));

        horizontalLayout_4->addWidget(lineEditBinutils64);

        browseButton64 = new QToolButton(groupBox64);
        browseButton64->setObjectName(QStringLiteral("browseButton64"));

        horizontalLayout_4->addWidget(browseButton64);


        verticalLayout_6->addLayout(horizontalLayout_4);

        lineEditPrefix64 = new QLineEdit(groupBox64);
        lineEditPrefix64->setObjectName(QStringLiteral("lineEditPrefix64"));

        verticalLayout_6->addWidget(lineEditPrefix64);


        horizontalLayout_8->addLayout(verticalLayout_6);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        isOkLabel64 = new QLabel(groupBox64);
        isOkLabel64->setObjectName(QStringLiteral("isOkLabel64"));

        horizontalLayout_9->addWidget(isOkLabel64);

        labelFound64 = new QLabel(groupBox64);
        labelFound64->setObjectName(QStringLiteral("labelFound64"));

        horizontalLayout_9->addWidget(labelFound64);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_9);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);


        verticalLayout_11->addWidget(groupBox64);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox32 = new QGroupBox(GCCSetup);
        groupBox32->setObjectName(QStringLiteral("groupBox32"));
        groupBox32->setFlat(true);
        gridLayout = new QGridLayout(groupBox32);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_11 = new QLabel(groupBox32);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_2->addWidget(label_11);

        label_12 = new QLabel(groupBox32);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_2->addWidget(label_12);

        label_4 = new QLabel(groupBox32);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEditEnv32 = new QLineEdit(groupBox32);
        lineEditEnv32->setObjectName(QStringLiteral("lineEditEnv32"));

        verticalLayout->addWidget(lineEditEnv32);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEditBinutils32 = new QLineEdit(groupBox32);
        lineEditBinutils32->setObjectName(QStringLiteral("lineEditBinutils32"));

        horizontalLayout_3->addWidget(lineEditBinutils32);

        browseButton32 = new QToolButton(groupBox32);
        browseButton32->setObjectName(QStringLiteral("browseButton32"));

        horizontalLayout_3->addWidget(browseButton32);


        verticalLayout->addLayout(horizontalLayout_3);

        lineEditPrefix32 = new QLineEdit(groupBox32);
        lineEditPrefix32->setObjectName(QStringLiteral("lineEditPrefix32"));

        verticalLayout->addWidget(lineEditPrefix32);


        horizontalLayout_6->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        isOkLabel32 = new QLabel(groupBox32);
        isOkLabel32->setObjectName(QStringLiteral("isOkLabel32"));

        horizontalLayout_7->addWidget(isOkLabel32);

        labelFound32 = new QLabel(groupBox32);
        labelFound32->setObjectName(QStringLiteral("labelFound32"));

        horizontalLayout_7->addWidget(labelFound32);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_7);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox32);

        groupBoxProDGps3 = new QGroupBox(GCCSetup);
        groupBoxProDGps3->setObjectName(QStringLiteral("groupBoxProDGps3"));
        groupBoxProDGps3->setFlat(true);
        gridLayout_3 = new QGridLayout(groupBoxProDGps3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_15 = new QLabel(groupBoxProDGps3);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout_8->addWidget(label_15);

        label_16 = new QLabel(groupBoxProDGps3);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout_8->addWidget(label_16);


        horizontalLayout_10->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        lineEditEnvProDGps3 = new QLineEdit(groupBoxProDGps3);
        lineEditEnvProDGps3->setObjectName(QStringLiteral("lineEditEnvProDGps3"));

        verticalLayout_9->addWidget(lineEditEnvProDGps3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lineEditBinutilsProDGps3 = new QLineEdit(groupBoxProDGps3);
        lineEditBinutilsProDGps3->setObjectName(QStringLiteral("lineEditBinutilsProDGps3"));

        horizontalLayout_5->addWidget(lineEditBinutilsProDGps3);

        browseButtonProDGps3 = new QToolButton(groupBoxProDGps3);
        browseButtonProDGps3->setObjectName(QStringLiteral("browseButtonProDGps3"));

        horizontalLayout_5->addWidget(browseButtonProDGps3);


        verticalLayout_9->addLayout(horizontalLayout_5);


        horizontalLayout_10->addLayout(verticalLayout_9);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        isOkLabelProDGps3 = new QLabel(groupBoxProDGps3);
        isOkLabelProDGps3->setObjectName(QStringLiteral("isOkLabelProDGps3"));

        horizontalLayout_11->addWidget(isOkLabelProDGps3);

        labelFoundProDGps3 = new QLabel(groupBoxProDGps3);
        labelFoundProDGps3->setObjectName(QStringLiteral("labelFoundProDGps3"));

        horizontalLayout_11->addWidget(labelFoundProDGps3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);


        verticalLayout_7->addLayout(horizontalLayout_11);


        gridLayout_3->addLayout(verticalLayout_7, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBoxProDGps3);


        verticalLayout_11->addLayout(horizontalLayout_2);


        gridLayout_4->addLayout(verticalLayout_11, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(GCCSetup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        horizontalLayout_12->addWidget(buttonBox);


        gridLayout_4->addLayout(horizontalLayout_12, 1, 0, 1, 1);


        horizontalLayout_13->addLayout(gridLayout_4);


        retranslateUi(GCCSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), GCCSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GCCSetup, SLOT(reject()));
        QObject::connect(browseButton64, SIGNAL(clicked()), GCCSetup, SLOT(pathBrowse64()));
        QObject::connect(browseButton32, SIGNAL(clicked()), GCCSetup, SLOT(pathBrowse32()));
        QObject::connect(browseButtonProDGps3, SIGNAL(clicked()), GCCSetup, SLOT(pathBrowseProDGps3()));
        QObject::connect(lineEditEnv32, SIGNAL(textChanged(QString)), GCCSetup, SLOT(envEdited32(QString)));
        QObject::connect(lineEditBinutils32, SIGNAL(textChanged(QString)), GCCSetup, SLOT(pathEdited32(QString)));
        QObject::connect(lineEditPrefix32, SIGNAL(textChanged(QString)), GCCSetup, SLOT(prefixEdited32(QString)));
        QObject::connect(lineEditEnv64, SIGNAL(textChanged(QString)), GCCSetup, SLOT(envEdited64(QString)));
        QObject::connect(lineEditBinutils64, SIGNAL(textChanged(QString)), GCCSetup, SLOT(pathEdited64(QString)));
        QObject::connect(lineEditPrefix64, SIGNAL(textChanged(QString)), GCCSetup, SLOT(prefixEdited64(QString)));
        QObject::connect(lineEditEnvProDGps3, SIGNAL(textChanged(QString)), GCCSetup, SLOT(envEditedProDGps3(QString)));
        QObject::connect(lineEditBinutilsProDGps3, SIGNAL(textChanged(QString)), GCCSetup, SLOT(pathEditedProDGps3(QString)));
        QObject::connect(lineEditToolchainName, SIGNAL(textChanged(QString)), GCCSetup, SLOT(toolchainRenamed(QString)));
        QObject::connect(toolchainCombo, SIGNAL(activated(int)), GCCSetup, SLOT(toolchainSelected(int)));

        QMetaObject::connectSlotsByName(GCCSetup);
    } // setupUi

    void retranslateUi(QDialog *GCCSetup)
    {
        GCCSetup->setWindowTitle(QApplication::translate("GCCSetup", "Setup GCC toolchains", Q_NULLPTR));
        toolchainCombo->setItemText(3, QApplication::translate("GCCSetup", "Custom toolchain 1", Q_NULLPTR));
        toolchainCombo->setItemText(4, QApplication::translate("GCCSetup", "Custom toolchain 2", Q_NULLPTR));
        toolchainCombo->setItemText(5, QApplication::translate("GCCSetup", "Custom toolchain 3", Q_NULLPTR));
        toolchainCombo->setItemText(6, QApplication::translate("GCCSetup", "Custom toolchain 4", Q_NULLPTR));
        toolchainCombo->setItemText(7, QApplication::translate("GCCSetup", "Custom toolchain 5", Q_NULLPTR));
        toolchainCombo->setItemText(8, QApplication::translate("GCCSetup", "Custom toolchain 6", Q_NULLPTR));
        toolchainCombo->setItemText(9, QApplication::translate("GCCSetup", "Custom toolchain 7", Q_NULLPTR));
        toolchainCombo->setItemText(10, QApplication::translate("GCCSetup", "Custom toolchain 8", Q_NULLPTR));
        toolchainCombo->setItemText(11, QApplication::translate("GCCSetup", "Custom toolchain 9", Q_NULLPTR));

        labelToolchainName->setText(QApplication::translate("GCCSetup", "Toolchain name:", Q_NULLPTR));
        groupBox64->setTitle(QApplication::translate("GCCSetup", "64 bit", Q_NULLPTR));
        label_13->setText(QApplication::translate("GCCSetup", "Environment variable", Q_NULLPTR));
        label_14->setText(QApplication::translate("GCCSetup", "Binutils path", Q_NULLPTR));
        label_6->setText(QApplication::translate("GCCSetup", "Toolchain prefix", Q_NULLPTR));
        browseButton64->setText(QApplication::translate("GCCSetup", "...", Q_NULLPTR));
        isOkLabel64->setText(QApplication::translate("GCCSetup", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
        labelFound64->setText(QString());
        groupBox32->setTitle(QApplication::translate("GCCSetup", "32 bit", Q_NULLPTR));
        label_11->setText(QApplication::translate("GCCSetup", "Environment variable", Q_NULLPTR));
        label_12->setText(QApplication::translate("GCCSetup", "Binutils path", Q_NULLPTR));
        label_4->setText(QApplication::translate("GCCSetup", "Toolchain prefix", Q_NULLPTR));
        browseButton32->setText(QApplication::translate("GCCSetup", "...", Q_NULLPTR));
        isOkLabel32->setText(QApplication::translate("GCCSetup", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
        labelFound32->setText(QString());
        groupBoxProDGps3->setTitle(QApplication::translate("GCCSetup", "SN ProDG", Q_NULLPTR));
        label_15->setText(QApplication::translate("GCCSetup", "Environment variable", Q_NULLPTR));
        label_16->setText(QApplication::translate("GCCSetup", "Binutils path", Q_NULLPTR));
        browseButtonProDGps3->setText(QApplication::translate("GCCSetup", "...", Q_NULLPTR));
        isOkLabelProDGps3->setText(QApplication::translate("GCCSetup", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
        labelFoundProDGps3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GCCSetup: public Ui_GCCSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GCC_UI_H
