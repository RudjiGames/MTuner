//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_TREEMAPVIEW_H
#define RTM_MTUNER_TREEMAPVIEW_H

class TreeMapWidget;
class TreeMapGraphicsItem;
struct CaptureContext;

struct TreeMapNode
{
	rtm::StackTraceTree*	m_tree;		///< Pointer to the actual stact trace tree node, used to resolve symbols
	uint64_t				m_size;		///< Size of the node, based on the view type (usage, peak, etc.)
	uint32_t				m_allocs;	///< Number of allocations
	uint32_t				m_reallocs;	///< Number of reallocations
	uint32_t				m_frees;	///< Number of frees
	QRectF					m_rect;
	
	TreeMapNode()
		: m_size(0)
		, m_allocs(0)
		, m_reallocs(0)
		, m_frees(0)
	{}
};

class TreeMapView : public QGraphicsView
{
	Q_OBJECT

private:
	CaptureContext*					m_context;
	rtm_vector<TreeMapNode>			m_tree;
	QList<QLineF>					m_treeLines;
	TreeMapNode*					m_highlightNode;
	uint32_t						m_mapType;
	TreeMapGraphicsItem*			m_item;
	QLabel*							m_toolTipLabel;

public:
	TreeMapView(QWidget* _parent = 0);

	void						setItem(TreeMapGraphicsItem* _item) { m_item = _item; }
	void						setContext(CaptureContext* _context);
	void						setMapType(uint32_t _type);
	uint32_t					getMapType() const { return m_mapType; }
	void						updateHighlight(const QPoint& _pos);
	inline TreeMapNode*			getHighlightNode() { return m_highlightNode; }
	rtm_vector<TreeMapNode>&	getTree() { return m_tree; }
	QVector<QLineF>&			getTreeLines() { return m_treeLines; }
	/// QWidget
	void resizeEvent(QResizeEvent* _event);
	void mousePressEvent(QMouseEvent* _event);
	void mouseMoveEvent(QMouseEvent* _event);
	void mouseReleaseEvent(QMouseEvent* _event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);

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
	virtual void			paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
};

#endif // RTM_MTUNER_TREEMAPVIEW_H
