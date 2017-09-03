//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/treemapview.h>
#include <MTuner/src/treemap.h>
#include <MTuner/src/capturecontext.h>

uint64_t getTotalMem(rtm_vector<TreeMapNode>& _items, int _start, int _end)
{
	uint64_t sum = 0;
	for (int i=_start; i<=_end; ++i)
		sum += _items[i].m_size;
	return sum;
}

void sliceLayout(rtm_vector<TreeMapNode>& _items, int _start, int _end, QRectF& _rect)
{
	double total = getTotalMem(_items, _start, _end);
	double a = 0.0;

	if (_rect.bottom() < _rect.top())
		_rect.setBottom(_rect.top());

	if (_rect.right() < _rect.left())
		_rect.setLeft(_rect.right());

	bool bVertical = (_rect.right() - _rect.left()) < (_rect.bottom() - _rect.top());
	bool bOrderAsc = true;

	if (total == 0.0)
		return;

	for (int i=_start; i<=_end; ++i) 
	{
		TreeMapNode& child = _items[i];
		QRectF itemRect;
		double b = double(child.m_size) / total;
		if (bVertical)
		{
			itemRect.setLeft(_rect.left());
			itemRect.setRight(_rect.right());
			if (bOrderAsc)
				itemRect.setTop(_rect.top() + (_rect.bottom() - _rect.top()) * a);
			else
				itemRect.setTop(_rect.top() + (_rect.bottom() - _rect.top()) * (1.0 - a - b));
			itemRect.setBottom(itemRect.top() + (_rect.bottom() - _rect.top()) * b);
		}
		else 
		{
			if (bOrderAsc)
				itemRect.setLeft(_rect.left() + (_rect.right() - _rect.left()) * a);
			else
				itemRect.setLeft(_rect.left() + (_rect.right() - _rect.left()) * (1.0 - a - b));
			itemRect.setRight(itemRect.left() + (_rect.right() - _rect.left()) * b);
			itemRect.setTop(_rect.top());
			itemRect.setBottom(_rect.bottom());
		}
		child.m_rect = itemRect;
		a += b;
	}
}

static inline double getNormAspect(double _big, double _small, double _a, double _b)
{
	double x = (_big*_b) / (_small*_a/_b);
	if (x < 1.0)
		return 1.0/x;
	return x;
}

static inline bool sortMapItems(TreeMapNode& _in1, TreeMapNode& _in2)
{
	return _in1.m_size > _in2.m_size;
}

void squaredLayout(rtm_vector<TreeMapNode>& _aitems, int _start, int _end, QRectF& _rect)
{
	if (_start > _end)
		return;

	if (_end - _start < 2)
	{
		sliceLayout(_aitems, _start, _end, _rect);
		return;
	}
	
	double x = _rect.left();
	double y = _rect.top();
	double w = _rect.right() - _rect.left();
	double h = _rect.bottom() - _rect.top();
	double dblTotal = getTotalMem(_aitems, _start, _end);

	if (dblTotal == 0.0)
		return;

	int iMid = _start;
	double a = double(_aitems[_start].m_size) / dblTotal;
	double b = a;

	if (w < h)
	{
		while (iMid < _end)
		{
			double dblAspect = getNormAspect(h, w, a, b);
			double q = double(_aitems[iMid + 1].m_size) / dblTotal;
			if (getNormAspect(h, w, a, b + q) > dblAspect)
				break;
			b += q;
			++iMid;
		}
		QRectF rcSliced( x, y, w, h*b );
		QRectF rcSquared( x, y+h*b, w, h*(1.0-b) );
		sliceLayout(_aitems, _start, iMid, rcSliced);
		squaredLayout(_aitems, iMid + 1, _end, rcSquared);
	}
	else
	{
		while (iMid < _end)
		{
			double dblAspect = getNormAspect(w, h, a, b);
			double q = double(_aitems[iMid + 1].m_size) / dblTotal;
			if (getNormAspect(w, h, a, b + q) > dblAspect)
				break;
			b += q;
			++iMid;
		}
		QRectF rcSlice( x, y, w*b, h );
		QRectF rcSquared( x + w*b, y, w*(1.0-b), h );
		sliceLayout(_aitems, _start, iMid, rcSlice);
		squaredLayout(_aitems, iMid + 1, _end, rcSquared);
	}
}

