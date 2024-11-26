//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/graphwidget.h>
#include <MTuner/src/binloaderview.h>
#include <MTuner/src/graphgrid.h>
#include <MTuner/src/graphcurve.h>
#include <MTuner/src/graphselect.h>
#include <MTuner/src/graphmarkers.h>
#include <MTuner/src/capturecontext.h>

static QFont s_toolTipFont(QFont("Verdana", 8, 3));

extern QString getTimeString(float _time, uint64_t* _mSec = 0);

QString QStringColor(const QString& _string, const char* _color, bool _addColon = true)
{
	return QString("<font color=\"#") + QString(_color) + QString("\">") + _string + (_addColon ? QString(":</font> ") : QString("</font> "));
}

GraphWidget::GraphWidget(QWidget* _parent) :
	QGraphicsView(_parent)
{
	m_toolTipLabel = new QLabel;
	m_toolTipLabel->setWindowFlag(Qt::ToolTip);
	s_toolTipFont.setStyleHint(QFont::Monospace);

	m_scene = new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(m_scene);
	setCacheMode(CacheBackground);
    setViewportUpdateMode(FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
	setMouseTracking(true);

	m_minTime				= 0;
	m_maxTime				= 0;
	m_hightlightTime		= (uint64_t)-1;
	m_hightlightTimeEnd		= (uint64_t)-1;
	m_hightlightIntensity	= 0.f;
	m_highlightAnimation	= nullptr;
	m_LButtonDown			= false;
	m_isDragging			= false;
	m_RButtonDown			= false;
	m_isPanning				= false;
	m_hoverMarkerTime		= 0;
	m_markerSelectFromTime	= (uint64_t)-1;
	m_markerSelectToTime	= (uint64_t)-1;
	m_context				= nullptr;
	m_inContextMenu			= false;

	GraphCurve* curve = new GraphCurve(this);
	curve->parentResized();
	m_curves.append(curve);
	m_scene->addItem(curve);

	m_markers = new GraphMarkers(this);
	m_markers->parentResized();
	m_scene->addItem(m_markers);

	m_grid = new GraphGrid(this,curve);
	m_grid->parentResized();
	m_scene->addItem(m_grid);

	m_select = new GraphSelect(this);
	m_select->parentResized();
	m_scene->addItem(m_select);

	fitInView(m_scene->sceneRect());

	createCustomContextMenu();
}

void GraphWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
	{
		createCustomContextMenu();
	}
}

void GraphWidget::setGraph(Graph* _graph)
{
	m_graph = _graph;
	Q_FOREACH( GraphCurve* it, m_curves ) {
		it->setGraph(m_graph); 
	}
}

void GraphWidget::setMinTime(uint64_t _minTime)
{
	m_minTime = _minTime;
	invalidateScene();
	emit minMaxChanged();
}

void GraphWidget::setMaxTime(uint64_t _maxTime)
{
	m_maxTime = _maxTime;
	invalidateScene();
	emit minMaxChanged();
}

void GraphWidget::setMinMaxTime(uint64_t _minTime, uint64_t _maxTime)
{
	m_minTime = _minTime;
	m_maxTime = _maxTime;
	invalidateScene();
}

bool GraphWidget::event(QEvent* _event)
{
	if (_event->type() == QEvent::ToolTip)
		return false;
	return QGraphicsView::event(_event);
}

void GraphWidget::setContext(CaptureContext* _context, BinLoaderView* _view)
{
	m_context = _context;
	if (_context)
	{
		m_minTime = _view->getMinTime();
		m_maxTime = _view->getMaxTime();
	
		if ((m_context->m_capture->getMinTime() == m_context->m_capture->getSnapshotTimeMin()) &&
			(m_context->m_capture->getMaxTime() == m_context->m_capture->getSnapshotTimeMax()))
			m_select->setSelectRange(0, 0);
		else
			m_select->setSelectRange(m_context->m_capture->getSnapshotTimeMin(), m_context->m_capture->getSnapshotTimeMax());
	}
	invalidateScene();
}

void GraphWidget::drawBackground(QPainter* _painter, const QRectF& _rect)
{
	RTM_UNUSED(_rect);
	QPolygonF polygon = mapToScene(viewport()->geometry());
	QRectF fullRect = polygon.boundingRect();

	QLinearGradient gradient(fullRect.topLeft(), fullRect.bottomLeft());
    gradient.setColorAt(0, QColor(Qt::darkGray).darker(180));
    gradient.setColorAt(1, QColor(Qt::darkGray).darker(230));
    _painter->setBrush(gradient);
    _painter->drawRect(fullRect);
}

