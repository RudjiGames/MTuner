//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_STARTPAGEWIDGET_H__
#define __RTM_MTUNER_STARTPAGEWIDGET_H__

#include <mtuner/.qt/qt_ui/startpage_ui.h>

class StartPageWidget : public QWidget
{
	Q_OBJECT

public:
	StartPageWidget(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void changeEvent(QEvent* _event);

private:
	Ui::StartPageWidget ui;
};

#endif // __RTM_MTUNER_STARTPAGEWIDGET_H__
