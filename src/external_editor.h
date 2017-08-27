//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_EXTERNALEDITOR_H
#define RTM_MTUNER_EXTERNALEDITOR_H

#include <mtuner/.qt/qt_ui/external_editor_ui.h>

class ExternalEditor : public QDialog
{
	Q_OBJECT

	QLineEdit*	m_editorText;
	QLineEdit*	m_editorArgs;

public:
	ExternalEditor(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void	changeEvent(QEvent* _event);
	void	setEditor(const QString& _editorPath);
	QString	getEditorPath() const { return m_editorText->text(); }
	void	setEditorArgs(const QString& _editorArgs);
	QString	getEditorArgs() const { return m_editorArgs->text(); }
	void	run();

public Q_SLOTS:
	void browseForEditor();

private:
	Ui::ExternalEditor ui;
};

#endif // RTM_MTUNER_EXTERNALEDITOR_H
