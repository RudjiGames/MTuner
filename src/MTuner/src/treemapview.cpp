//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/treemapview.h>
#include <MTuner/src/treemap.h>
#include <MTuner/src/capturecontext.h>

static QFont s_sizeFont(QFont("Arial", 7));
static QFont s_toolTipFont(QFont("Arial", 8));

QString QStringColor(const QString& _string, const char* _color, bool _addColon = true);

static inline uint64_t getTotalMem(rtm_vector<TreeMapNode>& _nodes, int _start, int _end)
{
	uint64_t sum = 0;
	for (int i=_start; i<=_end; ++i)
		sum += _nodes[i].m_size;
	return sum;
}

void sliceLayout(rtm_vector<TreeMapNode>& _nodes, int _start, int _end, QRectF& _rect)
{
	float total = getTotalMem(_nodes, _start, _end);
	float a = 0.0;

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
		TreeMapNode& child = _nodes[i];
		QRectF& itemRect = _nodes[i].m_rect;
		float b = float(child.m_size) / total;
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
		a += b;
	}
}

static inline float getNormAspect(float _big, float _small, float _a, float _b)
{
	float x = (_big*_b) / (_small*_a/_b);
	if (x < 1.0)
		return 1.0/x;
	return x;
}

static inline bool sortMapItems(const TreeMapNode& _in1, const TreeMapNode& _in2)
{
	return _in1.m_size > _in2.m_size;
}

void calcLines(const rtm_vector<TreeMapNode>& _nodes, QVector<QLineF>& _lines)
{
	_lines.clear();
	for (const TreeMapNode& node : _nodes)
	{
		_lines.push_back(QLineF(node.m_rect.bottomLeft(), node.m_rect.bottomRight()));
		_lines.push_back(QLineF(node.m_rect.topRight(), node.m_rect.bottomRight()));
	}
}

void squaredLayout(rtm_vector<TreeMapNode>& _nodes, int _start, int _end, QRectF& _rect)
{
	if (_start > _end)
		return;

	if (_end - _start < 2)
	{
		sliceLayout(_nodes, _start, _end, _rect);
		return;
	}
	
	float x = _rect.left();
	float y = _rect.top();
	float w = _rect.right() - _rect.left();
	float h = _rect.bottom() - _rect.top();
	float dblTotal = getTotalMem(_nodes, _start, _end);

	if (dblTotal == 0.0)
		return;

	int iMid = _start;
	float a = float(_nodes[_start].m_size) / dblTotal;
	float b = a;

	if (w < h)
	{
		while (iMid < _end)
		{
			float dblAspect = getNormAspect(h, w, a, b);
			float q = float(_nodes[iMid + 1].m_size) / dblTotal;
			if (getNormAspect(h, w, a, b + q) > dblAspect)
				break;
			b += q;
			++iMid;
		}
		QRectF rcSliced( x, y, w, h*b );
		QRectF rcSquared( x, y+h*b, w, h*(1.0-b) );
		sliceLayout(_nodes, _start, iMid, rcSliced);
		squaredLayout(_nodes, iMid + 1, _end, rcSquared);
	}
	else
	{
		while (iMid < _end)
		{
			float dblAspect = getNormAspect(w, h, a, b);
			float q = float(_nodes[iMid + 1].m_size) / dblTotal;
			if (getNormAspect(w, h, a, b + q) > dblAspect)
				break;
			b += q;
			++iMid;
		}
		QRectF rcSlice( x, y, w*b, h );
		QRectF rcSquared( x + w*b, y, w*(1.0-b), h );
		sliceLayout(_nodes, _start, iMid, rcSlice);
		squaredLayout(_nodes, iMid + 1, _end, rcSquared);
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
	m_clickedNode	= NULL;
	m_mapType		= 0;
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setMouseTracking(true);
	m_toolTipLabel = new QLabel;
	m_toolTipLabel->setWindowFlag(Qt::ToolTip);

	s_sizeFont.setStyleHint(QFont::Monospace);
	s_toolTipFont.setStyleHint(QFont::Monospace);
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
	m_treeLines.clear();
	buildTree();
	m_item->redraw();
	repaint();
}

void TreeMapView::updateHighlight(const QPoint& _pos)
{
	QPoint scenePos = mapToScene(_pos).toPoint();

	m_highlightNode = 0;
	for (size_t i=0; i<m_tree.size(); ++i)
		if (m_tree[i].m_rect.contains(scenePos))
			if (m_highlightNode != &m_tree[i])
			{
				m_highlightNode		= &m_tree[i];

				QLocale locale;
				QString str =	"<pre>" +
										QStringColor(tr("Total size"), "ff42a6ba") + QStringColor(locale.toString(qulonglong(m_highlightNode->m_size)), "ffffff33", false) + "<br>" +
										QStringColor(tr("Operations"), "ff83cf67") + locale.toString(qulonglong(m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Alloc] + m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Realloc] + m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Free])) + "<br><br>" +
										QStringColor(tr("  Allocs"), "ffffffff") + locale.toString(qulonglong(m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Alloc])) + "<br>" +
										QStringColor(tr("Reallocs"), "ffffffff") + locale.toString(qulonglong(m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Realloc])) + "<br>" +
										QStringColor(tr("   Frees"), "ffffffff") + locale.toString(qulonglong(m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Free])) + "</pre>";
				m_toolTipLabel->setText(str);
				m_item->redraw();
				invalidateScene();
				return;
			}
}

