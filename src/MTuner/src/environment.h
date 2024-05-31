//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_ENVIRONMENT_H
#define RTM_MTUNER_ENVIRONMENT_H

#include <MTuner/.qt/qt_ui/environment_ui.h>

class Environment : public QDialog
{
	Q_OBJECT

	QStringList	m_environment;

public:
	Environment(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void changeEvent(QEvent* _event);

	void		setEnvironment(QStringList _env);
	QStringList	getEnvironment();

public Q_SLOTS:
	void newVar();
	void editVar();
	void deleteVar();
	void accept();
	void reject();

private:
	Ui::Environment ui;
};

#endif // RTM_MTUNER_ENVIRONMENT_H
