//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/graphcurve.h>
#include <MTuner/src/graphmarkers.h>
#include <MTuner/src/graphwidget.h>
#include <MTuner/src/capturecontext.h>

GraphMarkers::GraphMarkers(GraphWidget* _graphWidget)
{
	m_graphWidget = _graphWidget;
}

MarkerToolTip GraphMarkers::getTooltip(const QPointF& _point) const
{
	MarkerToolTip ret;

	if (!m_graphWidget->getContext())
		return ret;

	CaptureContext* ctx = m_graphWidget->getContext();
	QRect rect = m_graphWidget->getDrawRect();
	int bottom = rect.height() + rect.y();

	const std::vector<rtm::MemoryMarkerTime>& mm = ctx->m_capture->getMemoryMarkers();

	for (size_t i = 0; i < mm.size(); ++i)
	{
		const rtm::MemoryMarkerTime& mt = mm[i];
		if (mt.m_time < m_graphWidget->minTime())
			continue;
		if (mt.m_time > m_graphWidget->maxTime())
			continue;

		int posX = m_graphWidget->mapTimeToPos(mt.m_time);
		QRectF markerRect = QRect(posX - 3, bottom + 3, 6, GraphWidget::s_marginBottom - 12);

		if (markerRect.contains(_point))
		{
			ret.m_rect = markerRect;
			ret.m_text = ctx->m_capture->getMemoryMarkerName(mm[i].m_eventHash);
			ret.m_time = mm[i].m_time;
			ret.m_threadID = mm[i].m_threadID;
			return ret;
		}
	}
	return ret;
}

QRectF GraphMarkers::boundingRect() const
{
	QSize sz = m_graphWidget->size();
	return QRectF(-sz.width()/2, -sz.height()/2, sz.width(), sz.height());
}

void GraphMarkers::paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget)
{
	RTM_UNUSED(_option);
	RTM_UNUSED(_widget);

	if (!m_graphWidget->getContext())
		return;

	_painter->setRenderHint(QPainter::Antialiasing, true);
	CaptureContext* ctx = m_graphWidget->getContext();
	QRect rect = m_graphWidget->getDrawRect();
	int bottom = rect.height() + rect.y();
	
	uint64_t m1 = m_graphWidget->getMarkerFromTime();
	uint64_t m2 = m_graphWidget->getMarkerToTime();

	_painter->setPen(QPen(Qt::darkGray, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	const std::vector<rtm::MemoryMarkerTime>& mm = ctx->m_capture->getMemoryMarkers();

	for (size_t i=0; i< mm.size(); ++i)
	{
		const rtm::MemoryMarkerTime& mt = mm[i];
		if (mt.m_time < m_graphWidget->minTime())
			continue;
		if (mt.m_time > m_graphWidget->maxTime())
			continue;

		uint32_t color = ctx->m_capture->getMemoryMarkerColor(mm[i].m_eventHash);
		_painter->setBrush(QBrush(QColor( (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff)));
		int posX = m_graphWidget->mapTimeToPos(mt.m_time);
		QRect markerRect = QRect(posX-3,bottom+3,6,GraphWidget::s_marginBottom-12);

		if ((m1 == mt.m_time) || (m2 == mt.m_time))
		{
			if (m1 == mt.m_time)
				_painter->setPen(QPen(Qt::darkGreen, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
			else
				_painter->setPen(QPen(Qt::darkRed, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
			_painter->drawEllipse(markerRect.center(),6,6);
		}
		else
		{
			_painter->setPen(QPen(Qt::darkGray, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
			_painter->drawRect(markerRect);
		}

		_painter->drawLine(posX, bottom-3, posX, bottom+3);
	}
}
