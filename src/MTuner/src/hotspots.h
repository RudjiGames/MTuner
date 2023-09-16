//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_HOTSPOTS_H
#define RTM_MTUNER_HOTSPOTS_H

#include <MTuner/src/grouplistwidget.h>
#include <MTuner/.qt/qt_ui/hotspot_ui.h>

class TableKeyWatcher : public QObject
{
	Q_OBJECT

	bool eventFilter(QObject* _receiver, QEvent* _event) override
	{
		QTableWidget* table = qobject_cast<QTableWidget*>(_receiver);
		if (table && _event->type() == QEvent::KeyPress)
		{
			auto keyEvent = static_cast<QKeyEvent*>(_event);
			if ((keyEvent->key() == Qt::Key_Up) ||
				(keyEvent->key() == Qt::Key_Down))
			{
				emit updateStackTrace(table);
			}
		}
		return false;
	}

Q_SIGNALS:
	void updateStackTrace(QTableWidget*);

public:
	void installOn(QTableWidget* _table)
	{
		_table->installEventFilter(this);
	}
};

class HotspotsWidget : public QWidget
{
	Q_OBJECT

	QTableWidget*		m_usageTable;
	GroupMapping*		m_usageMapping;
	QTableWidget*		m_peakUsageTable;
	GroupMapping*		m_peakUsageMapping;
	QTableWidget*		m_peakCountTable;
	GroupMapping*		m_peakCountUsageMapping;
	QTableWidget*		m_leaksTable;
	GroupMapping*		m_leaksMapping;
	TableKeyWatcher*	m_tableKeyWatch;

public:
	HotspotsWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);
	
	void changeEvent(QEvent* _event);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);
	void highlightRange(uint64_t, uint64_t);

public Q_SLOTS:
	void usageSortingDone(GroupMapping*);
	void peakUsageSortingDone(GroupMapping*);
	void peakCountSortingDone(GroupMapping*);
	void leaksSortingDone(GroupMapping*);
	void rowSelected(QTableWidgetItem*);
	void updateStackTrace(QTableWidget*);

private:
	Ui::hotspotWidget ui;
};

#endif // RTM_MTUNER_HOTSPOTS_H
