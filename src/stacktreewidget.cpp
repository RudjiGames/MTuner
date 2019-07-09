//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/stacktreewidget.h>
#include <MTuner/src/capturecontext.h>

struct Header
{
	enum Enum
	{
		Name,
		Module,
		Usage,
		PeakUsage,
		Allocs,
		Frees,
		Reallocs,
		File,
		Line
	};
};

class TreeItem
{
public:
	TreeItem(CaptureContext* _context, const rtm::StackTraceTree* _tree, TreeItem* _parent, const rtm::StackTraceTree* _root, int _depth);
	~TreeItem();

	void appendChild(TreeItem* _child);

	TreeItem*			child(int _row);
	int					childCount() const;
	int					columnCount() const;
	QVariant			data(int _column) const;
	int					row() const;
	TreeItem*			parent();
	rtm::StackTrace*	getStackTraceListRoot()
	{
		return m_tree->m_stackTraceList;
	}
	int					depth() const { return m_depth; }

//private:
	int							m_depth;
	rtm_vector<TreeItem*>		m_children;
	CaptureContext*				m_context;
	const rtm::StackTraceTree*	m_tree;
	TreeItem*					m_parent;
	const rtm::StackTraceTree*	m_root;
	mutable QString				m_module;
	mutable QString				m_file;
	mutable QString				m_func;
	mutable int					m_line;
	mutable bool				m_resolved;
};


// SORTING by func

static inline bool sortTreeFunc_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_func < _in2->m_func;
}

static inline bool sortTreeFunc_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_func > _in2->m_func;
}

void sortTreeCol_Func_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeFunc_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Func_asc(item);
}

void sortTreeCol_Func_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeFunc_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Func_des(item);
}

// SORTING by module

static inline bool sortTreeModule_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_module < _in2->m_module;
}

static inline bool sortTreeModule_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_module > _in2->m_module;
}

void sortTreeCol_Module_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeModule_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Module_asc(item);
}

void sortTreeCol_Module_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeModule_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Module_des(item);
}

// SORTING by usage

static inline bool sortTreeUsage_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_memUsage < _in2->m_tree->m_memUsage;
}

static inline bool sortTreeUsage_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_memUsage > _in2->m_tree->m_memUsage;
}

void sortTreeCol_Usage_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeUsage_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Usage_asc(item);
}

void sortTreeCol_Usage_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeUsage_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Usage_des(item);
}

// SORTING by peak allocs
static inline bool sortTreeAllocs_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_opCount[rtm::StackTraceTree::ALLOC] < _in2->m_tree->m_opCount[rtm::StackTraceTree::ALLOC];
}

static inline bool sortTreeAllocs_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_opCount[rtm::StackTraceTree::ALLOC] > _in2->m_tree->m_opCount[rtm::StackTraceTree::ALLOC];
}

void sortTreeCol_Allocs_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeAllocs_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Allocs_asc(item);
}

void sortTreeCol_Allocs_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeAllocs_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Allocs_des(item);
}

// SORTING by peak frees
static inline bool sortTreeFrees_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_opCount[rtm::StackTraceTree::FREE] < _in2->m_tree->m_opCount[rtm::StackTraceTree::FREE];
}

static inline bool sortTreeFrees_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_opCount[rtm::StackTraceTree::FREE] > _in2->m_tree->m_opCount[rtm::StackTraceTree::FREE];
}

void sortTreeCol_Frees_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeFrees_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Frees_asc(item);
}

void sortTreeCol_Frees_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeFrees_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Frees_des(item);
}

// SORTING by peak reallocs
static inline bool sortTreeReallocs_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_opCount[rtm::StackTraceTree::REALLOC] < _in2->m_tree->m_opCount[rtm::StackTraceTree::REALLOC];
}

static inline bool sortTreeReallocs_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_opCount[rtm::StackTraceTree::REALLOC] > _in2->m_tree->m_opCount[rtm::StackTraceTree::REALLOC];
}

void sortTreeCol_Reallocs_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeReallocs_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Reallocs_asc(item);
}

void sortTreeCol_Reallocs_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeReallocs_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Reallocs_des(item);
}

// SORTING by peak usage

static inline bool sortTreeUsagePeak_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_memUsagePeak < _in2->m_tree->m_memUsagePeak;
}

static inline bool sortTreeUsagePeak_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_tree->m_memUsagePeak > _in2->m_tree->m_memUsagePeak;
}

void sortTreeCol_PeakUsage_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeUsagePeak_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_PeakUsage_asc(item);
}

void sortTreeCol_PeakUsage_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeUsagePeak_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_PeakUsage_des(item);
}

