//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
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

QRectF GraphMarkers::boundingRect() const
{
	QSize sz = m_graphWidget->size();
	return QRectF(-sz.width()/2, -sz.height()/2, sz.width(), sz.height());
}

QPainterPath GraphMarkers::shape() const
{
    QPainterPath path;
	path.addRect( QRectF(0, 0, 0, 0) );
    return path;
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
	
	m_toolTips.clear();

	uint64_t m1 = m_graphWidget->getMarkerFromTime();
	uint64_t m2 = m_graphWidget->getMarkerToTime();

	_painter->setPen(QPen(Qt::darkGray, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	const rtm_vector<rtm::MemoryMarkerTime>& mm = ctx->m_capture->getMemoryMarkers();
	size_t numMarkers = mm.size();
	for (size_t i=0; i<numMarkers; ++i)
	{
		const rtm::MemoryMarkerTime& mt = mm[i];
		if (mt.m_time < m_graphWidget->minTime())
			continue;
		if (mt.m_time > m_graphWidget->maxTime())
			continue;

		uint32_t color = mm[i].m_event->m_color;
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

		MarkerToolTip tt;
		tt.m_rect		= markerRect;
		tt.m_text		= mm[i].m_event->m_name.c_str();
		tt.m_time		= mm[i].m_time;
		tt.m_threadID	= mm[i].m_threadID;
		m_toolTips.push_back(tt);
	}
}
