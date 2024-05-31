//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/environment.h>
#include <MTuner/src/env_var.h>

Environment::Environment(QWidget* _parent, Qt::WindowFlags _flags)
	: QDialog(_parent, _flags)
{
	ui.setupUi(this);
}

void Environment::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void Environment::setEnvironment(QStringList _env)
{
	m_environment = _env;
	ui.tableWidget->setRowCount(_env.size());
	int row = 0;
	Q_FOREACH(QString e, _env)
	{
		int eq = e.indexOf("=");
		QString variable	= e.left(eq);
		QString value		= e.right(e.size() - eq - 1);

		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(variable));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(value));
		++row;
	}
}

QStringList Environment::getEnvironment()
{
	QStringList ret;

	int numRows = ui.tableWidget->rowCount();
	for (int i=0; i<numRows; ++i)
	{
		QString key = ui.tableWidget->item(i, 0)->text();
		QString val = ui.tableWidget->item(i, 1)->text();
		ret << key + QString("=") + val;
	}

	return ret;
}

void Environment::newVar()
{
	EnvVar varEdit;
	varEdit.set("", "");
	int ret = varEdit.exec();

	if (ret == QDialog::Rejected)
		return;

	QString key, var;
	varEdit.get(key, var);

	int numRows = ui.tableWidget->rowCount();
	ui.tableWidget->setRowCount(numRows + 1);
	ui.tableWidget->setItem(numRows, 0, new QTableWidgetItem(key));
	ui.tableWidget->setItem(numRows, 1, new QTableWidgetItem(var));
}

void Environment::editVar()
{
	int currentRow = ui.tableWidget->currentIndex().row();
	if (currentRow == -1)
		return;

	QString key = ui.tableWidget->item(currentRow, 0)->text();
	QString val = ui.tableWidget->item(currentRow, 1)->text();

	EnvVar varEdit;
	varEdit.set(key, val);
	int ret = varEdit.exec();

	if (ret == QDialog::Rejected)
		return;

	varEdit.get(key, val);
	ui.tableWidget->setItem(currentRow, 0, new QTableWidgetItem(key));
	ui.tableWidget->setItem(currentRow, 1, new QTableWidgetItem(val));
}

void Environment::deleteVar()
{
	int currentRow = ui.tableWidget->currentIndex().row();
	if (currentRow == -1)
		return;

	ui.tableWidget->removeRow(currentRow);
}

void Environment::accept()
{
	m_environment = getEnvironment();
	QDialog::accept();
}

void Environment::reject()
{
	setEnvironment(m_environment);
	QDialog::reject();
}
