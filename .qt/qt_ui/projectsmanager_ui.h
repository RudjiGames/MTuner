/********************************************************************************
** Form generated from reading UI file 'projectsmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PROJECTSMANAGER_UI_H
#define PROJECTSMANAGER_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProjectsDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *listOfProjects;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelExe;
    QLabel *labelCmdLine;
    QLabel *labelWorkingDir;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtExecutable;
    QPushButton *buttonBrowseExe;
    QLineEdit *txtCommandLine;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *txtWorkingDir;
    QPushButton *buttonBrowseWorkingDir;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *buttonAdd;
    QPushButton *buttonDelete;
    QPushButton *buttonRun;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonCancel;
    QPushButton *buttonOK;

    void setupUi(QDialog *ProjectsDialog)
    {
        if (ProjectsDialog->objectName().isEmpty())
            ProjectsDialog->setObjectName(QStringLiteral("ProjectsDialog"));
        ProjectsDialog->resize(477, 310);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProjectsDialog->sizePolicy().hasHeightForWidth());
        ProjectsDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Icon64.png"), QSize(), QIcon::Normal, QIcon::Off);
        ProjectsDialog->setWindowIcon(icon);
        verticalLayout_4 = new QVBoxLayout(ProjectsDialog);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        listOfProjects = new QTreeWidget(ProjectsDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        listOfProjects->setHeaderItem(__qtreewidgetitem);
        listOfProjects->setObjectName(QStringLiteral("listOfProjects"));
        listOfProjects->header()->setVisible(false);
        listOfProjects->header()->setDefaultSectionSize(24);

        verticalLayout_4->addWidget(listOfProjects);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelExe = new QLabel(ProjectsDialog);
        labelExe->setObjectName(QStringLiteral("labelExe"));
        labelExe->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(labelExe);

        labelCmdLine = new QLabel(ProjectsDialog);
        labelCmdLine->setObjectName(QStringLiteral("labelCmdLine"));
        labelCmdLine->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(labelCmdLine);

        labelWorkingDir = new QLabel(ProjectsDialog);
        labelWorkingDir->setObjectName(QStringLiteral("labelWorkingDir"));
        labelWorkingDir->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(labelWorkingDir);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        txtExecutable = new QLineEdit(ProjectsDialog);
        txtExecutable->setObjectName(QStringLiteral("txtExecutable"));

        horizontalLayout->addWidget(txtExecutable);

        buttonBrowseExe = new QPushButton(ProjectsDialog);
        buttonBrowseExe->setObjectName(QStringLiteral("buttonBrowseExe"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonBrowseExe->sizePolicy().hasHeightForWidth());
        buttonBrowseExe->setSizePolicy(sizePolicy1);
        buttonBrowseExe->setMaximumSize(QSize(42, 16777215));

        horizontalLayout->addWidget(buttonBrowseExe);


        verticalLayout_3->addLayout(horizontalLayout);

        txtCommandLine = new QLineEdit(ProjectsDialog);
        txtCommandLine->setObjectName(QStringLiteral("txtCommandLine"));

        verticalLayout_3->addWidget(txtCommandLine);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        txtWorkingDir = new QLineEdit(ProjectsDialog);
        txtWorkingDir->setObjectName(QStringLiteral("txtWorkingDir"));

        horizontalLayout_4->addWidget(txtWorkingDir);

        buttonBrowseWorkingDir = new QPushButton(ProjectsDialog);
        buttonBrowseWorkingDir->setObjectName(QStringLiteral("buttonBrowseWorkingDir"));
        sizePolicy1.setHeightForWidth(buttonBrowseWorkingDir->sizePolicy().hasHeightForWidth());
        buttonBrowseWorkingDir->setSizePolicy(sizePolicy1);
        buttonBrowseWorkingDir->setMaximumSize(QSize(42, 16777215));

        horizontalLayout_4->addWidget(buttonBrowseWorkingDir);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        buttonAdd = new QPushButton(ProjectsDialog);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));

        horizontalLayout_3->addWidget(buttonAdd);

        buttonDelete = new QPushButton(ProjectsDialog);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));

        horizontalLayout_3->addWidget(buttonDelete);

        buttonRun = new QPushButton(ProjectsDialog);
        buttonRun->setObjectName(QStringLiteral("buttonRun"));

        horizontalLayout_3->addWidget(buttonRun);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonCancel = new QPushButton(ProjectsDialog);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));

        horizontalLayout_3->addWidget(buttonCancel);

        buttonOK = new QPushButton(ProjectsDialog);
        buttonOK->setObjectName(QStringLiteral("buttonOK"));

        horizontalLayout_3->addWidget(buttonOK);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(ProjectsDialog);
        QObject::connect(buttonCancel, SIGNAL(clicked()), ProjectsDialog, SLOT(reject()));
        QObject::connect(buttonAdd, SIGNAL(clicked()), ProjectsDialog, SLOT(buttonAdd()));
        QObject::connect(buttonDelete, SIGNAL(clicked()), ProjectsDialog, SLOT(buttonRemove()));
        QObject::connect(buttonRun, SIGNAL(clicked()), ProjectsDialog, SLOT(buttonRun()));
        QObject::connect(buttonBrowseExe, SIGNAL(clicked()), ProjectsDialog, SLOT(browseExecutable()));
        QObject::connect(buttonBrowseWorkingDir, SIGNAL(clicked()), ProjectsDialog, SLOT(browseWorkingDir()));
        QObject::connect(buttonOK, SIGNAL(clicked()), ProjectsDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(ProjectsDialog);
    } // setupUi

    void retranslateUi(QDialog *ProjectsDialog)
    {
        ProjectsDialog->setWindowTitle(QApplication::translate("ProjectsDialog", "Projects manager", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ProjectsDialog->setToolTip(QApplication::translate("ProjectsDialog", "Hint: drag and drop an executable to the dialog", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        labelExe->setText(QApplication::translate("ProjectsDialog", "Executable", Q_NULLPTR));
        labelCmdLine->setText(QApplication::translate("ProjectsDialog", "Command line args", Q_NULLPTR));
        labelWorkingDir->setText(QApplication::translate("ProjectsDialog", "Working directory", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        txtExecutable->setToolTip(QApplication::translate("ProjectsDialog", "Path of executable to run in instrumented mode", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        buttonBrowseExe->setToolTip(QApplication::translate("ProjectsDialog", "Browse for executable", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonBrowseExe->setText(QApplication::translate("ProjectsDialog", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        txtCommandLine->setToolTip(QApplication::translate("ProjectsDialog", "Command line arguments for the executable", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txtWorkingDir->setToolTip(QApplication::translate("ProjectsDialog", "Directory to start the executable at. Leaving it empty will start the executable at it's location.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        buttonBrowseWorkingDir->setToolTip(QApplication::translate("ProjectsDialog", "Browse for a working directory", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonBrowseWorkingDir->setText(QApplication::translate("ProjectsDialog", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonAdd->setToolTip(QApplication::translate("ProjectsDialog", "Adds executable with run parameters to the list of projects", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonAdd->setText(QApplication::translate("ProjectsDialog", "Add", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonDelete->setToolTip(QApplication::translate("ProjectsDialog", "Deletes a project from the list", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonDelete->setText(QApplication::translate("ProjectsDialog", "Delete", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonRun->setToolTip(QApplication::translate("ProjectsDialog", "Run the MTuner instrumented executable", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonRun->setText(QApplication::translate("ProjectsDialog", "Run", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonCancel->setToolTip(QApplication::translate("ProjectsDialog", "Close dialog", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonCancel->setText(QApplication::translate("ProjectsDialog", "Cancel", Q_NULLPTR));
        buttonOK->setText(QApplication::translate("ProjectsDialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProjectsDialog: public Ui_ProjectsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PROJECTSMANAGER_UI_H
