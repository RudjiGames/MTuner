//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GROUPLISTWIDGET_H
#define RTM_MTUNER_GROUPLISTWIDGET_H

#include <MTuner/.qt/qt_ui/grouplist_ui.h>

class GroupTableSource;
struct CaptureContext;

struct GroupMapping
{
	uint32_t								m_columnIndex;
	rtm_vector<rtm::MemoryOperationGroup*>*	m_allGroups;
	rtm_vector<uint32_t>					m_sortedIdx;
};

class GroupList : public QWidget
{
	Q_OBJECT

private:
	CaptureContext*		m_context;
	BigTable*			m_groupList;
	GroupTableSource*	m_tableSource;
	bool				m_enableFiltering;
	uint64_t			m_lastRange[2];
	QAction*			m_selectAction;
	QMenu*				m_contextMenu;

	int					m_savedColumn;
	Qt::SortOrder		m_savedOrder;
	QByteArray			m_headerState;
	QString				m_settingsGroupName;

public:
	GroupList(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);
	~GroupList();

	void changeEvent(QEvent* _event);
	void setContext(CaptureContext* _context);
	void setFilteringState(bool _state);
	bool getFilteringState() const;

	void loadState(QSettings& _settings, const QString& _name, bool _resetGeometry);
	void saveState(QSettings& _settings);

	void mouseMoveEvent(QMouseEvent* _event);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);
	void usageSortingDone(GroupMapping*);
	void peakUsageSortingDone(GroupMapping*);
	void peakCountSortingDone(GroupMapping*);
	void leaksSortingDone(GroupMapping*);
	void highlightTime(uint64_t);
	void highlightRange(uint64_t, uint64_t);
	void selectRange(uint64_t, uint64_t);

public Q_SLOTS:
	void selectionChanged(void*);
	void groupRightClick(void*, const QPoint&);
	void sortingDoneUsage();
	void sortingDonePeakUsage();
	void sortingDonePeakCount();
	void sortingDoneLeaks();
	void selectTriggered();

private:
	Ui::GroupListWidget ui;
};

#endif // RTM_MTUNER_GROUPLISTWIDGET_H
