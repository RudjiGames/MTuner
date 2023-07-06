//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_TAGTREEWIDGET_H
#define RTM_MTUNER_TAGTREEWIDGET_H

#include <MTuner/.qt/qt_ui/tagtree_ui.h>

class TagTreeItem;
struct CaptureContext;

class TagTreeModel : public QAbstractItemModel
{
	Q_OBJECT

private:
	CaptureContext*	m_context;
	TagTreeItem*	m_rootItem;

public:
	TagTreeModel(CaptureContext* _context, QObject* _parent = 0);
	~TagTreeModel();

	QVariant		data(const QModelIndex& _index, int _role) const;
	Qt::ItemFlags	flags(const QModelIndex& _index) const;
	QVariant		headerData(int _section, Qt::Orientation _orientation, int _role = Qt::DisplayRole) const;
	QModelIndex		index(int _row, int _column, const QModelIndex& _parent = QModelIndex()) const;
	QModelIndex		parent(const QModelIndex& _index) const;
	int				rowCount(const QModelIndex& _parent = QModelIndex()) const;
	int				columnCount(const QModelIndex& _parent = QModelIndex()) const;

private:
	void setupModelData(const rtm::MemoryTagTree* _tree, TagTreeItem* _parent);
};

class TagTreeWidget : public QWidget
{
	Q_OBJECT

	CaptureContext*	m_context;
	QTreeView*		m_tree;

public:
	TagTreeWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* event);
	void setContext(CaptureContext* _context);
	void setupTree();

public Q_SLOTS:
	void rowClicked(const QModelIndex&);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);
	void tagClicked();

private:
	Ui::tagTree ui;
};

#endif // RTM_MTUNER_TAGTREEWIDGET_H
