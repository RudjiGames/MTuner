/********************************************************************************
** Form generated from reading UI file 'external_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EXTERNAL_EDITOR_UI_H
#define EXTERNAL_EDITOR_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExternalEditor
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelEditor;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditEditor;
    QToolButton *toolButtonBrowseEditor;
    QLineEdit *lineEditCmdLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExternalEditor)
    {
        if (ExternalEditor->objectName().isEmpty())
            ExternalEditor->setObjectName(QStringLiteral("ExternalEditor"));
        ExternalEditor->resize(571, 138);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MTuner/resources/images/Editor64.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExternalEditor->setWindowIcon(icon);
        horizontalLayout_3 = new QHBoxLayout(ExternalEditor);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelEditor = new QLabel(ExternalEditor);
        labelEditor->setObjectName(QStringLiteral("labelEditor"));

        verticalLayout_2->addWidget(labelEditor);

        label_2 = new QLabel(ExternalEditor);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEditEditor = new QLineEdit(ExternalEditor);
        lineEditEditor->setObjectName(QStringLiteral("lineEditEditor"));
        lineEditEditor->setText(QStringLiteral("devenv.exe"));

        horizontalLayout->addWidget(lineEditEditor);

        toolButtonBrowseEditor = new QToolButton(ExternalEditor);
        toolButtonBrowseEditor->setObjectName(QStringLiteral("toolButtonBrowseEditor"));

        horizontalLayout->addWidget(toolButtonBrowseEditor);


        verticalLayout->addLayout(horizontalLayout);

        lineEditCmdLine = new QLineEdit(ExternalEditor);
        lineEditCmdLine->setObjectName(QStringLiteral("lineEditCmdLine"));
        lineEditCmdLine->setText(QStringLiteral("\"%F\" /Command \"Edit.GoTo %L\""));

        verticalLayout->addWidget(lineEditCmdLine);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ExternalEditor);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);


        retranslateUi(ExternalEditor);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExternalEditor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExternalEditor, SLOT(reject()));
        QObject::connect(toolButtonBrowseEditor, SIGNAL(clicked()), ExternalEditor, SLOT(browseForEditor()));

        QMetaObject::connectSlotsByName(ExternalEditor);
    } // setupUi

    void retranslateUi(QDialog *ExternalEditor)
    {
        ExternalEditor->setWindowTitle(QApplication::translate("ExternalEditor", "Setup external editor", Q_NULLPTR));
        labelEditor->setText(QApplication::translate("ExternalEditor", "Editor:", Q_NULLPTR));
        label_2->setText(QApplication::translate("ExternalEditor", "Command line:", Q_NULLPTR));
        toolButtonBrowseEditor->setText(QApplication::translate("ExternalEditor", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ExternalEditor: public Ui_ExternalEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // EXTERNAL_EDITOR_UI_H
