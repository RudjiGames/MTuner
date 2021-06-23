//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_ENVVAR_H
#define RTM_MTUNER_ENVVAR_H

#include <MTuner/.qt/qt_ui/env_var_ui.h>

class EnvVar : public QDialog
{
	Q_OBJECT

	QString m_key;
	QString m_val;

public:
	EnvVar(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);

	void set(const QString& _key, const QString& _value);
	void get(QString& _key, QString& _value);

public Q_SLOTS:
	void keyChanged();
	void reject();

private:
	Ui::env ui;
};

#endif // RTM_MTUNER_ENVVAR_H