void TreeMapView::buildTreeRecurse(rtm::StackTraceTree* _tree)
{
	if (_tree->m_children.size() == 0)
	{
		TreeMapNode node;

		node.m_tree		= _tree;
		node.m_size		= getNodeValueByType( node, m_mapType );

		m_tree.push_back(node);
		m_treeLines.append(QLineF());
		m_treeLines.append(QLineF());
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
	m_item->redraw();
	invalidateScene();
}

void TreeMapView::mousePressEvent(QMouseEvent* _event)
{
	QGraphicsView::mousePressEvent(_event);
}

void TreeMapView::mouseMoveEvent(QMouseEvent* _event)
{
	updateHighlight(_event->pos());

	if (m_highlightNode)
	{
		m_toolTipLabel->move(QCursor::pos() + QPoint(15,15));
		m_toolTipLabel->setFont(s_toolTipFont);
		m_toolTipLabel->adjustSize();
		if(m_toolTipLabel->isHidden())
			m_toolTipLabel->show();
	}
	else
		m_toolTipLabel->hide();

	QGraphicsView::mouseMoveEvent(_event);

	static TreeMapNode* lastHLnode = 0;
	if (lastHLnode != m_highlightNode)
	{
		lastHLnode = m_highlightNode;
		repaint();
	}
}

void TreeMapView::mouseReleaseEvent(QMouseEvent* _event)
{
	if (_event->button() == Qt::LeftButton)
	{
		if (m_highlightNode)
		{
			rtm::StackTrace** trace = &m_highlightNode->m_tree->m_stackTraceList;
			emit setStackTrace(trace, 1);

			if (m_clickedNode != m_highlightNode)
			{
				m_clickedNode = m_highlightNode;
				repaint();
			}

			const uint32_t numOps =	m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Alloc] +
									m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Free]  +
									m_highlightNode->m_tree->m_opCount[rtm::StackTraceTree::Realloc];
			if (numOps == 1)
				emit highlightTime(m_highlightNode->m_tree->m_minTime);
			else
				emit highlightRange(m_highlightNode->m_tree->m_minTime, m_highlightNode->m_tree->m_maxTime);
		}
		else
		{
			emit setStackTrace(NULL, 0);
			m_clickedNode = NULL;
		}
	}

	QGraphicsView::mouseReleaseEvent(_event);
}

void TreeMapView::enterEvent(QEnterEvent*)
{
	repaint();
}

