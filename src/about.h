//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_ABOUT_H__
#define __RTM_MTUNER_ABOUT_H__

#include <mtuner/.qt/qt_ui/about_ui.h>

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);
	void changeEvent(QEvent* _event);

private:
	Ui::About ui;
};

#endif // __RTM_MTUNER_ABOUT_H__
