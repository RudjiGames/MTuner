//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/mtuner.h>
#include <MTuner/src/gcc.h>
#include <MTuner/src/version.h>
#include <MTuner/src/capturecontext.h>
#include <rbase/inc/cmdline.h>
#include <MTuner/src/loader/util.h>

#include <rqt/inc/rqt.h>
#include <rqt/inc/rqt_widget_assert.h>

#if RTM_PLATFORM_WINDOWS
#include "shellapi.h"
#if RTM_COMPILER_MSVC
#include <DIA/include/diacreate.h>
#include <DIA/include/dia2.h>
#endif
#endif // RTM_PLATFORM_WINDOWS

static const char* g_banner = "Copyright (c) 2025 by Milos Tosic. All rights reserved.\n";

void setupLoaderToolchain(CaptureContext* _context, const QString& _file, GCCSetup* inGCCSetup, 
							QFileDialog* _fileDialog, MTuner* _MTuner, const QString& _symSource, rdebug::module_load_cb _callBack);

extern void getStoragePath(wchar_t _path[512]);

void err(const char* _message)
{
	rtm::Console::error(_message);
	exit(1);
}

bool handleInject(rtm::CommandLine& _cmdLine)
{
	const char* profileExeConst	= nullptr;
	const char* profileWorkDir	= nullptr;
	const char* profileCmdArgs	= nullptr;

	if (!_cmdLine.getArg('p', profileExeConst))
		return false;

	char profileExe[1024];
	rtm::strlCpy(profileExe, 1024, profileExeConst);
	rtm::pathCanonicalize(profileExe);

	_cmdLine.getArg('w', profileWorkDir);
	_cmdLine.getArg('c', profileCmdArgs);

	const char* MTunerDirConst = _cmdLine.getArg(0);
	char MTunerDir[1024];
	rtm::strlCpy(MTunerDir, 1024, MTunerDirConst);
	rtm::pathCanonicalize(MTunerDir);

	char* exePos = MTunerDir + rtm::strLen(MTunerDir) - 1;
	while ((*exePos != '/') && (*exePos != '\\')) exePos--;
	exePos[1] = L'\0';

	char workingDir[512];
	if (profileWorkDir == nullptr)
	{
		rtm::strlCpy(workingDir, 512, profileExe);
		size_t end = strlen(workingDir) - 1;
		while ((workingDir[end] != '/') && (workingDir[end] != '\\')) --end;
		workingDir[end+1] = '\0';
	}
	else
		rtm::strlCpy(workingDir, 512, profileWorkDir);
	rtm::pathCanonicalize(workingDir);

	char cmdArgs[512];
	if (profileCmdArgs == nullptr)
		strcpy(cmdArgs, "");
	else
		strcpy(cmdArgs, profileCmdArgs);

	char inject32[512];
	char inject64[512];
	rtm::strlCpy(inject32, 512, MTunerDir);
	rtm::strlCpy(inject64, 512, MTunerDir);
	rtm::strlCat(inject32, 512, "MTunerInject32.exe");
	rtm::strlCat(inject64, 512, "MTunerInject64.exe");

	char cmdLine32[4096];
	rtm::strlCpy(cmdLine32, 4096, "\"");
	rtm::strlCat(cmdLine32, 4096, inject32);
	rtm::strlCat(cmdLine32, 4096, "\" #23#");
	rtm::strlCat(cmdLine32, 4096, profileExe);
	rtm::strlCat(cmdLine32, 4096, "#23# #23#");
	rtm::strlCat(cmdLine32, 4096, cmdArgs);
	rtm::strlCat(cmdLine32, 4096, "#23# #23#");
	rtm::strlCat(cmdLine32, 4096, workingDir);
	rtm::strlCat(cmdLine32, 4096, "#23#");

	char cmdLine64[4096];
	rtm::strlCpy(cmdLine64, 4096, "\"");
	rtm::strlCat(cmdLine64, 4096, inject64);
	rtm::strlCat(cmdLine64, 4096, "\" #23#");
	rtm::strlCat(cmdLine64, 4096, profileExe);
	rtm::strlCat(cmdLine64, 4096, "#23# #23#");
	rtm::strlCat(cmdLine64, 4096, cmdArgs);
	rtm::strlCat(cmdLine64, 4096, "#23# #23#");
	rtm::strlCat(cmdLine64, 4096, workingDir);
	rtm::strlCat(cmdLine64, 4096, "#23#");

	rdebug::processRun(cmdLine32);
	rdebug::processRun(cmdLine64);

	return true;
}

void resolverCallBack(const char* _name, void* _customData)
{
	MTuner* mt = (MTuner*)_customData;

	mt->statusBar()->showMessage(QString("Loading symbols for: ") + QString(_name), 2300);
	mt->statusBar()->repaint();
}

