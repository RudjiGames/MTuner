//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/binloaderview.h>
#include <MTuner/src/operationslist.h>
#include <MTuner/src/capturecontext.h>

BinLoaderView::BinLoaderView(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);
	m_context			= NULL;
	m_savedStackTraces	= NULL;
	m_savedStackTracesCount = 0;

	m_histogramType		= 0;
	m_histogramMode		= 0;
	m_histogramPeaks	= false;
	m_filteringEnabled	= false;
	m_currentHeap		= (uint64_t)-1;

	m_tab			= findChild<QTabWidget*>("tabWidget");
	m_treeMap		= m_tab->findChild<TreeMapWidget*>("treeMapWidget");
	m_stackTree		= findChild<StackTreeWidget*>("stackTree");
	m_groupList		= findChild<GroupList*>("groupListWidget");
	m_operationList = findChild<OperationsList*>("operationsListWidget");
	m_hotspots		= findChild<HotspotsWidget*>("hotspotsWidget");
	m_operationListInvalid = findChild<OperationsList*>("invalidOpsWidget");
	m_operationListInvalid->setSearchVisible(false);

	connect(m_groupList, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SIGNAL(setStackTrace(rtm::StackTrace**,int)));
	connect(m_operationList, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SIGNAL(setStackTrace(rtm::StackTrace**,int)));
	connect(m_operationListInvalid, SIGNAL(setStackTrace(rtm::StackTrace**, int)), this, SIGNAL(setStackTrace(rtm::StackTrace**, int)));
	connect(m_treeMap, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SIGNAL(setStackTrace(rtm::StackTrace**,int)));
	connect(m_treeMap, SIGNAL(highlightTime(uint64_t)), this, SIGNAL(highlightTime(uint64_t)));
	connect(m_treeMap, SIGNAL(highlightRange(uint64_t, uint64_t)), this, SIGNAL(highlightRange(uint64_t, uint64_t)));
	connect(m_hotspots, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SIGNAL(setStackTrace(rtm::StackTrace**,int)));
	connect(m_stackTree, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SIGNAL(setStackTrace(rtm::StackTrace**,int)));
	connect(this, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SLOT(saveStackTrace(rtm::StackTrace**,int)));

	connect(m_groupList, SIGNAL(usageSortingDone(GroupMapping*)), m_hotspots, SLOT(usageSortingDone(GroupMapping*)));
	connect(m_groupList, SIGNAL(peakUsageSortingDone(GroupMapping*)), m_hotspots, SLOT(peakUsageSortingDone(GroupMapping*)));
	connect(m_groupList, SIGNAL(peakCountSortingDone(GroupMapping*)), m_hotspots, SLOT(peakCountSortingDone(GroupMapping*)));
	connect(m_groupList, SIGNAL(leaksSortingDone(GroupMapping*)), m_hotspots, SLOT(leaksSortingDone(GroupMapping*)));
	connect(m_groupList, SIGNAL(usageSortingDone(GroupMapping*)), m_hotspots, SLOT(usageSortingDone(GroupMapping*)));

	connect(m_operationList, SIGNAL(highlightTime(uint64_t)), this, SIGNAL(highlightTime(uint64_t)));
	connect(m_operationListInvalid, SIGNAL(highlightTime(uint64_t)), this, SIGNAL(highlightTime(uint64_t)));
	connect(m_groupList, SIGNAL(highlightTime(uint64_t)), this, SIGNAL(highlightTime(uint64_t)));
	connect(m_groupList, SIGNAL(highlightRange(uint64_t, uint64_t)), this, SIGNAL(highlightRange(uint64_t, uint64_t)));
	connect(m_hotspots, SIGNAL(highlightRange(uint64_t, uint64_t)), this, SIGNAL(highlightRange(uint64_t, uint64_t)));

	connect(m_groupList, SIGNAL(selectRange(uint64_t, uint64_t)), this, SIGNAL(selectRange(uint64_t, uint64_t)));

	readSettings();
}

void BinLoaderView::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

BinLoaderView::~BinLoaderView()
{
	delete m_context;
}

void BinLoaderView::setContext(CaptureContext* _context)
{
	m_context = _context;
	m_treeMap->setContext(_context);
	m_stackTree->setContext(_context);
	m_operationList->setContext(_context, true);
	m_operationListInvalid->setContext(_context, false);
	m_groupList->setContext(_context);
	m_minTime = m_context->m_capture->getMinTime();
	m_maxTime = m_context->m_capture->getMaxTime();
}

void BinLoaderView::setFilteringEnabled(bool _filter)
{
	m_filteringEnabled = _filter;
	m_context->m_capture->setFilteringEnabled(_filter);
	m_operationList->setFilteringState(_filter, m_operationList->isLeaksOnlyChecked());
	m_operationListInvalid->setFilteringState(_filter, m_operationList->isLeaksOnlyChecked());
	m_groupList->setFilteringState(_filter);
	m_stackTree->setFilteringState(_filter);
	m_treeMap->setFilteringState(_filter);
}

void BinLoaderView::saveStackTrace(rtm::StackTrace** _stackTrace, int _num)
{
	m_savedStackTraces		= _stackTrace;
	m_savedStackTracesCount	= _num;
}

extern bool g_resetWindowGeometries;

void BinLoaderView::readSettings()
{
	QSettings settings;

	settings.beginGroup("CaptureWindow");

	m_operationList->loadState(settings, "OpList", g_resetWindowGeometries);
	m_operationListInvalid->loadState(settings, "OpListInvalid", g_resetWindowGeometries);
	m_groupList->loadState(settings, "GroupList", g_resetWindowGeometries);
	m_stackTree->loadState(settings, "StackTrace", g_resetWindowGeometries);

	if (settings.contains("captureWindowTabIndex"))
		m_tab->setCurrentIndex(settings.value("captureWindowTabIndex").toInt());
	else
	{
		settings.endGroup();
		return;
	}

	settings.endGroup();
}

void BinLoaderView::saveSettings()
{
	QSettings settings;

	settings.beginGroup("CaptureWindow");

	settings.setValue("captureWindowTabIndex", m_tab->currentIndex());
	
	m_operationList->saveState(settings);
	m_operationListInvalid->saveState(settings);
	m_groupList->saveState(settings);
	m_stackTree->saveState(settings);

	settings.endGroup();
}
