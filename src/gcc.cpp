//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/gcc.h>
#include <rbase/inc/winchar.h>

GCCSetup::GCCSetup(QWidget* _parent, Qt::WindowFlags _flags) :
	QDialog(_parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
	RTM_UNUSED(_flags);

	ui.setupUi(this);

	m_currentToolchain = 0;

	m_toolchainCombo = findChild<QComboBox*>("toolchainCombo");

	m_ToolchainNameLabel = findChild<QLabel*>("labelToolchainName");
	m_ToolchainNameEdit = findChild<QLineEdit*>("lineEditToolchainName");
	m_ToolchainNameLabel->hide();
	m_ToolchainNameEdit->hide();

	m_group32		= findChild<QGroupBox*>("groupBox32");
	m_group64		= findChild<QGroupBox*>("groupBox64");
	m_groupProDGps3	= findChild<QGroupBox*>("groupBoxProDGps3");
	m_groupProDGps3->hide();

	m_leditEnv32			= findChild<QLineEdit*>("lineEditEnv32");
	m_leditBinutils32		= findChild<QLineEdit*>("lineEditBinutils32");
	m_leditPrefix32			= findChild<QLineEdit*>("lineEditPrefix32");

	m_leditEnv64			= findChild<QLineEdit*>("lineEditEnv64");
	m_leditBinutils64		= findChild<QLineEdit*>("lineEditBinutils64");
	m_leditPrefix64			= findChild<QLineEdit*>("lineEditPrefix64");

	m_leditEnvProDGps3		= findChild<QLineEdit*>("lineEditEnvProDGps3");
	m_leditBinutilsProDgps3	= findChild<QLineEdit*>("lineEditBinutilsProDGps3");

	m_labelOk64				= findChild<QLabel*>("isOkLabel64");
	m_labelOk32				= findChild<QLabel*>("isOkLabel32");
	m_labelOkProDGps3		= findChild<QLabel*>("isOkLabelProDGps3");

	m_labelFound64			= findChild<QLabel*>("labelFound64");
	m_labelFound32			= findChild<QLabel*>("labelFound32");
	m_labelFoundProDGps3	= findChild<QLabel*>("labelFoundProDGps3");

	m_toolchainCombo->setIconSize(QSize(m_toolchainCombo->size().width(), m_toolchainCombo->iconSize().height()));
}