QRect GraphWidget::getDrawRect() const
{
	QSize sz = size();
	int hWidth	= sz.width()/2;
	int hHeight	= sz.height()/2;

	int left	= -hWidth  + GraphWidget::s_marginLeft;
	int right	=  hWidth  - GraphWidget::s_marginRight;
	int top		= -hHeight + GraphWidget::s_marginTop;
	int bottom	=  hHeight - GraphWidget::s_marginBottom;
	
	return QRect(left,top,right-left,bottom-top);
}

uint64_t GraphWidget::mapPosToTime(int _x) const
{
	if (!m_context)
		return 0;
	
	QPointF scenePos = mapToScene(QPoint(_x,0));
	QRectF drawRect = getDrawRect();
		
	scenePos.setX(qMax(scenePos.x(), drawRect.x()));
	scenePos.setX(qMin(scenePos.x(), drawRect.x() + drawRect.width()));
		
	float offset = scenePos.x() - float(drawRect.x());
	float w = drawRect.width();
	uint64_t time = ((offset) * (m_maxTime - m_minTime)) / w;
	time += m_minTime;
	return time;
}

int	GraphWidget::mapTimeToPos(uint64_t _x) const
{
	if (!m_context)
		return 0;
	
	QRectF drawRect = getDrawRect();
	uint64_t offset = ((_x - m_minTime) * drawRect.width()) / (m_maxTime - m_minTime);
	
	return drawRect.x() + offset;	
}

void GraphWidget::highlightTime(uint64_t _time)
{
	if (!m_context)
		return;

	if (_time < m_context->m_capture->getMinTime())
		return;
	if (_time > m_context->m_capture->getMaxTime())
		return;

	m_hightlightTime		= _time;
	m_hightlightTimeEnd		= _time;

	animateHighlight();
}

void GraphWidget::highlightRange(uint64_t _minTime, uint64_t _maxTime)
{
	if (!m_context)
		return;

	if (_minTime > _maxTime)
		std::swap(_minTime, _maxTime);

	if (_maxTime < m_context->m_capture->getMinTime())
		return;
	if (_minTime > m_context->m_capture->getMaxTime())
		return;

	if (_minTime < m_context->m_capture->getMinTime())
		_minTime = m_context->m_capture->getMinTime();
	if (_maxTime > m_context->m_capture->getMaxTime())
		_maxTime = m_context->m_capture->getMaxTime();

	m_hightlightTime		= _minTime;
	m_hightlightTimeEnd		= _maxTime;

	animateHighlight();
}

void GraphWidget::animateHighlight()
{
	if (m_highlightAnimation != nullptr)
		m_highlightAnimation->stop();

	m_hightlightIntensity	= 1.0f;

	m_highlightAnimation = new QPropertyAnimation(this, "highlightIntensity");
	connect(m_highlightAnimation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(zoomAnimEvent()));

	m_highlightAnimation->setDuration(666);
	m_highlightAnimation->setStartValue(1.0f);
	m_highlightAnimation->setEndValue(0.0f);
	m_highlightAnimation->start();
}

void GraphWidget::selectFromTimes(uint64_t _t1, uint64_t _t2)
{
	uint64_t mn = qMin(_t1,_t2);
	uint64_t mx = qMax(_t1,_t2);
	m_context->m_capture->setSnapshot(mn, mx);
	m_select->setSelectRange(mn, mx);
	emit snapshotSelected();
	invalidateScene();
	m_markerSelectFromTime	= (uint64_t)-1;
	m_markerSelectToTime	= (uint64_t)-1;
	m_actionZoomToSelection->setEnabled(true);
	m_actionSnapSelectionToMarker->setEnabled(true);
}

void GraphWidget::animateRange(uint64_t _min, uint64_t _max)
{
	QPropertyAnimation* animation = new QPropertyAnimation(this, "minTime");
	animation->setDuration(150);
	animation->setStartValue(qulonglong(m_minTime));
	animation->setEndValue(qulonglong(_min));
	animation->start();

	connect(animation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(zoomAnimEvent()));

	animation = new QPropertyAnimation(this, "maxTime");
	animation->setDuration(150);
	animation->setStartValue(qulonglong(m_maxTime));
	animation->setEndValue(qulonglong(_max));
	animation->start();
}

