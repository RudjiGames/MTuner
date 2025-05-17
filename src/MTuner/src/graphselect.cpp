//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/graphselect.h>
#include <MTuner/src/graphwidget.h>

GraphSelect::GraphSelect(GraphWidget* _graphWidget)
{
	m_graphWidget	= _graphWidget;
	m_minTime		= 0;
	m_maxTime		= 0;
}

void GraphSelect::setSelectRange(uint64_t _minTime, uint64_t _maxTime)
{
	m_minTime = qMin(_minTime, _maxTime);
	m_maxTime = qMax(_minTime, _maxTime);
}

QRectF	GraphSelect::boundingRect() const
{
	QSize sz = m_graphWidget->size();
	return QRectF(-sz.width()/2, -sz.height()/2, sz.width(), sz.height());
}

void GraphSelect::paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget)
{
	RTM_UNUSED(_option);
	RTM_UNUSED(_widget);
	if (!m_graphWidget->getContext())
		return;

	if (m_minTime == m_maxTime)		return;
	if (m_maxTime < m_graphWidget->minTime()) return;
	if (m_minTime > m_graphWidget->maxTime()) return;

	uint64_t minTime = qMax(m_minTime, m_graphWidget->minTime());
	uint64_t maxTime = qMin(m_maxTime, m_graphWidget->maxTime());

	QRect rect = m_graphWidget->getDrawRect();
	int minX = m_graphWidget->mapTimeToPos(minTime);
	int maxX = m_graphWidget->mapTimeToPos(maxTime);

	int top = rect.y();
	int bottom = rect.height() + rect.y();

	_painter->setPen(Qt::NoPen);
	_painter->setBrush(QColor(50, 150, 170, 138));
	_painter->drawRect(minX,top,maxX-minX,bottom-top);
}
