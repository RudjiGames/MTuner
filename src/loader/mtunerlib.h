//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_MTUNERLIB_H__
#define __RTM_MTUNER_MTUNERLIB_H__

#include <rmem/src/rmem_enums.h>

namespace rtm {

bool mtunerLoaderInit(bool _MTuner = false);
bool mtunerLoaderShutDown();

struct StackTrace;
struct MemoryStatsLocalPeak;

class uint32_t_hash
{
public:	inline size_t operator() (const uint32_t _key) const { return (size_t)_key; }
};

class uintptr_t_hash
{
public:	inline size_t operator() (const uintptr_t _key) const { return (size_t)_key; }
};

class uint32_t_equal
{
public:	inline bool operator() (const uint32_t _key1, const uint32_t _key2) const { return _key1 == _key2; }
};

class uintptr_t_equal
{
public:	inline bool operator() (const uintptr_t _key1, const uintptr_t _key2) const { return _key1 == _key2; }
};

//--------------------------------------------------------------------------
/// Structure adding information on top of memory operation
//--------------------------------------------------------------------------
struct MemoryOperation
{
	uint64_t			m_allocatorHandle;		//< Allocator handle
	uint64_t			m_threadID;				//< Thread ID
	uint64_t			m_pointer;				//< Allocated/freed pointer
	uint64_t			m_previousPointer;		//< Valid for realloc operations
	MemoryOperation*	m_chainPrev;
	MemoryOperation*	m_chainNext;
	StackTrace*			m_stackTrace;
	uint64_t			m_operationTime;
	uint32_t			m_indexMapping;
	uint32_t			m_allocSize;
	uint32_t			m_overhead;
	uint16_t			m_tag;
	uint8_t				m_operationType : 7;
	uint8_t				m_isValid		: 1;
	uint8_t				m_alignment;
};

//--------------------------------------------------------------------------
/// Methods of sorting memory operations
//--------------------------------------------------------------------------
enum eOperationSort
{
	OP_SORT_POINTER,							///< Sort by pointer value
	OP_SORT_TIME								///< Sort by operation time
};

//--------------------------------------------------------------------------
/// Methods of sorting memory operation groups
//--------------------------------------------------------------------------
enum eGroupSort
{
	GROUP_SORT_COUNT,							///< Sort by number of operations in the group
	GROUP_SORT_SIZE,							///< Sort by size of the operation in the group
	GROUP_SORT_TOTAL_SIZE						///< Sort by total size (number*size) of the group
};

//--------------------------------------------------------------------------
/// Histogram data for a single bin (memory size range) - AOS
//--------------------------------------------------------------------------
struct HistogramBin
{
	uint64_t	m_size;							///< Memory usage at the end of time slice
	uint64_t	m_sizePeak;						///< Peak memory usage inside the time slice
	uint32_t	m_overhead;						///< Overhead at the end of time slice
	uint32_t	m_overheadPeak;					///< Peak overhead inside the time slice
	uint32_t	m_count;						///< Number of surviving memory blocks at the end of time slice
	uint32_t	m_countPeak;					///< Peak number of live blocks inside the time slice
};

//--------------------------------------------------------------------------
/// We need additional information for quick searches
//--------------------------------------------------------------------------
struct MemoryStats
{
	enum { 
		MIN_HISTOGRAM_SIZE	= 8,
		HISTOGRAM_BIN_SHIFT	= 3,				///< 3 bits for minimum of 8 bytes
		NUM_HISTOGRAM_BINS	= 23				///< up to 8 bytes to 32M+
	}; 

	uint64_t		m_memoryUsage;				///< Memory usage at the end of time slice
	uint64_t		m_memoryUsagePeak;			///< Peak memory usage inside the time slice
	uint32_t		m_overhead;					///< Allocation overhead at the end of time slice
	uint32_t		m_overheadPeak;				///< Peak allocation overhead inside the time slice
	uint32_t		m_numberOfOperations;		///< Number of operations inside the time slice
	uint32_t		m_numberOfAllocations;		///< Number of allocations inside the time slice
	uint32_t		m_numberOfReAllocations;	///< Number of reallocations inside the time slice
	uint32_t		m_numberOfFrees;			///< Number of frees inside the time slice
	uint32_t		m_numberOfLiveBlocks;		///< Memory blocks allocated but not freed inside the time slice - Memory leaks!
	uint32_t		m_numberOfLiveBlocksPeak;
	HistogramBin	m_histogram[NUM_HISTOGRAM_BINS];

	void reset()
	{
		memset(this,0,sizeof(MemoryStats));
	}

	void setPeaksToCurrent();
	void setPeaksFrom(MemoryStatsLocalPeak& _peaks);
};

//--------------------------------------------------------------------------
/// Group of memory operations
//--------------------------------------------------------------------------
struct MemoryOperationGroup
{
	enum { INDEX_MAPPINGS = 11 };

	uint32_t						m_minSize;			// single allocation size
	uint32_t						m_maxSize;			// single allocation size
	int64_t							m_peakSize;			// group size
	int64_t							m_peakSizeGlobal;	// total memory usage at the time of group peak size
	int64_t							m_liveSize;			// group size
	uint32_t						m_count;
	uint32_t						m_liveCount;
	uint32_t						m_liveCountPeak;
	uint32_t						m_liveCountPeakGlobal;
	rtm_vector<MemoryOperation*>	m_operations;
	uint32_t						m_indexMappings[INDEX_MAPPINGS];
	uint32_t						m_histogram[rtm::MemoryStats::NUM_HISTOGRAM_BINS];
	uint32_t						m_histogramPeak[rtm::MemoryStats::NUM_HISTOGRAM_BINS];

