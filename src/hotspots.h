//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_HOTSPOTS_H__
#define __RTM_MTUNER_HOTSPOTS_H__

#include <mtuner/src/grouplistwidget.h>
#include <mtuner/.qt/qt_ui/hotspot_ui.h>

class HotspotsWidget : public QWidget
{
	Q_OBJECT

	QTableWidget*	m_usageTable;
	GroupMapping*	m_usageMapping;
	QTableWidget*	m_peakUsageTable;
	GroupMapping*	m_peakUsageMapping;
	QTableWidget*	m_peakCountTable;
	GroupMapping*	m_peakCountUsageMapping;
	QTableWidget*	m_leaksTable;
	GroupMapping*	m_leaksMapping;

public:
	HotspotsWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);
	
	void changeEvent(QEvent* _event);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);

public Q_SLOTS:
	void usageSortingDone(GroupMapping*);
	void peakUsageSortingDone(GroupMapping*);
	void peakCountSortingDone(GroupMapping*);
	void leaksSortingDone(GroupMapping*);
	void rowSelected(QTableWidgetItem*);

private:
	Ui::hotspotWidget ui;
};

#endif // __RTM_MTUNER_HOTSPOTS_H__
