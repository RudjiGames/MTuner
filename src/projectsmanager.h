//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_PROJECTSMANAGER_H
#define RTM_MTUNER_PROJECTSMANAGER_H

#include <MTuner/.qt/qt_ui/projectsmanager_ui.h>

struct Project
{
	QString m_executablePath;
	QString m_cmdArgs;
	QString m_workingDir;

	bool operator == (const Project& _other)
	{
		return !(*this != _other);
	}

	bool operator != (const Project& _other)
	{
		return ((m_executablePath	!= _other.m_executablePath)	||
				(m_cmdArgs			!= _other.m_cmdArgs)		||
				(m_workingDir		!= _other.m_workingDir));
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
	QProcess*			m_process;
	bool				m_processRunning;
	QString				m_currentCaptureFile;

public:
	ProjectsManager(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void			save();
	void			changeEvent(QEvent* _event);
	void			addProject(const Project& _project) { m_projects.push_back(_project); updateProjectList(); }
	int				getNumProjects() const { return m_projects.size(); }
	const Project&	getProject(int _index) const { return m_projects[_index]; }
	void			run(const QString& _executable, const QString& _cmd = QString(), const QString& _workingDir = QString());

public Q_SLOTS:
	void buttonAdd();
	void buttonRemove();
	void buttonRun();
	void textParamsChanged();
	void projectSelectionChanged();
	void browseExecutable();
	void browseWorkingDir();
	void dirChanged(const QString&);
	void restore();
	void processFinished(int _exitCode, QProcess::ExitStatus _status);

Q_SIGNALS:
	void captureCreated(const QString& _path);
	void captureSetProcessID(uint64_t _pid);

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
