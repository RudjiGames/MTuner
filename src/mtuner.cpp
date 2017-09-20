//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/mtuner.h>
#include <MTuner/src/about.h>
#include <MTuner/src/projectsmanager.h>
#include <MTuner/src/symbolstore.h>
#include <MTuner/src/centralwidget.h>
#include <MTuner/src/external_editor.h>
#include <MTuner/src/graphwidget.h>
#include <MTuner/src/heapswidget.h>
#include <MTuner/src/histogramwidget.h>
#include <MTuner/src/stackandsource.h>
#include <MTuner/src/stats.h>
#include <MTuner/src/binloaderview.h>
#include <MTuner/src/sourceview.h>
#include <MTuner/src/graph.h>
#include <MTuner/src/gcc.h>
#include <MTuner/src/welcome.h>
#include <MTuner/src/tagtreewidget.h>
#include <MTuner/src/capturecontext.h>

#if RTM_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Shlobj.h>
#endif

QString getDirFromFile(const QString& _file)
{
	int idx1 = _file.lastIndexOf("/");
	int idx2 = _file.lastIndexOf("\\");
	int idx = idx1>idx2 ? idx1 : idx2;
	QString workdir = _file;
	workdir.truncate(idx);
	return workdir;
}

char* stringDup(const QByteArray& _string)
{
	return rtm::strdup(_string.constData());
}

void setupLoaderToolchain(CaptureContext* _context, const QString& _file, GCCSetup* _gccSetup,
						  QFileDialog* _fileDialog, MTuner* _mtuner, const QString& _symSource)
{
	rdebug::Toolchain tc;
	rtm_string executable;

	// if not a windows toolchain - locate the executable
	if (_context->m_capture->getToolchain() != rmem::ToolChain::Win_MSVC)
	{
		const char* extensions = "All files (*.*)";
		switch (_context->m_capture->getToolchain())
		{
		case rmem::ToolChain::Win_gcc:		extensions = "Exe files (*.exe)"; break;
		case rmem::ToolChain::Linux_gcc:	break;
		case rmem::ToolChain::OSX_gcc:		break;
		case rmem::ToolChain::PS4_clang:	extensions = "Elf files (*.elf)"; break;
		case rmem::ToolChain::PS3_gcc:		extensions = "Elf files (*.elf)"; break;
		case rmem::ToolChain::PS3_snc:		extensions = "Self files (*.self)"; break;
		case rmem::ToolChain::Android_arm:	break;
		case rmem::ToolChain::Android_mips:	break;
		case rmem::ToolChain::Android_x86:	break;
		default: break;
		};

		bool symSrcFound = false;
		if (_context->m_capture->getToolchain() == rmem::ToolChain::Win_gcc)
		{
			const char* exe = _context->m_capture->getModuleInfos()[0].m_modulePath;
			if (strstr(exe, ".exe") || strstr(exe, ".elf"))
			{
				if (QFileInfo(QString::fromUtf8(exe)).exists())
				{
					executable = exe;
					symSrcFound = true;
				}
			}
		}

		if (_fileDialog && !symSrcFound)
		{
			// gui
			QString dir = getDirFromFile(_file);
			QString fileName = _fileDialog->getOpenFileName(_mtuner, QObject::tr("select symbol source"), dir, extensions);
			executable = fileName.toUtf8().constData();
		}
		else
			if (!symSrcFound)
			{
				// cmd
				executable = _symSource.toUtf8().constData();
				if (executable.length() == 0)
					rtm::Console::info("No symbol source specified, symbols will not be resolved!\n");
			}

		// check if toolchain is configured, if not - ask
		if (!_gccSetup->isConfigured(_context->m_capture->getToolchain(), _context->m_capture->is64bit()))
		{
			if (_fileDialog)
			{
				// gui
				QMessageBox message(QMessageBox::Question, QObject::tr("Toolchain is not configured"), QObject::tr("Toolchain needs to be configured in order to resolve symbols.\nWould you like to configure the toolchain now?"), QMessageBox::Yes | QMessageBox::No);
				message.exec();
				if (message.result() == QMessageBox::Yes)
				{
					_gccSetup->exec();
				}
			}
			else
			{
				// cmd
				rtm::Console::info("Toolchain is not configured, no symbols can be resolved!\n");
			}
		}

		tc = _gccSetup->getToolchainInfo(_context->m_capture->getToolchain(), _context->m_capture->is64bit());
	}
	else
	{
		tc.m_type = rdebug::Toolchain::MSVC;
		strcpy(tc.m_toolchainPath, _symSource.toUtf8());
		executable = _context->m_capture->getModuleInfos()[0].m_modulePath;
	}

	_context->setToolchain(tc, executable);
}

