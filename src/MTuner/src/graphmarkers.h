//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GRAPHMARKERS_H
#define RTM_MTUNER_GRAPHMARKERS_H

class GraphWidget;
class GraphCurve;

struct MarkerToolTip
{
	QRectF		m_rect;
	float		m_time;
	uint64_t	m_threadID;
	std::string	m_text;

	MarkerToolTip() {}
	MarkerToolTip(const QRect& _rect, float _time, uint64_t _threadID, const char* _text) :
		m_rect(_rect), 
		m_time(_time), 
		m_threadID(_threadID)
	{
		m_text = _text;
	}
};

class GraphMarkers : public QGraphicsItem
{
private:
	GraphWidget*			m_graphWidget;

public:
	GraphMarkers(GraphWidget* _graphWidget);

	void parentResized() { prepareGeometryChange(); }
	MarkerToolTip getTooltip(const QPointF& _point) const;

	/// QWidget
	virtual QRectF			boundingRect() const;
	virtual QPainterPath	shape() const;
	virtual void			paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
};

#endif // RTM_MTUNER_GRAPHMARKERS_H