void GCCSetup::changeEvent(QEvent* _event)
{
	QDialog::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

int GCCSetup::exec()
{
	toolchainSelected(m_currentToolchain);
	// fix combo box names
	for (int i=0; i<m_toolchains.length(); ++i)
	{
		if (m_toolchains[i].m_toolchain >= rmem::ToolChain::Custom1)
			m_toolchainCombo->setItemText(i, m_toolchains[i].m_name);
	}
	return QDialog::exec();
}

void GCCSetup::readSettings(QSettings& _settings)
{
	setupDefaultTC(m_toolchains);
	if (_settings.childGroups().contains("GCCToolchains_3"))
	{
		_settings.beginGroup("GCCToolchains_3");
		int size = _settings.beginReadArray("GCCToolchainsArray");
		for (int i=0; i<size; ++i)
		{
			_settings.setArrayIndex(i);

			Toolchain tc;
			tc.m_toolchain	= (rmem::ToolChain::Enum)_settings.value("tcToolchain").toInt();

			for (int j=0; j<m_toolchains.size(); ++j)
			if (tc.m_toolchain == m_toolchains[j].m_toolchain)
			{
				m_toolchains[j].m_name				= _settings.value("tcName").toString();
				m_toolchains[j].m_Environment32		= _settings.value("tcEnv32").toString();
				m_toolchains[j].m_ToolchainPath32	= _settings.value("tcPath32").toString();
				m_toolchains[j].m_ToolchainPrefix32	= _settings.value("tcPrefix32").toString();
				m_toolchains[j].m_Environment64		= _settings.value("tcEnv64").toString();
				m_toolchains[j].m_ToolchainPath64	= _settings.value("tcPath64").toString();
				m_toolchains[j].m_ToolchainPrefix64	= _settings.value("tcPrefix64").toString();
				break;
			}
		}
		_settings.endArray();
		_settings.endGroup();
	}
}

void  GCCSetup::writeSettings(QSettings& _settings)
{
	_settings.beginGroup("GCCToolchains_3");
	_settings.beginWriteArray("GCCToolchainsArray", m_toolchains.length());
	for (int i=0; i<m_toolchains.length(); ++i)
	{
		_settings.setArrayIndex(i);

		Toolchain& tc = m_toolchains[i];
		_settings.setValue("tcName", tc.m_name);
		_settings.setValue("tcEnv32", tc.m_Environment32);
		_settings.setValue("tcPath32", tc.m_ToolchainPath32);
		_settings.setValue("tcPrefix32", tc.m_ToolchainPrefix32);
		_settings.setValue("tcEnv64", tc.m_Environment64);
		_settings.setValue("tcPath64", tc.m_ToolchainPath64);
		_settings.setValue("tcPrefix64", tc.m_ToolchainPrefix64);
		_settings.setValue("tcToolchain", (int)tc.m_toolchain);
	}
	_settings.endArray();
	_settings.endGroup();
}

bool GCCSetup::isConfigured(rmem::ToolChain::Enum _toolchain, bool _64bit)
{
	rdebug::Toolchain tc = getToolchainInfo(_toolchain,_64bit);
	if (strcmp(tc.m_toolchainPath, "") == 0)
	{
		if (tc.m_type != rdebug::Toolchain::MSVC)
			return false;
	}
	return true;
}

rdebug::Toolchain GCCSetup::getToolchainInfo(rmem::ToolChain::Enum _toolchain, bool _64bit)
{
	// special case ProDG for PS3
	if ((_toolchain == rmem::ToolChain::PS3_gcc) ||
		(_toolchain == rmem::ToolChain::PS4_clang))
		_64bit = true;

	if (_toolchain == rmem::ToolChain::PS3_snc)
		_toolchain = rmem::ToolChain::PS3_gcc;

	rdebug::Toolchain tc;
	for (int i=0; i<m_toolchains.length(); ++i)
	{
		if (m_toolchains[i].m_toolchain == _toolchain)
		{
			resolveToolchain(m_toolchains[i], _64bit, tc);
			break;
		}
	}

	return tc;
}

rdebug::Toolchain::Type getTCType(rmem::ToolChain::Enum _toolchain)
{
	switch (_toolchain)
	{
		case rmem::ToolChain::Win_MSVC: return rdebug::Toolchain::MSVC;
		case rmem::ToolChain::PS3_snc:	return rdebug::Toolchain::PS3SNC;
		default:						return rdebug::Toolchain::GCC;
	};
}

bool GCCSetup::resolveToolchain(Toolchain& _toolchain, bool _64bit, rdebug::Toolchain& _tc)
{
	QString append1 = "nm";
	QString append2 = "addr2line";
	QString append3 = "c++filt";

	if ((_toolchain.m_toolchain == rmem::ToolChain::PS3_gcc) && (_64bit == false))
	{
		append1 = "ps3bin";
		append2 = "ps3bin";
		append3 = "ps3name";
	}

#if RTM_PLATFORM_WINDOWS
	append1 += ".exe";
	append2 += ".exe";
	append3 += ".exe";
#endif

	QString envVar = _64bit ? _toolchain.m_Environment64 : _toolchain.m_Environment32;
	QString tcPath = _64bit ? _toolchain.m_ToolchainPath64 : _toolchain.m_ToolchainPath32;
	QString prefix = _64bit ? _toolchain.m_ToolchainPrefix64 : _toolchain.m_ToolchainPrefix32;

	// try to match absolute path + prefix + postfix
	QString basePath = tcPath + "/";

	QString fullPath = basePath + prefix;

	fullPath = fullPath.replace("//","/");
	fullPath = fullPath.replace("\\","/");
	if ((QFileInfo(fullPath + append1).exists()) &&
		(QFileInfo(fullPath + append2).exists()) &&
		(QFileInfo(fullPath + append3).exists()))
	{
#if 0
		rtm::WideToMulti tcPathM((wchar_t*)fullPath.utf16());
		rtm::WideToMulti tcPrefM((wchar_t*)prefix.utf16());

		_tc.m_toolchainPath		= tcPathM.m_ptr;
		_tc.m_toolchainPrefix	= tcPrefM.m_ptr;
#else
		_tc.m_toolchainPath		= stringDup(fullPath.toUtf8());
		_tc.m_toolchainPrefix	= stringDup(prefix.toUtf8());
#endif
		_tc.m_type				= getTCType(_toolchain.m_toolchain);
		return true;
	}

	// try to match environment variable + relative path + postfix
	if (envVar.length())
	{
		std::wstring env = (wchar_t*)envVar.utf16();
#if RTM_PLATFORM_WINDOWS
		wchar_t* envData = _wgetenv(env.c_str());
		basePath = QString::fromUtf16((const ushort*)envData) + "/";
#else
		const char *const envData = getenv(env.c_str());
		basePath = QString::fromUtf8(envData) + "/";
#endif
		basePath += tcPath + "/";
		fullPath = basePath + prefix;

		fullPath = fullPath.replace("//","/");
		fullPath = fullPath.replace("\\","/");

		if ((QFileInfo(fullPath + append1).exists()) &&
			(QFileInfo(fullPath + append2).exists()) &&
			(QFileInfo(fullPath + append3).exists()))
		{
#if 0
			rtm::WideToMulti tcPathM((wchar_t*)basePath.utf16());
			rtm::WideToMulti tcPrefM((wchar_t*)prefix.utf16());

			_tc.m_toolchainPath		= tcPathM.m_ptr;
			_tc.m_toolchainPrefix	= tcPrefM.m_ptr;
#else
			_tc.m_toolchainPath		= stringDup(basePath.toUtf8());
			_tc.m_toolchainPrefix	= stringDup(prefix.toUtf8());
#endif
			_tc.m_type				= getTCType(_toolchain.m_toolchain);
			return true;
		}
	}

	// not found
	return false;
}

void GCCSetup::setupDefaultTC(QVector<Toolchain>& _toolchains)
{
	Toolchain minGW;
	minGW.m_name				= "MinGW";
	minGW.m_Environment32		= "MINGW";
	minGW.m_ToolchainPath32		= "";
	minGW.m_ToolchainPrefix32	= "";
	minGW.m_Environment64		= "MINGW64";
	minGW.m_ToolchainPath64		= "";
	minGW.m_ToolchainPrefix64	= "";
	minGW.m_toolchain			= rmem::ToolChain::Win_gcc;

	Toolchain ps3gcc;
	ps3gcc.m_name				= "PlayStation 3";
	ps3gcc.m_Environment32		= "SCE_PS3_ROOT";
	ps3gcc.m_ToolchainPath32	= "/host-win32/sn/bin/";
	ps3gcc.m_ToolchainPrefix32	= "";
	ps3gcc.m_Environment64		= "SCE_PS3_ROOT";
	ps3gcc.m_ToolchainPath64	= "/host-win32/ppu/bin/";
	ps3gcc.m_ToolchainPrefix64	= "ppu-lv2-";
	ps3gcc.m_toolchain			= rmem::ToolChain::PS3_gcc;

	Toolchain ps4clang;
	ps4clang.m_name				= "PlayStation 4";
	ps4clang.m_Environment32	= "SCE_ORBIS_SDK_DIR";
	ps4clang.m_ToolchainPath32	= "/host_tools/bin/";
	ps4clang.m_ToolchainPrefix32= "";
	ps4clang.m_Environment64	= "SCE_ORBIS_SDK_DIR";
	ps4clang.m_ToolchainPath64	= "/host_tools/bin/";
	ps4clang.m_ToolchainPrefix64= "orbis-";
	ps4clang.m_toolchain		= rmem::ToolChain::PS4_clang;

	_toolchains.append(minGW);
	_toolchains.append(ps3gcc);
	_toolchains.append(ps4clang);

	for (int i=0; i<9; ++i)
	{
		rmem::ToolChain::Enum tc = (rmem::ToolChain::Enum)(rmem::ToolChain::Custom1 + i);
		Toolchain ctc;
		ctc.m_name				= "Custom Toolchain " + QString::number(i+1);
		ctc.m_Environment32		= "";
		ctc.m_ToolchainPath32	= "";
		ctc.m_Environment64		= "";
		ctc.m_ToolchainPath64	= "";
		ctc.m_toolchain			= tc;

		_toolchains.append(ctc);
	}
}

void GCCSetup::toolchainSelected(int _index)
{
	m_currentToolchain = _index;
	if (m_toolchains[_index].m_toolchain >= rmem::ToolChain::Custom1)
	{
		m_ToolchainNameLabel->show();
		m_ToolchainNameEdit->show();
	}
	else
	{
		m_ToolchainNameLabel->hide();
		m_ToolchainNameEdit->hide();
	}

	if (m_toolchains[_index].m_toolchain == rmem::ToolChain::PS3_gcc)
	{
		m_group32->hide();
		m_groupProDGps3->show();
	}
	else
	{
		m_group32->show();
		m_groupProDGps3->hide();
	}


	if (m_toolchains[_index].m_toolchain == rmem::ToolChain::PS4_clang)
		m_group32->setEnabled(false);
	else
		m_group32->setEnabled(true);


	Toolchain& tc = m_toolchains[m_currentToolchain];

	m_ToolchainNameEdit->setText(tc.m_name);
	m_leditEnv32->setText(tc.m_Environment32);
	m_leditBinutils32->setText(tc.m_ToolchainPath32);
	m_leditPrefix32->setText(tc.m_ToolchainPrefix32);

	// special case - ProDG ps3
	m_leditEnvProDGps3->setText(tc.m_Environment32);
	m_leditBinutilsProDgps3->setText(tc.m_ToolchainPath32);

	m_leditEnv64->setText(tc.m_Environment64);
	m_leditBinutils64->setText(tc.m_ToolchainPath64);
	m_leditPrefix64->setText(tc.m_ToolchainPrefix64);

	setLabels();
}

void GCCSetup::toolchainRenamed(QString _text)
{
	m_toolchains[m_currentToolchain].m_name = _text;
	if (m_toolchains[m_currentToolchain].m_toolchain >= rmem::ToolChain::Custom1)
		m_toolchainCombo->setItemText(m_currentToolchain, _text);
}

void GCCSetup::envEdited32(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_Environment32 = _text;
	setLabels();
}

void GCCSetup::pathEdited32(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_ToolchainPath32 = _text;
	setLabels();
}

void GCCSetup::pathBrowse32()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select folder with binutils"));
	if (path.length()>0)
		m_leditBinutils32->setText(path);
}