	inline MemoryOperationGroup()
		: m_minSize(0xffffffff)
		, m_maxSize(0)
		, m_peakSize(0)
		, m_liveSize(0)
		, m_count(0)
		, m_liveCount(0)
		, m_liveCountPeak(0)
		, m_liveCountPeakGlobal(0)
	{
		for (int i=0; i<rtm::MemoryStats::NUM_HISTOGRAM_BINS; i++)
		{
			m_histogram[i] = 0;
			m_histogramPeak[i] = 0;
		}
	}
};

//--------------------------------------------------------------------------
/// Helper structure storing peak values of a histogram bin
//--------------------------------------------------------------------------
struct HistogramBinPeak
{
	uint64_t	m_sizePeak;
	uint32_t	m_overheadPeak;
	uint32_t	m_countPeak;
};

//--------------------------------------------------------------------------
/// Helper structure storing local peak values of a time range
//--------------------------------------------------------------------------
struct MemoryStatsLocalPeak
{
	uint64_t			m_memoryUsagePeak;
	uint32_t			m_overheadPeak;
	uint32_t			m_numberOfLiveBlocksPeak;
	HistogramBinPeak	m_HistogramPeak[MemoryStats::NUM_HISTOGRAM_BINS];
};

//--------------------------------------------------------------------------
/// Structure used for quick calculations of snapshot timelines/histograms
//--------------------------------------------------------------------------
struct MemoryStatsTimed
{
	uint64_t				m_time;
	uint32_t				m_operationIndex;
	MemoryStatsLocalPeak	m_localPeak;
	MemoryStats				m_stats;
};

//--------------------------------------------------------------------------
/// Structure representing a single call stack
//--------------------------------------------------------------------------
struct StackTrace
{
	enum Scope
	{
		Global,
		Filtered
	};

	uint32_t		m_numFrames;
	int16_t			m_addedToTree[2];
	uint64_t		m_frames[1];

	static uint32_t		calculateSize(uint32_t numFrames);
	static void			init(StackTrace* st, uint32_t numFrames);
	static uint16_t*	getIndexArray(StackTrace* st);
	static StackTrace** getNextArray(StackTrace* st);
};

//--------------------------------------------------------------------------
/// Stack trace tree
//--------------------------------------------------------------------------
struct StackTraceTree
{
	typedef rtm_vector<StackTraceTree>	ChildNodes;

	enum Enum
	{
		Alloc,
		Free,
		Realloc,

		Count
	};

	uint64_t			m_addressID;
	int64_t				m_memUsage;
	int64_t				m_memUsagePeak;
	int32_t				m_overhead;
	int32_t				m_overheadPeak;
	int32_t				m_depth;
	int32_t				m_opCount[StackTraceTree::Count];
	StackTraceTree*		m_parent;
	StackTrace*			m_stackTraceList;
	ChildNodes			m_children;
	
	inline StackTraceTree() : 
		m_addressID(0),
		m_memUsage(0),
		m_memUsagePeak(0), 
		m_overhead(0),
		m_overheadPeak(0),
		m_depth(0),
		m_parent(NULL),
		m_stackTraceList(NULL)
	{
		memset(&m_opCount[0], 0, sizeof(int32_t)*StackTraceTree::Count);
	}
};

void destroyStackTree( StackTraceTree& _tree );

//--------------------------------------------------------------------------
/// Memory tag tree
//--------------------------------------------------------------------------
struct MemoryTagTree
{
	typedef rtm_unordered_map<uint32_t,MemoryTagTree*>	ChildMap;
	typedef rtm_vector<MemoryOperation*>				OpList;

	rtm_string			m_name;
	uint32_t			m_hash;
	uint64_t			m_usage;
	uint64_t			m_usagePeak;
	uint64_t			m_overhead;
	uint64_t			m_overheadPeak;
	uint32_t			m_operationCount[rmem::LogMarkers::OpCount];
	MemoryTagTree*		m_parent;
	ChildMap			m_children;
	OpList				m_operations;

	inline MemoryTagTree()
	{
		m_name			= "";
		m_hash			= 0;
		m_usage			= 0;
		m_usagePeak		= 0;
		m_overhead		= 0;
		m_overheadPeak	= 0;
		m_parent		= NULL;

		for (uint32_t i=0; i<rmem::LogMarkers::OpCount; i++)
			m_operationCount[i] = 0;
	}
};

bool tagFind(MemoryTagTree& _rootTag, uint32_t _hash, MemoryTagTree*& ioResult, MemoryTagTree*& _prevTag);
bool tagInsert(MemoryTagTree* _rootTag, MemoryTagTree* _tag, uint32_t _parentTagHash);
void tagTreeDestroy(MemoryTagTree& _rootTag);
void tagAddOp(MemoryTagTree& _rootTag, MemoryOperation* _op, MemoryTagTree*& _prevTag);

struct MemoryMarkerEvent
{
	rtm_string			m_name;
	uint32_t			m_nameHash;
	uint32_t			m_color;
};

struct MemoryMarkerTime
{
	uint64_t			m_threadID;
	uint64_t			m_time;
	MemoryMarkerEvent*	m_event;
};

} // namespace rtm

#endif // __RTM_MTUNER_MTUNERLIB_H__
