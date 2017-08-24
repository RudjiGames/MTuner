//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_TREEMAP_H__
#define __RTM_MTUNER_TREEMAP_H__

#include <mtuner/src/treemapview.h>
#include <mtuner/.qt/qt_ui/treemap_ui.h>

class TreeMapWidget : public QWidget
{
	Q_OBJECT

private:
	QGraphicsScene*			m_scene;
	CaptureContext*			m_context;
	TreeMapView*			m_graphicsView;
	TreeMapGraphicsItem*	m_map;

public:
	TreeMapWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void changeEvent(QEvent* _event);

	void setContext(CaptureContext* _context);
	void setFilteringState(bool _state);
	
public Q_SLOTS:
	void treeMapTypeChanged(int _type);
	
Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);

private:
	Ui::TreeMap ui;
};

#endif // __RTM_MTUNER_TREEMAP_H__
