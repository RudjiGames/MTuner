//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/moduleswidget.h>
#include <MTuner/src/capturecontext.h>

ModulesWidget::ModulesWidget(QWidget* _parent, Qt::WindowFlags _flags)
	: QWidget(_parent, _flags)
	, m_currentItem(0)
	, m_currentInfo(0)
{
	ui.setupUi(this);
	
	m_filter	= findChild<QLineEdit*>("lineEdit");
	connect(m_filter, SIGNAL(textChanged(const QString&)), this, SLOT(filterChanged(const QString&)));

	m_list		= findChild<QTreeWidget*>("treeWidget");
	connect(m_list, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
}

void ModulesWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void ModulesWidget::setContext(CaptureContext* _context)
{
	if (m_context == _context)
		return;

	m_context = _context;
	filterChanged(QString());
}

void ModulesWidget::itemClicked(QTreeWidgetItem* _currentItem, int _column)
{
	RTM_UNUSED(_column);
	if (!_currentItem)
		return;

	m_list->setFocus();

	if (m_currentItem == _currentItem)
	{
		m_currentItem = 0;
		m_currentInfo = 0;
		m_list->setCurrentItem(0);
		emit moduleSelected(0);
	}
	else
	{
		m_currentItem = _currentItem;
		m_list->setCurrentItem(_currentItem);
		rdebug::ModuleInfo* info = (rdebug::ModuleInfo*)_currentItem->data(0,Qt::UserRole).toLongLong();
		m_currentInfo = info;
		emit moduleSelected(info);
	}
}

void ModulesWidget::filterChanged(const QString& _text)
{
	rdebug::ModuleInfo* info = m_currentInfo;

	if (m_context)
	{
		m_list->clear();
		std::vector<rdebug::ModuleInfo>&	modules = m_context->m_capture->getModuleInfos();
		std::vector<rdebug::ModuleInfo>::reverse_iterator it  = modules.rbegin();
		std::vector<rdebug::ModuleInfo>::reverse_iterator end = modules.rend();

		QLocale locale;
		QTreeWidgetItem* curItem = 0;
		while (it != end)
		{
			QString path = QString::fromUtf8(it->m_modulePath);

			if ((_text.length() == 0) ||
				(path.indexOf(_text, 0, Qt::CaseInsensitive) >= 0))
			{
				QString name = QString::fromUtf8(rtm::pathGetFileName(it->m_modulePath));
				QTreeWidgetItem* item = new QTreeWidgetItem(QStringList()
											<< name
											<< ("0x" + QString::number(it->m_baseAddress, 16))
											<< ("0x" + QString::number(it->m_baseAddress + it->m_size, 16))
											<< locale.toString(it->m_size)
											<< QString::fromUtf8(it->m_modulePath));
				item->setData(0, Qt::UserRole, (qlonglong)&*it);
				item->setTextAlignment(3, Qt::AlignRight);

				if (&*it == info)
					curItem = item;

				m_list->addTopLevelItem(item);
			}
			++it;
		}
		m_filter->setEnabled(true);
		m_list->setCurrentItem(curItem);

		if (_text.length() == 0)
			m_list->setFocus();
	}
	else
	{
		m_list->clear();
		m_filter->setEnabled(false);
	}
}

void ModulesWidget::setCurrentModule(rdebug::ModuleInfo* _module)
{
	QTreeWidgetItemIterator it(m_list);
	while (*it)
	{
		if ((rdebug::ModuleInfo*)(*it)->data(0,Qt::UserRole).toULongLong() == _module)
		{
			(*it)->setSelected(true);
			return;
		}
		++it;
	}
}
