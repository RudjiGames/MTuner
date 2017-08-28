//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_MTUNER_H
#define RTM_MTUNER_MTUNER_H

#include <mtuner/src/stats.h>
#include <mtuner/.qt/qt_ui/mtuner_ui.h>

class ProjectsManager;
class SymbolStore;
class HeapsWidget;
class HistogramWidget;
class StackAndSource;
class ExternalEditor;
class CentralWidget;
class SourceView;
class Graph;
class BinLoaderView;
class TagTreeWidget;
class GCCSetup;

class MTuner : public QMainWindow
{
	Q_OBJECT

private:
	ProjectsManager*		m_projectsManager;
	QString					m_watchedFile;
	QTimer*					m_watchTimer;
	SymbolStore*			m_symbolStore;
	GCCSetup*				m_gccSetup;
	QDockWidget*			m_graphDock;
	QDockWidget*			m_statsDock;
	QDockWidget*			m_histogramDock;
	QDockWidget*			m_tagTreeDock;
	QDockWidget*			m_stackAndSourceDock;
	QDockWidget*			m_heapsDock;
	QProgressBar*			m_loadingProgressBar;
	QLabel*					m_statusBarRedDot;
	CentralWidget*			m_centralWidget;
	QFileDialog*			m_fileDialog;

	Graph*					m_graph;
	HistogramWidget*		m_histogramWidget;
	HeapsWidget*			m_heapsWidget;
	SourceView*				m_sourceView;
	StackAndSource*			m_stackAndSource;
	ExternalEditor*			m_externalEditor;

	Stats*					m_stats;
	bool					m_showStartPageWidget;
	bool					m_closeStartPageWidgetOnOpen;

	TagTreeWidget*			m_tagTree;
	
public:
	MTuner(QWidget* _parent = 0, Qt::WindowFlags _flags = 0);

	void show();
	void setLoadingProgress(float _progress, const wchar_t* _message);
	void changeEvent(QEvent* _event);
	void closeEvent(QCloseEvent* _event);
	void openFileFromPath(const QString& _file);
	void handleFile(const QString& _file);

public Q_SLOTS:

	// File
	void openFile();
	void closeFile();
	void openCaptureLocation();
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
	void readDocumentation();
	void about();

	void heapSelected(uint64_t);
	void graphModified();
	void setWidgetSources(CaptureContext* _binView);

	void suicide();
	void showHistogram(bool);
	void showGraph(bool);
	void showStats(bool);
	void showTagTree(bool);
	void showStackTrace(bool);
	void showHeaps(bool);

	void setStatusBarText(const QString&);
	void watchFile(const QString&);
	void tryOpeWatchedFile();

	void setFilteringState(bool,bool);

	QMenu* getLanguageParentMenu() { return ui.menuLanguage; }

Q_SIGNALS:
	void binLoaded(bool);
	void setFilterState(bool);
	void setFilterButtonEnabled(bool);

private:
	void showWelcomeDialog();
	void setupDockWindows();
	void readSettings();
	void writeSettings();

protected:
	void dragEnterEvent(QDragEnterEvent* _event);
	void dragMoveEvent(QDragMoveEvent* _event);
	void dragLeaveEvent(QDragLeaveEvent* _event);
	void dropEvent(QDropEvent* _event);

private:
	Ui::MTunerClass ui;
};

#endif // RTM_MTUNER_MTUNER_H
