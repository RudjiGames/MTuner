//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/environment.h>
#include <MTuner/src/projectsmanager.h>

ProjectsManager::ProjectsManager(QWidget* _parent, Qt::WindowFlags _flags)
	: QDialog(_parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
	RTM_UNUSED(_flags);
	setAcceptDrops(true);
	ui.setupUi(this);

	m_txtExecutable		= findChild<QLineEdit*>("txtExecutable");
	m_txtCommandLine	= findChild<QLineEdit*>("txtCommandLine");
	m_txtWorkingDir		= findChild<QLineEdit*>("txtWorkingDir");
	m_listProjects		= findChild<QTreeWidget*>("listOfProjects");

	m_buttonAdd			= findChild<QPushButton*>("buttonAdd");
	m_buttonRemove		= findChild<QPushButton*>("buttonDelete");
	m_buttonRun			= findChild<QPushButton*>("buttonRun");

	m_watcher			= NULL;

	m_buttonAdd->setEnabled(false);
	m_buttonRemove->setEnabled(false);
	m_buttonRun->setEnabled(false);
	ui.editVars->setEnabled(false);
	ui.inherit->setChecked(true);

	connect(m_txtExecutable,SIGNAL(textChanged(const QString&)), this, SLOT(textParamsChanged()));
	connect(m_txtCommandLine,SIGNAL(textChanged(const QString&)), this, SLOT(textParamsChanged()));
	connect(m_txtWorkingDir,SIGNAL(textChanged(const QString&)), this, SLOT(textParamsChanged()));

	connect(m_listProjects, SIGNAL(itemSelectionChanged()), this, SLOT(projectSelectionChanged()));

	connect(this, SIGNAL(rejected()), this, SLOT(restore()));

	m_process			= 0;
	m_processRunning	= false;
}

void ProjectsManager::save()
{
	m_savedProjects			= m_projects;
	m_projectListModified	= false;
}

void ProjectsManager::changeEvent(QEvent* _event)
{
	QDialog::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void ProjectsManager::dragEnterEvent(QDragEnterEvent* _event)
{
	const QMimeData* mimeData = _event->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urls = mimeData->urls();
		if (urls.size() == 1)
		{
			QUrl url = urls.at(0);

			if (url.isValid() && (url.scheme().toLower() == "file") && url.path().toLower().endsWith(".exe") && mimeData->hasFormat("text/uri-list"))
				_event->acceptProposedAction();
		}
	}
}

void ProjectsManager::dragLeaveEvent(QDragLeaveEvent* _event)
{
	_event->accept();
}

void ProjectsManager::dragMoveEvent(QDragMoveEvent* _event)
{
	_event->acceptProposedAction();
}

void ProjectsManager::dropEvent(QDropEvent* _event)
{
	const QMimeData* mimeData = _event->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();
		QString filePath = urlList.at(0).toLocalFile();

		int idx1 = filePath.lastIndexOf("/");
		int idx2 = filePath.lastIndexOf("\\");
		int idx = idx1>idx2 ? idx1 : idx2;
		QString workdir = filePath;
		workdir.truncate(idx);
		
		m_txtExecutable->setText(filePath);
		m_txtCommandLine->setText("");
		m_txtWorkingDir->setText(workdir);
		ui.inherit->setChecked(true);
	}
}

void ProjectsManager::reject()
{
	bool shouldReject = true;
	if (m_projectListModified)
	{
		QMessageBox::StandardButton reply =
			QMessageBox::question(	this,
									tr("Are you sure?"),
									tr("Project list was modified, if you close project manager it will not be saved."),
									QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::No)
			shouldReject = false;
	}

	if (shouldReject)
		QDialog::reject();
}

void ProjectsManager::buttonAdd()
{
	Project p;
	p.m_executablePath	= m_txtExecutable->text();
	p.m_cmdArgs			= m_txtCommandLine->text();
	p.m_workingDir		= m_txtWorkingDir->text();
	p.m_environment		= m_currentEnvironment;
	p.m_inheritEnv		= ui.inherit->isChecked();
	m_projects.append(p);
	m_projectListModified = true;
	updateProjectList();
}

void ProjectsManager::buttonRemove()
{
	int row = m_listProjects->currentIndex().row();
	m_projects.erase(m_projects.begin() + row);
	m_projectListModified = true;
	m_listProjects->setCurrentIndex(QModelIndex());
	updateProjectList();
}

extern void getStoragePath(wchar_t _path[512]);

