/********************************************************************************
** Form generated from reading UI file 'graph.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GRAPH_UI_H
#define GRAPH_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../src/graphwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Graph
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QToolButton *buttonZoomIn;
    QToolButton *buttonZoomOut;
    QToolButton *buttonZoomReset;
    QToolButton *buttonZoomSelection;
    QToolButton *buttonZoomAuto;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    GraphWidget *graphWidget;
    QScrollBar *scrollBar;

    void setupUi(QWidget *Graph)
    {
        if (Graph->objectName().isEmpty())
            Graph->setObjectName(QStringLiteral("Graph"));
        Graph->resize(769, 249);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Graph64.png"), QSize(), QIcon::Normal, QIcon::Off);
        Graph->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(Graph);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttonZoomIn = new QToolButton(Graph);
        buttonZoomIn->setObjectName(QStringLiteral("buttonZoomIn"));
        buttonZoomIn->setMinimumSize(QSize(24, 0));
        buttonZoomIn->setMaximumSize(QSize(24, 16777215));

        verticalLayout->addWidget(buttonZoomIn);

        buttonZoomOut = new QToolButton(Graph);
        buttonZoomOut->setObjectName(QStringLiteral("buttonZoomOut"));
        buttonZoomOut->setMinimumSize(QSize(24, 0));
        buttonZoomOut->setMaximumSize(QSize(24, 16777215));

        verticalLayout->addWidget(buttonZoomOut);

        buttonZoomReset = new QToolButton(Graph);
        buttonZoomReset->setObjectName(QStringLiteral("buttonZoomReset"));
        buttonZoomReset->setMinimumSize(QSize(24, 0));
        buttonZoomReset->setMaximumSize(QSize(24, 16777215));

        verticalLayout->addWidget(buttonZoomReset);

        buttonZoomSelection = new QToolButton(Graph);
        buttonZoomSelection->setObjectName(QStringLiteral("buttonZoomSelection"));
        buttonZoomSelection->setMinimumSize(QSize(24, 0));
        buttonZoomSelection->setMaximumSize(QSize(24, 16777215));

        verticalLayout->addWidget(buttonZoomSelection);

        buttonZoomAuto = new QToolButton(Graph);
        buttonZoomAuto->setObjectName(QStringLiteral("buttonZoomAuto"));
        buttonZoomAuto->setMinimumSize(QSize(24, 0));
        buttonZoomAuto->setCheckable(true);
        buttonZoomAuto->setChecked(true);

        verticalLayout->addWidget(buttonZoomAuto);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        graphWidget = new GraphWidget(Graph);
        graphWidget->setObjectName(QStringLiteral("graphWidget"));

        verticalLayout_2->addWidget(graphWidget);

        scrollBar = new QScrollBar(Graph);
        scrollBar->setObjectName(QStringLiteral("scrollBar"));
        scrollBar->setEnabled(false);
        scrollBar->setMaximum(1000);
        scrollBar->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(scrollBar);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(Graph);

        QMetaObject::connectSlotsByName(Graph);
    } // setupUi

    void retranslateUi(QWidget *Graph)
    {
        Graph->setWindowTitle(QApplication::translate("Graph", "Form", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonZoomIn->setToolTip(QApplication::translate("Graph", "Zoom in", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonZoomIn->setText(QApplication::translate("Graph", "+", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonZoomOut->setToolTip(QApplication::translate("Graph", "Zoom out", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonZoomOut->setText(QApplication::translate("Graph", "-", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonZoomReset->setToolTip(QApplication::translate("Graph", "Reset zoom", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonZoomReset->setText(QApplication::translate("Graph", "R", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonZoomSelection->setToolTip(QApplication::translate("Graph", "Zoom to snapshot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonZoomSelection->setText(QApplication::translate("Graph", "S", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonZoomAuto->setToolTip(QApplication::translate("Graph", "Auto scale to range", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonZoomAuto->setText(QApplication::translate("Graph", "A", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Graph: public Ui_Graph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GRAPH_UI_H
