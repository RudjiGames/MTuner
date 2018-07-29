//--------------------------------------------------------------------------//
/// Copyright (c) 2018 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/stackandsource.h>
#include <MTuner/src/binloaderview.h>

StackAndSource::StackAndSource(ExternalEditor* _editorDlg, QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags),
	m_editorDialog(_editorDlg)
{
	ui.setupUi(this);

	m_source = findChild<SourceView*>("sourceViewWidget");
	m_source->setEditorDialog(m_editorDialog);
	m_stackTrace = findChild<StackTrace*>("stackTraceWidget");

	connect(m_stackTrace, SIGNAL(openFile(const QString&,int,int)), m_source, SLOT(openFile(const QString&,int,int)));
}

void StackAndSource::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void StackAndSource::setContext(CaptureContext* _context)
{
	m_source->setContext(_context);
	m_stackTrace->setContext(_context);
}

void StackAndSource::setStackTrace(rtm::StackTrace** _trace, int _num)
{
	m_stackTrace->setStackTrace(_trace, _num);
}