// SORTING by file

static inline bool sortTreeFile_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_file < _in2->m_file;
}

static inline bool sortTreeFile_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_file > _in2->m_file;
}

void sortTreeCol_File_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeFile_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_File_asc(item);
}

void sortTreeCol_File_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeFile_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_File_des(item);
}

// SORTING by line

static inline bool sortTreeLine_asc(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_line < _in2->m_line;
}

static inline bool sortTreeLine_des(TreeItem* _in1, TreeItem* _in2)
{
	return _in1->m_line > _in2->m_line;
}

void sortTreeCol_Line_asc(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeLine_asc);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Line_asc(item);
}

void sortTreeCol_Line_des(TreeItem* _item)
{
	std::sort(_item->m_children.begin(), _item->m_children.end(), sortTreeLine_des);
	for (TreeItem* item : _item->m_children)
		sortTreeCol_Line_des(item);
}


TreeItem::TreeItem(CaptureContext* _context, const rtm::StackTraceTree* _tree, TreeItem* _parent, const rtm::StackTraceTree* _root, int _depth)
{
	m_resolved	= false;
	m_context	= _context;
	m_tree		= _tree;
	m_root		= _root;
	m_parent	= _parent;
	m_depth		= _depth;

	if (m_parent)
		m_parent->appendChild(this);
}

TreeItem::~TreeItem()
{
	qDeleteAll(m_children);
	m_children.clear();
}

void TreeItem::appendChild(TreeItem* _item)
{
	m_children.push_back(_item);
}

TreeItem *TreeItem::child(int _row)
{
	return m_children[_row];
}

int TreeItem::childCount() const
{
	return (int)m_children.size();
}

int TreeItem::columnCount() const
{
	return 9;
}

QVariant TreeItem::data(int _column) const
{
	if (m_parent == NULL)
	{
		switch (_column)
		{
			case Header::Name:		return QObject::tr("Name");
			case Header::Module:	return QObject::tr("Module");
			case Header::Usage:		return QObject::tr("Usage");
			case Header::PeakUsage:	return QObject::tr("Peak Usage");
			case Header::Allocs:	return QObject::tr("Allocations");
			case Header::Frees:		return QObject::tr("Frees");
			case Header::Reallocs:	return QObject::tr("Reallocations");
			case Header::File:		return QObject::tr("File");
			case Header::Line:		return QObject::tr("Line");
		};
		return "";
	}
	else
	{
		if (!m_resolved)
		{
			rdebug::StackFrame frame;
			m_context->resolveStackFrame(m_tree->m_stackTraceList->m_entries[m_tree->m_stackTraceList->m_numEntries - m_depth], frame);

			QString file = QString::fromUtf8(frame.m_file);

			QString srcpath = QDir(file).path();
			if (!QDir::isRelativePath(srcpath))
				m_file = QDir(srcpath).absolutePath();
			else
				m_file = srcpath;

			m_module	= QString::fromUtf8(frame.m_moduleName);
			m_func		= QString::fromUtf8(frame.m_func);
			m_line		= frame.m_line;
			m_resolved	= true;
		}

		QLocale locale;

		switch (_column)
		{
			case Header::Name:		return m_func;
			case Header::Module:	return m_module;
			case Header::Usage:		return m_tree->m_memUsage ? ((float(m_tree->m_memUsage) * 100.0f) / float(m_root->m_memUsage)) : 0;
			case Header::PeakUsage:	return m_tree->m_memUsagePeak ? ((float(m_tree->m_memUsagePeak) * 100.0f) / float(m_root->m_memUsagePeak)) : 0;
			case Header::Allocs:	return locale.toString(m_tree->m_opCount[rtm::StackTraceTree::ALLOC]);
			case Header::Frees:		return locale.toString(m_tree->m_opCount[rtm::StackTraceTree::FREE]);
			case Header::Reallocs:	return locale.toString(m_tree->m_opCount[rtm::StackTraceTree::REALLOC]);
			case Header::File:		return m_file;
			case Header::Line:		return QString::number(m_line);
		};
		return "";
	}
}

TreeItem* TreeItem::parent()
{
	return m_parent;
}

int TreeItem::row() const
{
	if (m_parent)
	{
		const size_t children = m_parent->m_children.size();
		for (size_t i=0; i<children; ++i)
			if (m_parent->m_children[i] == this)
				return (int)i;
	}

	return 0;
}