MTuner::MTuner(QWidget* _parent, Qt::WindowFlags _flags) :
	QMainWindow(_parent, _flags)
{
	ui.setupUi(this);
	emit setFilterButtonEnabled(false);

	m_projectsManager = new ProjectsManager(this);
	connect(m_projectsManager, SIGNAL(captureCreated(const QString&)), this, SLOT(captureStarted(const QString&)));
	connect(m_projectsManager, SIGNAL(captureSetProcessID(uint64_t)), this, SLOT(captureSetProcessID(uint64_t)));
	m_watchTimer = NULL;
	m_capturePid = 0;

	m_loadingProgressBar = new QProgressBar();
	m_loadingProgressBar->setRange(0,10000);
	m_loadingProgressBar->setValue(0);
	m_loadingProgressBar->setAlignment(Qt::AlignRight);
	m_loadingProgressBar->setVisible(false);
	statusBar()->insertPermanentWidget(0,m_loadingProgressBar);

	m_statusBarRedDot	= new QLabel();
	m_statusBarRedDot->setPixmap(QPixmap(":/MTuner/resources/images/red_dot.png"));
	statusBar()->insertPermanentWidget(1,m_statusBarRedDot);
	m_statusBarRedDot->setVisible(false);

	m_fileDialog	= new QFileDialog(this);
	m_symbolStore	= new SymbolStore(this);
	m_gccSetup		= new GCCSetup(this);

	m_centralWidget = new CentralWidget();
	connect(m_centralWidget, SIGNAL(contextChanged(CaptureContext*)), this, SLOT(setWidgetSources(CaptureContext*)));
	connect(m_centralWidget, SIGNAL(changeWindowTitle(const QString&)), this, SLOT(setWindowTitle(const QString&)));
	connect(m_centralWidget, SIGNAL(setFilteringEnabled(bool,bool)), this, SLOT(setFilteringState(bool,bool)));
	setCentralWidget(m_centralWidget);

	m_externalEditor = new ExternalEditor();

	setupDockWindows();

	QWidget* spacerWidget = new QWidget(this);
	spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	spacerWidget->setVisible(true);
	ui.toolBar->addWidget(spacerWidget);

	connect(ui.action_Save_capture_window_layout, SIGNAL(triggered(bool)), this, SLOT(saveCaptureWindowLayout()));
	ui.action_Save_capture_window_layout->setEnabled(false);

	readSettings();
	emit binLoaded(false);
}

void MTuner::show()
{
	QMainWindow::show();
	QApplication::processEvents(QEventLoop::AllEvents,1);
	showWelcomeDialog();
}

void MTuner::setLoadingProgress(float _progress, const QString &_message)
{
	if (_progress == 100.0f)
		m_loadingProgressBar->setVisible(false);
	else
		m_loadingProgressBar->setVisible(true);

	int value = m_loadingProgressBar->value();
	int newVal = _progress*100;
	if (newVal != value)
	{
		m_loadingProgressBar->setValue(newVal);
		setStatusBarText(_message);
		QApplication::processEvents(QEventLoop::AllEvents,1);
	}
}