void GraphWidget::zoomIn()
{
	zoomIn(UINT64_MAX);
}

void GraphWidget::zoomIn(uint64_t _time)
{
	int64_t timeSpan = (m_maxTime - m_minTime) / 2;
	int64_t middle = (m_maxTime + m_minTime) / 2;
	if (_time != UINT64_MAX)
	{
		middle = _time;
	}

	int64_t newMinTime = middle - timeSpan * 2/3;
	int64_t newMaxTime = middle + timeSpan * 2/3;

	int64_t mintime = m_context->m_capture->getMinTime();
	int64_t maxtime = m_context->m_capture->getMaxTime();
	if (newMaxTime > maxtime)
	{
		uint64_t delta = newMaxTime - maxtime;
		newMinTime -= delta;
	}

	if (newMinTime < mintime)
	{
		uint64_t delta = mintime - newMinTime;
		newMaxTime += delta;
	}

	newMaxTime = qMin(newMaxTime, (int64_t)m_context->m_capture->getMaxTime());
	newMinTime = qMax(newMinTime, (int64_t)m_context->m_capture->getMinTime());

	animateRange(newMinTime,newMaxTime);
	m_actionZoomReset->setEnabled(true);
}

void GraphWidget::zoomOut()
{
	zoomOut(UINT64_MAX);
}

void GraphWidget::zoomOut(uint64_t _time)
{
	int64_t timeSpan = (m_maxTime - m_minTime) / 2;
	int64_t middle   = (m_maxTime + m_minTime) / 2;
	if (_time != UINT64_MAX)
	{
		middle = _time;
	}

	int64_t newMinTime = middle - timeSpan * 3/2;
	int64_t newMaxTime = middle + timeSpan * 3/2;

	int64_t mintime = m_context->m_capture->getMinTime();
	int64_t maxtime = m_context->m_capture->getMaxTime();
	if (newMaxTime > maxtime)
	{
		int64_t delta = newMaxTime - maxtime;
		newMinTime -= delta;
	}

	if (newMinTime < mintime)
	{
		int64_t delta = mintime - newMinTime;
		newMaxTime += delta;
	}

	newMaxTime = qMin(newMaxTime, (int64_t)m_context->m_capture->getMaxTime());
	newMinTime = qMax(newMinTime, (int64_t)m_context->m_capture->getMinTime());

	if ((newMinTime == (int64_t)m_context->m_capture->getMinTime()) && (newMaxTime == (int64_t)m_context->m_capture->getMaxTime()))
		m_actionZoomReset->setEnabled(false);

	animateRange(newMinTime,newMaxTime);
}

void GraphWidget::updateToolTip(const QPoint& _position)
{
	QPoint gpt = mapToGlobal(_position);
	QRect drawRect = getDrawRect();
	QPoint position = mapFromGlobal(gpt);
	QPointF pt = mapToScene(position);

	static const QString sqs_BR("<br>");
	static const QString sqs_PRE("<pre>");

	if (rect().contains(_position) && m_LButtonDown && !m_inContextMenu)
	{
		uint64_t pL = mapPosToTime(m_dragStartPos.x());
		uint64_t pR = mapPosToTime(_position.x());
		uint64_t startTime = qMin(pL, pR);
		uint64_t endTime = qMax(pL, pR);

		rtm::GraphEntry entry;
		m_context->m_capture->getGraphAtTime(endTime, entry);

		float startTimeF = m_context->m_capture->getFloatTime(startTime);
		float endTimeF = m_context->m_capture->getFloatTime(endTime);

		const static QString sqs_1 = QStringColor(("Start time"), "ffffffff");
		const static QString sqs_2 = QStringColor(("  End time"), "ffffffff");
		const static QString sqs_3 = QStringColor(("  Duration"), "ffffffff");
		const static QString sqs_4 = QStringColor(("Usage at end"), "ff42a6ba");
		const static QString sqs_5 = QStringColor((" Live blocks"), "ff83cf67");

		QString ttip = sqs_PRE + sqs_1 + getTimeString(startTimeF) + sqs_BR +
								 sqs_2 + getTimeString(endTimeF) + sqs_BR +
								 sqs_3 + getTimeString(endTimeF - startTimeF) + sqs_BR + sqs_BR +
								 sqs_4 + m_locale.toString(qulonglong(entry.m_usage)) + sqs_BR +
								 sqs_5 + m_locale.toString(qulonglong(entry.m_numLiveBlocks)) + QString("</pre>");

		m_toolTipLabel->setText(ttip);
		m_toolTipLabel->adjustSize();
	}
	else
		if (drawRect.contains(pt.x(), pt.y()) && !m_LButtonDown && !m_inContextMenu)
		{
			uint64_t pL = mapPosToTime(position.x());
			float timeF = m_context->m_capture->getFloatTime(pL);
			rtm::GraphEntry entry;
			m_context->m_capture->getGraphAtTime(pL, entry);
			QString timeStr = getTimeString(timeF);

			static const QString sqs_1 = QStringColor(tr(" Time"), "ffffffff");
			static const QString sqs_2 = QStringColor(tr("Usage"), "ff42a6ba");
			static const QString sqs_3 = QStringColor(tr("Live blocks"), "ff83cf67");

			QString ttip = sqs_PRE + sqs_1 + timeStr + sqs_BR +
									 sqs_2 + m_locale.toString(qulonglong(entry.m_usage)) + sqs_BR +
									 sqs_3 + m_locale.toString(qulonglong(entry.m_numLiveBlocks)) + sqs_PRE + QString("\n");

			m_toolTipLabel->setText(ttip);
			m_toolTipLabel->adjustSize();
		}
		else
			if (!m_LButtonDown)
				m_toolTipLabel->setText("");

	showToolTip();
}