int handleCommandLine(int argc, char const* argv[])
{
	rtm::Console::print("%s",g_banner);

	rtm::CommandLine cmdLine(argc, argv);

	QSettings settings;
	GCCSetup gcc_setup;
	gcc_setup.readSettings(settings);

	int numToolchains = 0;

	if (cmdLine.hasArg("help"))
	{
		rtm::Console::print(
			"\nUsage: MTuner.com [OPTION] -i <input file> -o <output file>\nOptions:\n"
			"   -help       Prints this message\n"
			"   -p [EXE]    Specify executable to instrument and start profiling for\n"
			"   -s [FILE]   Specify symbol source for GCC based toolchains\n"
			"   -w [PATH]   Working directory for instrumented executable\n"
			"   -c [ARGS]   Command line arguments for the instrumented executable\n"
			"   -i [FILE]   Specify input (.MTuner) file\n"
			"   -o [FILE]   Specify output file with profile results\n"
			"   -l          Outputs only live allocations (leaks)\n"
			"   -tag [TAG]  Filter operations by tag\n"
			"   -h [SIZE]   Filter operations by size, operations are filtered by being\n"
			"               between the next and previous power of two nearest to given\n"
			"               size. For input size of 192 operations with sizes between\n"
			"               128 and 256 will be included.\n"
			"   -ts [TIME]  Set start (minimum) time for operation filtering\n"
			"   -te [TIME]  Set end (maximum) time for operation filtering\n"
			"   -ss         Sort memory operations by size\n"
			"   -sc         Sort memory operations by count\n"
			"   -st         Sort memory operations by size*count\n"
			"   -xml        Output as XML file\n"
			"\n");

			int numTCs = gcc_setup.getNumToolchains();
			for (int i=0; i<numTCs; ++i)
			{
				const Toolchain& tc = gcc_setup.getToolchain(i);
				if (gcc_setup.isConfigured(tc.m_toolchain, true))
				{
					QByteArray nameUTF8 = tc.m_name.toUtf8();
					if (numToolchains == 0)
						rtm::Console::print("Properly configured GCC toolchains:\n");
					rtm::Console::print("   ");
					numToolchains++;
					if (tc.m_toolchain == rmem::ToolChain::PS3_gcc)
						rtm::Console::print("Playstation 3 GCC");
					else
					{
						rtm::Console::print(nameUTF8.data());
						rtm::Console::print(" 64bit");
					}
					rtm::Console::print("\n");
				}

				if (gcc_setup.isConfigured(tc.m_toolchain, false))
				{
					QByteArray nameUTF8 = tc.m_name.toUtf8();
					if (numToolchains == 0)
						rtm::Console::print("Properly configured GCC toolchains:\n");
					rtm::Console::print("   ");
					numToolchains++;
					if (tc.m_toolchain == rmem::ToolChain::PS3_gcc)
						rtm::Console::print("Playstation 3 SNC");
					else
					{
						rtm::Console::print(nameUTF8.data());
						rtm::Console::print(" 32bit");
					}
					rtm::Console::print("\n");
				}
			}

			if (numToolchains == 0)
				rtm::Console::print("No GCC toolchains have been configured!\n"
				"Symbols may not be resolved for captures made with non MSVC based executables!\n");

			rtm::Console::print("\n"
			"Examples:\n"
			"   MTuner.com: -l -xml -tag \"Tag name\" -h 256 -i \"Capture.MTuner\" -o \"Log.xml\"\n"
			"   MTuner.com: -p \"D:\\Project Dir\\bin\\ProjectExe.exe\"\n"
		);
		
		return 0;
	}

	const char* profileExe = nullptr;
	if (cmdLine.getArg('p', profileExe))
	{
#if RTM_PLATFORM_WINDOWS
		wchar_t capturePath[512];
		getStoragePath( capturePath );
		wcscat(capturePath, L"\\MTuner\\");
		rtm::Console::print("\nCapture location: %s\n", rtm::WideToMulti(capturePath));
#endif
		handleInject(cmdLine);
		return 0;
	}
	
	const char* filePath = nullptr;
	char inFilePath[1024];
	if (!cmdLine.getArg('i', filePath))
	{
		err("ERROR: Input file must be specified!");
	}
	else
	{
#if RTM_PLATFORM_WINDOWS
		if ((strstr(filePath, "/") == 0) && (strstr(filePath, "\\") == 0))
		{
			wchar_t inFilePathW[1024];
			GetCurrentDirectoryW(1024, inFilePathW);
			strcpy(inFilePath, rtm::WideToMulti(inFilePathW));
			strcat(inFilePath, "\\");
			strcat(inFilePath, filePath);
		}
		else
#endif
			strcpy(inFilePath, filePath);
	}
	
	const char* symSource = nullptr;
	cmdLine.getArg('s', symSource);

	const char* outFilePath = nullptr;;
	if (!cmdLine.getArg('o', outFilePath))
	{
		err("ERROR: Output file must be specified!");
	} 

	bool sortBySize  = cmdLine.hasArg("ss");
	bool sortByCount = cmdLine.hasArg("sc");
	bool sortByTotal = cmdLine.hasArg("st");

	int numSorts = 0;
	numSorts += sortBySize  ? 1 : 0;
	numSorts += sortByCount ? 1 : 0;
	numSorts += sortByTotal ? 1 : 0;
	if (numSorts > 1)
	{
		err("ERROR: Only one sorting method can be specified!");
	}
	
	bool enableFiltering = false;

	uint32_t tagHash = 0;
	const char* tag = nullptr;
	if (cmdLine.getArg("tag", tag))
	{
		tagHash = rtm::hashStr(tag);
		enableFiltering = true;
	}

	uint32_t binIndex = 0xffffffff;
	const char* histogram = nullptr;
	if (cmdLine.getArg('h', histogram))
	{
		int size = atoi(histogram);
		binIndex = rtm::getHistogramBinIndex(size);
		enableFiltering = true;
	}

	float timeMin = -1.0f;
	const char* timeMinArg = nullptr;
	if (cmdLine.getArg("ts", timeMinArg))
	{
		timeMin = (float)atof(timeMinArg);
		enableFiltering = true;
	}

	float timeMax = -1.0f;
	const char* timeMaxArg = nullptr;
	if (cmdLine.getArg("te", timeMaxArg))
	{
		timeMax = (float)atof(timeMaxArg);
		enableFiltering = true;
	}

	bool leakedOnly = cmdLine.hasArg("l");
	enableFiltering = enableFiltering || leakedOnly;

	bool doXML = cmdLine.hasArg("xml");
	
	rtm::mtunerLoaderInit(false);

	{
		CaptureContext context;

		if (context.m_capture->loadBin(inFilePath) == rtm::Capture::LoadResult::LoadSuccess)
		{
			setupLoaderToolchain(&context, inFilePath, &gcc_setup, nullptr, nullptr,  symSource ? QString(symSource) : QString(""), resolverCallBack);

			rtm::Console::debug("Building analysis data...\n");
			context.m_capture->buildAnalyzeData(context.m_symbolResolver);

			if (enableFiltering)
			{
				rtm::Console::debug("Filtering enabled\n");

				context.m_capture->setLeakedOnly(leakedOnly);

				if (binIndex != 0xffffffff)
					context.m_capture->selectHistogramBin(binIndex);

				if (tagHash != 0)
					context.m_capture->selectTag(tagHash);

				if ((timeMin != -1.0f) || (timeMax != -1.0f))
				{
					uint64_t minTimeFilter = context.m_capture->getMinTime();
					uint64_t maxTimeFilter = context.m_capture->getMaxTime();
					uint64_t minTimeClocks = context.m_capture->getClocksFromTime(timeMin);
					uint64_t maxTimeClocks = context.m_capture->getClocksFromTime(timeMax);

					if ((minTimeClocks > maxTimeFilter) || (maxTimeClocks < minTimeFilter))
						err("ERROR: input time is out of range!");

					if ((timeMin != -1.0f) && (minTimeClocks > minTimeFilter))
						minTimeFilter = minTimeClocks;

					if ((timeMax != -1.0f) && (maxTimeClocks < maxTimeFilter))
						maxTimeFilter = maxTimeClocks;

					if (minTimeFilter > maxTimeFilter)
						err("ERROR: minimum time must be smaller than maximum time!");

					context.m_capture->setSnapshot(minTimeFilter, maxTimeFilter);
					rtm::Console::debug("Calculating filtered info...\n");
					context.m_capture->setFilteringEnabled(true);
				}
			}

			rtm::eGroupSort sorting = rtm::GROUP_SORT_SIZE;
			if (sortByCount)
				sorting = rtm::GROUP_SORT_COUNT;

			if (sortByTotal)
				sorting = rtm::GROUP_SORT_TOTAL_SIZE;

			if (doXML)
			{
				if (!context.m_capture->saveGroupsLogXML(outFilePath, sorting, context.m_symbolResolver))
				{
					err("ERROR: Could not save output XML file!");
				}
			}
			else
			if (!context.m_capture->saveGroupsLog(outFilePath, sorting, context.m_symbolResolver))
			{
				err("ERROR: Could not save output file!");
			}
		}
		else
		{
			err("ERROR: Could not load input file!");
		}
	}

	rtm::mtunerLoaderShutDown();
	return 0;
}

