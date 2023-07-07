//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_PROJECTSMANAGER_H
#define RTM_MTUNER_PROJECTSMANAGER_H

#include <MTuner/src/environment.h>
#include <MTuner/.qt/qt_ui/projectsmanager_ui.h>

struct Project
{
	QString		m_executablePath;
	QString		m_cmdArgs;
	QString		m_workingDir;
	QStringList m_environment;
	bool		m_inheritEnv;

	Project()
		: m_inheritEnv(true)
	{
	}

	bool operator == (const Project& _other)
	{
		return !(*this != _other);
	}

	bool operator != (const Project& _other)
	{
		return ((m_executablePath	!= _other.m_executablePath)	||
				(m_cmdArgs			!= _other.m_cmdArgs)		||
				(m_workingDir		!= _other.m_workingDir)		||
				(m_environment		!= _other.m_environment)	||
				(m_inheritEnv		!= _other.m_inheritEnv));
	}
};

class ProjectsManager : public QDialog
{
	Q_OBJECT

public:
	QVector<Project>	m_savedProjects;
	QVector<Project>	m_projects;
	bool				m_projectListModified;
	QLineEdit*			m_txtExecutable;
	QLineEdit*			m_txtCommandLine;
	QLineEdit*			m_txtWorkingDir;
	QTreeWidget*		m_listProjects;
	QPushButton*		m_buttonAdd;
	QPushButton*		m_buttonRemove;
	QPushButton*		m_buttonRun;
	QFileSystemWatcher*	m_watcher;
	bool				m_injecting;
	QString				m_currentCaptureFile;
	QStringList			m_currentEnvironment;

public:
	ProjectsManager(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void			save();
	void			changeEvent(QEvent* _event);
	void			addProject(const Project& _project) { m_projects.push_back(_project); updateProjectList(); }
	int				getNumProjects() const { return m_projects.size(); }
	const Project&	getProject(int _index) const { return m_projects[_index]; }
	bool			run(const QString& _executable, const QString& _cmd = QString(), const QString& _workingDir = QString(), const QStringList& _environment = QStringList(), bool _inheritEnv = true, int _allocator = 0, bool _shouldCapture = true, bool _shouldLoad = true);

	void			loadSettings(QSettings& _settings);
	void			saveSettings(QSettings& _settings);

public Q_SLOTS:
	void buttonAdd();
	void buttonRemove();
	void buttonRun();
	void textParamsChanged();
	void projectSelectionChanged();
	void browseExecutable();
	void browseWorkingDir();
	void editEnvironment();
	void dirChanged(const QString&);
	void inheritEnv(bool);
	void restore();
	void processInjectFinished(int _exitCode, QProcess::ExitStatus _status);
	bool isInjecting();

Q_SIGNALS:
	void captureCreated(const QString& _path);
	void captureSetProcessID(uint64_t _pid);
	void captureStartMonitoring();

private:
	void updateProjectList();
	bool isExecutablePathValid();
	bool projectExists();
	bool isWorkingDirectoryValid();

protected:
	void dragEnterEvent(QDragEnterEvent* _event);
	void dragMoveEvent(QDragMoveEvent* _event);
	void dragLeaveEvent(QDragLeaveEvent* _event);
	void dropEvent(QDropEvent* _event);
	void reject();	// QDialog

private:
	Ui::ProjectsDialog ui;
};

#endif // RTM_MTUNER_PROJECTSMANAGER_H