void GraphWidget::zoomReset()
{
	animateRange(m_context->m_capture->getMinTime(), m_context->m_capture->getMaxTime());
	m_actionZoomReset->setEnabled(false);
}

void GraphWidget::zoomSelect()
{
	animateRange(m_context->m_capture->getSnapshotTimeMin(), m_context->m_capture->getSnapshotTimeMax());
	m_actionZoomReset->setEnabled(true);
}

void GraphWidget::zoomAnimEvent()
{
	invalidateScene();
}

void GraphWidget::markerSnapTo()
{
	uint64_t f = m_hoverMarkerTime;
	uint64_t maxS = m_context->m_capture->getSnapshotTimeMax();
	uint64_t minS = m_context->m_capture->getSnapshotTimeMin();

	if (f>maxS)
		maxS = f;
	else
		if (f<minS)
			minS = f;
		else
		{
			// who is closer?
			uint64_t max = maxS - f;
			uint64_t min = f - minS;
			if (max < min)
				maxS = f;
			else
				minS = f;
		}

	selectFromTimes(minS,maxS);
}

void GraphWidget::markerSelectFrom()
{
	m_markerSelectFromTime = m_hoverMarkerTime;

	if ((m_markerSelectFromTime != UINT64_MAX) && (m_markerSelectToTime != UINT64_MAX))
		selectFromTimes(m_markerSelectFromTime,m_markerSelectToTime);
	else
		invalidateScene();
}

void GraphWidget::markerSelectTo()
{
	m_markerSelectToTime = m_hoverMarkerTime;

	if ((m_markerSelectFromTime != UINT64_MAX) && (m_markerSelectToTime != UINT64_MAX))
		selectFromTimes(m_markerSelectFromTime,m_markerSelectToTime);
	else
		invalidateScene();
}

void GraphWidget::resizeEvent(QResizeEvent* _event)
{
	RTM_UNUSED(_event);
	QSize newSize = size();

	m_scene->setSceneRect(-newSize.width()/2, -newSize.height()/2, newSize.width(), newSize.height());

	if (m_grid)
		m_grid->parentResized();

	Q_FOREACH( GraphCurve* it, m_curves ) {
		it->parentResized();
	}

	fitInView(m_scene->sceneRect());
	invalidateScene();
}

void GraphWidget::wheelEvent(QWheelEvent* _event)
{
	RTM_UNUSED(_event);
	int delta = _event->angleDelta().y();
	QPointF position = _event->position();
	uint64_t relTime = mapPosToTime(position.x());
	if (delta < 0)
		zoomOut(relTime);
	else
		zoomIn(relTime);
}

