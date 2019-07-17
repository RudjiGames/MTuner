//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_TREEMAPVIEW_H
#define RTM_MTUNER_TREEMAPVIEW_H

class TreeMapWidget;
class TreeMapGraphicsItem;
struct CaptureContext;

struct TreeMapNode
{
	QRectF					m_rect;		///< Rectangle in the scene
	QString					m_text;		///< Tool tip text
	uint64_t				m_size;		///< Size of the node, based on the view type (usage, peak, etc.)
	uint64_t				m_allocs;	///< Number of allocations
	uint64_t				m_reallocs;	///< Number of reallocations
	uint64_t				m_frees;	///< Number of frees
	rtm::StackTraceTree*	m_tree;		///< Pointer to the actual stact trace tree node, used to resolve symbols
	
	TreeMapNode()
		: m_size(0)
		, m_allocs(0)
		, m_reallocs(0)
		, m_frees(0)
		, m_tree(NULL)
	{}
	
	void reset() { m_text.clear(); }
};

class TreeMapView : public QGraphicsView
{
	Q_OBJECT

private:
	QGraphicsScene*					m_scene;
	CaptureContext*					m_context;
	rtm_vector<TreeMapNode>			m_tree;
	TreeMapNode*					m_highlightNode;
	QElapsedTimer					m_timer;
	qint64							m_lastClick;
	uint32_t						m_mapType;
	TreeMapGraphicsItem*			m_item;

public:
	TreeMapView(QWidget* _parent = 0);

	void						setItem(TreeMapGraphicsItem* _item) { m_item = _item; }
	void						setContext(CaptureContext* _context);
	void						setMapType(uint32_t _type);
	uint32_t					getMapType() const { return m_mapType; }
	TreeMapNode*				findNode(QPoint& _point);
	inline TreeMapNode*			getHighlightNode() { return m_highlightNode; }
	rtm_vector<TreeMapNode>&	getTree() { return m_tree; }
	
	/// QWidget
	void resizeEvent(QResizeEvent* _event);
	void mousePressEvent(QMouseEvent* _event);
	void mouseMoveEvent(QMouseEvent* _event);
	void mouseReleaseEvent(QMouseEvent* _event);
	void leaveEvent(QEvent* _event);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);

private:
	void buildTreeRecurse(rtm::StackTraceTree* _tree);
	void buildTree();
};

class TreeMapGraphicsItem : public QGraphicsItem
{
private:
	QRectF			m_oldRect;
	TreeMapView*	m_treeView;
	CaptureContext*	m_context;

public:
	TreeMapGraphicsItem(TreeMapView* _treeView, CaptureContext* _context);

	void redraw();
	void parentResized() { prepareGeometryChange(); }

	/// QWidget
	virtual QRectF			boundingRect() const;
	virtual QPainterPath	shape() const;
	virtual void			paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
};

#endif // RTM_MTUNER_TREEMAPVIEW_H
