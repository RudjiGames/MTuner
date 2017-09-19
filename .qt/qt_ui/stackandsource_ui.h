/********************************************************************************
** Form generated from reading UI file 'stackandsource.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STACKANDSOURCE_UI_H
#define STACKANDSOURCE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "../src/sourceview.h"
#include "../src/stacktrace.h"

QT_BEGIN_NAMESPACE

class Ui_StackAndSource
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    StackTrace *stackTraceWidget;
    SourceView *sourceViewWidget;

    void setupUi(QWidget *StackAndSource)
    {
        if (StackAndSource->objectName().isEmpty())
            StackAndSource->setObjectName(QStringLiteral("StackAndSource"));
        StackAndSource->resize(453, 829);
        gridLayout = new QGridLayout(StackAndSource);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(StackAndSource);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        stackTraceWidget = new StackTrace(splitter);
        stackTraceWidget->setObjectName(QStringLiteral("stackTraceWidget"));
        splitter->addWidget(stackTraceWidget);
        sourceViewWidget = new SourceView(splitter);
        sourceViewWidget->setObjectName(QStringLiteral("sourceViewWidget"));
        sourceViewWidget->setMinimumSize(QSize(300, 0));
        splitter->addWidget(sourceViewWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(StackAndSource);

        QMetaObject::connectSlotsByName(StackAndSource);
    } // setupUi

    void retranslateUi(QWidget *StackAndSource)
    {
        StackAndSource->setWindowTitle(QApplication::translate("StackAndSource", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StackAndSource: public Ui_StackAndSource {};
} // namespace Ui

QT_END_NAMESPACE

#endif // STACKANDSOURCE_UI_H