void MTuner::changeEvent(QEvent* _event)
{
	QMainWindow::changeEvent(_event);
	switch (_event->type())
	{
		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			if (m_graphDock) m_graphDock->setWindowTitle(tr("Memory timeline"));
			if (m_histogramDock) m_histogramDock->setWindowTitle(tr("Allocation histogram"));
			if (m_statsDock) m_statsDock->setWindowTitle(tr("Statistics"));
			if (m_tagTreeDock) m_tagTreeDock->setWindowTitle(tr("Memory tag tree"));
			if (m_stackAndSourceDock) m_stackAndSourceDock->setWindowTitle(tr("Stack trace"));
			if (m_heapsDock) m_heapsDock->setWindowTitle(tr("Heaps / Allocators"));
			break;
		default:
			break;
	};
}

void MTuner::closeEvent(QCloseEvent*)
{
	writeSettings();
}

void MTuner::openFile()
{
	m_fileDialog->setFileMode(QFileDialog::ExistingFile);
	QString fileName = m_fileDialog->getOpenFileName(this,tr("select a capture file"),"","MTuner files (*.MTuner)");
	openFileFromPath(fileName);
}

void MTuner::closeFile()
{
	m_centralWidget->removeCurrentTab();
}

#if RTM_PLATFORM_WINDOWS
bool windowsVersionGreaterOrEqual(DWORD majorVersion)
{
    OSVERSIONINFOEX osVersionInfo;
    ::ZeroMemory(&osVersionInfo, sizeof(OSVERSIONINFOEX));
    osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osVersionInfo.dwMajorVersion = majorVersion;
    ULONGLONG maskCondition = ::VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL);
    return ::VerifyVersionInfo(&osVersionInfo, VER_MAJORVERSION, maskCondition) ? true : false;
}
#endif

void getStoragePath(wchar_t _path[512])
{
#if RTM_PLATFORM_WINDOWS

	bool vistaOrHigher = windowsVersionGreaterOrEqual(6);
	bool pathRetrieved = false;

	if (vistaOrHigher)
	{
		wchar_t* str;
		HRESULT hr = SHGetKnownFolderPath( FOLDERID_RoamingAppData, 0, NULL, &str);
		if (hr == S_OK)
		{
			wcscpy(_path, str);
			CoTaskMemFree(static_cast<void*>(str));
			pathRetrieved = true;
		}
	}
	else
	{
		HRESULT hr = SHGetFolderPathW(0, CSIDL_APPDATA, 0, 0, _path);
		if (hr == S_OK)
			pathRetrieved = true;
	}

	if (!pathRetrieved)
	{
		// fall back on env variable
		wchar_t* path = _wgetenv(L"APPDATA");
		if (path)
			wcscpy(_path, path);
		else
			wcscpy(_path, L"");  // nothing worked ;(
	}

#else
	wcscpy(_path,L"");
#endif
}

void MTuner::openCaptureLocation()
{
	wchar_t capturePath[512];
	getStoragePath( capturePath );
	wcscat(capturePath, L"\\MTuner\\");
	QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromWCharArray(capturePath)));
}

void MTuner::exit()
{
	close();
}

void MTuner::manageProjects()
{
	m_projectsManager->save();
	m_projectsManager->exec();
}

void MTuner::setFilters(bool _filters)
{
	m_centralWidget->toggleFilteringForCurrentView(_filters);
}

void MTuner::setupGCCToolchains()
{
	m_gccSetup->exec();
}

void MTuner::setupSymbols()
{
	m_symbolStore->save();
	m_symbolStore->exec();
}

void MTuner::setupEditor()
{
	m_externalEditor->run();
}

void MTuner::saveCaptureWindowLayout()
{
	BinLoaderView* view = m_centralWidget->getCurrentView();
	if (view)
	{
		view->saveSettings();
	}
}

void MTuner::readDocumentation()
{
	QDesktopServices::openUrl(QUrl("http://www.mtuner.net/documentation.html", QUrl::TolerantMode));
}

void MTuner::about()
{
	AboutDialog a(this);
	a.exec();
}

