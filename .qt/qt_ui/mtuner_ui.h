/********************************************************************************
** Form generated from reading UI file 'mtuner.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MTUNER_UI_H
#define MTUNER_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MTunerClass
{
public:
    QAction *action_Open;
    QAction *action_Exit;
    QAction *action_About;
    QAction *action_Manage_projects;
    QAction *action_Close;
    QAction *action_Symbols;
    QAction *action_Contents;
    QAction *action_Filters;
    QAction *action_View_Memory_Graph;
    QAction *action_View_Memory_Stats;
    QAction *action_English;
    QAction *action_View_Histograms;
    QAction *action_View_Tag_Tree;
    QAction *action_View_StackTrace;
    QAction *action_External_editor;
    QAction *action_Import_license_file;
    QAction *action_Activation_MTuner;
    QAction *action_GCC_toolchains;
    QAction *action_View_Heaps_Allocators;
    QAction *actionOpen_capture_storage;
    QAction *action_Save_capture_window_layout;
    QWidget *CentralWidget;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QMenu *menu_Settings;
    QMenu *menu_View;
    QMenu *menuLanguage;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MTunerClass)
    {
        if (MTunerClass->objectName().isEmpty())
            MTunerClass->setObjectName(QStringLiteral("MTunerClass"));
        MTunerClass->resize(1280, 720);
        MTunerClass->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Icon64.png"), QSize(), QIcon::Normal, QIcon::Off);
        MTunerClass->setWindowIcon(icon);
        action_Open = new QAction(MTunerClass);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MTuner/resources/images/Open64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon1);
        action_Exit = new QAction(MTunerClass);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        action_About = new QAction(MTunerClass);
        action_About->setObjectName(QStringLiteral("action_About"));
        action_Manage_projects = new QAction(MTunerClass);
        action_Manage_projects->setObjectName(QStringLiteral("action_Manage_projects"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MTuner/resources/images/Projects64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Manage_projects->setIcon(icon2);
        action_Close = new QAction(MTunerClass);
        action_Close->setObjectName(QStringLiteral("action_Close"));
        action_Symbols = new QAction(MTunerClass);
        action_Symbols->setObjectName(QStringLiteral("action_Symbols"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MTuner/resources/images/Symbol64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Symbols->setIcon(icon3);
        action_Contents = new QAction(MTunerClass);
        action_Contents->setObjectName(QStringLiteral("action_Contents"));
        action_Filters = new QAction(MTunerClass);
        action_Filters->setObjectName(QStringLiteral("action_Filters"));
        action_Filters->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MTuner/resources/images/Filter64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Filters->setIcon(icon4);
        action_View_Memory_Graph = new QAction(MTunerClass);
        action_View_Memory_Graph->setObjectName(QStringLiteral("action_View_Memory_Graph"));
        action_View_Memory_Graph->setCheckable(true);
        action_View_Memory_Graph->setChecked(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/MTuner/resources/images/Graph64.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QStringLiteral(":/MTuner/resources/images/Graph64.png"), QSize(), QIcon::Active, QIcon::On);
        action_View_Memory_Graph->setIcon(icon5);
        action_View_Memory_Stats = new QAction(MTunerClass);
        action_View_Memory_Stats->setObjectName(QStringLiteral("action_View_Memory_Stats"));
        action_View_Memory_Stats->setCheckable(true);
        action_View_Memory_Stats->setChecked(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/MTuner/resources/images/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_View_Memory_Stats->setIcon(icon6);
        action_English = new QAction(MTunerClass);
        action_English->setObjectName(QStringLiteral("action_English"));
        action_View_Histograms = new QAction(MTunerClass);
        action_View_Histograms->setObjectName(QStringLiteral("action_View_Histograms"));
        action_View_Histograms->setCheckable(true);
        action_View_Histograms->setChecked(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/MTuner/resources/images/Histogram64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_View_Histograms->setIcon(icon7);
        action_View_Tag_Tree = new QAction(MTunerClass);
        action_View_Tag_Tree->setObjectName(QStringLiteral("action_View_Tag_Tree"));
        action_View_Tag_Tree->setCheckable(true);
        action_View_Tag_Tree->setChecked(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/MTuner/resources/images/StackTree64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_View_Tag_Tree->setIcon(icon8);
        action_View_StackTrace = new QAction(MTunerClass);
        action_View_StackTrace->setObjectName(QStringLiteral("action_View_StackTrace"));
        action_View_StackTrace->setCheckable(true);
        action_View_StackTrace->setChecked(true);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/MTuner/resources/images/StackTraceSource64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_View_StackTrace->setIcon(icon9);
        action_External_editor = new QAction(MTunerClass);
        action_External_editor->setObjectName(QStringLiteral("action_External_editor"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/MTuner/resources/images/Editor64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_External_editor->setIcon(icon10);
        action_Import_license_file = new QAction(MTunerClass);
        action_Import_license_file->setObjectName(QStringLiteral("action_Import_license_file"));
        action_Activation_MTuner = new QAction(MTunerClass);
        action_Activation_MTuner->setObjectName(QStringLiteral("action_Activation_MTuner"));
        action_GCC_toolchains = new QAction(MTunerClass);
        action_GCC_toolchains->setObjectName(QStringLiteral("action_GCC_toolchains"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/MTuner/resources/images/gnu64.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_GCC_toolchains->setIcon(icon11);
        action_View_Heaps_Allocators = new QAction(MTunerClass);
        action_View_Heaps_Allocators->setObjectName(QStringLiteral("action_View_Heaps_Allocators"));
        action_View_Heaps_Allocators->setCheckable(true);
        action_View_Heaps_Allocators->setChecked(true);
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/MTuner/resources/images/Heaps.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_View_Heaps_Allocators->setIcon(icon12);
        actionOpen_capture_storage = new QAction(MTunerClass);
        actionOpen_capture_storage->setObjectName(QStringLiteral("actionOpen_capture_storage"));
        action_Save_capture_window_layout = new QAction(MTunerClass);
        action_Save_capture_window_layout->setObjectName(QStringLiteral("action_Save_capture_window_layout"));
        CentralWidget = new QWidget(MTunerClass);
        CentralWidget->setObjectName(QStringLiteral("CentralWidget"));
        gridLayout = new QGridLayout(CentralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        MTunerClass->setCentralWidget(CentralWidget);
        menuBar = new QMenuBar(MTunerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 26));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        menu_Settings = new QMenu(menuBar);
        menu_Settings->setObjectName(QStringLiteral("menu_Settings"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QStringLiteral("menu_View"));
        menuLanguage = new QMenu(menuBar);
        menuLanguage->setObjectName(QStringLiteral("menuLanguage"));
        MTunerClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MTunerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MTunerClass->setStatusBar(statusBar);
        toolBar = new QToolBar(MTunerClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MTunerClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Settings->menuAction());
        menuBar->addAction(menuLanguage->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Close);
        menu_File->addSeparator();
        menu_File->addAction(actionOpen_capture_storage);
        menu_File->addSeparator();
        menu_File->addAction(action_Manage_projects);
        menu_File->addSeparator();
        menu_File->addAction(action_Exit);
        menu_Help->addAction(action_Contents);
        menu_Help->addSeparator();
        menu_Help->addSeparator();
        menu_Help->addSeparator();
        menu_Help->addAction(action_About);
        menu_Settings->addAction(action_Symbols);
        menu_Settings->addAction(action_External_editor);
        menu_Settings->addAction(action_GCC_toolchains);
        menu_Settings->addSeparator();
        menu_Settings->addAction(action_Save_capture_window_layout);
        menu_View->addAction(action_View_Memory_Graph);
        menu_View->addAction(action_View_Memory_Stats);
        menu_View->addAction(action_View_Histograms);
        menu_View->addAction(action_View_Tag_Tree);
        menu_View->addAction(action_View_Heaps_Allocators);
        toolBar->addAction(action_Open);
        toolBar->addAction(action_Manage_projects);
        toolBar->addAction(action_Symbols);
        toolBar->addAction(action_Filters);
        toolBar->addAction(action_View_Memory_Stats);
        toolBar->addAction(action_View_Tag_Tree);
        toolBar->addAction(action_View_Heaps_Allocators);
        toolBar->addAction(action_View_Memory_Graph);
        toolBar->addAction(action_View_Histograms);
        toolBar->addAction(action_View_StackTrace);
        toolBar->addSeparator();

        retranslateUi(MTunerClass);
        QObject::connect(action_Manage_projects, SIGNAL(triggered()), MTunerClass, SLOT(manageProjects()));
        QObject::connect(action_Symbols, SIGNAL(triggered()), MTunerClass, SLOT(setupSymbols()));
        QObject::connect(action_Open, SIGNAL(triggered()), MTunerClass, SLOT(openFile()));
        QObject::connect(action_Close, SIGNAL(triggered()), MTunerClass, SLOT(closeFile()));
        QObject::connect(action_Exit, SIGNAL(triggered()), MTunerClass, SLOT(exit()));
        QObject::connect(action_Filters, SIGNAL(toggled(bool)), MTunerClass, SLOT(setFilters(bool)));
        QObject::connect(action_Contents, SIGNAL(triggered()), MTunerClass, SLOT(readDocumentation()));
        QObject::connect(action_About, SIGNAL(triggered()), MTunerClass, SLOT(about()));
        QObject::connect(MTunerClass, SIGNAL(binLoaded(bool)), action_Close, SLOT(setEnabled(bool)));
        QObject::connect(action_View_Histograms, SIGNAL(toggled(bool)), MTunerClass, SLOT(showHistogram(bool)));
        QObject::connect(action_View_Memory_Graph, SIGNAL(toggled(bool)), MTunerClass, SLOT(showGraph(bool)));
        QObject::connect(action_View_Memory_Stats, SIGNAL(toggled(bool)), MTunerClass, SLOT(showStats(bool)));
        QObject::connect(action_View_Tag_Tree, SIGNAL(toggled(bool)), MTunerClass, SLOT(showTagTree(bool)));
        QObject::connect(MTunerClass, SIGNAL(setFilterState(bool)), action_Filters, SLOT(setChecked(bool)));
        QObject::connect(MTunerClass, SIGNAL(setFilterButtonEnabled(bool)), action_Filters, SLOT(setEnabled(bool)));
        QObject::connect(action_View_StackTrace, SIGNAL(toggled(bool)), MTunerClass, SLOT(showStackTrace(bool)));
        QObject::connect(action_External_editor, SIGNAL(triggered()), MTunerClass, SLOT(setupEditor()));
        QObject::connect(action_GCC_toolchains, SIGNAL(triggered()), MTunerClass, SLOT(setupGCCToolchains()));
        QObject::connect(action_View_Heaps_Allocators, SIGNAL(toggled(bool)), MTunerClass, SLOT(showHeaps(bool)));
        QObject::connect(actionOpen_capture_storage, SIGNAL(triggered()), MTunerClass, SLOT(openCaptureLocation()));

        QMetaObject::connectSlotsByName(MTunerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MTunerClass)
    {
        MTunerClass->setWindowTitle(QApplication::translate("MTunerClass", "MTuner", Q_NULLPTR));
        action_Open->setText(QApplication::translate("MTunerClass", "&Open", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Open->setToolTip(QApplication::translate("MTunerClass", "Open capture (.MTuner file)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        action_Open->setShortcut(QApplication::translate("MTunerClass", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Exit->setText(QApplication::translate("MTunerClass", "&Exit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Exit->setShortcut(QApplication::translate("MTunerClass", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_About->setText(QApplication::translate("MTunerClass", "&About", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_About->setToolTip(QApplication::translate("MTunerClass", "About MTuner", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Manage_projects->setText(QApplication::translate("MTunerClass", "&Manage projects", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Manage_projects->setShortcut(QApplication::translate("MTunerClass", "Ctrl+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Close->setText(QApplication::translate("MTunerClass", "&Close", Q_NULLPTR));
        action_Symbols->setText(QApplication::translate("MTunerClass", "&Debug symbols", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Symbols->setToolTip(QApplication::translate("MTunerClass", "Debug symbol sources setting", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Contents->setText(QApplication::translate("MTunerClass", "&Contents", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Contents->setShortcut(QApplication::translate("MTunerClass", "F1", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Filters->setText(QApplication::translate("MTunerClass", "Toggle &filtering mode", Q_NULLPTR));
        action_Filters->setIconText(QApplication::translate("MTunerClass", "Toggle filtering mode", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Filters->setToolTip(QApplication::translate("MTunerClass", "Toggle filtering mode", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        action_Filters->setShortcut(QApplication::translate("MTunerClass", "Ctrl+F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_View_Memory_Graph->setText(QApplication::translate("MTunerClass", "Ti&meline", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_View_Memory_Graph->setToolTip(QApplication::translate("MTunerClass", "Toggle timeline graph visibility", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_View_Memory_Stats->setText(QApplication::translate("MTunerClass", "&Statistics", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_View_Memory_Stats->setToolTip(QApplication::translate("MTunerClass", "Toggle statistics visibility", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_English->setText(QApplication::translate("MTunerClass", "&English", Q_NULLPTR));
        action_View_Histograms->setText(QApplication::translate("MTunerClass", "&Histograms", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_View_Histograms->setToolTip(QApplication::translate("MTunerClass", "Toggle histogram window visibility", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_View_Tag_Tree->setText(QApplication::translate("MTunerClass", "&Tag Tree", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_View_Tag_Tree->setToolTip(QApplication::translate("MTunerClass", "Toggle tag tree visibility", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_View_StackTrace->setText(QApplication::translate("MTunerClass", "StackTrace", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_View_StackTrace->setToolTip(QApplication::translate("MTunerClass", "Toggle stack trace and source visibility", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_External_editor->setText(QApplication::translate("MTunerClass", "&External editor", Q_NULLPTR));
        action_Import_license_file->setText(QApplication::translate("MTunerClass", "Import license file", Q_NULLPTR));
        action_Activation_MTuner->setText(QApplication::translate("MTunerClass", "Activate MTuner", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Activation_MTuner->setToolTip(QApplication::translate("MTunerClass", "Deactivate MTuner", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_GCC_toolchains->setText(QApplication::translate("MTunerClass", "&Toolchains Setup", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_GCC_toolchains->setShortcut(QApplication::translate("MTunerClass", "Ctrl+G", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_View_Heaps_Allocators->setText(QApplication::translate("MTunerClass", "Heaps / Allocators", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_View_Heaps_Allocators->setToolTip(QApplication::translate("MTunerClass", "Toggle visibility of heaps / allocators dock", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionOpen_capture_storage->setText(QApplication::translate("MTunerClass", "Open capture location", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpen_capture_storage->setToolTip(QApplication::translate("MTunerClass", "Opens, in Windows Explorer, a folder where capture files (*.MTuner) are recorder", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Save_capture_window_layout->setText(QApplication::translate("MTunerClass", "&Save capture window settings", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("MTunerClass", "&File", Q_NULLPTR));
        menu_Help->setTitle(QApplication::translate("MTunerClass", "&Help", Q_NULLPTR));
        menu_Settings->setTitle(QApplication::translate("MTunerClass", "&Settings", Q_NULLPTR));
        menu_View->setTitle(QApplication::translate("MTunerClass", "&View", Q_NULLPTR));
        menuLanguage->setTitle(QApplication::translate("MTunerClass", "&Language", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MTunerClass", "Main tool bar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MTunerClass: public Ui_MTunerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MTUNER_UI_H
