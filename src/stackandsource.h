//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_STACKANDSOURCE_H
#define RTM_MTUNER_STACKANDSOURCE_H

#include <MTuner/.qt/qt_ui/stackandsource_ui.h>

class BinLoaderView;
class ExternalEditor;

class StackAndSource : public QWidget
{
	Q_OBJECT

	StackTrace*		m_stackTrace;
	SourceView*		m_source;
	ExternalEditor*	m_editorDialog;

public:
	StackAndSource(ExternalEditor* inEditorDlg, QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);
	StackTrace*	getStackTrace() { return m_stackTrace; }

public Q_SLOTS:
	void setContext(CaptureContext*);
	void setStackTrace(rtm::StackTrace**, int);

private:
	Ui::StackAndSource ui;
};

#endif // RTM_MTUNER_STACKANDSOURCE_H