void MTuner::heapSelected(uint64_t _handle)
{
	BinLoaderView* view = m_centralWidget->getCurrentView();
	if (view)
	{
		view->setCurrentHeap(_handle);
		CaptureContext* m_context = view ? view->getContext() : NULL;
		if (m_context)
			m_context->m_capture->setCurrentHeap(_handle);
	}
}

void MTuner::graphModified()
{
	BinLoaderView* view = m_centralWidget->getCurrentView();
	if (view)
	{
		GraphWidget* graphWidget = m_graph->getGraphWidget();
		view->setMinTime(graphWidget->minTime());
		view->setMaxTime(graphWidget->maxTime());
	}
}

void MTuner::setupDockWindows()
{
	setDockNestingEnabled(true);
	m_graphDock = new QDockWidget(tr("Memory timeline"),this);
	m_histogramDock = new QDockWidget(tr("Allocation histogram"),this);
	m_statsDock = new QDockWidget(tr("Statistics"),this);
	m_tagTreeDock = new QDockWidget(tr("Memory tag tree"),this);
	m_stackAndSourceDock = new QDockWidget(tr("Stack trace"), this);
	m_heapsDock = new QDockWidget(tr("Heaps / Allocators"),this);

	m_graphDock->setObjectName("GraphDock");
	m_histogramDock->setObjectName("HistogramDock");
	m_statsDock->setObjectName("StatsDock");
	m_tagTreeDock->setObjectName("TagTreeDock");
	m_stackAndSourceDock->setObjectName("StackTraceDock");
	m_heapsDock->setObjectName("HeapsDock");

	addDockWidget(Qt::BottomDockWidgetArea, m_graphDock);
	addDockWidget(Qt::BottomDockWidgetArea, m_histogramDock);
	addDockWidget(Qt::LeftDockWidgetArea, m_statsDock);
	addDockWidget(Qt::LeftDockWidgetArea, m_tagTreeDock);
	addDockWidget(Qt::LeftDockWidgetArea, m_heapsDock);
	addDockWidget(Qt::RightDockWidgetArea, m_stackAndSourceDock);

	m_graphDock->setVisible(true);
	m_statsDock->setVisible(true);
	m_histogramDock->setVisible(true);
	m_tagTreeDock->setVisible(true);
	m_stackAndSourceDock->setVisible(true);
	m_heapsDock->setVisible(true);

	connect(m_graphDock,			SIGNAL(visibilityChanged(bool)), ui.action_View_Memory_Graph,		SLOT(setChecked(bool)));
	connect(m_statsDock,			SIGNAL(visibilityChanged(bool)), ui.action_View_Memory_Stats,		SLOT(setChecked(bool)));
	connect(m_histogramDock,		SIGNAL(visibilityChanged(bool)), ui.action_View_Histograms,			SLOT(setChecked(bool)));
	connect(m_tagTreeDock,			SIGNAL(visibilityChanged(bool)), ui.action_View_Tag_Tree,			SLOT(setChecked(bool)));
	connect(m_stackAndSourceDock,	SIGNAL(visibilityChanged(bool)), ui.action_View_StackTrace,			SLOT(setChecked(bool)));
	connect(m_heapsDock,			SIGNAL(visibilityChanged(bool)), ui.action_View_Heaps_Allocators,	SLOT(setChecked(bool)));

	/// histogram dock
	m_histogramWidget = new HistogramWidget();
	m_histogramWidget->resize(size().width()/2,m_histogramWidget->height());
	m_histogramWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	m_histogramDock->setWidget(m_histogramWidget);

	/// graph dock
	m_graph = new Graph();
	GraphWidget* graphWidget = m_graph->getGraphWidget();
	m_graph->resize(size().width()/2,m_graph->height());
	m_graph->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_graph->setMinimumSize(120,90);

	m_graphDock->setWidget(m_graph);

	/// stats dock
	m_stats = new Stats();
	m_stats->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	m_statsDock->setWidget(m_stats);

	/// tag tree dock
	m_tagTree = new TagTreeWidget();
	m_tagTreeDock->setWidget(m_tagTree);

	/// heaps dock
	m_heapsWidget = new HeapsWidget();
	m_heapsDock->setWidget(m_heapsWidget);

	/// stack/source dock
	m_stackAndSource = new StackAndSource(m_externalEditor);
	m_stackAndSourceDock->setWidget(m_stackAndSource);

	connect(m_centralWidget, SIGNAL(setStackTrace(rtm::StackTrace**,int)), m_stackAndSource, SLOT(setStackTrace(rtm::StackTrace**,int)));

	connect(m_heapsWidget,SIGNAL(heapSelected(uint64_t)), this, SLOT(heapSelected(uint64_t)));

	connect(graphWidget,SIGNAL(snapshotSelected()), m_histogramWidget, SLOT(updateUI()));
	connect(graphWidget,SIGNAL(snapshotSelected()), m_stats, SLOT(updateUI()));
	connect(graphWidget,SIGNAL(minMaxChanged()), this, SLOT(graphModified()));
	connect(graphWidget,SIGNAL(snapshotSelected()), this, SLOT(graphModified()));

	connect(graphWidget,SIGNAL(snapshotSelected()), m_centralWidget, SLOT(updateFilterDataIfNeeded()));
	connect(m_histogramWidget,SIGNAL(binClicked()), m_centralWidget, SLOT(updateFilterDataIfNeeded()));
	connect(m_tagTree,SIGNAL(tagClicked()), m_centralWidget, SLOT(updateFilterDataIfNeeded()));
	connect(m_heapsWidget,SIGNAL(heapSelected(uint64_t)), m_centralWidget, SLOT(updateFilterDataIfNeeded()));
}

