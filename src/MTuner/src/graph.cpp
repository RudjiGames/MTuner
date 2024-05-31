//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/graph.h>
#include <MTuner/src/binloaderview.h>
#include <MTuner/src/capturecontext.h>

Graph::Graph(QWidget* _parent, Qt::WindowFlags _flags) : 
	QWidget(_parent, _flags)
{
	ui.setupUi(this);

	m_graph = findChild<GraphWidget*>("graphWidget");

	connect(m_graph, SIGNAL(snapshotSelected()), this, SLOT(snapshotSelected()));
	connect(m_graph, SIGNAL(minMaxChanged()), this, SLOT(zoomChanged()));

	m_buttonZoomIn = findChild<QToolButton*>("buttonZoomIn");
	connect(m_buttonZoomIn,SIGNAL(clicked()), m_graph, SLOT(zoomIn()));

	m_buttonZoomOut = findChild<QToolButton*>("buttonZoomOut");
	connect(m_buttonZoomOut,SIGNAL(clicked()), m_graph, SLOT(zoomOut()));

	m_buttonZoomReset = findChild<QToolButton*>("buttonZoomReset");
	connect(m_buttonZoomReset,SIGNAL(clicked()), m_graph, SLOT(zoomReset()));

	m_buttonZoomSelect = findChild<QToolButton*>("buttonZoomSelection");
	connect(m_buttonZoomSelect,SIGNAL(clicked()), m_graph, SLOT(zoomSelect()));

	m_buttonAutoZoom = findChild<QToolButton*>("buttonZoomAuto");
	connect(m_buttonAutoZoom, SIGNAL(clicked()), m_graph, SLOT(zoomAnimEvent()));

	m_scroll = findChild<QScrollBar*>("scrollBar");
	connect(m_scroll, SIGNAL(sliderMoved(int)), this, SLOT(scrollMoved(int)));

	m_graph->setGraph(this);

	setContext(NULL,NULL);
}

void Graph::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void Graph::setContext(CaptureContext* _context, BinLoaderView* _binView)
{
	m_context = _context;
	m_graph->setContext(_context, _binView);
	if (!_context)
	{
		m_buttonZoomIn->setEnabled(false);
		m_buttonZoomOut->setEnabled(false);
		m_buttonZoomReset->setEnabled(false);
		m_buttonZoomSelect->setEnabled(false);
		m_scroll->setEnabled(false);
		m_buttonAutoZoom->setEnabled(false);
	}
	else
	{
		m_buttonZoomIn->setEnabled(true);
		m_buttonZoomOut->setEnabled(false);
		m_buttonZoomReset->setEnabled(false);
		m_buttonZoomSelect->setEnabled(false);
		m_scroll->setEnabled(false);
		m_buttonAutoZoom->setEnabled(true);
	}
	
	m_scroll->setEnabled(false);
}

bool Graph::isAutoZoomSet() const
{
	return m_buttonAutoZoom ? m_buttonAutoZoom->isChecked() : true;
}

void Graph::snapshotSelected()
{
	if ((m_context->m_capture->getMinTime() != m_context->m_capture->getSnapshotTimeMin()) ||
		(m_context->m_capture->getMaxTime() != m_context->m_capture->getSnapshotTimeMax()))
	{
		m_buttonZoomSelect->setEnabled(true);
	}
	else
	{
		m_buttonZoomSelect->setEnabled(false);
	}
}

void Graph::zoomChanged()
{
	if ((m_context->m_capture->getMinTime() != m_graph->minTime()) ||
		(m_context->m_capture->getMaxTime() != m_graph->maxTime()))
	{
		m_buttonZoomReset->setEnabled(true);
		m_buttonZoomOut->setEnabled(true);
		m_scroll->setEnabled(true);
		
		float visRange = m_graph->maxTime() - m_graph->minTime();
		float hVisRange = visRange*0.5f;

		float newMin = m_context->m_capture->getMinTime() + hVisRange;
		float newMax = m_context->m_capture->getMaxTime() - hVisRange;

		m_scroll->setValue(m_scroll->maximum() * (m_graph->minTime() - m_context->m_capture->getMinTime()) / (newMax-newMin));
	}
	else
	{
		m_buttonZoomReset->setEnabled(false);
		m_buttonZoomOut->setEnabled(false);
		m_scroll->setEnabled(false);
		m_scroll->setValue(0);
	}
}

void Graph::scrollMoved(int _value)
{
	uint64_t visRange = m_graph->maxTime() - m_graph->minTime();
	uint64_t fullRange = m_context->m_capture->getMaxTime() - m_context->m_capture->getMinTime();
	uint64_t range = fullRange - visRange;
	float ratio = float(_value)/float(m_scroll->maximum());
	uint64_t min = m_context->m_capture->getMinTime() + range*ratio;
	uint64_t max = min + visRange;
	min = qMax(min, m_context->m_capture->getMinTime());
	max = qMin(max, m_context->m_capture->getMaxTime());
	m_graph->setMinMaxTime( min, max );
}

void Graph::highlightTime(uint64_t _time)
{
	m_graph->highlightTime(_time);
}

void Graph::highlightRange(uint64_t _minTime, uint64_t _maxTime)
{
	m_graph->highlightRange(_minTime, _maxTime);
}
