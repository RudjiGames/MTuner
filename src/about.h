//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_ABOUT_H
#define RTM_MTUNER_ABOUT_H

#include <MTuner/.qt/qt_ui/about_ui.h>

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);
	void changeEvent(QEvent* _event);

private:
	Ui::About ui;
};

#endif // RTM_MTUNER_ABOUT_H
