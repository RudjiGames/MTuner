//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/mtuner.h>
#include <MTuner/src/stacktrace.h>
#include <MTuner/src/capturecontext.h>

#include <rbase/inc/path.h>

bool QToolTipper::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::ToolTip)
	{
		QAbstractItemView* view = qobject_cast<QAbstractItemView*>(obj->parent());
		if (!view)
			return false;

		QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
		QPoint pos = helpEvent->pos();
		QModelIndex index = view->indexAt(pos);
		if (!index.isValid())
			return false;

		QString itemText = view->model()->data(index).toString();
		QString itemTooltip = view->model()->data(index, Qt::ToolTipRole).toString();

		QFontMetrics fm(view->font());
		int itemTextWidth = fm.horizontalAdvance(itemText);
		QRect rect = view->visualRect(index);
		int rectWidth = rect.width();

		// only elided text
		if ((itemTextWidth > rectWidth) && !itemTooltip.isEmpty())
			QToolTip::showText(helpEvent->globalPos(), itemTooltip, view, rect);
		else
			QToolTip::hideText();

		return true;
	}
	return false;
}

enum StackTraceColumns
{
	Module,
	Function,
	File,
	Line,
	Path
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

	m_actionCopy	= new QAction(QString(tr("Copy")), this);
	m_actionCopyAll	= new QAction(QString(tr("Copy all")), this);

	m_contextMenu = new QMenu();
	m_contextMenu->addAction(m_actionCopy);
	m_contextMenu->addAction(m_actionCopyAll);

	connect(m_actionCopy,		SIGNAL(triggered()), this, SLOT(copy()));
	connect(m_actionCopyAll,	SIGNAL(triggered()), this, SLOT(copyAll()));
	copyResetIndex();

	updateView();
}

void StackTrace::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void StackTrace::contextMenuEvent(QContextMenuEvent* _event)
{
	if (!m_context)
		return;

	QPoint pos = m_table->viewport()->mapFromGlobal(_event->globalPos());
	m_copyIndex = m_table->indexAt(pos).row();

	if (m_copyIndex != -1)
		m_contextMenu->exec(mapToGlobal(_event->pos()));
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
	QTableWidgetItem* lineItem = m_table->item(_currentRow, StackTraceColumns::Line);
	QTableWidgetItem* funcItem = m_table->item(_currentRow, StackTraceColumns::Function);
	QTableWidgetItem* pathItem = m_table->item(_currentRow, StackTraceColumns::Path);

	if (!lineItem || !funcItem || !pathItem)
		return;

	QString file = pathItem->text();
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

QTableWidgetItem* makeItemWithTooltip(const QString& _string)
{
	QTableWidgetItem* item = new QTableWidgetItem(_string);
	item->setToolTip(_string);
	return item;
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
	m_table->viewport()->installEventFilter(new QToolTipper(m_table));
	m_table->setRowCount(rows);
	uint32_t selectedRow = rows;

	for (uint32_t i=0; i<rows; ++i)
	{
		uint64_t address = m_currentTrace[m_currentTraceIdx]->m_entries[i];
		rdebug::StackFrame frame;
		m_context->resolveStackFrame(address, frame);

		QString sourcefile	= QString::fromUtf8(frame.m_file);
		QString func		= QString::fromUtf8(frame.m_func);
		QString symStoreDir	= QString::fromUtf8(m_context->getSymbolStoreDir().c_str());

		QFileInfo info(QDir(symStoreDir), sourcefile);
		if (info.exists())
			sourcefile = info.absoluteFilePath();

		QTableWidgetItem* item = new QTableWidgetItem(frame.m_moduleName);
		item->setToolTip(frame.m_moduleName);

		// module, file, line, function, Path
		m_table->setItem(i, StackTraceColumns::Module,		makeItemWithTooltip(frame.m_moduleName));
		m_table->setItem(i, StackTraceColumns::Function,	makeItemWithTooltip(func));
		m_table->setItem(i, StackTraceColumns::File,		makeItemWithTooltip(QString::fromUtf8(rtm::pathGetFileName(frame.m_file))));
		m_table->setItem(i, StackTraceColumns::Line,		new QTableWidgetItem(QString::number(frame.m_line)));
		m_table->setItem(i, StackTraceColumns::Path,		makeItemWithTooltip(QString::fromUtf8(frame.m_file)));

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

void StackTrace::loadState(QSettings& _settings, const QString& _name, bool _resetGeometries)
{
	m_settingsGroupName = _name;

	_settings.beginGroup(m_settingsGroupName);
	if (!_resetGeometries)
	{
		restoreGeometry(_settings.value("stackTraceGeometry").toByteArray());
		m_table->horizontalHeader()->restoreState(_settings.value("stackTraceHeader").toByteArray());
	}
	_settings.endGroup();
}

void StackTrace::saveState(QSettings& _settings)
{
	_settings.beginGroup(m_settingsGroupName);
	_settings.setValue("stackTraceGeometry", saveGeometry());
	_settings.setValue("stackTraceHeader", m_table->horizontalHeader()->saveState());
	_settings.endGroup();
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

void StackTrace::copy()
{
	QString text;
	text += m_table->item(m_copyIndex, StackTraceColumns::Module)->text()	+ '\t';
	text += m_table->item(m_copyIndex, StackTraceColumns::Function)->text()	+ '\t';
	text += m_table->item(m_copyIndex, StackTraceColumns::File)->text()		+ '\t';
	text += m_table->item(m_copyIndex, StackTraceColumns::Line)->text()		+ '\t';
	text += m_table->item(m_copyIndex, StackTraceColumns::Path)->text()		+ '\n';

	QApplication::clipboard()->setText(text);
	copyResetIndex();
}

void StackTrace::copyAll()
{
	const uint32_t rows = m_currentTrace[m_currentTraceIdx]->m_numEntries;

	QString text;
	for (uint32_t i=0; i<rows; ++i)
	{
		text += m_table->item(i, StackTraceColumns::Module)->text()		+ '\t';
		text += m_table->item(i, StackTraceColumns::Function)->text()	+ '\t';
		text += m_table->item(i, StackTraceColumns::File)->text()		+ '\t';
		text += m_table->item(i, StackTraceColumns::Line)->text()		+ '\t';
		text += m_table->item(i, StackTraceColumns::Path)->text()		+ '\n';
	}

	QApplication::clipboard()->setText(text);
	copyResetIndex();
}

void StackTrace::copyResetIndex()
{
	m_copyIndex = -1;
}
