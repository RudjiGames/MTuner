//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_STACKTREEWIDGET_H
#define RTM_MTUNER_STACKTREEWIDGET_H

#include <MTuner/.qt/qt_ui/stacktree_ui.h>

class TreeItem;
struct CaptureContext;

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

private:
	CaptureContext*	m_context;
	TreeItem*		m_rootItem;

public:
	int				m_savedColumn;
	Qt::SortOrder	m_savedOrder;

	TreeModel(CaptureContext* _context, QObject* _parent = 0);
	~TreeModel();

	QVariant		data(const QModelIndex& _index, int _role) const;
	Qt::ItemFlags	flags(const QModelIndex& _index) const;
	QVariant		headerData(int _section, Qt::Orientation _orientation, int _role = Qt::DisplayRole) const;
	QModelIndex		index(int _row, int _column, const QModelIndex& _parent = QModelIndex()) const;
	QModelIndex		parent(const QModelIndex& _index) const;
	int				rowCount(const QModelIndex& _parent = QModelIndex()) const;
	int				columnCount(const QModelIndex& _parent = QModelIndex()) const;
    void			sort(int _column, Qt::SortOrder _order);
	void			updateData();

private:
	void setupModelData(const rtm::StackTraceTree& _tree, TreeItem* _parent,const rtm::StackTraceTree* _root, int _depth);
};

class ProgressBarDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	ProgressBarDelegate(QWidget* _parent = 0) : 
		QStyledItemDelegate(_parent)
	{}

	void	paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
	QSize	sizeHint(const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
};

class StackTreeWidget : public QWidget
{
	Q_OBJECT

	std::vector<rtm::StackTrace*>	m_stackTraces;
	bool							m_headerStateRestored;
	CaptureContext*					m_context;
	QTreeView*						m_tree;
	bool							m_enableFiltering;

	int								m_savedColumn;
	Qt::SortOrder					m_savedOrder;
	QString							m_settingsGroupName;

public:
	StackTreeWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);
	virtual ~StackTreeWidget();

	void changeEvent(QEvent* _event);
	void loadState(QSettings& _settings, const QString& _name, bool _resetGeometry);
	void saveState(QSettings& _settings);
	void setContext(CaptureContext* _context);
	void setFilteringState(bool _state);
	bool getFilteringState() const;
	void setupTree();

public Q_SLOTS:
	void rowClicked(const QModelIndex&);

Q_SIGNALS:
	void setStackTrace(rtm::StackTrace**, int);

private:
	Ui::stackTree ui;
};

#endif // RTM_MTUNER_STACKTREEWIDGET_H
