//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_OPERATIONSLIST_H
#define RTM_MTUNER_OPERATIONSLIST_H

#include <MTuner/.qt/qt_ui/operationslist_ui.h>

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
	QString					m_settingsGroupName;

public:
	OperationsList(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);
	~OperationsList();

	bool isLeaksOnlyChecked() const { return m_operationSearch->isLeaksOnlyChecked(); }
	void changeEvent(QEvent* _event);

	void setContext(CaptureContext* _context, bool _valid = false);
	void setFilteringState(bool _state, bool _leaksOnly);
	bool getFilteringState() const;
	void setSearchVisible(bool _visible) { m_operationSearch->setVisible(_visible);  }

	void loadState(QSettings& _settings, const QString& _name, bool _resetGeometry);
	void saveState(QSettings& _settings);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);
	void highlightTime(uint64_t);

public Q_SLOTS:
	void selectionChanged(void*);
	void selectPrevious();
	void selectNext();
	void selectNextByAddress(uint64_t);
	void selectNextBySize(uint64_t);
	void toggleLeaksOnly(bool);

private:
	Ui::OperationsListWidget ui;
};

#endif // RTM_MTUNER_OPERATIONSLIST_H
