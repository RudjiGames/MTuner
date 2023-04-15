//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_MTUNER_H
#define RTM_MTUNER_MTUNER_H

#include <MTuner/src/stats.h>
#include <MTuner/.qt/qt_ui/mtuner_ui.h>

class ProjectsManager;
class SymbolStore;
class HeapsWidget;
class ModulesWidget;
class HistogramWidget;
class StackAndSource;
class ExternalEditor;
class CentralWidget;
class SourceView;
class Graph;
class BinLoaderView;
class TagTreeWidget;
class GCCSetup;

class DockWidget : public QDockWidget
{
	Q_OBJECT
public:
	DockWidget(const QString& _title, QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0)
		: QDockWidget(_title, _parent, _flags)	{}

public Q_SLOTS:
	void toggleDock(bool)
	{
		setFloating(!isFloating());
	}
};

class ToolButtonHover : public QToolButton
{
	Q_OBJECT
	QIcon	m_default;
	QIcon	m_hover;

public:
	ToolButtonHover(QIcon _default, QIcon _hover, QWidget* _parent = 0)
		: QToolButton(_parent)
		, m_default(_default)
		, m_hover(_hover)
	{
	}

	void setDefaultAction(QAction* _action) { _action->setIcon(m_default); QToolButton::setDefaultAction(_action); }
	void leaveEvent(QEvent*) { defaultAction()->setIcon(m_default); }
	virtual void enterEvent(QEvent*) { defaultAction()->setIcon(m_hover); }
};

class MTuner : public QMainWindow
{
	Q_OBJECT

private:
	ProjectsManager*		m_projectsManager;
	QString					m_watchedFile;
	QTimer*					m_watchTimer;
	uint64_t				m_capturePid;
	SymbolStore*			m_symbolStore;
	GCCSetup*				m_gccSetup;
	DockWidget*				m_graphDock;
	DockWidget*				m_statsDock;
	DockWidget*				m_histogramDock;
	DockWidget*				m_tagTreeDock;
	DockWidget*				m_stackAndSourceDock;
	DockWidget*				m_heapsDock;
	DockWidget*				m_modulesDock;
	QProgressBar*			m_loadingProgressBar;
	QLabel*					m_statusBarRedDot;
	CentralWidget*			m_centralWidget;
	QFileDialog*			m_fileDialog;

	Graph*					m_graph;
	HistogramWidget*		m_histogramWidget;
	HeapsWidget*			m_heapsWidget;
	ModulesWidget*			m_modulesWidget;
	SourceView*				m_sourceView;
	StackAndSource*			m_stackAndSource;
	ExternalEditor*			m_externalEditor;

	Stats*					m_stats;
	bool					m_showWelcomeDialog;
	bool					m_closeStartPageWidgetOnOpen;

	TagTreeWidget*			m_tagTree;

public:
	MTuner(QWidget* _parent = 0, Qt::WindowFlags _flags = (Qt::WindowFlags)0);

	void show();
	void setLoadingProgress(float _progress, const QString &_message);
	void changeEvent(QEvent* _event);
	void closeEvent(QCloseEvent* _event);
	void openFileFromPath(const QString& _file);
	void handleFile(const QString& _file);

public Q_SLOTS:

	// File
	void openFile();
	void closeFile();
	void openCaptureLocation();
	QString getCaptureLocation();
	void exit();
	// Edit
	void manageProjects();
	void setFilters(bool _filters);
	void setupGCCToolchains();
	// Settings
	void setupSymbols();
	void setupEditor();
	void saveCaptureWindowLayout();
	// Help
	void openDocumentation();
	void about();

	void heapSelected(uint64_t);
	void moduleSelected(void*);
	void graphModified();
	void setWidgetSources(CaptureContext* _binView);

	void suicide();
	void showHistogram(bool);
	void showGraph(bool);
	void showStats(bool);
	void showTagTree(bool);
	void showStackTrace(bool);
	void showHeaps(bool);
	void showModules(bool);

	void setStatusBarText(const QString&);
	void checkCaptureStatus();
	void startCaptureStatusTimer();
	void captureStarted(const QString&);
	void captureSetProcessID(uint64_t);

	void setFilteringState(bool,bool);

	QMenu* getLanguageParentMenu() { return ui.menuLanguage; }

Q_SIGNALS:
	void binLoaded(bool);
	void setFilterState(bool);
	void setFilterButtonEnabled(bool);

private:
	void showWelcomeDialog();
	void setDockWindowIcon(DockWidget* _widget, const QString& _icon);
	void setupDockWindows();
	void readSettings();
	void writeSettings();

	static uint32_t makeVersion(uint8_t _major, uint8_t _minor, uint8_t _detail);

protected:
	void dragEnterEvent(QDragEnterEvent* _event);
	void dragMoveEvent(QDragMoveEvent* _event);
	void dragLeaveEvent(QDragLeaveEvent* _event);
	void dropEvent(QDropEvent* _event);

private:
	Ui::MTunerClass ui;
};

#endif // RTM_MTUNER_MTUNER_H
