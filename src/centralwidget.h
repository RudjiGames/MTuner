//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_CENTRALWIDGET_H
#define RTM_MTUNER_CENTRALWIDGET_H

#include <MTuner/.qt/qt_ui/centralwidget_ui.h>

class StackTrace;
class SourceView;
class BinLoaderView;
struct CaptureContext;

class CentralWidget : public QWidget
{
	Q_OBJECT

	QTabWidget*	m_tabWidget;

public:
	CentralWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void changeEvent(QEvent* _event);
	void addTab(CaptureContext* _context, const QString& _name);
	void removeCurrentTab();
	void toggleFilteringForCurrentView(bool _state);
	BinLoaderView* getCurrentView();

Q_SIGNALS:
	void contextChanged(CaptureContext* _view);
	void changeWindowTitle(const QString&);
	void setStackTrace(rtm::StackTrace**, int);
	void setFilteringEnabled(bool, bool);

public Q_SLOTS:
	void tabSelectionChanged(int _tabIndex);
	void tabClose(int _index);
	void updateFilterDataIfNeeded();

private:
	Ui::CentralWidget ui;
};

#endif // RTM_MTUNER_CENTRALWIDGET_H
