//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GRAPHGRID_H
#define RTM_MTUNER_GRAPHGRID_H

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
	virtual QRectF	boundingRect() const;
	virtual void	paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
};

#endif // RTM_MTUNER_GRAPHGRID_H
