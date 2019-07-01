//--------------------------------------------------------------------------//
/// Copyright (c) 2018 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/mtuner.h>
#include <MTuner/src/stacktrace.h>
#include <MTuner/src/capturecontext.h>

enum StackTraceColumns
{
	Module,
	Function,
	File,
	Line
};

StackTrace::StackTrace(QWidget* _parent, Qt::WindowFlags _flags) : 
	QWidget(_parent, _flags)
{
	m_context			= NULL;
	m_currentTrace		= NULL;
	m_currentTraceCnt	= 0;
	m_currentTraceIdx	= 0;

	ui.setupUi(this);

	m_table = findChild<QTableWidget*>("tableWidget");
	m_table->horizontalHeader()->setHighlightSections(false);
	connect(m_table, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(currentCellChanged(int, int, int, int)));

	m_buttonDec		= findChild<QToolButton*>("button_dec");
	m_buttonInc		= findChild<QToolButton*>("button_inc");
	m_spinBox		= findChild<QSpinBox*>("spinBox");
	m_totalTraces	= findChild<QLabel*>("label_total");

	updateView();
}

void StackTrace::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void StackTrace::setContext(CaptureContext* _context)
{
	m_context		= _context;
	m_currentTrace	= 0;
	updateView();
}

void StackTrace::clear()
{
	m_selectedFunc.clear();
	m_table->setRowCount(0);
	m_table->update();
}

void StackTrace::currentCellChanged(int _currentRow, int _currentColumn, int _previousRow, int _previousColumn)
{
	RTM_UNUSED_3(_currentColumn, _previousRow, _previousColumn);
	QTableWidgetItem* fileItem = m_table->item(_currentRow, StackTraceColumns::File);
	QTableWidgetItem* lineItem = m_table->item(_currentRow, StackTraceColumns::Line);
	QTableWidgetItem* funcItem = m_table->item(_currentRow, StackTraceColumns::Function);

	if (!fileItem || !lineItem || !funcItem)
		return;

	QString file = fileItem->text();
	int		line = lineItem->text().toInt();
	m_selectedFunc	= funcItem->text();
	emit openFile(file, line, 0);
}

void StackTrace::setStackTrace(rtm::StackTrace** _stackTrace, int _num)
{
	m_currentTrace		= _stackTrace;

	if (_stackTrace && (_stackTrace[0] == 0))
	{
		m_currentTrace	= 0;
		_num			= 0;
	}

	m_currentTraceCnt	= _num;
	m_currentTraceIdx	= 0;

	updateView();
}

void StackTrace::setCount(uint32_t _cnt)
{
	m_totalTraces->setText(tr("of") + " " + QString::number(_cnt));
	m_spinBox->setValue(_cnt ? m_currentTraceIdx + 1 : 0);
	m_spinBox->setMinimum(_cnt ? 1 : 0);
	m_spinBox->setMaximum(_cnt ? _cnt : 0);
	m_spinBox->setEnabled(_cnt != 0);
	m_buttonDec->setEnabled(_cnt != 0);
	m_buttonInc->setEnabled(_cnt != 0);
}

void StackTrace::updateView()
{
	if (!m_currentTrace)
	{
		m_selectedFunc.clear();
		m_table->setRowCount(0);
		emit openFile("", 0, 0);
		setCount(0);
		return;
	}

	setCount(m_currentTraceCnt);

	const uint32_t rows = m_currentTrace[m_currentTraceIdx]->m_numEntries;
	m_table->model()->removeRows(0, m_table->model()->rowCount());
	m_table->setRowCount(rows);
	uint32_t selectedRow = rows;

	for (uint32_t i=0; i<rows; ++i)
	{
		uint64_t address = m_currentTrace[m_currentTraceIdx]->m_entries[i];
		rdebug::StackFrame frame;
		m_context->resolveStackFrame(address, frame);

		QString sourcefile	= QString::fromUtf8(frame.m_file);
		QString module		= QString::fromUtf8(frame.m_moduleName);
		QString func		= QString::fromUtf8(frame.m_func);
		QString symStoreDir	= QString::fromUtf8(m_context->getSymbolStoreDir().c_str());

		QFileInfo info(QDir(symStoreDir), sourcefile);
		if (info.exists())
			sourcefile = info.absoluteFilePath();

		// module, file, line, function
		m_table->setItem(i, StackTraceColumns::Module,		new QTableWidgetItem(module));
		m_table->setItem(i, StackTraceColumns::Function,	new QTableWidgetItem(func));
		m_table->setItem(i, StackTraceColumns::File,		new QTableWidgetItem(sourcefile));
		m_table->setItem(i, StackTraceColumns::Line,		new QTableWidgetItem(QString::number(frame.m_line)));

		if (m_selectedFunc.compare(func) == 0)
			selectedRow = i;
	}

	m_table->update();
	m_table->setCurrentIndex(QModelIndex());
	if (selectedRow != rows)
	{
		m_table->selectRow(selectedRow);
		currentCellChanged(selectedRow, 0, 0, 0);
		return;
	}

	emit openFile("", 0, 0);
}

void StackTrace::saveState(QSettings& _settings)
{
	_settings.setValue("stackTraceGeometry", saveGeometry());
	_settings.setValue("stackTraceHeader", m_table->horizontalHeader()->saveState());
}

void StackTrace::loadState(QSettings& _settings)
{
	restoreGeometry(_settings.value("stackTraceGeometry").toByteArray());
	m_table->horizontalHeader()->restoreState(_settings.value("stackTraceHeader").toByteArray());
}

void StackTrace::incClicked()
{
	if (m_currentTraceIdx == (m_currentTraceCnt-1))
		return;
	++m_currentTraceIdx;
	updateView();
}

void StackTrace::decClicked()
{
	if (m_currentTraceIdx == 0)
		return;
	--m_currentTraceIdx;
	updateView();
}
