//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_OPERATIONSLIST_H__
#define __RTM_MTUNER_OPERATIONSLIST_H__

#include <mtuner/.qt/qt_ui/operationslist_ui.h>

struct CaptureContext;
class OperationTableSource;

class OperationsList : public QWidget
{
	Q_OBJECT

private:
	CaptureContext*			m_context;
	BigTable*				m_operationList;
	OperationSearch*		m_operationSearch;
	OperationTableSource*	m_tableSource;
	rtm::MemoryOperation*	m_currentItem;
	bool					m_enableFiltering;

	int						m_savedColumn;
	Qt::SortOrder			m_savedOrder;
	QByteArray				m_headerState;

public:
	OperationsList(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);
	~OperationsList();

	void changeEvent(QEvent* _event);

	void setContext(CaptureContext* _context);
	void setFilteringState(bool _state);
	bool getFilteringState() const;

	void saveState(QSettings& _settings);
	void loadState(QSettings& _settings);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);
	void highlightTime(uint64_t);

public Q_SLOTS:
	void selectionChanged(void*);
	void selectPrevious();
	void selectNext();
	void selectNextByAddress(uint64_t);
	void selectNextBySize(uint64_t);

private:
	Ui::OperationsListWidget ui;
};

#endif // __RTM_MTUNER_OPERATIONSLIST_H__