namespace mtuner {
bool init(rtmLibInterface* _libInterface);
void shutDown();
}

int main(int argc, const char* argv[])
{
#ifdef Q_OS_WIN
	SetProcessDPIAware(); // call before the main event loop
#endif // Q_OS_WIN 

#if QT_VERSION < QT_VERSION_CHECK(5,6,0)
	qputenv("QT_DEVICE_PIXEL_RATIO", QByteArray("1"));
#endif // QT_VERSION

	rtm::mtunerLoaderInit(true);
	int ret = 0;

	wchar_t path[512];
	getStoragePath( path );
	wcscat(path, L"\\");
	QDir dirAppData;
	dirAppData.mkdir(QString::fromUtf16((const char16_t*)path));
	wcscat(path, L"MTuner\\");
	dirAppData.mkdir(QString::fromUtf16((const char16_t*)path));

	RQtErrorHandler error;
	rtmLibInterface libInterface;
	libInterface.m_error = &error;

	QApplication app(argc, (char**)argv);
	rqt::init(&libInterface);
	mtuner::init(&libInterface);
	rqt::appInit(&app, rqt::AppStyle::RTM);

	app.setApplicationName("MTuner");
	app.setApplicationVersion(MTunerVersion);

#if RTM_PLATFORM_WINDOWS
#if RTM_DEBUG
	// Setup SYMSRV_DBGOUT to enable debug log of symsrv.dll
	SetEnvironmentVariableW(L"SYMSRV_DBGOUT", L"1");
#endif
	// DIA registration hack!
	QDir dir(QString::fromUtf8(argv[0]));
	dir.makeAbsolute();
	dir.cdUp();
	QString mtuner_dir = dir.absolutePath();
	
	QString regArg = mtuner_dir + "/msdia140.dll";
	QFileInfo info(regArg);

	bool skipDiaRegister = false;
#if RTM_COMPILER_MSVC
	void* ptr;
	HRESULT hr = NoRegCoCreate(L"msdia140.dll", __uuidof(DiaSource), __uuidof(IDiaDataSource), &ptr);
	if(SUCCEEDED(hr))
		skipDiaRegister = true;
#endif // RTM_COMPILER_MSVC

	if (info.exists() && !skipDiaRegister)
	{
		regArg.replace("/","\\");
		regArg = "/s \"" + regArg + "\"";

		SHELLEXECUTEINFOW shExecInfo;
		shExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);

		wchar_t diaPathW[512];
		regArg.toWCharArray(diaPathW);
		diaPathW[regArg.length()] = 0;

		shExecInfo.fMask		= 0;
		shExecInfo.hwnd			= nullptr;
		shExecInfo.lpVerb		= L"runas";
		shExecInfo.lpFile		= L"regsvr32";
		shExecInfo.lpParameters	= diaPathW;
		shExecInfo.lpDirectory	= nullptr;
		shExecInfo.nShow		= SW_MAXIMIZE;
		shExecInfo.hInstApp		= nullptr;

		if (!ShellExecuteExW(&shExecInfo))
		{
			QMessageBox regFail(QMessageBox::Warning, QObject::tr("Failed to register DIA dll!"), QObject::tr("Debug symbols may not be loaded correctly"));
		}
	}