void MTuner::setWidgetSources(CaptureContext* _context)
{
	ui.action_Save_capture_window_layout->setEnabled(_context != 0);

	CaptureContext* ctx = _context;
	BinLoaderView* binView = _context ? _context->m_binLoaderView : NULL;
	m_stats->setContext(ctx);
	m_graph->setContext(ctx, binView);
	m_histogramWidget->setContext(ctx, binView);
	m_tagTree->setContext(ctx);
	m_heapsWidget->setContext(ctx);
	m_stackAndSource->setContext(ctx);

	if (binView)
	{
		connect(binView, SIGNAL(highlightTime(uint64_t)), m_graph, SLOT(highlightTime(uint64_t)));
		connect(binView, SIGNAL(selectRange(uint64_t,uint64_t)), m_graph->getGraphWidget(), SLOT(selectFromTimes(uint64_t, uint64_t)));
		connect(binView, SIGNAL(highlightRange(uint64_t, uint64_t)), m_graph, SLOT(highlightRange(uint64_t, uint64_t)));
		m_heapsWidget->setCurrentHeap(binView->getCurrentHeap());
		GraphWidget* graphWidget = m_graph->getGraphWidget();
		graphWidget->setMinTime(binView->getMinTime());
		graphWidget->setMaxTime(binView->getMaxTime());
	}

	emit binLoaded(binView != NULL);
}

void MTuner::suicide()
{
	close();
}

void MTuner::showHistogram(bool _visible)
{
	m_histogramDock->setVisible(_visible);
}

void MTuner::showGraph(bool _visible)
{
	m_graphDock->setVisible(_visible);
}

void MTuner::showStats(bool _visible)
{
	m_statsDock->setVisible(_visible);
}

void MTuner::showTagTree(bool _visible)
{
	m_tagTreeDock->setVisible(_visible);
}

void MTuner::showStackTrace(bool _visible)
{
	m_stackAndSourceDock->setVisible(_visible);
}

void MTuner::showHeaps(bool _visible)
{
	m_heapsDock->setVisible(_visible);
}

void MTuner::setStatusBarText(const QString& _text)
{
	statusBar()->showMessage(_text, 2300);
}

static const uint32_t g_watchInterval = 460;

