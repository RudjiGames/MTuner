//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <mtuner_pch.h>
#include <mtuner/src/about.h>
#include <mtuner/src/version.h>

AboutDialog::AboutDialog(QWidget* _parent, Qt::WindowFlags _flags) :
	QDialog(_parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
	RTM_UNUSED(_flags);
	ui.setupUi(this);
	QLabel* version = findChild<QLabel*>("labelVersion");
	version->setText(tr("Version") + " " + MTunerVersion);
}

void AboutDialog::changeEvent(QEvent* _event)
{
	QDialog::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}
