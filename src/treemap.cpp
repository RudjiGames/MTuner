//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/treemap.h>

TreeMapWidget::TreeMapWidget(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);
	m_graphicsView		= findChild<TreeMapView*>("graphicsView");
	m_context			= NULL;
	m_map				= NULL;

	QComboBox* cb = findChild<QComboBox*>("comboBoxType");
	connect(cb, SIGNAL(currentIndexChanged(int)), this, SLOT(treeMapTypeChanged(int)));

	m_scene = new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    m_graphicsView->setScene(m_scene);
    m_graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_graphicsView->scale(qreal(1.0), qreal(1.0));
	connect(m_graphicsView, SIGNAL(setStackTrace(rtm::StackTrace**,int)), this, SIGNAL(setStackTrace(rtm::StackTrace**,int)));
}

void TreeMapWidget::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void TreeMapWidget::setContext(CaptureContext* _context)
{
	m_context = _context;
	m_graphicsView->setContext(_context);
	m_map = new TreeMapGraphicsItem(m_graphicsView, _context);
	m_scene->addItem(m_map);
}

void TreeMapWidget::setFilteringState(bool _state)
{
	RTM_UNUSED(_state);
	m_graphicsView->setMapType(m_graphicsView->getMapType());
}

void TreeMapWidget::treeMapTypeChanged(int _type)
{
	m_graphicsView->setMapType(_type);
}