void MTuner::captureStarted(const QString& _file)
{
	setStatusBarText(QString(tr("Created ")) + _file);
	if (m_watchTimer)
		m_watchTimer->stop();

	m_watchedFile		= _file;

	m_watchTimer = new QTimer(this);
	m_watchTimer->setInterval(g_watchInterval);
	connect(m_watchTimer, SIGNAL(timeout()), this, SLOT(checkCaptureStatus()));
	m_watchTimer->start();
}

void MTuner::captureSetProcessID(uint64_t _pid)
{
	m_capturePid = _pid;
	m_projectsManager->close();

	m_statusBarRedDot->setVisible(false);
	openFileFromPath(m_watchedFile);
	m_watchedFile = "";
}

#if RTM_PLATFORM_WINDOWS
bool isProcessRunning(uint64_t _pid)
{
	HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, (DWORD)_pid);
	DWORD ret = WaitForSingleObject(process, 0);
	CloseHandle(process);
	return ret == WAIT_TIMEOUT;
}
#else
bool isProcessRunning(uint64_t pid)
{
	return false;
}
#endif

void MTuner::checkCaptureStatus()
{
	statusBar()->showMessage(tr("Capture in progress") + " - " + m_watchedFile, g_watchInterval);

	m_statusBarRedDot->setVisible(!m_statusBarRedDot->isVisible());

	if (m_capturePid && (!isProcessRunning(m_capturePid)))
	{
		m_capturePid = 0;
		m_projectsManager->close();
		m_statusBarRedDot->setVisible(false);
		openFileFromPath(m_watchedFile);
		m_watchedFile = "";
		m_watchTimer->stop();
	}
	else
	{
		m_watchTimer->start();
	}
}

void MTuner::setFilteringState(bool _checked, bool _enabled)
{
	emit setFilterState(_checked);
	emit setFilterButtonEnabled(_enabled);
}

void MTuner::showWelcomeDialog()
{
	if (m_showWelcomeDialog)
	{
		WelcomeDialog w(this);
		connect(&w, &WelcomeDialog::setupSymbols, this, &MTuner::setupSymbols);
		connect(&w, &WelcomeDialog::readDocumentation, this, &MTuner::readDocumentation);
		w.exec();
		m_showWelcomeDialog = w.shouldShowNextTime();
	}
}

