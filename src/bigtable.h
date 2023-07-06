//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_BIGTABLE_H
#define RTM_MTUNER_BIGTABLE_H

#include <MTuner/.qt/qt_ui/bigtable_ui.h>

class BigTableTableWidget;

class BigTableSource
{
public:
	virtual QStringList			getHeaderInfo(int32_t& _sortCol, Qt::SortOrder& _sortOrder, QList<int>& _widths) = 0;
	virtual uint32_t			getNumberOfRows() = 0;
	virtual	QString				getItem(uint32_t _index, int32_t _column, QColor* _color, bool* _setColor) = 0;
	virtual void				getItem(uint32_t _index, void**) = 0;
	virtual Qt::AlignmentFlag	getAlignment(uint32_t _index) = 0;
	virtual	uint32_t			getItemIndex(void* _item) = 0;
	virtual void				sortColumn(uint32_t _colIndex, Qt::SortOrder _order) = 0;
};

class BigTable : public QWidget
{
	Q_OBJECT

private:
	QStringList				m_header;
	BigTableTableWidget*	m_tree;
	QScrollBar*				m_scroll;
	BigTableSource*			m_source;
	int32_t					m_numColumns;
	int32_t					m_selectedRows;
	int32_t					m_firstVisible;
	int32_t					m_visibleRows;

public:
	BigTable(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);
	void setSource(BigTableSource* _src);
	void select(void* _item);
	void updateTable();
	void resetView();
	void ensureSelectionVisible();

	/// QWidget
	void resizeEvent(QResizeEvent* _event);
	void wheelEvent(QWheelEvent* _event);
	void keyPressEvent(QKeyEvent* _event);

	QHeaderView* getHeader() { return m_tree->horizontalHeader(); }

Q_SIGNALS:
	void itemSelected(void*);
	void itemRightClicked(void*, const QPoint&);

public Q_SLOTS:
	void scroll(int);
	void rowSelected(QTableWidgetItem*);
	void rowRightClick(QTableWidgetItem*, const QPoint&);
	void sortSelection(int, Qt::SortOrder);

private:
	Ui::BigTableWidget ui;
};

#endif // RTM_MTUNER_BIGTABLE_H
