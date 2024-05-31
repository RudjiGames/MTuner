//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_BIGTABLETABLEWIDGET_H
#define RTM_MTUNER_BIGTABLETABLEWIDGET_H

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

#endif // RTM_MTUNER_BIGTABLETABLEWIDGET_H
