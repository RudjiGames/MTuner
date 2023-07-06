//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GRAPHCURVE_H
#define RTM_MTUNER_GRAPHCURVE_H

class Graph;
class GraphWidget;

class GraphCurve : public QGraphicsItem
{
private:
	typedef rtm_vector<rtm::GraphEntry> GraphVec;

	Graph*			m_graph;
	GraphWidget*	m_graphWidget;
	uint64_t		m_minUsage;
	uint64_t		m_maxUsage;
	GraphVec		m_graphValues;
	bool			m_prevAutoZoom;
	uint64_t		m_prevMinTime;
	uint64_t		m_prevMaxTime;
	int64_t			m_prevLeft;
	int64_t			m_prevRight;
	uint64_t		m_prevPeakUsage;
	uint64_t		m_prevMinUsage;
	uint64_t		m_prevPeakLive;
	uint64_t		m_prevMinLive;

public:
	GraphCurve(GraphWidget* _graphWidget);

	void		setGraph(Graph* _graph);
	uint64_t	getMinUsage() const { return m_prevMinUsage; }
	uint64_t	getMaxUsage() const { return m_prevPeakUsage; }
	void		parentResized() { prepareGeometryChange(); }

	/// QWidget
	virtual QRectF			boundingRect() const;
	virtual QPainterPath	shape() const;
	virtual void			paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
	
};

#endif // RTM_MTUNER_GRAPHCURVE_H
