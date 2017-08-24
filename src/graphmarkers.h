//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_GRAPHMARKERS_H__
#define __RTM_MTUNER_GRAPHMARKERS_H__

class GraphWidget;
class GraphCurve;

struct MarkerToolTip
{
	QRectF		m_rect;
	const char*	m_text;
	float		m_time;
	uint64_t	m_threadID;

	MarkerToolTip() {}
	MarkerToolTip(const QRect& _rect, const char* _text, float _time, uint64_t _threadID) : 
		m_rect(_rect), 
		m_text(_text), 
		m_time(_time), 
		m_threadID(_threadID)
	{}
};

class GraphMarkers : public QGraphicsItem
{
private:
	GraphWidget*			m_graphWidget;
	QVector<MarkerToolTip>	m_toolTips;

public:
	GraphMarkers(GraphWidget* _graphWidget);

	void parentResized() { prepareGeometryChange(); }
	const QVector<MarkerToolTip>& getTooltips() const { return m_toolTips; }

	/// QWidget
	virtual QRectF			boundingRect() const;
	virtual QPainterPath	shape() const;
	virtual void			paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
};

#endif // __RTM_MTUNER_GRAPHMARKERS_H__
