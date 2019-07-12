//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/bigtable.h>
#include <MTuner/src/bigtabletablewidget.h>

class ForegroundColorItemDelegate : public QItemDelegate
{
public:
	ForegroundColorItemDelegate(QObject* _parent = 0) :
		QItemDelegate(_parent)
	{}

	void paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const  
	{
		QStyleOptionViewItem ViewOption(_option);

		QColor ItemForegroundColor = _index.data(Qt::ForegroundRole).value<QColor>();
		if (ItemForegroundColor.isValid())
		{
			if (ItemForegroundColor != _option.palette.color(QPalette::WindowText))
			{
				ViewOption.palette.setColor(QPalette::HighlightedText, ItemForegroundColor);
			}
		}
		QItemDelegate::paint(_painter, ViewOption, _index);
	}
};

BigTableTableWidget::BigTableTableWidget(QWidget* _parent) :
		QTableWidget(_parent)
{
}

void BigTableTableWidget::contextMenuEvent(QContextMenuEvent* _event)
{
    QTableWidgetItem* itemHover = itemAt(_event->pos());
	emit itemContextMenu(itemHover, _event->globalPos());
}

BigTable::BigTable(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);
	m_source		= NULL;
	m_numColumns	= 0;
	m_firstVisible	= 0;
	m_visibleRows	= 0;
	m_selectedRows	= -1;

	m_tree		= findChild<BigTableTableWidget*>("tableWidget");
	m_scroll	= findChild<QScrollBar*>("verticalScrollBar");

	m_tree->setItemDelegate(new ForegroundColorItemDelegate());

	// hidden by default
	m_scroll->setVisible(false);
	connect(m_scroll, SIGNAL(valueChanged(int)), this, SLOT(scroll(int)));
	connect(m_tree, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(rowSelected(QTableWidgetItem*)));
	connect(m_tree, SIGNAL(itemContextMenu(QTableWidgetItem*,const QPoint&)), this, SLOT(rowRightClick(QTableWidgetItem*,const QPoint&)));
}

void BigTable::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	switch (_event->type())
	{
		case QEvent::LanguageChange:
			{
				ui.retranslateUi(this);
				int32_t sortCol;
				Qt::SortOrder sortOrder;
				m_header = m_source->getHeaderInfo(sortCol, sortOrder);
				m_tree->setHorizontalHeaderLabels(m_header);
			}
			break;
		// This silences warnings about cases not handled by the switch statement
		default:
			break;
	};
}

