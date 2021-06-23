//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_GCC_H
#define RTM_MTUNER_GCC_H

#include <MTuner/.qt/qt_ui/gcc_ui.h>

struct Toolchain
{
	QString	m_name;
	QString	m_Environment32;
	QString	m_ToolchainPath32;
	QString	m_ToolchainPrefix32;
	QString	m_Environment64;
	QString	m_ToolchainPath64;
	QString	m_ToolchainPrefix64;
	rmem::ToolChain::Enum m_toolchain;
};

class GCCSetup : public QDialog
{
	Q_OBJECT

	QComboBox*			m_toolchainCombo;
	QLabel*				m_ToolchainNameLabel;
	QLineEdit*			m_ToolchainNameEdit;
	QVector<Toolchain>	m_toolchains;

	QGroupBox*			m_group32;
	QGroupBox*			m_group64;
	QGroupBox*			m_groupProDGps3;

	QLineEdit*			m_leditEnv32;
	QLineEdit*			m_leditBinutils32;
	QLineEdit*			m_leditPrefix32;

	QLineEdit*			m_leditEnv64;
	QLineEdit*			m_leditBinutils64;
	QLineEdit*			m_leditPrefix64;

	QLineEdit*			m_leditEnvProDGps3;
	QLineEdit*			m_leditBinutilsProDgps3;

	int					m_currentToolchain;

	QLabel*				m_labelOk64;
	QLabel*				m_labelOk32;
	QLabel*				m_labelOkProDGps3;

	QLabel*				m_labelFound64;
	QLabel*				m_labelFound32;
	QLabel*				m_labelFoundProDGps3;

public:
	GCCSetup(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void	changeEvent(QEvent* _event);
	int		exec();
	void	readSettings(QSettings& _settings);
	void	writeSettings(QSettings& _settings);
	bool	isConfigured(rmem::ToolChain::Enum _toolchain, bool _64bit);
	void	setupDefaultTC(QVector<Toolchain>& _toolchains);
	int		getNumToolchains() const { return m_toolchains.length(); }
	const Toolchain& getToolchain(int _index) const { return m_toolchains[_index]; }
	rdebug::Toolchain getToolchainInfo(rmem::ToolChain::Enum _toolchain, bool _64bit);

public Q_SLOTS:
	void toolchainSelected(int _index);
	void toolchainRenamed(QString);
	void envEdited32(QString);
	void pathEdited32(QString);
	void pathBrowse32();
	void prefixEdited32(QString);
	void envEdited64(QString);
	void pathEdited64(QString);
	void pathBrowse64();
	void prefixEdited64(QString);
	void envEditedProDGps3(QString);
	void pathEditedProDGps3(QString);
	void pathBrowseProDGps3();

private:
	bool resolveToolchain(Toolchain& _toolchain, bool _64bit, rdebug::Toolchain& _tc);
	void setLabels();

	Ui::GCCSetup ui;
};

#endif // RTM_MTUNER_GCC_H