void ProgressBarDelegate::paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const
{
	if ((_index.column() == 2) || (_index.column() == 3))
	{
		float progress = _index.data().toFloat();

		QRect rr = _option.rect;
		rr.adjust(-1,-1,1,1);
		_painter->setClipRect(rr);
		QRect rect(_option.rect);
		rect.adjust(2,0,-2,0);
		
		_painter->setBrush(Qt::NoBrush);
		_painter->setPen(Qt::gray);
		_painter->drawRect(rect);

		QString txt = QString::number(progress,'f',2) + "%";
		rect.adjust(1,1,0,0);
		_painter->setPen(Qt::gray);
		_painter->drawText(rect, txt, QTextOption(Qt::AlignCenter));

		QRect pRect = rect;
		pRect.adjust(0,0,-rect.width()*(100-progress)/100,0);

		QLinearGradient gr(pRect.topLeft(), pRect.topRight());

		QColor c(50, 150, 170, 131);

		gr.setColorAt(0.0f, c);
		gr.setColorAt(1.0f, c);
		
		_painter->setBrush(gr);
		_painter->setPen(Qt::NoPen);
		_painter->drawRect(pRect);

		_painter->setPen(Qt::white);
		_painter->setClipRect(pRect);
		_painter->drawText(rect, Qt::AlignCenter, txt);
		_painter->setClipRect(pRect);
		_painter->setClipping(false);
	}
	else
		QStyledItemDelegate::paint(_painter, _option, _index);
}

QSize ProgressBarDelegate::sizeHint(const QStyleOptionViewItem& _option, const QModelIndex& _index) const
{
	return QStyledItemDelegate::sizeHint(_option, _index);
}

TreeModel::TreeModel(CaptureContext* _context, QObject* _parent) :
	QAbstractItemModel(_parent)
{
	m_context = _context;
	updateData();
}

TreeModel::~TreeModel()
{
	beginResetModel();
	delete m_rootItem;
	endResetModel();
}

int TreeModel::columnCount(const QModelIndex& _parent) const
{
	if (_parent.isValid())
		return static_cast<TreeItem*>(_parent.internalPointer())->columnCount();
	else
		return m_rootItem->columnCount();
}

void TreeModel::sort(int _column, Qt::SortOrder _order)
{
	switch (_column)
	{
	case Header::Name:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_Func_asc(m_rootItem);
			else
				sortTreeCol_Func_des(m_rootItem);
			break;

	case Header::Module:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_Module_asc(m_rootItem);
			else
				sortTreeCol_Module_des(m_rootItem);
			break;

	case Header::Usage:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_Usage_asc(m_rootItem);
			else
				sortTreeCol_Usage_des(m_rootItem);
			break;

	case Header::Allocs:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_Allocs_asc(m_rootItem);
			else
				sortTreeCol_Allocs_des(m_rootItem);
			break;

	case Header::Frees:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_Frees_asc(m_rootItem);
			else
				sortTreeCol_Frees_des(m_rootItem);
			break;

	case Header::Reallocs:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_Reallocs_asc(m_rootItem);
			else
				sortTreeCol_Reallocs_des(m_rootItem);
			break;

	case Header::PeakUsage:	if (_order == Qt::AscendingOrder)
				sortTreeCol_PeakUsage_asc(m_rootItem);
			else
				sortTreeCol_PeakUsage_des(m_rootItem);
			break;

	case Header::File:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_File_asc(m_rootItem);
			else
				sortTreeCol_File_des(m_rootItem);
			break;

	case Header::Line:
			if (_order == Qt::AscendingOrder)
				sortTreeCol_Line_asc(m_rootItem);
			else
				sortTreeCol_Line_des(m_rootItem);
			break;
	};

	m_savedColumn	= _column;
	m_savedOrder	= _order;
}