void GraphWidget::mousePressEvent(QMouseEvent* _event)
{
	if (!m_context)
		return;

	QRect drawRect = getDrawRect();
	QPointF pt = mapToScene(_event->pos());

	if ((_event->buttons() & Qt::LeftButton) && drawRect.contains(pt.x(),pt.y()))
	{
		m_LButtonDown	= true;
		m_dragStartPos	= _event->pos();
	}

	if ((_event->buttons() & Qt::RightButton) && drawRect.contains(pt.x(),pt.y()))
	{
		m_RButtonDown	= true;
		m_dragStartPos	= _event->pos();
	}

	QGraphicsView::mousePressEvent(_event);
}

void GraphWidget::mouseMoveEvent(QMouseEvent* _event)
{
	mouseMovement(_event->pos(), _event->buttons());
	QGraphicsView::mouseMoveEvent(_event);
}

void GraphWidget::mouseMovement(const QPoint& _position, Qt::MouseButtons _buttons)
{
	if (!m_context)
		return;

	QPointF spt = mapToScene(_position);

	const QVector<MarkerToolTip>& toolTips = m_markers->getTooltips();
	for (int i = 0; i < toolTips.size(); ++i)
	{
		if (toolTips[i].m_rect.contains(spt) && !m_inContextMenu)
		{
			QString text(toolTips[i].m_text);
			text = text + QString("\n") + tr("Time") + QString(": ") + getTimeString(m_context->m_capture->getFloatTime(toolTips[i].m_time));
			text = text + QString("\n") + tr("Thread") + QString(": 0x") + QString::number(toolTips[i].m_threadID, 16);

			m_toolTipLabel->setText(text);

			m_hoverMarkerTime = toolTips[i].m_time;
			break;
		}
	}

	if ((_buttons & Qt::LeftButton) && m_LButtonDown && !m_isDragging)
		m_isDragging = true;

	if ((_buttons & Qt::RightButton) && m_RButtonDown && !m_isPanning && m_actionZoomReset->isEnabled())
	{
		m_isPanning = true;
		setCursor(Qt::ClosedHandCursor);
	}

	if ((_buttons & Qt::LeftButton) && m_isDragging)
	{
		uint64_t pL = mapPosToTime(m_dragStartPos.x());
		uint64_t pR = mapPosToTime(_position.x());
		m_select->setSelectRange(pL,pR);

		if (!m_context->m_capture->getFilteringEnabled())
		{
			uint64_t startTime = qMin(pL,pR);
			uint64_t endTime = qMax(pL,pR);
			m_context->m_capture->setSnapshot(startTime,endTime);
			emit snapshotSelected();
		}
	}

	if ((_buttons & Qt::RightButton) && m_isPanning)
	{
		setCursor(Qt::ClosedHandCursor);
		uint64_t pL = mapPosToTime(m_dragStartPos.x());
		uint64_t pR = mapPosToTime(_position.x());
		int64_t delta = pL - pR;

		if (delta != 0)
		{
			m_dragStartPos = _position;
			int64_t newMinTime = m_minTime + delta;
			int64_t newMaxTime = m_maxTime + delta;

			int64_t mintime = m_context->m_capture->getMinTime();
			int64_t maxtime = m_context->m_capture->getMaxTime();
			if (newMaxTime > maxtime)
			{
				uint64_t deltaU = newMaxTime - maxtime;
				newMinTime -= deltaU;
			}

			if (newMinTime < mintime)
			{
				uint64_t deltaU = mintime - newMinTime;
				newMaxTime += deltaU;
			}

			newMaxTime = qMin(newMaxTime, (int64_t)m_context->m_capture->getMaxTime());
			newMinTime = qMax(newMinTime, (int64_t)m_context->m_capture->getMinTime());

			m_minTime = newMinTime;
			m_maxTime = newMaxTime;

			emit minMaxChanged();
		}
	}

	updateToolTip(_position);

	invalidateScene();
}

