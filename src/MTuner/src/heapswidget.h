//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_HEAPSWIDGET_H
#define RTM_MTUNER_HEAPSWIDGET_H

#include <MTuner/.qt/qt_ui/heapswidget_ui.h>

struct CaptureContext;

class HeapsWidget : public QWidget
{
	Q_OBJECT

private:
	QTreeWidget*	m_treeWidget;
	QTreeWidgetItem*m_currentItem;
	CaptureContext*	m_context;

public:
	HeapsWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);
	void setContext(CaptureContext* _capture);
	void setCurrentHeap(uint64_t _handle);

public Q_SLOTS:
	void selectionChanged();

Q_SIGNALS:
	void heapSelected(uint64_t);

private:
	Ui::HeapsWidget ui;
};

#endif // RTM_MTUNER_HEAPSWIDGET_H
