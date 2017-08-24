//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <mtuner_pch.h>
#include <mtuner/src/external_editor.h>

ExternalEditor::ExternalEditor(QWidget* _parent, Qt::WindowFlags _flags) : 
	QDialog(_parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
	RTM_UNUSED(_flags);
	ui.setupUi(this);
	m_editorText = findChild<QLineEdit*>("lineEditEditor");
	m_editorArgs = findChild<QLineEdit*>("lineEditCmdLine");
}

void ExternalEditor::changeEvent(QEvent* _event)
{
	QDialog::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void ExternalEditor::setEditor(const QString& _editorPath)
{
	m_editorText->setText(_editorPath);
}

void ExternalEditor::setEditorArgs(const QString& _editorArgs)
{
	m_editorArgs->setText(_editorArgs);
}

void ExternalEditor::run()
{
	QString exe = m_editorText->text();
	QString arg = m_editorArgs->text();
	int r = exec();
	if (r == QDialog::Rejected)
	{
		m_editorText->setText(exe);
		m_editorArgs->setText(arg);
	}
}

void ExternalEditor::browseForEditor()
{
	QString exe = QFileDialog::getOpenFileName(this, tr("Select executable"), "", "exe files (*.exe)");
	if (exe.size() != 0)
		m_editorText->setText(exe);
}
