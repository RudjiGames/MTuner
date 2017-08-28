//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/centralwidget.h>
#include <MTuner/src/startpage.h>
#include <MTuner/src/binloaderview.h>
#include <MTuner/src/capturecontext.h>

CentralWidget::CentralWidget(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);

	m_tabWidget = findChild<QTabWidget*>("tabWidget");
	m_tabWidget->addTab(new StartPageWidget(), QObject::tr("Start Page"));

	connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelectionChanged(int)));
	connect(m_tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabClose(int)));
}

void CentralWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	switch (_event->type())
	{
		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			for (int i=0; i<m_tabWidget->count(); ++i)
			{
				StartPageWidget* pg = qobject_cast<StartPageWidget*>(m_tabWidget->widget(i));
				if (pg)
				{
					m_tabWidget->setTabText(i,QObject::tr("Start Page"));
					break;
				}
			}
			break;
		// This silences warnings from the compiler about unhandled cases
		default:
			break;
	};
}

void CentralWidget::addTab(CaptureContext* _context, const QString& _name)
{
	BinLoaderView* view = new BinLoaderView;
	connect(view, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SIGNAL(setStackTrace(rtm::StackTrace**,int)));

	_context->m_binLoaderView = view;
	view->setContext(_context);
	m_tabWidget->addTab(view,_name);
	m_tabWidget->setCurrentIndex(m_tabWidget->count()-1);
	emit contextChanged(_context);
}

void CentralWidget::removeCurrentTab()
{
	m_tabWidget->removeTab(m_tabWidget->currentIndex());
	emit contextChanged(NULL);
}

BinLoaderView* CentralWidget::getCurrentView()
{
	int index = m_tabWidget->currentIndex();
	QWidget* widget = m_tabWidget->widget(index);
	BinLoaderView* view = qobject_cast<BinLoaderView*>(widget);
	return view;
}

void CentralWidget::toggleFilteringForCurrentView(bool _state)
{
	BinLoaderView* view = getCurrentView();
	if (view)
		view->setFilteringEnabled(_state);
}

void CentralWidget::tabSelectionChanged(int _tabIndex)
{
	QWidget* widget = m_tabWidget->widget(_tabIndex);
	BinLoaderView* view = qobject_cast<BinLoaderView*>(widget);

	QString title = "MTuner";
	if (view)
		title += " - " + m_tabWidget->tabText(_tabIndex);

	emit changeWindowTitle(title);
	emit contextChanged(view ? view->getContext() : NULL);

	if (view)
	{
		emit setStackTrace(view->getSavedStackTraces(), view->getSavedStackTracesCount());
		emit setFilteringEnabled(view->getFilteringEnabled(),true);
	}
	else
	{
		emit setStackTrace(NULL, 0);
		emit setFilteringEnabled(false,false);
	}
}

void CentralWidget::tabClose(int _tabIndex)
{
	QWidget* widget = m_tabWidget->widget(_tabIndex);
	m_tabWidget->removeTab(_tabIndex);
	delete widget;
}

void CentralWidget::updateFilterDataIfNeeded()
{
	BinLoaderView* view = getCurrentView();
	if (!view)
		return;

	CaptureContext* ctx = view->getContext();
	if (!ctx->m_capture->getFilteringEnabled())
		return;

	toggleFilteringForCurrentView(true);
}
