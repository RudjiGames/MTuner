//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_STARTPAGEWIDGET_H
#define RTM_MTUNER_STARTPAGEWIDGET_H

#include <MTuner/.qt/qt_ui/startpage_ui.h>

class StartPageWidget : public QWidget
{
	Q_OBJECT

public:
	StartPageWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);

private:
	Ui::StartPageWidget ui;
};

#endif // RTM_MTUNER_STARTPAGEWIDGET_H
