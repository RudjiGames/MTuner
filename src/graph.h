//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GRAPH_H
#define RTM_MTUNER_GRAPH_H

#include <MTuner/.qt/qt_ui/graph_ui.h>

class GraphWidget;
class BinLoaderView;
struct CaptureContext;

class Graph : public QWidget
{
	Q_OBJECT

private:
 	GraphWidget*	m_graph;
	QToolButton*	m_buttonZoomIn;
	QToolButton*	m_buttonZoomOut;
	QToolButton*	m_buttonZoomReset;
	QToolButton*	m_buttonZoomSelect;
	QToolButton*	m_buttonAutoZoom;
	QScrollBar*		m_scroll;
	CaptureContext*	m_context;

public:
	Graph(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);
	void setContext(CaptureContext* _context, BinLoaderView* _binView);
	bool isAutoZoomSet() const;
	inline GraphWidget* getGraphWidget() { return m_graph; }

public Q_SLOTS:
	void snapshotSelected();
	void zoomChanged();
	void scrollMoved(int);
	void highlightTime(uint64_t);
	void highlightRange(uint64_t, uint64_t);

private:
	Ui::Graph ui;
};

#endif // RTM_MTUNER_GRAPH_H
