//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/mtuner.h>
#include <MTuner/src/welcome.h>

WelcomeDialog::WelcomeDialog(QWidget* _parent, Qt::WindowFlags _flags) :
	QDialog(_parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
	RTM_UNUSED(_flags);
	ui.setupUi(this);

	connect(ui.buttonSymbols,		&QPushButton::clicked, this, &WelcomeDialog::setupSymbols);
	connect(ui.buttonDocumentation,	&QPushButton::clicked, this, &WelcomeDialog::readDocumentation);
}

void WelcomeDialog::changeEvent(QEvent* _event)
{
	QDialog::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

bool WelcomeDialog::shouldShowNextTime() const
{
	return ui.checkBox->isChecked();
}
