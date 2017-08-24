//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_STACKTRACE_H__
#define __RTM_MTUNER_STACKTRACE_H__

#include <mtuner/.qt/qt_ui/stacktrace_ui.h>

class QSpinBox;
struct CaptureContext;

class StackTrace : public QWidget
{
	Q_OBJECT

private:
	rtm::StackTrace**	m_currentTrace;
	uint32_t			m_currentTraceCnt;
	uint32_t			m_currentTraceIdx;
	QTableWidget*		m_table;
	QToolButton*		m_buttonDec;
	QToolButton*		m_buttonInc;
	QSpinBox*			m_spinBox;
	QLabel*				m_totalTraces;
	CaptureContext*		m_context;
	rtm::StackTrace*	m_stackTrace;
	QString				m_selectedFunc;

public:
	StackTrace(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void changeEvent(QEvent* _event);
	void setContext(CaptureContext* _context);
	void clear();
	void updateView();
	void saveState(QSettings& _settings);
	void loadState(QSettings& _settings);

public Q_SLOTS:
	void selected(int _row, int _column);
	void setStackTrace(rtm::StackTrace** _stackTrace, int);
	void incClicked();
	void decClicked();

Q_SIGNALS:
	void openFile(const QString& _file, int _row, int _column);

private:
	void setCount(uint32_t _cnt);
	Ui::StackTrace ui;
};

#endif // __RTM_MTUNER_STACKTRACE_H__
