//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GRAPHSELECT_H
#define RTM_MTUNER_GRAPHSELECT_H

class GraphWidget;

class GraphSelect : public QGraphicsItem
{
private:
	GraphWidget*	m_graphWidget;
	uint64_t		m_minTime;
	uint64_t		m_maxTime;

public:
	GraphSelect(GraphWidget* _graphWidget);

	void parentResized() { prepareGeometryChange(); }
	void setSelectRange(uint64_t _minTime, uint64_t _maxTime);

	/// QWidget
	virtual QRectF	boundingRect() const;
	virtual void	paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);
	
};

#endif // RTM_MTUNER_GRAPHSELECT_H