void MTuner::readSettings()
{
	QSettings settings;

	// MTuner main window
	settings.beginGroup("MainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());
	m_graphDock->restoreGeometry(settings.value("geometry0").toByteArray());
	m_statsDock->restoreGeometry(settings.value("geometry1").toByteArray());
	m_histogramDock->restoreGeometry(settings.value("geometry2").toByteArray());
	m_tagTreeDock->restoreGeometry(settings.value("geometry3").toByteArray());
	m_stackAndSourceDock->restoreGeometry(settings.value("geometry4").toByteArray());
	m_heapsDock->restoreGeometry(settings.value("geometry5").toByteArray());
	m_fileDialog->restoreState(settings.value("fileDialog").toByteArray());

	if (settings.contains("ShowWelcome"))
		m_showWelcomeDialog = settings.value("ShowWelcome").toBool();
	else
		m_showWelcomeDialog = true;

	if (settings.contains("geometry6"))
		m_symbolStore->restoreGeometry(settings.value("geometry6").toByteArray());

	if (settings.contains("stackTraceGeometry"))
	{
		StackAndSource* ss = (StackAndSource*)m_stackAndSourceDock->widget();
		StackTrace* st = ss->getStackTrace();
		st->loadState(settings);
	}

	settings.endGroup();

	settings.beginGroup("ToolBar");
	if (settings.contains("dockGraph"))
	ui.action_View_Memory_Graph->setChecked( settings.value("dockGraph").toBool() );
	if (settings.contains("dockHisto"))
	ui.action_View_Histograms->setChecked( settings.value("dockHisto").toBool() );
	if (settings.contains("dockStats"))
	ui.action_View_Memory_Stats->setChecked( settings.value("dockStats").toBool() );
	if (settings.contains("dockTagTr"))
	ui.action_View_Tag_Tree->setChecked( settings.value("dockTagTr").toBool() );
	if (settings.contains("dockHeaps"))
	ui.action_View_Heaps_Allocators->setChecked( settings.value("dockHeaps").toBool() );
	if (settings.contains("dockStack"))
	ui.action_View_StackTrace->setChecked( settings.value("dockStack").toBool() );
	settings.endGroup();

	//// language
	//if (settings.contains("language"))
	//	m_langManager.setLanguage(settings.value("language").toString());
	//else
	//	m_langManager.setLanguage(QLocale::system().name());

	// editor
	if (settings.contains("editorExe"))
	{
		m_externalEditor->setEditor(settings.value("editorExe").toString());
		m_externalEditor->setEditorArgs(settings.value("editorArgs").toString());
	}
	
	// Symbol store
	QString str;
	str = settings.value("SymLocalStore").toString();
	m_symbolStore->setLocalStore(str);
	str = settings.value("SymPublicStore").toString();
	m_symbolStore->setPublicStore(str);
	bool symReg = false;
	symReg = settings.value("SymRegistry").toBool();
	m_symbolStore->setChecked(symReg);

	// projects
	int numProjects = settings.beginReadArray("Projects");
	for (int i=0; i<numProjects; ++i)
	{
		settings.setArrayIndex(i);
		QString key = QString("Project") + QString::number(i);
		Project p;
		p.m_executablePath = settings.value(key + "Exe").toString();
		p.m_cmdArgs = settings.value(key + "Cmd").toString();
		p.m_workingDir = settings.value(key + "Dir").toString();
		m_projectsManager->addProject(p);
	}
	settings.endArray();

	// toolchains
	m_gccSetup->readSettings(settings);
}

void MTuner::writeSettings()
{
	QSettings settings;

	// MTuner main window
	settings.beginGroup("MainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());
	settings.setValue("geometry0", m_graphDock->saveGeometry());
	settings.setValue("geometry1", m_statsDock->saveGeometry());
	settings.setValue("geometry2", m_histogramDock->saveGeometry());
	settings.setValue("geometry3", m_tagTreeDock->saveGeometry());
	settings.setValue("geometry4", m_stackAndSourceDock->saveGeometry());
	settings.setValue("geometry5", m_heapsDock->saveGeometry());
	settings.setValue("geometry6", m_symbolStore->saveGeometry());
	settings.setValue("fileDialog",m_fileDialog->saveState());

	settings.setValue("ShowWelcome", m_showWelcomeDialog);

	StackAndSource* ss = (StackAndSource*)m_stackAndSourceDock->widget();
	StackTrace* st = ss->getStackTrace();
	st->saveState(settings);

	settings.endGroup();

	settings.beginGroup("ToolBar");
	settings.setValue("dockGraph", ui.action_View_Memory_Graph->isChecked());
	settings.setValue("dockHisto", ui.action_View_Histograms->isChecked());
	settings.setValue("dockStats", ui.action_View_Memory_Stats->isChecked());
	settings.setValue("dockHeaps", ui.action_View_Heaps_Allocators->isChecked());
	settings.setValue("dockTagTr", ui.action_View_Tag_Tree->isChecked());
	settings.setValue("dockStack", ui.action_View_StackTrace->isChecked());
	settings.endGroup();

	//// language
	//settings.setValue("language",m_langManager.language());

	// editor
	settings.setValue("editorExe", m_externalEditor->getEditorPath());
	settings.setValue("editorArgs", m_externalEditor->getEditorArgs());

	// Symbol store
	settings.setValue("SymLocalStore", m_symbolStore->getLocalStore());
	settings.setValue("SymPublicStore", m_symbolStore->getPublicStore());
	settings.setValue("SymRegistry", m_symbolStore->isRegistryChecked());

	// projects
	settings.beginWriteArray("Projects");
	int numProjects = m_projectsManager->getNumProjects();
	for (int i=0; i<numProjects; ++i)
	{
		settings.setArrayIndex(i);
		const Project& p = m_projectsManager->getProject(i);
		QString key = QString("Project") + QString::number(i);
		settings.setValue(key + "Exe", p.m_executablePath);
		settings.setValue(key + "Cmd", p.m_cmdArgs);
		settings.setValue(key + "Dir", p.m_workingDir);
	}
	settings.endArray();
	settings.sync();

	// toolchains
	m_gccSetup->writeSettings(settings);
}

void loadProgression(void* _customData, float _progress, const char* _message)
{
	MTuner* mt = (MTuner*)_customData;
	mt->setLoadingProgress(_progress, QString::fromUtf8(_message));
}

void MTuner::openFileFromPath(const QString& _file)
{
	QFileInfo info(_file);
	QString name = info.completeBaseName();

	if (_file.size() != 0)
	{
		CaptureContext* ctx = new CaptureContext();
		ctx->m_capture->setLoadProgressCallback(this, loadProgression);
		rtm_string fn;

		fn += _file.toUtf8().constData();

		// pass symbol store
		QString symStore = m_symbolStore->getSymbolStoreString();

		statusBar()->showMessage(tr("Loading, please wait..."));

		// load binary
		rtm::Capture::LoadResult res = ctx->m_capture->loadBin(fn.c_str());
		if (res != rtm::Capture::LoadFail)
		{
			if (res == rtm::Capture::LoadPartial)
			{
				QMessageBox msgInfo(QMessageBox::Information, tr("Capture loaded partially!"),tr("Capture file was only partially loaded!\nInformation may be missing from the profile!"), QMessageBox::Ok);
				msgInfo.setWindowIcon(this->windowIcon());
				msgInfo.exec();
			}

			// if not a windows toolchain - locate the executable
			setupLoaderToolchain(ctx, _file, m_gccSetup, m_fileDialog, this, symStore);

			ctx->m_capture->buildAnalyzeData(ctx->m_symbolResolver);

			QString ld(tr("Loaded "));

			statusBar()->showMessage(ld + QString::fromUtf8(fn.c_str()),3000);

			m_centralWidget->addTab(ctx, name);
		}
		else
		{
			statusBar()->showMessage(tr("Error loading!"),3000);
			QMessageBox info_dlg(QMessageBox::Information, tr("Failed to load file!"),tr("File may be corrupted, try to repeat the capture"), QMessageBox::Ok);
			info_dlg.setWindowIcon(this->windowIcon());
			info_dlg.exec();
			delete ctx;
		}
	}
}

void MTuner::dragEnterEvent(QDragEnterEvent* _event)
{
	const QMimeData* mimeData = _event->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urls = mimeData->urls();
		if (urls.size() == 1)
		{
			QUrl url = urls.at(0);

			bool accept = false;
			accept = accept || url.path().toLower().endsWith(".mtuner");
			accept = accept || url.path().toLower().endsWith(".exe");
			if (url.isValid() && (url.scheme().toLower() == "file") && accept && mimeData->hasFormat("text/uri-list"))
				_event->acceptProposedAction();
		}
	}
}

void MTuner::dragLeaveEvent(QDragLeaveEvent* _event)
{
	_event->accept();
}

void MTuner::dragMoveEvent(QDragMoveEvent* _event)
{
	_event->acceptProposedAction();
}

void MTuner::dropEvent(QDropEvent* _event)
{
	const QMimeData* mimeData = _event->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();

		Q_FOREACH(QUrl url, urlList)
		{
			QString filePath = url.toLocalFile();
			handleFile(filePath);
		}
	}
}

void MTuner::handleFile(const QString& _file)
{
	QString workdir = getDirFromFile(_file);

	if (_file.toLower().endsWith(".mtuner"))
		openFileFromPath(_file);

	if (_file.toLower().endsWith(".exe"))
	{
		if (m_capturePid)
		{
			QMessageBox message(QMessageBox::Information, tr("Capture in progress"), tr("Cannot start a new capture while capture is in progress"));
			message.exec();
		}
		else
			m_projectsManager->run(_file);
	}
}