void ProjectsManager::run(const QString& _executable, const QString& _cmd, const QString& _workingDir, const QStringList& _environment, bool _inheritEnv)
{
	QString currpath = QDir::currentPath();

	QString watchDir;
	if (_workingDir.length() == 0)
	{
		QFileInfo info(_executable);
		QDir d = info.absoluteDir();
		watchDir = d.absolutePath();
	}
	else
		watchDir = _workingDir;

	m_watcher = new QFileSystemWatcher(this);
	connect(m_watcher, SIGNAL(directoryChanged(const QString&)), this, SLOT(dirChanged(const QString&)));

	wchar_t watchPath[512];
	getStoragePath( watchPath );
	wcscat(watchPath, L"\\MTuner\\");
	m_watcher->addPath(QString::fromWCharArray(watchPath));

	QString arguments = " #23#" + _executable + "#23# #23#" + _cmd + "#23# #23#" + _workingDir + "#23#";

	QString exePath;
	if (rdebug::processIs64bitBinary(_executable.toUtf8()))
		exePath = currpath + "/MTunerInject64.exe";
	else
		exePath = currpath + "/MTunerInject32.exe";

	m_process = new QProcess(this);
	m_process->setProgram(exePath);
	m_process->setWorkingDirectory(_workingDir);
	m_process->setArguments(QStringList() << arguments);

	QStringList env;
	if (_inheritEnv)
		env = QProcess::systemEnvironment();

	env << "MTuner_Allocator=0";
	env << _environment;
	m_process->setEnvironment(env);

	connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
	m_process->start();
	m_processRunning = true;
}

void ProjectsManager::loadSettings(QSettings& _settings)
{
	int numProjects = _settings.beginReadArray("Projects");
	for (int i = 0; i < numProjects; ++i)
	{
		_settings.setArrayIndex(i);
		QString key = QString("Project") + QString::number(i);
		Project p;
		p.m_executablePath	= _settings.value(key + "Exe").toString();
		p.m_cmdArgs			= _settings.value(key + "Cmd").toString();
		p.m_workingDir		= _settings.value(key + "Dir").toString();
		p.m_environment		= _settings.value(key + "Env").toStringList();

		if (_settings.contains(key + "EnvInherit"))
			p.m_inheritEnv	= _settings.value(key + "EnvInherit").toBool();
		else
			p.m_inheritEnv	= true;

		addProject(p);
	}
	_settings.endArray();
}

void ProjectsManager::saveSettings(QSettings& _settings)
{
	_settings.beginWriteArray("Projects");
	int numProjects = getNumProjects();
	for (int i = 0; i < numProjects; ++i)
	{
		_settings.setArrayIndex(i);
		const Project& p = getProject(i);
		QString key = QString("Project") + QString::number(i);
		_settings.setValue(key + "Exe",			p.m_executablePath);
		_settings.setValue(key + "Cmd",			p.m_cmdArgs);
		_settings.setValue(key + "Dir",			p.m_workingDir);
		_settings.setValue(key + "Env",			p.m_environment);
		_settings.setValue(key + "EnvInherit",	p.m_inheritEnv);
	}
	_settings.endArray();
}

void ProjectsManager::buttonRun()
{
	QString exe = m_txtExecutable->text();
	QString cmd = m_txtCommandLine->text();
	QString dir = m_txtWorkingDir->text();
	
	run(exe, cmd, dir, m_currentEnvironment);
}

void ProjectsManager::textParamsChanged()
{
	if (isExecutablePathValid() && isWorkingDirectoryValid())
	{
		if (!projectExists())
			m_buttonAdd->setEnabled(true);
		else
			m_buttonAdd->setEnabled(false);
		m_buttonRun->setEnabled(true);
	}
	else
	{
		m_buttonAdd->setEnabled(false);
		m_buttonRun->setEnabled(false);
	}
}

void ProjectsManager::projectSelectionChanged()
{
	int currentRow = m_listProjects->currentIndex().row();
	if ((currentRow != -1) && (m_projects.size() > currentRow))
	{
		const Project& proj = m_projects.at(currentRow);
		m_txtExecutable->setText(proj.m_executablePath);
		m_txtCommandLine->setText(proj.m_cmdArgs);
		m_txtWorkingDir->setText(proj.m_workingDir);
		m_buttonRemove->setEnabled(true);
		ui.editVars->setEnabled(true);
		ui.inherit->setEnabled(true);
		ui.inherit->setChecked(proj.m_inheritEnv);
		m_currentEnvironment = proj.m_environment;
		ui.inherit->setChecked(proj.m_inheritEnv);
	}
	else
	{
		ui.editVars->setEnabled(false);
		ui.inherit->setEnabled(false);
		m_buttonRemove->setEnabled(false);
	}
}

