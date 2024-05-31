//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/tagtreewidget.h>
#include <MTuner/src/capturecontext.h>

class TagTreeItem
{
public:
	TagTreeItem(CaptureContext* _context, const rtm::MemoryTagTree* _tree, TagTreeItem* _parent = 0);
	~TagTreeItem();

	void appendChild(TagTreeItem* _child);

	TagTreeItem*	child(int _row);
	int				childCount() const;
	int				columnCount() const;
	QVariant		data(int _column) const;
	int				row() const;
	TagTreeItem*	parent();
	uint32_t		getHash() { return m_tree->m_hash; }

private:
	QList<TagTreeItem*>			m_children;
	CaptureContext*				m_context;
	const rtm::MemoryTagTree*	m_tree;
	TagTreeItem*				m_parent;
};

TagTreeItem::TagTreeItem(CaptureContext* _context, const rtm::MemoryTagTree* _tree, TagTreeItem* _parent)
{
	m_context	= _context;
	m_tree		= _tree;
	m_parent	= _parent;
	if (m_parent)
		m_parent->appendChild(this);
}

TagTreeItem::~TagTreeItem()
{
	qDeleteAll(m_children);
}

void TagTreeItem::appendChild(TagTreeItem* _item)
{
	m_children.append(_item);
}

TagTreeItem *TagTreeItem::child(int _row)
{
	return m_children[_row];
}

int TagTreeItem::childCount() const
{
	return m_children.size();
}

int TagTreeItem::columnCount() const
{
	return 5;
}

QVariant TagTreeItem::data(int _column) const
{
	if (m_parent == NULL)
	{
		switch (_column)
		{
			case 0: return QObject::tr("Tag");
			case 1: return QObject::tr("Usage");
			case 2: return QObject::tr("Peak Usage");
			case 3: return QObject::tr("Overhead");
			case 4: return QObject::tr("Peak Overhead");
		};
	}
	else
	{
		QLocale locale;
		switch (_column)
		{
			case 0: if (m_tree->m_name.size() == 0)
						return QString(QObject::tr("Root"));
					else
						return QString(m_tree->m_name.c_str());
			case 1: return locale.toString(qulonglong(m_tree->m_usage));
			case 2: return locale.toString(qulonglong(m_tree->m_usagePeak));
			case 3:	return locale.toString(qulonglong(m_tree->m_overhead));
			case 4: return locale.toString(qulonglong(m_tree->m_overheadPeak));
		};
	}
	return "";
}

TagTreeItem* TagTreeItem::parent()
{
	return m_parent;
}

int TagTreeItem::row() const
{
	if (m_parent)
		return m_parent->m_children.indexOf(const_cast<TagTreeItem*>(this));

	return 0;
}

TagTreeModel::TagTreeModel(CaptureContext* _context, QObject* _parent) :
	QAbstractItemModel(_parent)
{
	m_context = _context;
	m_rootItem = new TagTreeItem(_context, NULL);
	setupModelData(&_context->m_capture->getTagTree(), m_rootItem);
}

TagTreeModel::~TagTreeModel()
{
	delete m_rootItem;
}

int TagTreeModel::columnCount(const QModelIndex& _parent) const
{
	if (_parent.isValid())
		return static_cast<TagTreeItem*>(_parent.internalPointer())->columnCount();
	else
		return m_rootItem->columnCount();
}

QVariant TagTreeModel::data(const QModelIndex& _index, int _role) const
{
	if (!_index.isValid())
		return QVariant();

	if (_role != Qt::DisplayRole)
		return QVariant();

	TagTreeItem *item = static_cast<TagTreeItem*>(_index.internalPointer());

	return item->data(_index.column());
}

Qt::ItemFlags TagTreeModel::flags(const QModelIndex& _index) const
{
	if (!_index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TagTreeModel::headerData(int _section, Qt::Orientation _orientation, int _role) const
{
	if (_orientation == Qt::Horizontal && _role == Qt::DisplayRole)
		return m_rootItem->data(_section);

	return QVariant();
}

QModelIndex TagTreeModel::index(int _row, int _column, const QModelIndex& _parent) const
{
	if (!hasIndex(_row, _column, _parent))
		return QModelIndex();

	TagTreeItem *parentItem;

	if (!_parent.isValid())
		parentItem = m_rootItem;
	else
		parentItem = static_cast<TagTreeItem*>(_parent.internalPointer());

	TagTreeItem *childItem = parentItem->child(_row);
	if (childItem)
		return createIndex(_row, _column, childItem);
	else
		return QModelIndex();
}

QModelIndex TagTreeModel::parent(const QModelIndex& _index) const
{
	if (!_index.isValid())
		return QModelIndex();

	TagTreeItem *childItem  = static_cast<TagTreeItem*>(_index.internalPointer());
	TagTreeItem *parentItem = childItem->parent();

	if (parentItem == m_rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int TagTreeModel::rowCount(const QModelIndex& _parent) const
{
	TagTreeItem *parentItem;
	if (_parent.column() > 0)
		return 0;

	if (!_parent.isValid())
		parentItem = m_rootItem;
	else
		parentItem = static_cast<TagTreeItem*>(_parent.internalPointer());

	return parentItem->childCount();
}

void TagTreeModel::setupModelData(const rtm::MemoryTagTree* _tree, TagTreeItem* _parent)
{
	TagTreeItem* treeItem = new TagTreeItem(m_context, _tree, _parent);

	rtm::MemoryTagTree::ChildMap::const_iterator it  = _tree->m_children.begin();
	rtm::MemoryTagTree::ChildMap::const_iterator end = _tree->m_children.end();

	while (it != end)
	{
		rtm::MemoryTagTree* tree = it->second;
		setupModelData(tree,treeItem);
		++it;
	}
}

TagTreeWidget::TagTreeWidget(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);

	m_context = NULL;
	m_tree = findChild<QTreeView*>("treeWidget");
	connect(m_tree,SIGNAL(entered(const QModelIndex&)), this, SLOT(rowClicked(const QModelIndex&)));
}

void TagTreeWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
	{
		ui.retranslateUi(this);
		setContext(m_context); // could be more efficient...
	}
}

void TagTreeWidget::setContext(CaptureContext* _context)
{
	m_context = _context;
	if (m_context)
		setupTree();
	else
		m_tree->setModel(NULL);
}

void TagTreeWidget::setupTree()
{
	TagTreeModel* model = new TagTreeModel(m_context);
	m_tree->setModel(model);
	m_tree->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(m_tree->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(rowClicked(const QModelIndex&)));
	m_tree->setRootIsDecorated(true);
	m_tree->setHeaderHidden(false);
	m_tree->setUniformRowHeights(true);
	m_tree->expandAll();
	for (int i=0; i<5; ++i)
		m_tree->resizeColumnToContents(i);
}

void TagTreeWidget::rowClicked(const QModelIndex& _index)
{
	TagTreeItem *item = static_cast<TagTreeItem*>(_index.internalPointer());
	if (m_context && item)
	{
		m_context->m_capture->selectTag(item->getHash());
		emit tagClicked();
	}
}