void GraphWidget::mouseReleaseEvent(QMouseEvent* _event)
{
	if (!m_context)
		return;

	if ((_event->button() == Qt::LeftButton) && m_LButtonDown)
	{
		m_LButtonDown = false;
		updateToolTip(_event->pos());
	}

	if ((_event->button() == Qt::RightButton) && m_RButtonDown)
	{
		m_RButtonDown = false;
		setCursor(Qt::ArrowCursor);
	}

	if (_event->button() == Qt::LeftButton)
	{
		if (m_isDragging)
		{
			uint64_t time1 = mapPosToTime(_event->pos().x());
			uint64_t time2 = mapPosToTime(m_dragStartPos.x());
			if (m_context->m_capture->getFilteringEnabled())
			{
				uint64_t startTime = qMin(time1,time2);
				uint64_t endTime = qMax(time1,time2);
				m_context->m_capture->setSnapshot(startTime,endTime);
				emit snapshotSelected();
			}
			m_actionZoomToSelection->setEnabled(true);
			m_actionSnapSelectionToMarker->setEnabled(true);
			m_isDragging = false;
		}
		else
		{
			m_context->m_capture->setSnapshot(m_context->m_capture->getMinTime(), m_context->m_capture->getMaxTime());
			m_select->setSelectRange(0,0);
			m_actionZoomToSelection->setEnabled(false);
			m_actionSnapSelectionToMarker->setEnabled(false);
			invalidateScene();
			emit snapshotSelected();
		}

		m_markerSelectFromTime	= (uint64_t)-1;
		m_markerSelectToTime	= (uint64_t)-1;
	}

	QGraphicsView::mouseReleaseEvent(_event);

	mouseMovement(mapToScene(QCursor::pos()).toPoint(), Qt::LeftButton);
}

void GraphWidget::contextMenuEvent(QContextMenuEvent* _event)
{
	if (!m_context)
		return;

	if (m_isPanning)
	{
		m_isPanning = false;
		return;
	}

	bool isInMarker = false;
	QPoint pt = QCursor::pos();
	QPointF spt = mapToScene(mapFromGlobal(pt));
	const QVector<MarkerToolTip>&	toolTips = m_markers->getTooltips();
	for (int i=0; i<toolTips.size(); ++i)
	{
		if (toolTips[i].m_rect.contains(spt))
		{
			isInMarker = true;
			m_hoverMarkerTime = toolTips[i].m_time;
			break;
		}
	}

	m_inContextMenu = true;

	if (isInMarker)
		m_contextMenuMarker->exec(mapToGlobal(_event->pos()));
	else
		m_contextMenu->exec(mapToGlobal(_event->pos()));
}

void GraphWidget::createCustomContextMenu()
{
	m_actionZoomToSelection = new QAction(QString(tr("Zoom to selection")),this);
	m_actionZoomReset = new QAction(QString(tr("Reset zoom")),this);

	m_actionZoomToSelection->setEnabled(false);
	m_actionZoomReset->setEnabled(false);

	m_contextMenu = new QMenu();
	m_contextMenu->addAction(m_actionZoomToSelection);
	m_contextMenu->addAction(m_actionZoomReset);
	connect(m_contextMenu, SIGNAL(aboutToHide()), this, SLOT(leaveContextMenu()));

	connect(m_actionZoomToSelection, SIGNAL(triggered()), this, SLOT(zoomSelect()));
	connect(m_actionZoomReset, SIGNAL(triggered()), this, SLOT(zoomReset()));

	m_actionSnapSelectionToMarker = new QAction(QString(tr("Snap selection to marker")), this);
	m_actionSelectFromMarker = new QAction(QString(tr("Select from marker")), this);
	m_actionSelectToMarker = new QAction(QString(tr("Select to marker")), this);
	m_contextMenuMarker = new QMenu();
	connect(m_contextMenuMarker, SIGNAL(aboutToHide()), this, SLOT(leaveContextMenu()));

	m_actionSnapSelectionToMarker->setEnabled(false);

	m_contextMenuMarker->addAction(m_actionSnapSelectionToMarker);
	m_contextMenuMarker->addAction(m_actionSelectFromMarker);
	m_contextMenuMarker->addAction(m_actionSelectToMarker);

	connect(m_actionSnapSelectionToMarker, SIGNAL(triggered()), this, SLOT(markerSnapTo()));
	connect(m_actionSelectFromMarker, SIGNAL(triggered()), this, SLOT(markerSelectFrom()));
	connect(m_actionSelectToMarker, SIGNAL(triggered()), this, SLOT(markerSelectTo()));
}

void GraphWidget::showToolTip()
{
	if (m_toolTipLabel->text().size())
	{
		m_toolTipLabel->move(QCursor::pos() + QPoint(15,15));
		m_toolTipLabel->setFont(s_toolTipFont);
		if(m_toolTipLabel->isHidden())
			m_toolTipLabel->show();
	}
	else
		m_toolTipLabel->hide();
}

void GraphWidget::leaveContextMenu()
{
	m_inContextMenu = false;
}
