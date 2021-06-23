//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_MODULESWIDGET_H
#define RTM_MTUNER_MODULESWIDGET_H

#include <MTuner/.qt/qt_ui/moduleswidget_ui.h>

struct CaptureContext;

class ModulesWidget : public QWidget
{
	Q_OBJECT

private:
	QLineEdit*		m_filter;
	QTreeWidget*	m_list;
	QTreeWidgetItem*m_currentItem;
	CaptureContext*	m_context;
	rdebug::ModuleInfo* m_currentInfo;

public:
	ModulesWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);
	void setContext(CaptureContext* _capture);
	void setCurrentModule(rdebug::ModuleInfo* _module);

public Q_SLOTS:
	void itemClicked(QTreeWidgetItem* _currentItem, int _column);
	void filterChanged(const QString&);

Q_SIGNALS:
	void moduleSelected(void*);

private:
	Ui::ModulesWidget ui;
};

#endif // RTM_MTUNER_MODULESWIDGET_H
