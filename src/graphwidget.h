//--------------------------------------------------------------------------//
/// Copyright (c) 2018 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GRAPHWIDGET_H
#define RTM_MTUNER_GRAPHWIDGET_H

class Graph;
class GraphCurve;
class GraphGrid;
class GraphSelect;
class GraphMarkers;
class BinLoaderView;
struct CaptureContext;

class GraphWidget : public QGraphicsView
{
	Q_OBJECT

    Q_PROPERTY(float minTime READ minTime WRITE setMinTime)
    Q_PROPERTY(float maxTime READ maxTime WRITE setMaxTime)
	Q_PROPERTY(float highlightIntensity READ highlightIntensity WRITE setHighlightIntensity)

private:
	Graph*					m_graph;
    QGraphicsScene*			m_scene;
	QPoint					m_dragStartPos;
	uint64_t				m_minTime;
	uint64_t				m_maxTime;
	uint64_t				m_hightlightTime;
	uint64_t				m_hightlightTimeEnd;
	float					m_hightlightIntensity;
	QPropertyAnimation*		m_highlightAnimation;
	bool					m_LButtonDown;
	bool					m_isDragging;
	bool					m_RButtonDown;
	bool					m_isPanning;
	uint64_t				m_hoverMarkerTime;
	uint64_t				m_markerSelectFromTime;
	uint64_t				m_markerSelectToTime;
	CaptureContext*			m_context;
	QVector<GraphCurve*>	m_curves;
	GraphGrid*				m_grid;
	GraphSelect*			m_select;
	GraphMarkers*			m_markers;
	QMenu*					m_contextMenu;
	QAction*				m_actionZoomToSelection;
	QAction*				m_actionZoomReset;
	bool					m_inContextMenu;
	QMenu*					m_contextMenuMarker;
	QAction*				m_actionSnapSelectionToMarker;
	QAction*				m_actionSelectFromMarker;
	QAction*				m_actionSelectToMarker;
	QLocale					m_locale;

public:
	static const int	s_marginLeft	= 45;
	static const int	s_marginRight	= 21;
	static const int	s_marginTop		= 15;
	static const int	s_marginBottom	= 27;

	GraphWidget(QWidget* _parent = 0);

	void			changeEvent(QEvent* _event);
	void			setGraph(Graph* _graph);
	uint64_t		minTime() { return m_minTime; }
	uint64_t		maxTime() { return m_maxTime; }
	float			highlightIntensity() { return m_hightlightIntensity; }
	void			setHighlightIntensity(float inI) { m_hightlightIntensity = inI; }
	void			setMinTime(uint64_t _minTime);
	void			setMaxTime(uint64_t _maxTime);
	void			setMinMaxTime( uint64_t _minTime, uint64_t _maxTime);
	uint64_t		getMarkerFromTime() const { return m_markerSelectFromTime; }
	uint64_t		getMarkerToTime() const { return m_markerSelectToTime; }
	void			setContext(CaptureContext* _context, BinLoaderView* _view);
	CaptureContext* getContext() { return m_context; };
	QRect			getDrawRect() const;
	uint64_t		mapPosToTime(int _x) const;
	int				mapTimeToPos(uint64_t _x) const;
	void			highlightTime(uint64_t _time);
	void			highlightRange(uint64_t _minTime, uint64_t _maxTime);
	void			animateHighlight();
	uint64_t		getHighlightTime() const { return m_hightlightTime; }
	uint64_t		getHighlightTimeEnd() const { return m_hightlightTimeEnd; }
	void			zoomIn(uint64_t _time);
	void			zoomOut(uint64_t _time);
	uint64_t		currentPos();

	/// QGraphicsView
	void drawBackground(QPainter* _painter, const QRectF& _rect);
	
	/// QWidget
	void resizeEvent(QResizeEvent* _event);
	void wheelEvent(QWheelEvent* _event);
	void mousePressEvent(QMouseEvent* _event);
	void mouseMoveEvent(QMouseEvent* _event);
	void mouseReleaseEvent(QMouseEvent* _event);
	void contextMenuEvent(QContextMenuEvent* _event);

protected:
	void mouseMovement(const QPoint& _position, Qt::MouseButtons _buttons = Qt::NoButton);
	void createCustomContextMenu();
	void animateRange(uint64_t _min, uint64_t _max);

public Q_SLOTS:
	void zoomIn();
	void zoomOut();
	void zoomReset();
	void zoomSelect();
	void zoomAnimEvent();
	void markerSnapTo();
	void markerSelectFrom();
	void markerSelectTo();
	void showToolTip();
	void selectFromTimes(uint64_t, uint64_t);

Q_SIGNALS:
	void snapshotSelected();
	void minMaxChanged();
};

#endif // RTM_MTUNER_GRAPHWIDGET_H