void GCCSetup::prefixEdited32(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_ToolchainPrefix32 = _text;
	setLabels();
}

void GCCSetup::envEdited64(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_Environment64 = _text;
	setLabels();
}

void GCCSetup::pathEdited64(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_ToolchainPath64 = _text;
	setLabels();
}

void GCCSetup::pathBrowse64()
{
	QString caption = tr("Select folder with binutils");
	Toolchain& tc = m_toolchains[m_currentToolchain];
	if (tc.m_toolchain == rmem::ToolChain::PS4_clang)
		caption = tr("Select folder with orbis-bin.exe");

	QString path = QFileDialog::getExistingDirectory(this, caption);
	if (path.length()>0)
		m_leditBinutils64->setText(path);
}

void GCCSetup::prefixEdited64(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_ToolchainPrefix64 = _text;
	setLabels();
}

void GCCSetup::envEditedProDGps3(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_Environment32 = _text;
	setLabels();
}

void GCCSetup::pathEditedProDGps3(QString _text)
{
	Toolchain& tc = m_toolchains[m_currentToolchain];
	tc.m_ToolchainPath32 = _text;
	setLabels();
}

void GCCSetup::pathBrowseProDGps3()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select folder with ps3bin.exe"));
	if (path.length()>0)
		m_leditBinutilsProDgps3->setText(path);
}

