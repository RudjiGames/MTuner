/********************************************************************************
** Form generated from reading UI file 'startpage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STARTPAGE_UI_H
#define STARTPAGE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartPageWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLabel *label_version;
    QFrame *line;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *StartPageWidget)
    {
        if (StartPageWidget->objectName().isEmpty())
            StartPageWidget->setObjectName(QStringLiteral("StartPageWidget"));
        StartPageWidget->resize(835, 763);
        verticalLayout = new QVBoxLayout(StartPageWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(StartPageWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font;
        font.setFamily(QStringLiteral("Maven Pro"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_4->addWidget(label_7);

        label_version = new QLabel(StartPageWidget);
        label_version->setObjectName(QStringLiteral("label_version"));
        label_version->setText(QStringLiteral("<html><head/><body><p><br/></p></body></html>"));
        label_version->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_4->addWidget(label_version);


        verticalLayout_3->addLayout(horizontalLayout_4);

        line = new QFrame(StartPageWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        label_3 = new QLabel(StartPageWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(442, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        frame = new QFrame(StartPageWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(128, 128));
        label_4->setMaximumSize(QSize(128, 128));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(128, 128));
        label->setMaximumSize(QSize(128, 128));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(153, 33));

        horizontalLayout_3->addWidget(label_5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(153, 33));

        horizontalLayout_3->addWidget(label_6);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);


        verticalLayout->addWidget(frame);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        retranslateUi(StartPageWidget);

        QMetaObject::connectSlotsByName(StartPageWidget);
    } // setupUi

    void retranslateUi(QWidget *StartPageWidget)
    {
        StartPageWidget->setWindowTitle(QApplication::translate("StartPageWidget", "StartPageWidget", Q_NULLPTR));
        label_7->setText(QApplication::translate("StartPageWidget", "<html><head/><body><p><span style=\" font-size:36pt; font-weight:600; color:#5a5a78;\">M</span><span style=\" font-size:36pt; font-weight:600; color:#787896;\">Tuner</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("StartPageWidget", "<html><head/><body><p><span style=\" font-size:9pt;\">Copyright \302\251 2017 by Milos Tosic - All Rights Reserved</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("StartPageWidget", "<html><head/><body><p><img src=\":/MTuner/resources/images/Run.png\"/></p><p><br/></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("StartPageWidget", "<html><head/><body><p><img src=\":/MTuner/resources/images/Icon128.png\"/></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("StartPageWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:9pt;\">Drag &amp; drop an executable<br/>to begin memory profiling</span></p></body></html>", Q_NULLPTR));
        label_6->setText(QApplication::translate("StartPageWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:9pt;\">Drag &amp; drop *.MTuner <br/>file to begin memory analysis</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StartPageWidget: public Ui_StartPageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // STARTPAGE_UI_H