void ProjectsManager::browseExecutable()
{
	QString exe = QFileDialog::getOpenFileName(this, tr("select executable"), "", "exe files (*.exe)");

	if (exe.size() != 0)
		m_txtExecutable->setText(exe);
}

void ProjectsManager::browseWorkingDir()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("select working directory"), 
		"", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (dir.size() != 0)
		m_txtWorkingDir->setText(dir);
}

void ProjectsManager::editEnvironment()
{
	Environment e;
	e.setEnvironment(m_currentEnvironment);
	e.exec();
	m_currentEnvironment = e.getEnvironment();

	int currentRow = m_listProjects->currentIndex().row();
	if ((currentRow != -1) && (m_projects.size() > currentRow))
	{
		Project proj = m_projects.at(currentRow);
		proj.m_environment = m_currentEnvironment;
		m_projects[currentRow] = proj;
	}
}

void ProjectsManager::dirChanged(const QString& _dir)
{
	QDir dir(_dir);
	QStringList list = dir.entryList(QStringList() << "*.MTuner", QDir::Files, QDir::Time);
	if (list.size())
	{
		m_watcher->deleteLater();
		m_watcher = 0;
		QString name = list.at(0);
		QString captureFile = QDir::toNativeSeparators(_dir + name);
		m_currentCaptureFile = captureFile;
		emit captureCreated(captureFile);
	}
}

void ProjectsManager::inheritEnv(bool _checked)
{
	int currentRow = m_listProjects->currentIndex().row();
	if ((currentRow != -1) && (m_projects.size() > currentRow))
	{
		Project proj = m_projects.at(currentRow);
		proj.m_inheritEnv = _checked;
		m_projects[currentRow] = proj;
	}
}

void ProjectsManager::updateProjectList()
{
	QVector<Project>::iterator it = m_projects.begin();
	QVector<Project>::iterator end = m_projects.end();

	ui.editVars->setEnabled(false);
	ui.inherit->setChecked(true);

	m_listProjects->clear();
	QFileIconProvider iconProv;
	while (it != end)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(it->m_executablePath));
		QString toolTip;
		toolTip += "<b>Exe:</b> " + it->m_executablePath + "<br>";
		toolTip += "<b>Args:</b> " + it->m_cmdArgs + "<br>";
		toolTip += "<b>Work dir:</b> " + it->m_workingDir;
		item->setToolTip(0,toolTip);
		QIcon icon = iconProv.icon(QFileInfo(it->m_executablePath));
		item->setIcon(0,icon);
		m_listProjects->addTopLevelItem(item);
		++it;
	}
	m_listProjects->update();
	textParamsChanged();
}

bool ProjectsManager::isExecutablePathValid()
{
	return (m_txtExecutable->text().size() && QFile::exists(m_txtExecutable->text()));
}

bool ProjectsManager::projectExists()
{
	QVector<Project>::iterator it  = m_projects.begin();
	QVector<Project>::iterator end = m_projects.end();

	while (it != end)
	{
		if ((m_txtExecutable->text()	== it->m_executablePath) &&
			(m_txtCommandLine->text()	== it->m_cmdArgs) &&
			(m_txtWorkingDir->text()	== it->m_workingDir) &&
			(m_currentEnvironment		== it->m_environment) &&
			(ui.inherit->isChecked()	== it->m_inheritEnv))
			return true;
		++it;
	}
	return false;
}

bool ProjectsManager::isWorkingDirectoryValid()
{
	return ((m_txtWorkingDir->text().size() && QFile::exists(m_txtWorkingDir->text())) || 
		(m_txtWorkingDir->text().size() == 0));
}

void ProjectsManager::restore()
{
	m_projects = m_savedProjects;
	updateProjectList();
}

void ProjectsManager::processFinished(int _exitCode, QProcess::ExitStatus /*_status*/)
{
	RTM_ASSERT(m_process, "");

	bool tryAnotherArch = m_processRunning && (_exitCode == 0);
	m_processRunning = false;

	if (tryAnotherArch)
	{
		QProcess* proc = qobject_cast<QProcess*>(sender());
		QString program = proc->program();
		if (program.endsWith("64.exe"))
			program.replace("64.exe", "32.exe");
		else
			program.replace("32.exe", "64.exe");
		proc->setProgram(program);
		proc->start();
		return;
	}

	emit captureSetProcessID((uint64_t)_exitCode);
	m_process->deleteLater();
	m_process = 0;
}