void TreeMapView::leaveEvent(QEvent*)
{
	m_highlightNode		= NULL;
	m_toolTipLabel->hide();

	repaint();
}

TreeMapGraphicsItem::TreeMapGraphicsItem(TreeMapView* _treeView, CaptureContext* _context)
{
	m_oldRect				= QRectF(0,0,0,0);
	m_treeView				= _treeView;
	m_context				= _context;
	_treeView->setItem(this);
	//setCacheMode(QGraphicsItem::DeviceCoordinateCache);
	setCacheMode(QGraphicsItem::NoCache);// ItemCoordinateCache);
	setAcceptHoverEvents(true);
}

void TreeMapGraphicsItem::redraw()
{
	m_oldRect = QRectF(0,0,0,0);
}

QRectF TreeMapGraphicsItem::boundingRect() const
{
	return QRectF(m_treeView->pos(), m_treeView->pos() + QPointF(m_treeView->width(), m_treeView->height()));
}

static inline void drawBlockText(const QString& _text, QPainter* _painter, int _fontHeight, int _fontWidths[17], QRectF& _rect, bool _highlight)
{
	if (_highlight)
		_painter->setPen(Qt::yellow);
	else
		_painter->setPen(Qt::white);

	int len = _text.length();
	if ((_rect.width() - _fontWidths[len] > 6.0f) && (_rect.height() > _fontHeight))
	{
		QRectF textRect = _rect.adjusted(3.0f,0,-3.0f,14-_rect.height());
		_painter->setFont(s_sizeFont);
		_painter->drawText(textRect,_text);
	}
}

void TreeMapGraphicsItem::paint(QPainter* _painter, const QStyleOptionGraphicsItem* _item, QWidget* _widget)
{
	RTM_UNUSED(_item);
	RTM_UNUSED(_widget);
	rtm_vector<TreeMapNode>& tree = m_treeView->getTree();
	QVector<QLineF>& lines = m_treeView->getTreeLines();

	QSize s = m_treeView->size();
	QRectF rect = m_treeView->mapToScene(QRect(0,0,s.width(),s.height())).boundingRect();
	if (m_oldRect != rect)
	{
		squaredLayout(tree, 0, (int)tree.size()-1, rect);
		calcLines(tree, lines);
		m_oldRect = rect;
	}

	TreeMapNode* highlight = m_treeView->getHighlightNode();
	TreeMapNode* clicked   = m_treeView->getClickedNode();

	_painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine));

	QColor c1(33, 80, 70, 255);
	QColor c2(33, 80, 90, 255);
	QColor c3(33, 70, 80, 255);

	_painter->setBrush(c2);
	_painter->drawLines(lines.data(), lines.size());

	if (clicked && (clicked != highlight))
	{
		QRectF highlightRect = clicked->m_rect;
		_painter->setBrush(c3);
		_painter->drawRect(highlightRect);
	}

	if (highlight)
	{
		QRectF highlightRect = highlight->m_rect;
		QLinearGradient gr(highlightRect.topLeft(), highlightRect.bottomRight());
		gr.setColorAt(0.0f, c1);
		gr.setColorAt(1.0f, c2);
		_painter->setBrush(gr);
		_painter->drawRect(highlightRect);
	}
	
	static const char* lenStrs[17] = {
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

	static bool initialized = false;
	static int textWidth[17];
	if (!initialized)
	{
		initialized = true;
		for (int i = 0; i < 17; ++i)
			textWidth[i] = QFontMetrics(s_sizeFont).horizontalAdvance(lenStrs[i]);
	}

	for (size_t i=0; i<tree.size(); ++i)
	{
		TreeMapNode& info = tree[i];
		if (info.m_tree->m_children.empty())
		{
			QLocale locale;
			int s_fontHeight = QFontMetrics(s_sizeFont).height();
			drawBlockText(locale.toString(qulonglong(info.m_size)), _painter, s_fontHeight, textWidth, info.m_rect, &info == highlight);
		}
	}
}