#endif

	//--------------------------------------------------------------------------
	// Check in which mode to run
	//--------------------------------------------------------------------------
	bool guiMode = true;
	if (argc > 1)
	{
		for (int i=1; i<argc; ++i)
		{
			char buffer[1024];
			strcpy(buffer, argv[i]);
			rtm::strToUpper(buffer);
			if ((strstr(buffer, ".MTUNER") == 0) && (strstr(buffer, ".EXE") == 0))
			{
				guiMode = false;
				break;
			}
		}
	}

	if (!guiMode)
		ret = handleCommandLine(argc, argv);
	else
	{
		QStringList list;
		list << "resources/fonts/Maven Pro Bold.otf" << "resources/fonts/Maven Pro Medium.otf" << "resources/fonts/Maven Pro Regular.otf";

		for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator) {
			QFile res(":MTuner/" + *constIterator);
			if (res.open(QIODevice::ReadOnly))
			{
				QByteArray ar = res.readAll();
				int fontID = QFontDatabase::addApplicationFontFromData(ar);
				if (fontID == -1)
				{
				}
			}
		}

		MTuner mtuner;
		rqt::appLocalize(&mtuner, mtuner.getLanguageParentMenu(), "MTuner_");

		mtuner.show();

		if (argc > 1)
		{
			for (int files=1; files<argc; files++)
			{
				QString file = QString::fromUtf8(argv[files]);
				mtuner.handleFile(file);
			}
		}
		ret = app.exec();
	}

	rtm::mtunerLoaderShutDown();
	mtuner::shutDown();
	rqt::shutDown();
	return ret;
}
