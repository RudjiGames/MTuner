//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <mtuner_pch.h>
#include <mtuner/src/heapswidget.h>
#include <mtuner/src/capturecontext.h>

HeapsWidget::HeapsWidget(QWidget* _parent, Qt::WindowFlags _flags) : 
	QWidget(_parent, _flags)
{
	ui.setupUi(this);
	
	m_treeWidget = findChild<QTreeWidget*>("treeWidget");
	connect(m_treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(ItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

void HeapsWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void HeapsWidget::setContext(CaptureContext* _context)
{
	if (m_context == _context)
		return;

	m_context = _context;

	if (m_context)
	{
		m_treeWidget->clear();
		rtm::Capture::HeapsType& heaps = m_context->m_capture->getHeaps();
		rtm::Capture::HeapsType::iterator it = heaps.begin();
		rtm::Capture::HeapsType::iterator end = heaps.end();

		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList()
									<< ""
									<< QString("All allocators/heaps"));
		item->setFirstColumnSpanned(true);
		item->setData(0, Qt::UserRole, (qlonglong)-1);
		m_treeWidget->addTopLevelItem(item);
		

		while (it != end)
		{
			item = new QTreeWidgetItem(QStringList()
										<< ("0x" + QString::number((qlonglong)it->first,16))
										<< QString(it->second.c_str()));
			item->setData(0, Qt::UserRole, (qlonglong)it->first);
			m_treeWidget->addTopLevelItem(item);
			++it;
		}
	}
	else
		m_treeWidget->clear();
}

void HeapsWidget::ItemChanged(QTreeWidgetItem* _currentItem, QTreeWidgetItem* _item)
{
	RTM_UNUSED(_item);
	if (!_currentItem)
		return;
	uint64_t handle = (uint64_t)_currentItem->data(0,Qt::UserRole).toLongLong();
	emit heapSelected(handle);
}

void HeapsWidget::setCurrentHeap(uint64_t _handle)
{
	QTreeWidgetItemIterator it(m_treeWidget);
	while (*it)
	{
		if ((*it)->data(0,Qt::UserRole).toULongLong() == _handle)
		{
			(*it)->setSelected(true);
			return;
		}
		++it;
	}
}