static inline uint64_t getNodeValueByType(TreeMapNode& _tree, uint32_t _type)
{
	switch (_type)
	{
		case 0: return _tree.m_tree->m_memUsage;
		case 1: return _tree.m_tree->m_memUsagePeak;
		case 2: return _tree.m_tree->m_overhead;
		case 3: return _tree.m_tree->m_overheadPeak;
	};
	return 0;
}

TreeMapView::TreeMapView(QWidget* _parent) :
	QGraphicsView(_parent)
{
	m_context		= NULL;
	m_highlightNode	= NULL;
	m_lastClick		= 0;
	m_mapType		= 0;
	m_scene			= new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	m_timer.start();

    setScene(m_scene);
    setViewportUpdateMode(FullViewportUpdate);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scale(qreal(1.0), qreal(1.0));
	setMouseTracking(true);
}

void TreeMapView::setContext(CaptureContext* _context)
{
	m_context = _context;
	buildTree();
}

void TreeMapView::setMapType(uint32_t _type)
{
	m_mapType = _type;
	m_tree.clear();
	buildTree();
	m_item->redraw();
	invalidateScene();
}

TreeMapNode* TreeMapView::findNode(QPoint& _point)
{
	for (size_t i=0; i<m_tree.size(); ++i)
	{
		if (m_tree[i].m_rect.contains(_point))
			return &m_tree[i];
	}

	return NULL;
}

void TreeMapView::buildTreeRecurse(rtm::StackTraceTree* _tree)
{
	if (_tree->m_children.size() == 0)
	{
		TreeMapNode node;

		node.m_tree		= _tree;
		node.m_text		= "";
		node.m_size		= getNodeValueByType( node, m_mapType );

		m_tree.push_back(node);
	}

	rtm::StackTraceTree::ChildNodes& children = _tree->m_children;
	rtm::StackTraceTree::ChildNodes::iterator it  = children.begin();
	rtm::StackTraceTree::ChildNodes::iterator end = children.end();
	while (it != end)
	{
		buildTreeRecurse(&*it);
		++it;
	}
}

void TreeMapView::buildTree()
{
	m_tree.clear();
	if (!(m_context && m_context->m_capture))
		return;

	bool filtered = m_context->m_capture->getFilteringEnabled();
	const rtm::StackTraceTree& tree = filtered ? m_context->m_capture->getStackTraceTreeFiltered() : m_context->m_capture->getStackTraceTree();
	rtm::StackTraceTree* rootNode = const_cast<rtm::StackTraceTree*>(&tree);
	
	buildTreeRecurse(rootNode);
	std::sort(m_tree.begin(), m_tree.end(), sortMapItems);
}

void TreeMapView::resizeEvent(QResizeEvent* _event)
{
	RTM_UNUSED(_event);
	invalidateScene();
}

void TreeMapView::mousePressEvent(QMouseEvent* _event)
{
	QGraphicsView::mousePressEvent(_event);
}

void TreeMapView::mouseMoveEvent(QMouseEvent* _event)
{
	QPointF scenePos = mapToScene(_event->pos());
	QPoint p(scenePos.x(), scenePos.y());
		
	TreeMapNode* tt = findNode(p);

	if (m_highlightNode != tt)
	{
		m_highlightNode = tt;
		invalidateScene();
	}

	if (tt)
	{
		QLocale locale;
		QPoint globalPos = mapToGlobal(_event->pos());
		QToolTip::showText(globalPos, QObject::tr("Size: ") + locale.toString(qulonglong(tt->m_size)) + QString("\n") + QObject::tr("Click to see call stack") + tt->m_text, this, QRect(globalPos,globalPos));
		QGraphicsView::mouseMoveEvent(_event);
		return;
	}

	QToolTip::hideText();
	QGraphicsView::mouseMoveEvent(_event);
}

void TreeMapView::mouseReleaseEvent(QMouseEvent* _event)
{
	if (_event->button() == Qt::LeftButton)
	{
		if (m_highlightNode)
		{
			rtm::StackTrace** trace = &m_highlightNode->m_tree->m_stackTraceList;
			emit setStackTrace(trace, 1);
		}
		else
			emit setStackTrace(NULL, 0);
	}

	QGraphicsView::mouseReleaseEvent(_event);
}

