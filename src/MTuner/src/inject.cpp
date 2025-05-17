//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/inject.h>

Inject::Inject(QWidget* _parent, Qt::WindowFlags _flags)
	: QDialog(_parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
	RTM_UNUSED(_flags);
	ui.setupUi(this);
	ui.capture->setEnabled(false);
	ui.capture->setChecked(true);
}

void Inject::changeEvent(QEvent* _event)
{
	QDialog::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

bool Inject::loadAfterCapture()
{
	return (ui.capture->isEnabled() || (ui.allocatorCombo->currentIndex() == 0)) && ui.capture->isChecked() && ui.loadAfterCapture->isChecked();
}

void Inject::capture(bool _shouldCapture)
{
	ui.loadAfterCapture->setEnabled(_shouldCapture);
}

void Inject::allocatorChanged(int _index)
{
	ui.capture->setEnabled(_index > 0);
	if (_index == 0)
	{
		ui.capture->setChecked(true);
		ui.loadAfterCapture->setEnabled(true);
	}
}
