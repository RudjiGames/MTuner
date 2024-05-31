//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_TREEMAP_H
#define RTM_MTUNER_TREEMAP_H

#include <MTuner/src/treemapview.h>
#include <MTuner/.qt/qt_ui/treemap_ui.h>

class TreeMapWidget : public QWidget
{
	Q_OBJECT

private:
	QGraphicsScene*			m_scene;
	CaptureContext*			m_context;
	TreeMapView*			m_graphicsView;
	TreeMapGraphicsItem*	m_map;

public:
	TreeMapWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);

	void setContext(CaptureContext* _context);
	void setFilteringState(bool _state);
	
public Q_SLOTS:
	void treeMapTypeChanged(int _type);
	
Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);
	void highlightTime(uint64_t);
	void highlightRange(uint64_t, uint64_t);

private:
	Ui::TreeMap ui;
};

#endif // RTM_MTUNER_TREEMAP_H
