//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/env_var.h>

EnvVar::EnvVar(QWidget* _parent, Qt::WindowFlags _flags)
	: QDialog(_parent, _flags)
{
	ui.setupUi(this);
}

void EnvVar::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void EnvVar::set(const QString& _key, const QString& _val)
{
	m_key = _key;
	m_val = _val;

	ui.key->setText(_key);
	ui.val->setText(_val);
	ui.buttonOK->setEnabled(_key.size() != 0);
}

void EnvVar::get(QString& _key, QString& _val)
{
	_key = ui.key->text();
	_val = ui.val->text();
}

void EnvVar::keyChanged()
{
	ui.buttonOK->setEnabled(ui.key->text().size() != 0);
}

void EnvVar::reject()
{
	ui.key->setText(m_key);
	ui.val->setText(m_val);

	QDialog::reject();
}
