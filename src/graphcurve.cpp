//--------------------------------------------------------------------------//
/// Copyright (c) 2018 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/graph.h>
#include <MTuner/src/graphcurve.h>
#include <MTuner/src/graphwidget.h>
#include <MTuner/src/capturecontext.h>

GraphCurve::GraphCurve(GraphWidget* _graphWidget)
{
	m_graphWidget	= _graphWidget;

	m_minUsage		= 0;
	m_maxUsage		= 0;
	m_prevMinTime	= 0;
	m_prevMaxTime	= 0;
	m_prevLeft		= 0;
	m_prevRight		= 0;
	m_prevPeakUsage = 0;
	m_prevMinUsage	= 0;
	m_prevPeakLive	= 0;
	m_prevMinLive	= 0;
}

void GraphCurve::setGraph(Graph* _graph)
{
	m_graph			= _graph;
	m_prevAutoZoom	= !m_graph->isAutoZoomSet();
}

QRectF GraphCurve::boundingRect() const
{
	QSize sz = m_graphWidget->size();
	return QRectF(-sz.width()/2, -sz.height()/2, sz.width()+1, sz.height());
}

QPainterPath GraphCurve::shape() const
{
    QPainterPath path;
	path.addRect( QRectF(-100, -100, 100, 100) );
    return path;
}

void GraphCurve::paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget)
{
	RTM_UNUSED(_option);
	RTM_UNUSED(_widget);
	CaptureContext* ctx = m_graphWidget->getContext();
	if (!(ctx && ctx->m_capture))
		return;

	bool autoZoom = m_graph->isAutoZoomSet();

	_painter->setRenderHint(QPainter::Antialiasing, true);

	QRect rect = m_graphWidget->getDrawRect();
	int left = rect.x();
	int top = rect.y();
	int right = rect.width() + rect.x();
	int bottom = rect.height() + rect.y();

	uint64_t minTime = m_graphWidget->minTime();
	uint64_t maxTime = m_graphWidget->maxTime();

	uint64_t displayTime = maxTime - minTime;

	int xcoord = left;
	rtm::GraphEntry entry;
	ctx->m_capture->getGraphAtTime(minTime, entry);
	const uint64_t startUsage	= entry.m_usage;
	const uint64_t startLive	= entry.m_numLiveBlocks;

	uint64_t peakUsage	= startUsage;
	uint64_t minUsage	= startUsage;

	uint64_t peakLive	= startLive;
	uint64_t minLive	= startLive;

	int32_t index;

	if ((m_prevMinTime != minTime) ||
		(m_prevMaxTime != maxTime) ||
		(m_prevLeft != left) ||
		(m_prevRight != right) || 
		(m_prevAutoZoom != autoZoom))
	{
		m_graphValues.resize(right-left);

		if (!autoZoom)
		{
			peakUsage	= ctx->m_capture->getGlobalStats().m_memoryUsagePeak;
			minUsage	= 0;

			peakLive	= ctx->m_capture->getGlobalStats().m_numberOfLiveBlocksPeak;
			minLive		= 0;
		}

		index = 0;
		double timeDelta =  double(displayTime) / double(right-left);
		double time = double(minTime);

		for (;xcoord<right;)
		{
			ctx->m_capture->getGraphAtTime((uint64_t)time, entry);
			
			m_graphValues[index++]	= entry;

			if (autoZoom)
			{
				peakUsage	= qMax(entry.m_usage, peakUsage);
				minUsage	= qMin(entry.m_usage, minUsage);

				peakLive	= qMax(entry.m_numLiveBlocks, peakLive);
				minLive		= qMin(entry.m_numLiveBlocks, minLive);
			}

			xcoord += 1;
			time += timeDelta;
			if (time > maxTime)
				time = maxTime;
		}

		m_prevPeakUsage = peakUsage;
		m_prevMinUsage	= minUsage;

		m_prevPeakLive	= peakLive;
		m_prevMinLive	= minLive;
	}
	else
	{
		peakUsage	= m_prevPeakUsage;
		minUsage	= m_prevMinUsage;

		peakLive	= m_prevPeakLive;
		minLive		= m_prevMinLive;
	}

	m_prevAutoZoom	= autoZoom;
	m_prevMinTime	= minTime;
	m_prevMaxTime	= maxTime;
	m_prevLeft		= left;
	m_prevRight		= right;

	xcoord = left;
	index = 0;

	int yUsage	= bottom - (bottom-top)/2;
	int yLive	= yUsage;

	if (peakUsage != minUsage)
	{
		peakUsage -= minUsage;
		yUsage	= bottom - ((startUsage - minUsage) * (bottom-top))/peakUsage;
	}

	if (peakLive != minLive)
	{
		peakLive -= minLive;
		yLive	= bottom - ((startLive - minLive) * (bottom-top))/peakLive;
	}

	QPainterPath pathUsageCurve;
	pathUsageCurve.moveTo(xcoord, yUsage);

	QPainterPath pathLiveCurve;
	pathLiveCurve.moveTo(xcoord, yLive);

	for (;xcoord<right;)
	{
		rtm::GraphEntry& entry_graph = m_graphValues[index++];

		yUsage	= bottom - ((entry_graph.m_usage		 - minUsage) * (bottom-top))/peakUsage;
		yLive	= bottom - ((entry_graph.m_numLiveBlocks - minLive)  * (bottom-top))/peakLive;

		pathUsageCurve.lineTo(xcoord, yUsage);
		pathLiveCurve.lineTo(xcoord, yLive);

		xcoord += 1;
	}

	_painter->setBrush(Qt::NoBrush);
	_painter->setPen(QPen(QColor(131, 207, 183, 150), 2.0, Qt::SolidLine));
	_painter->drawPath(pathLiveCurve);
	_painter->setPen(QPen(QColor(50, 150, 170), 2.0, Qt::SolidLine));
	_painter->drawPath(pathUsageCurve);

	// close 'em
	pathUsageCurve.lineTo(right, bottom);
	pathLiveCurve.lineTo(right, bottom);
	pathUsageCurve.lineTo(left, bottom);
	pathLiveCurve.lineTo(left, bottom);

	QLinearGradient gradLive(QPoint(left, top), QPoint(left, bottom));
	gradLive.setColorAt(0, QColor(131, 207, 183, 0));
	gradLive.setColorAt(1, QColor(131, 207, 183, 46));
	_painter->setPen(Qt::NoPen);
	_painter->fillPath(pathLiveCurve, gradLive);

	QLinearGradient gradUsage(QPoint(left, top), QPoint(left, bottom));
	gradUsage.setColorAt(0, QColor(50, 150, 170, 0));
	gradUsage.setColorAt(1, QColor(50, 150, 170, 46));
	_painter->setPen(Qt::NoPen);
	_painter->fillPath(pathUsageCurve, gradUsage);
}
