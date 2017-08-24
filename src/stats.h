//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_STATS_H__
#define __RTM_MTUNER_STATS_H__

#include <mtuner/.qt/qt_ui/stats_ui.h>

class QTableWidget;
struct CaptureContext;

/// Disable focus selection on table
class StatsDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	virtual void drawFocus(QPainter*,const QStyleOptionViewItem&,const QRect&) const {}
};

class Stats : public QWidget
{
	Q_OBJECT

private:
	QTableWidget*	m_table;
	CaptureContext*	m_context;

public:
	Stats(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void changeEvent(QEvent* event);
	void setContext(CaptureContext* _context);
	void clear();

public Q_SLOTS:
	void updateUI();

private:
	Ui::Stats ui;
};

#endif // __RTM_MTUNER_STATS_H__
