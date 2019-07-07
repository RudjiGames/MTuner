//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_BINLOADERVIEW_H
#define RTM_MTUNER_BINLOADERVIEW_H

#include <MTuner/.qt/qt_ui/binloaderview_ui.h>
#include <MTuner/src/treemap.h>

class Hotspots;
class OperationsList;
class HotspotsWidget;
class StackTreeWidget;
struct CaptureContext;

class BinLoaderView : public QWidget
{
	Q_OBJECT

private:
	QTabWidget*			m_tab;
	TreeMapWidget*		m_treeMap;
	CaptureContext*		m_context;
	OperationsList*		m_operationList;
	GroupList*			m_groupList;
	HotspotsWidget*		m_hotspots;
	StackTreeWidget*	m_stackTree;
	uint64_t			m_minTime;
	uint64_t			m_maxTime;
	uint64_t			m_currentHeap;
	rdebug::ModuleInfo*	m_currentModule;
	rtm::StackTrace**	m_savedStackTraces;
	uint32_t			m_savedStackTracesCount;
	int					m_histogramType;
	int					m_histogramMode;
	bool				m_histogramPeaks;
	bool				m_filteringEnabled;

public:
	BinLoaderView(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);
	virtual ~BinLoaderView();

	CaptureContext*		getContext() { return m_context; }
	void				setContext(CaptureContext* _context);

	rtm::StackTrace**	getSavedStackTraces() { return m_savedStackTraces; }
	uint32_t			getSavedStackTracesCount() { return m_savedStackTracesCount; }

	void		changeEvent(QEvent* _event);
	void		setHistogramType(int _type) { m_histogramType = _type; }
	void		setHistogramMode(int _mode) { m_histogramMode = _mode; }
	void		setHistogramPeaks(bool _peaks) { m_histogramPeaks = _peaks; }
	int			getHistogramType() { return m_histogramType; }
	int			getHistogramMode() { return m_histogramMode; }
	bool		getHistogramPeaks() { return m_histogramPeaks; }
	uint64_t	getMinTime() { return m_minTime; }
	uint64_t	getMaxTime() { return m_maxTime; }
	void		setMinTime(uint64_t	_minTime) { m_minTime = _minTime; }
	void		setMaxTime(uint64_t	_maxTime) { m_maxTime = _maxTime; }
	uint64_t	getCurrentHeap() { return m_currentHeap; }
	void		setCurrentHeap(uint64_t inHeap) { m_currentHeap = inHeap; }
	rdebug::ModuleInfo* getCurrentModule() { return m_currentModule; }
	void		setCurrentModule(rdebug::ModuleInfo* _module) { m_currentModule = _module; }
	void		setFilteringEnabled(bool _filter);
	bool		getFilteringEnabled() const { return m_filteringEnabled; }

	void readSettings();
	void saveSettings();

public Q_SLOTS:
	void saveStackTrace(rtm::StackTrace**, int);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);
	void highlightTime(uint64_t);
	void highlightRange(uint64_t, uint64_t);
	void selectRange(uint64_t, uint64_t);

private:
	Ui::BinLoaderView ui;
};

#endif // RTM_MTUNER_BINLOADERVIEW_H