QVariant TreeModel::data(const QModelIndex& _index, int _role) const
{
	if (!_index.isValid())
		return QVariant();

	if (_role != Qt::DisplayRole)
		return QVariant();

	TreeItem* item = static_cast<TreeItem*>(_index.internalPointer());

	return item->data(_index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& _index) const
{
	if (!_index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int _section, Qt::Orientation _orientation, int _role) const
{
	if ((_orientation == Qt::Horizontal) && (_role == Qt::DisplayRole))
		return m_rootItem->data(_section);

	return QVariant();
}

QModelIndex TreeModel::index(int _row, int _column, const QModelIndex& _parent) const
{
	if (!hasIndex(_row, _column, _parent))
		return QModelIndex();

	TreeItem *parentItem;

	if (!_parent.isValid())
		parentItem = m_rootItem;
	else
		parentItem = static_cast<TreeItem*>(_parent.internalPointer());

	TreeItem *childItem = parentItem->child(_row);
	if (childItem)
		return createIndex(_row, _column, childItem);
	else
		return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& _index) const
{
	if (!_index.isValid())
		return QModelIndex();

	TreeItem *childItem = static_cast<TreeItem*>(_index.internalPointer());
	TreeItem *parentItem = childItem->parent();

	if (parentItem == m_rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex& _parent) const
{
	TreeItem *parentItem;
	if (_parent.column() > 0)
		return 0;

	if (!_parent.isValid())
		parentItem = m_rootItem;
	else
		parentItem = static_cast<TreeItem*>(_parent.internalPointer());

	return parentItem->childCount();
}

void TreeModel::updateData()
{
	const rtm::StackTraceTree* tree = NULL;
	if (m_context->m_capture->getFilteringEnabled())
		tree = &m_context->m_capture->getStackTraceTreeFiltered();
	else
		tree = &m_context->m_capture->getStackTraceTree();

	m_rootItem = new TreeItem(m_context, NULL, NULL, tree, 0);

	if (m_context->m_capture->getFilteringEnabled())
		setupModelData(m_context->m_capture->getStackTraceTreeFiltered(), m_rootItem, tree, 1);
	else
		setupModelData(m_context->m_capture->getStackTraceTree(), m_rootItem, tree, 1);
}

void TreeModel::setupModelData(const rtm::StackTraceTree& _tree, TreeItem* _parent, const rtm::StackTraceTree* _root, int _depth)
{
	rtm::StackTraceTree::ChildNodes::const_iterator it  = _tree.m_children.begin();
	rtm::StackTraceTree::ChildNodes::const_iterator end = _tree.m_children.end();
	while (it != end)
	{
		const rtm::StackTraceTree& tree = *it;

		TreeItem* treeItem = new TreeItem(m_context, &tree, _parent, _root, _depth);
		setupModelData(tree, treeItem, _root, _depth+1);
		++it;
	}
}

StackTreeWidget::StackTreeWidget(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);

	m_context = NULL;
	m_enableFiltering = false;
	m_tree = findChild<QTreeView*>("treeWidget");
	m_tree->setItemDelegate( new ProgressBarDelegate() );
}

StackTreeWidget::~StackTreeWidget()
{
	m_tree->setModel(NULL);
}

void StackTreeWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void StackTreeWidget::loadState(QSettings& _settings)
{
	if (_settings.contains("stackTreeSortColumn"))
	{
		m_savedColumn = _settings.value("stackTreeSortColumn").toInt();
		m_savedOrder = (Qt::SortOrder)_settings.value("stackTreeSortOrder").toInt();
		m_headerState = _settings.value("stackTreeHeaderState").toByteArray();
	}
	else
	{
		m_savedColumn = Header::Usage;
		m_savedOrder = Qt::DescendingOrder;
	}
}

void StackTreeWidget::saveState(QSettings& _settings)
{
	TreeModel* model = (TreeModel*)m_tree->model();
	
	_settings.setValue("stackTreeSortColumn", model->m_savedColumn);
	_settings.setValue("stackTreeSortOrder", (int)model->m_savedOrder);
	_settings.setValue("stackTreeHeaderState", m_tree->header()->saveState());
}

void StackTreeWidget::setContext(CaptureContext* _context)
{
	m_tree->setSortingEnabled(false);

	m_context = _context;
	if (m_context)
		setupTree();

	m_tree->setSortingEnabled(true);
	m_tree->sortByColumn(m_savedColumn, m_savedOrder);
}

void StackTreeWidget::setFilteringState(bool _state)
{
	m_tree->setSortingEnabled(false);
	m_enableFiltering = _state;
	setupTree();
	m_tree->setSortingEnabled(true);
}

bool StackTreeWidget::getFilteringState() const
{
	return m_enableFiltering;
}

void StackTreeWidget::setupTree()
{
	TreeModel* model = new TreeModel(m_context);
	m_tree->setModel(model);
	m_tree->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(m_tree->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(rowClicked(const QModelIndex&)));
	m_tree->setRootIsDecorated(true);
	m_tree->setHeaderHidden(false);
	m_tree->setUniformRowHeights(true);
}

void StackTreeWidget::rowClicked(const QModelIndex& _index)
{
	TreeItem *item = static_cast<TreeItem*>(_index.internalPointer());
	rtm::StackTrace* trace = item->getStackTraceListRoot();
	int depth = item->depth();

	m_stackTraces.clear();

	while (trace)
	{
		m_stackTraces.push_back(trace);
		trace = trace->m_next[depth];
	}

	emit setStackTrace(m_stackTraces.data(), (int)m_stackTraces.size());
}
