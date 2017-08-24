//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_GRAPHGRID_H__
#define __RTM_MTUNER_GRAPHGRID_H__

class GraphWidget;
class GraphCurve;

class GraphGrid : public QGraphicsItem
{
private:
	GraphWidget*	m_graphWidget;
	GraphCurve*		m_curve;

public:
	GraphGrid(GraphWidget* _graphWidget, GraphCurve* _curve);

	void parentResized() { prepareGeometryChange(); }

	/// QWidget
	virtual QRectF			boundingRect() const;
	virtual QPainterPath	shape() const;
	virtual void			paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
	
};

#endif // __RTM_MTUNER_GRAPHGRID_H__
