//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_BIGTABLETABLEWIDGET_H__
#define __RTM_MTUNER_BIGTABLETABLEWIDGET_H__

class BigTableTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	BigTableTableWidget(QWidget* _parent = 0);

	/// Disable default navigation
	QModelIndex moveCursor(QAbstractItemView::CursorAction, Qt::KeyboardModifiers) { return QModelIndex(); }
	void contextMenuEvent(QContextMenuEvent* _event);

Q_SIGNALS:
	void itemContextMenu(QTableWidgetItem*, const QPoint&);
};

#endif // __RTM_MTUNER_BIGTABLETABLEWIDGET_H__
