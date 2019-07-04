//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/loader/capture.h>
#include <MTuner/src/loader/util.h>
#include <rdebug/inc/rdebug.h>

namespace rtm {

static const char* g_LogBanner = "MTuner v1.0 analysis log file\nCopyright (c) 2019 by Milos Tosic\n\n";

//--------------------------------------------------------------------------
static inline const char* gGetStringFromOperation( uint16_t _op )
{
	switch (_op)
	{
		case rmem::LogMarkers::OpAlloc:				return "Alloc";
		case rmem::LogMarkers::OpRealloc:			return "Realloc";
		case rmem::LogMarkers::OpCalloc:			return "Calloc";
		case rmem::LogMarkers::OpFree:				return "Free";
		case rmem::LogMarkers::OpAllocAligned:		return "Alloc aligned";
		case rmem::LogMarkers::OpReallocAligned:	return "Realloc aligned";
	}
	return "";
}

//--------------------------------------------------------------------------
template <typename T>
static char* FormatNumber( T inNum, char ioBuff[128] )
{
	ioBuff[127] = '\0';
	int j = 126;
	T num = inNum;
	uint32_t i = 0;
	if (num)
	{
		while (num)
		{
			ioBuff[j--] = '0' + num%10;
			i++;
			if (((i%3) == 0) && (num>=10))
				ioBuff[j--] = ',';
			num /= 10;
		}
		return &ioBuff[j+1];
	}
	ioBuff[j] = '0';
	return &ioBuff[j];
}

template <typename T>
static wchar_t* FormatNumber( T inNum, wchar_t ioBuff[128] )
{
	ioBuff[127] = L'\0';
	int j = 126;
	T num = inNum;
	uint32_t i = 0;
	if (num)
	{
		while (num)
		{
			ioBuff[j--] = L'0' + num%10;
			i++;
			if (((i%3) == 0) && (num>=10))
				ioBuff[j--] = L',';
			num /= 10;
		}
		return &ioBuff[j+1];
	}
	ioBuff[j] = L'0';
	return &ioBuff[j];
}

//--------------------------------------------------------------------------
static inline void WriteStackFrame(FILE* inFile, rdebug::StackFrame& inSt)
{
	fprintf(inFile, "%s!%s",inSt.m_moduleName, inSt.m_func);

	if (inSt.m_line != 0)
		fprintf(inFile, " Line %d  %s\n",inSt.m_line, inSt.m_file);
	else
		fprintf(inFile, "\n");
}

//--------------------------------------------------------------------------
/// Writes global stats information to the file
//--------------------------------------------------------------------------
void	Capture::writeGlobalStats( FILE* inFile )
{
	char buffer[128];

	fprintf(inFile,"----------------------------------------\n");
	fprintf(inFile,"Memory usage            : %s\n", FormatNumber(m_statsGlobal.m_memoryUsage,buffer));
	fprintf(inFile,"Memory usage at peak    : %s\n", FormatNumber(m_statsGlobal.m_memoryUsagePeak,buffer));
	fprintf(inFile,"Overhead                : %s\n", FormatNumber(m_statsGlobal.m_overhead,buffer));
	fprintf(inFile,"Overhead at peak        : %s\n", FormatNumber(m_statsGlobal.m_overheadPeak,buffer));
	fprintf(inFile,"Number of operations    : %s\n", FormatNumber(m_statsGlobal.m_numberOfOperations,buffer));
	fprintf(inFile,"Number of allocations   : %s\n", FormatNumber(m_statsGlobal.m_numberOfAllocations,buffer));
	fprintf(inFile,"Number of reallocations : %s\n", FormatNumber(m_statsGlobal.m_numberOfReAllocations,buffer));
	fprintf(inFile,"Number of frees         : %s\n", FormatNumber(m_statsGlobal.m_numberOfFrees,buffer));
	fprintf(inFile,"Number of memory leaks  : %s\n", FormatNumber(m_statsGlobal.m_numberOfLiveBlocks,buffer));
	fprintf(inFile,"----------------------------------------\n");
}

//--------------------------------------------------------------------------
/// Saves information about all memory operations to the file
//--------------------------------------------------------------------------
bool Capture::saveLog(const char* _path, uintptr_t _symResolver )
{
	FILE* f = fopen(_path, "wt");
	if (!f)
		return false;

	fprintf(f,"%s",g_LogBanner);

	uint32_t size = (uint32_t)m_operations.size();

	writeGlobalStats(f);

	// write ops
	for (uint32_t i=0; i<size; i++)
	{
		MemoryOperation* opEx = m_operations[i];
		const char* opType = gGetStringFromOperation(opEx->m_operationType);

		fprintf(f, "\n%s  size: %d\n", opType, opEx->m_allocSize);

		StackTrace* trace = opEx->m_stackTrace;
	
		if (!trace)
		{
			fprintf(f, "No call stack");
			continue;
		}

		uint32_t numFrames = (uint32_t)trace->m_numEntries;
		for (uint32_t e=0; e<numFrames; e++)
		{
			rdebug::StackFrame st;
			symbolResolverGetFrame(_symResolver, trace->m_entries[e], &st);
			WriteStackFrame(f, st);
		}
	}
	
	fclose(f);
	return true;
}


static inline bool sortGroupByCount( const MemoryOperationGroup* inG1, const MemoryOperationGroup* inG2)
{
	return (inG1->m_operations.size() > inG2->m_operations.size());
}

static inline bool sortGroupBySize( const MemoryOperationGroup* inG1, const MemoryOperationGroup* inG2)
{
	const uint32_t allocSize1 = inG1->m_operations[0]->m_allocSize;
	const uint32_t allocSize2 = inG2->m_operations[0]->m_allocSize;
	return (allocSize1 > allocSize2);
}

static inline bool sortGroupByTotal( const MemoryOperationGroup* inG1, const MemoryOperationGroup* inG2)
{
	const uint32_t allocSize1 = inG1->m_operations[0]->m_allocSize;
	const uint64_t totalSize1 = allocSize1 * inG1->m_operations.size();
	const uint32_t allocSize2 = inG2->m_operations[0]->m_allocSize;
	const uint64_t totalSize2 = allocSize2 * inG2->m_operations.size();
	return (totalSize1 > totalSize2);
}

//--------------------------------------------------------------------------
/// Saves information about all memory operations to the file
//--------------------------------------------------------------------------
bool Capture::saveGroupsLog(const char* _path, eGroupSort _sorting, uintptr_t _symResolver )
{
	rtm_vector<MemoryOperationGroup*> sortedGroups;
	sortedGroups.reserve(m_operationGroups.size());

	MemoryGroupsHashType& srcGroups = m_filteringEnabled ? m_filter.m_operationGroups : m_operationGroups;
	MemoryGroupsHashType::iterator it = srcGroups.begin();
	MemoryGroupsHashType::iterator end = srcGroups.end();
	while (it != end)
	{
		sortedGroups.push_back(&it->second);
		++it;
	}

	switch (_sorting)
	{
		case GROUP_SORT_COUNT: std::stable_sort(sortedGroups.begin(), sortedGroups.end(), sortGroupByCount);
			break;
		case GROUP_SORT_SIZE: std::stable_sort(sortedGroups.begin(), sortedGroups.end(), sortGroupBySize);
			break;
		case GROUP_SORT_TOTAL_SIZE: std::stable_sort(sortedGroups.begin(), sortedGroups.end(), sortGroupByTotal);
			break;
	};

	FILE* f = fopen(_path, "wt");
	if (!f)
		return false;

	fprintf(f,"%s",g_LogBanner);

	uint32_t size = (uint32_t)sortedGroups.size();

	writeGlobalStats(f);

	// write ops
	for (uint32_t i=0; i<size; i++)
	{
		MemoryOperationGroup* group = sortedGroups[i];
		uint32_t numOps = (uint32_t)group->m_operations.size();

		MemoryOperation* opEx = group->m_operations[0];
		const char* opType = gGetStringFromOperation(opEx->m_operationType);

		fprintf(f, "\n%s  size: %d   group size: %d\n", opType, opEx->m_allocSize, opEx->m_allocSize*numOps);

		StackTrace* trace = opEx->m_stackTrace;
	
		if (!trace)
		{
			fprintf(f, "No call stack");
			continue;
		}

		uint32_t numFrames = (uint32_t)trace->m_numEntries;
		for (uint32_t e=0; e<numFrames; e++)
		{
			rdebug::StackFrame st;
			symbolResolverGetFrame(_symResolver, trace->m_entries[e], &st);
			WriteStackFrame(f, st);
		}
	}

	fclose(f);
	return true;
}

//--------------------------------------------------------------------------
/// Saves information about all memory operations to the file
//--------------------------------------------------------------------------
bool Capture::saveGroupsLogXML(const char* _path, eGroupSort _sorting, uintptr_t _symResolver)
{
	rtm_vector<MemoryOperationGroup*> sortedGroups;
	sortedGroups.reserve(m_operationGroups.size());

	MemoryGroupsHashType& srcGroups = m_filteringEnabled ? m_filter.m_operationGroups : m_operationGroups;
	MemoryGroupsHashType::iterator it = srcGroups.begin();
	MemoryGroupsHashType::iterator end = srcGroups.end();
	while (it != end)
	{
		sortedGroups.push_back(&it->second);
		++it;
	}

	switch (_sorting)
	{
		case GROUP_SORT_COUNT: std::stable_sort(sortedGroups.begin(), sortedGroups.end(), sortGroupByCount);
			break;
		case GROUP_SORT_SIZE: std::stable_sort(sortedGroups.begin(), sortedGroups.end(), sortGroupBySize);
			break;
		case GROUP_SORT_TOTAL_SIZE: std::stable_sort(sortedGroups.begin(), sortedGroups.end(), sortGroupByTotal);
			break;
	};

	FILE* f = fopen(_path, "wt");
	if (!f)
		return false;

	fprintf(f, "<?xml version=\"1.0\"?>\n");
	fprintf(f, "<MTuner File=\"");
	fprintf(f, "%s", m_loadedFile.c_str());
	fprintf(f, "\">\n");

	char buffer[128];
	fprintf(f, "    <Stats>\n");
	fprintf(f, "        <Usage>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_memoryUsage,buffer));
	fprintf(f, "</Usage>\n");

	fprintf(f, "        <Peak>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_memoryUsagePeak,buffer));
	fprintf(f, "</Peak>\n");

	fprintf(f, "        <Overhead>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_overhead,buffer));
	fprintf(f, "</Overhead>\n");

	fprintf(f, "        <OverheadPeak>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_overheadPeak,buffer));
	fprintf(f, "</OverheadPeak>\n");

	fprintf(f, "        <Operations>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_numberOfOperations,buffer));
	fprintf(f, "</Operations>\n");

	fprintf(f, "        <Allocations>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_numberOfAllocations,buffer));
	fprintf(f, "</Allocations>\n");

	fprintf(f, "        <Reallocations>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_numberOfReAllocations,buffer));
	fprintf(f, "</Reallocations>\n");

	fprintf(f, "        <Frees>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_numberOfFrees,buffer));
	fprintf(f, "</Frees>\n");

	fprintf(f, "        <Leaks>");
	fprintf(f, "%s", FormatNumber(m_statsGlobal.m_numberOfLiveBlocks,buffer));
	fprintf(f, "</Leaks>\n");

	fprintf(f, "    </Stats>\n");

	uint32_t size = (uint32_t)sortedGroups.size();

	// write ops
	for (uint32_t i=0; i<size; i++)
	{
		MemoryOperationGroup* group = sortedGroups[i];
		uint32_t numOps = (uint32_t)group->m_operations.size();

		MemoryOperation* opEx = group->m_operations[0];
		const char* opType = gGetStringFromOperation(opEx->m_operationType);

		fprintf(f, "    <Group>\n");
		fprintf(f, "        <Type>%s</Type>\n",opType);
		fprintf(f, "        <Size>%d</Size>\n",opEx->m_allocSize);
		fprintf(f, "        <GroupSize>%d</GroupSize>\n",opEx->m_allocSize*numOps);

		StackTrace* trace = opEx->m_stackTrace;

		if (!trace)
			continue;

		uint32_t numFrames = (uint32_t)trace->m_numEntries;
		for (uint32_t e=0; e<numFrames; e++)
		{
			rdebug::StackFrame st;
			symbolResolverGetFrame(_symResolver, trace->m_entries[e], &st);

			fprintf(f, "        <Frame>\n");
			fprintf(f, "            <Module>%s</Module>\n", st.m_moduleName);
			fprintf(f, "            <Func>%s</Func>\n", st.m_func);
			if (st.m_line != 0)
			{
				fprintf(f, "            <File>%s</File>\n", st.m_file);
				fprintf(f, "            <Line>%d</Line>\n", st.m_line);
			}
			else
			{
				fprintf(f, "            <File>Unknown</File>\n");
				fprintf(f, "            <Line>0</Line>\n");
			}
			fprintf(f, "        </Frame>\n");
		}

		fprintf(f, "    </Group>\n");
	}

	fprintf(f, "</MTuner>\n");
	fclose(f);

	return true;
}

} // namespace rtm