void TreeMapView::leaveEvent(QEvent*)
{
	if (m_highlightNode)
	{
		m_highlightNode = NULL;
		invalidateScene();
	}
}

TreeMapGraphicsItem::TreeMapGraphicsItem(TreeMapView* _treeView, CaptureContext* _context)
{
	m_oldRect				= QRectF(0,0,0,0);
	m_treeView				= _treeView;
	m_context				= _context;
	_treeView->setItem(this);
}

void TreeMapGraphicsItem::redraw()
{
	m_oldRect = QRectF(0,0,0,0);
}

QRectF TreeMapGraphicsItem::boundingRect() const
{
	QSizeF sz = m_treeView->size();
	return QRectF(-sz.width()/2, -sz.height()/2, sz.width(), sz.height());
}

QPainterPath TreeMapGraphicsItem::shape() const
{
    QPainterPath path;
	path.addRect( QRectF(0, 0, 0, 0) );
    return path;
}

static inline void drawBlockText(const QString& _text, QPainter* _painter, int _fontHeight, int _fontWidths[17], QRectF& _rect, bool _highlight)
{
	if (_highlight)
		_painter->setPen(Qt::black);
	else
		_painter->setPen(Qt::white);

	int len = _text.length();
	if ((_rect.width() - _fontWidths[len] > 6.0f) && (_rect.height() > _fontHeight))
	{
		QRectF textRect = _rect.adjusted(3.0f,0,-3.0f,14-_rect.height());
		_painter->drawText(textRect,_text);
	}
}

void TreeMapGraphicsItem::paint(QPainter* _painter, const QStyleOptionGraphicsItem* _item, QWidget* _widget)
{
	RTM_UNUSED(_item);
	RTM_UNUSED(_widget);
	rtm_vector<TreeMapNode>& tree = m_treeView->getTree();

	QSize s = m_treeView->size();
	QRectF rect = m_treeView->mapToScene(QRect(0,0,s.width(),s.height())).boundingRect();
	if (m_oldRect != rect)
	{
		squaredLayout(tree, 0, (int)tree.size()-1, rect);
		m_oldRect = rect;
	}

	_painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine));

	TreeMapNode* highlight = m_treeView->getHighlightNode();

	_painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine));

	QVector<QRectF> rects;
	rects.resize((int)tree.size());

	QColor c1(50, 150, 170, 131);
	QColor c2(50, 150, 170, 111);

	for (size_t i=0; i<tree.size(); ++i)
	{
		TreeMapNode& info = tree[i];
		if (&info == highlight)
			continue;
		rects.push_back(info.m_rect);
	}

	_painter->setBrush(c2);
	_painter->drawRects(rects);
	if (highlight)
	{
		QLinearGradient gr(highlight->m_rect.topLeft(), highlight->m_rect.bottomRight());
		gr.setColorAt(0.0f, c1);
		gr.setColorAt(1.0f, c2);
		_painter->setBrush(gr);
		_painter->drawRect(highlight->m_rect);
	}
	
	int fontHeight = m_treeView->fontMetrics().height();
	const char* lenStrs[17] = {
		"0",
		"00",
		"000",
		",000",
		"0,000",
		"00,000",
		"000,000",
		",000,000",
		"0,000,000",
		"00,000,000",
		"000,000,000",
		",000,000,000",
		"0,000,000,000",
		"00,000,000,000",
		"000,000,000,000",
		",000,000,000,000",
		"0,000,000,000,000",
	};

	int textWidth[17];
	for (int i=0; i<17; ++i)
	{
		textWidth[i] = m_treeView->fontMetrics().width(lenStrs[i]);
	}

	for (size_t i=0; i<tree.size(); ++i)
	{
		TreeMapNode& info = tree[i];
		if (info.m_tree->m_children.empty())
		{
			QLocale locale;
			drawBlockText(locale.toString(qulonglong(info.m_size)), _painter, fontHeight, textWidth, info.m_rect, &info == highlight);
		}
	}
}
