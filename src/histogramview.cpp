//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/histogram.h>
#include <MTuner/src/histogramview.h>
#include <MTuner/src/capturecontext.h>

HistogramView::HistogramView(QWidget* _parent) : 
	QGraphicsView(_parent)
{
	m_scene = new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    m_context = NULL;
	m_histogram = NULL;

	m_mode		= 0;
	m_showPeaks	= false;
	m_histogramType	= 0;

    setScene(m_scene);
    setViewportUpdateMode(FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    scale(qreal(1.0), qreal(1.0));
	setMouseTracking(true);

	m_histogram = new Histogram(this);
	m_histogram->parentResized();
	m_scene->addItem(m_histogram);
	fitInView(m_scene->sceneRect());
}

QRect HistogramView::getDrawRect() const
{
	QSize sz = size();
	int hWidth	= sz.width()/2;
	int hHeight	= sz.height()/2;

	int left	= -hWidth + HistogramView::s_marginLeft;
	int right	= hWidth - HistogramView::s_marginRight;
	int top		= -hHeight + HistogramView::s_marginTop;
	int bottom	= hHeight - HistogramView::s_marginBottom;
	
	return QRect(left,top,right-left,bottom-top);
}

void HistogramView::setContext(CaptureContext* _context)
{
	m_context = _context;
	invalidateScene();
	m_histogram->setHighlight(QPoint(0,0),-1);
}

void HistogramView::updateUI()
{
	fitInView(m_scene->sceneRect());
	invalidateScene();
}

void HistogramView::drawBackground(QPainter* _painter, const QRectF& _rect)
{
	RTM_UNUSED(_rect);
	QRectF fullRect = mapToScene(viewport()->geometry()).boundingRect();
	QLinearGradient gradient(fullRect.topLeft(), fullRect.bottomLeft());
    gradient.setColorAt(0, QColor(Qt::darkGray).darker(180));
    gradient.setColorAt(1, QColor(Qt::darkGray).darker(230));
    _painter->setBrush(gradient);
    _painter->drawRect(fullRect);
}

void HistogramView::resizeEvent(QResizeEvent* _event)
{
	RTM_UNUSED(_event);
	QSize newSize = size();

	m_scene->setSceneRect(-newSize.width()/2, -newSize.height()/2, newSize.width(), newSize.height());

	if (m_histogram)
		m_histogram->parentResized();

	fitInView(m_scene->sceneRect());
	invalidateScene();
}

void HistogramView::mousePressEvent(QMouseEvent* _event)
{
	QGraphicsView::mousePressEvent(_event);
}

void HistogramView::mouseMoveEvent(QMouseEvent* _event)
{
	if (m_histogram)
	{
		QPointF scenePos = mapToScene(_event->pos());
		QPoint p(scenePos.x(), scenePos.y());
		
		const QVector<HistogramToolTip>& toolTips = m_histogram->getTooltips();
		int len = toolTips.size();
		
		for (int i=0; i<len; ++i)
		{
			const HistogramToolTip& tt = toolTips[i];
			if (tt.m_rect.contains(p))
			{
				QPoint globalPos = mapToGlobal(_event->pos());
				QToolTip::showText(globalPos, tt.m_text, this, QRect(globalPos,globalPos));
				QGraphicsView::mouseMoveEvent(_event);
				m_histogram->setHighlight(p, tt.m_bin);
				return;
			}
		}

		QRect _rect = getDrawRect();
		int left = _rect.x()-1;
		int top = _rect.y()-1;
		m_histogram->setHighlight(QPoint(left,top),-1); // outside
	}
	
	QToolTip::hideText();
	QGraphicsView::mouseMoveEvent(_event);
}

void HistogramView::mouseReleaseEvent(QMouseEvent* _event)
{
	if (_event->button() & Qt::LeftButton)
	{
		if (m_context && m_context->m_capture)
		{
			int bin = m_histogram->getHighlightIndex();
			uint32_t currBin = m_context->m_capture->getSelectHistogramBin();
			if (bin == static_cast<int>(currBin))
				m_context->m_capture->deselectHistogramBin();
			else
				if (bin != -1)
					m_context->m_capture->selectHistogramBin((uint32_t)bin);
				else
					m_context->m_capture->selectHistogramBin(0xffffffff);
			emit binClicked();
			m_histogram->parentResized();
		}
	}

	QGraphicsView::mouseReleaseEvent(_event);
}

void HistogramView::leaveEvent(QEvent* _event)
{
	RTM_UNUSED(_event);
	QRect drawRect = getDrawRect();
	int left = drawRect.x() - 1;
	int top  = drawRect.y() - 1;
	m_histogram->setHighlight(QPoint(left, top), -1);
}
