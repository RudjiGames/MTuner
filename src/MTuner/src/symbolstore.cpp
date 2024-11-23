//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/symbolstore.h>

#if RTM_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

SymbolStore::SymbolStore(QWidget* _parent, Qt::WindowFlags _flags)
	: QDialog(_parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
	RTM_UNUSED(_flags);
	ui.setupUi(this);

	m_publicStore	= findChild<QLineEdit*>("textPublicStore");
	m_localStore	= findChild<QLineEdit*>("textLocalStore");
	m_srcRegistry	= findChild<QCheckBox*>("checkRegistry");
	m_buttonDefault	= findChild<QToolButton*>("buttonDefault");
	m_buttonBrowse	= findChild<QToolButton*>("buttonBrowse");

	m_srcRegistry->setChecked(false);

#if RTM_PLATFORM_WINDOWS
	char buffer[2048];
	if (GetEnvironmentVariable("_NT_SYMBOL_PATH", (LPSTR)buffer, sizeof(buffer)))
	{
		m_hasRegistryEntry = true;
		m_srcRegistry->setEnabled(true);
	}
	else
	{
		m_hasRegistryEntry = false;
		m_srcRegistry->setEnabled(false);
	}
#else
	m_srcRegistry->setEnabled(false);
#endif
}

void SymbolStore::changeEvent(QEvent* _event)
{
	QDialog::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

QString	SymbolStore::getSymbolStoreString() const
{
	QString ret("");

	if (m_srcRegistry->isChecked())
	{
#if RTM_PLATFORM_WINDOWS
		wchar_t buffer[2048];
		GetEnvironmentVariableW(L"_NT_SYMBOL_PATH", (LPWSTR)buffer, sizeof(buffer));
		ret = QString::fromWCharArray(buffer);
#endif
	}

	// http server need a local cache folder to store the symbol
	if (m_publicStore->text().contains(QRegularExpression("https?://")))
	{
		if (ret.length())
			ret = ret + QString(";");

		ret = ret + QString("SRV*");
		if (!m_localStore->text().isEmpty())
		{
			ret = ret + m_localStore->text();
		}
		else
			ret = ret + QDir::toNativeSeparators(QDir::temp().absoluteFilePath("symbolcache"));

		ret = ret + QString("*");
		ret = ret + m_publicStore->text();
	}

	return ret;
}

QString	SymbolStore::getLocalStore() const
{
	return m_localStore->text();
}

void SymbolStore::setLocalStore(const QString& _localStore)
{
	m_localStore->setText(_localStore);
}

QString	SymbolStore::getPublicStore() const
{
	return m_publicStore->text();
}

void SymbolStore::setPublicStore(const QString& _publicStore)
{
	m_publicStore->setText(_publicStore);
}

bool SymbolStore::isRegistryChecked() const
{
	return m_srcRegistry->isChecked();
}

void SymbolStore::setChecked(bool _registry)
{
	if (m_hasRegistryEntry && _registry)
		m_srcRegistry->setChecked(_registry);
}

void SymbolStore::save()
{
	m_restoreRegistryChecked	= m_srcRegistry->isChecked();
	m_restorePublicStore		= m_publicStore->text();
	m_restoreLocalStore			= m_localStore->text();
}

void SymbolStore::selectLocalStore()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("select local symbol store directory"), 
		"", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (!dir.isEmpty())
		m_localStore->setText(QDir::toNativeSeparators(dir));
}

void SymbolStore::defaultSymbolServer()
{
	m_publicStore->setText("https://msdl.microsoft.com/download/symbols");
}

void SymbolStore::visitMSDN()
{
	QDesktopServices::openUrl(QUrl("https://msdn.microsoft.com/en-us/library/ff537994(v=vs.85).aspx", QUrl::TolerantMode));
}

int SymbolStore::exec()
{
	show();
	setFixedHeight(height());
	return QDialog::exec();
}

void SymbolStore::accept()
{
	QDialog::accept();
}

void SymbolStore::reject()
{
	m_srcRegistry->setChecked(m_restoreRegistryChecked);
	m_publicStore->setText(m_restorePublicStore);
	m_localStore->setText(m_restoreLocalStore);
	QDialog::reject();
}