void GCCSetup::setLabels()
{
	const QString ok = "<html><head/><body><p><img src=\":/MTuner/resources/images/ok.png\"/></p></body></html>";
	const QString notok = "<html><head/><body><p><img src=\":/MTuner/resources/images/notok.png\"/></p></body></html>";

	Toolchain& tc = m_toolchains[m_currentToolchain];

	rmem::ToolChain::Enum tc32 = tc.m_toolchain;
	if (tc.m_toolchain == rmem::ToolChain::PS3_gcc)
		tc32 = rmem::ToolChain::PS3_snc;

	bool config64 = isConfigured( tc.m_toolchain, true );
	bool config32 = isConfigured( tc32, false );

	m_labelOk64->setText( config64 ? ok : notok );
	m_labelOk32->setText( config32 ? ok : notok );
	m_labelOkProDGps3->setText( config32 ? ok : notok );

	if (tc.m_toolchain == rmem::ToolChain::PS4_clang)
	{
		m_labelFound64->setText( config64 ? tr("orbis tools found!") : tr("orbis tools not found!") );
		m_labelFound32->setText( config32 ? tr("orbis tools found!") : tr("orbis tools not found!") );
	}
	else
	{
		m_labelFound64->setText( config64 ? tr("toolchain found!") : tr("toolchain not found!") );
		m_labelFound32->setText( config32 ? tr("toolchain found!") : tr("toolchain not found!") );
	}

	m_labelFoundProDGps3->setText( config32 ? tr("ps3 tools found!") : tr("ps3 tools not found!") );
}