void BigTable::setSource(BigTableSource* _source)
{
	m_source = _source;
	resizeEvent(NULL);

	int32_t sortCol;
	Qt::SortOrder sortOrder;
	m_header = m_source->getHeaderInfo(sortCol, sortOrder);
	m_numColumns = m_header.size();
	m_tree->setColumnCount(m_numColumns);
	m_tree->setHorizontalHeaderLabels(m_header);
	m_tree->sortItems(sortCol, sortOrder);
	
	m_tree->horizontalHeader()->setHighlightSections(false);
	m_tree->horizontalHeader()->setSortIndicatorShown(true);

	connect(m_tree->horizontalHeader(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(sortSelection(int, Qt::SortOrder)));

	updateTable();
}

void BigTable::select(void* _item)
{
	m_selectedRows = m_source->getItemIndex(_item);
	ensureSelectionVisible();
	emit itemSelected(_item);
}

void BigTable::updateTable()
{
	m_tree->setUpdatesEnabled(false);
	m_tree->clearContents();

	m_tree->setRowCount(m_visibleRows);
	for (int32_t i=0; i<m_visibleRows; ++i)
	{
		for (int j=0; j<m_numColumns; j++)
		{
			QColor	col;
			bool	setColor = false;
			QString txt = m_source->getItem(i+m_firstVisible, j, &col, &setColor);
			QTableWidgetItem* item = new QTableWidgetItem(txt);
			item->setTextAlignment(m_source->getAlignment(j));

			if (setColor)
				item->setForeground(col);
			m_tree->setItem(i,j, item);
		}
	}

	if ((m_selectedRows >= m_firstVisible) && (m_selectedRows < m_firstVisible + m_visibleRows))
		m_tree->selectRow(m_selectedRows - m_firstVisible);
	m_tree->setUpdatesEnabled(true);
}

void BigTable::resetView()
{
	m_firstVisible	= 0;
	m_selectedRows	= -1;
	m_scroll->setValue(0);

	m_tree->setRowCount(2);
	uint32_t rowHeight = m_tree->rowHeight(0);
	uint32_t numRows = m_tree->size().height() / rowHeight;

	uint32_t visibleRows = numRows-1;

	if (visibleRows > m_source->getNumberOfRows())
	{
		visibleRows = m_source->getNumberOfRows();
		m_scroll->setVisible(false);
	}
	else
	{
		m_scroll->setVisible(true);
		m_scroll->setValue(0);
		m_scroll->setMaximum(m_source->getNumberOfRows() - visibleRows);
	}
	m_visibleRows = visibleRows;
	updateTable();
}

void BigTable::ensureSelectionVisible()
{
	if (m_selectedRows != -1)
	{
		if (m_selectedRows < m_firstVisible)
			m_firstVisible = m_selectedRows;
		else
			if (m_selectedRows > m_firstVisible + m_visibleRows - 1)
				m_firstVisible = m_selectedRows - m_visibleRows + 1;
	}

	m_scroll->setValue(m_firstVisible);
	updateTable();
}

void BigTable::resizeEvent(QResizeEvent* _event)
{
	RTM_UNUSED(_event);
	resetView();
	m_tree->clear();
	m_tree->setHorizontalHeaderLabels(m_header);
	m_tree->setRowCount(2);
	uint32_t rowHeight = m_tree->rowHeight(0);
	uint32_t numRows = m_tree->size().height() / rowHeight;
	rowHeight = rowHeight;

	uint32_t visibleRows = numRows-1;
	uint32_t numItems = m_source->getNumberOfRows();

	if ((numItems > visibleRows) && (m_scroll->isHidden() || (m_visibleRows != static_cast<int32_t>(visibleRows))))
	{
		m_scroll->setVisible(true);
		m_scroll->setMaximum(numItems - visibleRows);
		m_visibleRows = visibleRows;
	}
	else
	{
		if (numItems > visibleRows)
			m_visibleRows = visibleRows;
		else
			m_visibleRows = numItems;
	}
		
	m_tree->setRowCount(m_visibleRows);
	updateTable();
}

void BigTable::wheelEvent(QWheelEvent* _event)
{
	int delta = _event->delta();
	delta /= 120;
	delta = -delta;
	if (delta < 0)
	{
		if (m_firstVisible + delta >= 0)
			m_firstVisible += delta;
		else
			m_firstVisible = 0;
	}
	else
	{
		uint32_t lastVisibleRow = m_firstVisible + m_visibleRows;
		if (lastVisibleRow + delta < m_source->getNumberOfRows())
			m_firstVisible += delta;
		else
			m_firstVisible = m_source->getNumberOfRows() - m_visibleRows;
	}
	m_scroll->setValue(m_firstVisible);
	updateTable();
}

void BigTable::keyPressEvent(QKeyEvent* _event)
{
	if (_event->key() == Qt::Key_Up)
	{
		if (m_selectedRows == -1)
			m_selectedRows = 0;
		else
			if (m_selectedRows > 0)
				m_selectedRows--;
	}

	if (_event->key() == Qt::Key_Down)
	{
		if (m_selectedRows == -1)
			m_selectedRows = 0;
		else
			if (m_selectedRows < (int32_t)m_source->getNumberOfRows() - 1)
				m_selectedRows++;
	}

	if (_event->key() == Qt::Key_PageUp)
	{
		if (m_selectedRows == -1)
			m_selectedRows = 0;
		else
			if (m_selectedRows >= m_visibleRows)
				m_selectedRows -= m_visibleRows;
			else
				m_selectedRows = 0;
	}

	if (_event->key() == Qt::Key_PageDown)
	{
		if (m_selectedRows == -1)
			m_selectedRows = 0;
		else
			if (m_selectedRows < (int32_t)m_source->getNumberOfRows() - m_visibleRows - 1)
				m_selectedRows += m_visibleRows;
			else
				m_selectedRows = (int32_t)m_source->getNumberOfRows() - 1;
	}

	if (_event->key() == Qt::Key_Home)
		m_selectedRows = 0;

	if (_event->key() == Qt::Key_End)
		m_selectedRows = (int32_t)m_source->getNumberOfRows() - 1;


	void* item = NULL;
	m_source->getItem(m_selectedRows,&item);
	emit itemSelected(item);

	ensureSelectionVisible();
}

void BigTable::scroll(int _position)
{
	m_firstVisible = _position;
	updateTable();
}

void BigTable::rowSelected(QTableWidgetItem* _item)
{
	m_selectedRows = _item->row() + m_firstVisible;
	void* item = NULL;
	m_source->getItem(m_selectedRows,&item);
	emit itemSelected(item);
}

void BigTable::rowRightClick(QTableWidgetItem* _item, const QPoint& _pos)
{
	if (_item == NULL)
		return;
	
	m_selectedRows = _item->row() + m_firstVisible;
	void* item = NULL;
	m_source->getItem(m_selectedRows,&item);
	emit itemRightClicked(item, _pos);
}

void BigTable::sortSelection(int _section, Qt::SortOrder _sortOrder)
{
	void* item = NULL;
	if (m_selectedRows != -1)
		m_source->getItem(m_selectedRows,&item);

	m_source->sortColumn(_section, _sortOrder);
	ensureSelectionVisible();
}
