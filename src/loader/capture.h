//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_CAPTURE_H__
#define __RTM_MTUNER_CAPTURE_H__

#include <rdebug/inc/rdebug.h>
#include <rbase/inc/cpu.h>

namespace rtm {

class BinLoader;

//--------------------------------------------------------------------------

typedef void (*LoadProgress)(void* inCustomData, float inProgress, const char* inMessage);

typedef rtm_unordered_map<uint32_t,  StackTrace*,uint32_t_hash,uint32_t_equal>				StackTraceHashType;
typedef rtm_unordered_map<uintptr_t, MemoryOperationGroup,uintptr_t_hash,uintptr_t_equal>	MemoryGroupsHashType;
typedef rtm_unordered_map<uint32_t,  MemoryMarkerEvent,uint32_t_hash,uint32_t_equal>		MemoryMarkersHashType;
typedef rtm_unordered_map<uint64_t,  rtm_string>											HeapsType;

//--------------------------------------------------------------------------
struct GraphEntry
{
	uint64_t	m_usage			: 37;	// 128 GB max
	uint64_t	m_numLiveBlocks	: 27;	// 128 * 1024 * 1024 M live blocks max
};

//--------------------------------------------------------------------------
/// Memory operation filter description
//--------------------------------------------------------------------------
struct FilterDescription
{
	uint32_t						m_histogramIndex;
	uint32_t						m_tagHash;
	uint64_t						m_threadID;
	uint64_t						m_minTimeSnapshot;
	uint64_t						m_maxTimeSnapshot;
	MemoryTagTree					m_tagTree;
	rtm_vector<MemoryOperation*>	m_operations;
	MemoryGroupsHashType			m_operationGroups;
	StackTraceTree					m_stackTraceTree;
	bool							m_leakedOnly;
};

//--------------------------------------------------------------------------
/// Memory tracking binary file loader
//--------------------------------------------------------------------------
class Capture
{
	private:
		rtm_string						m_loadedFile;			///< Symbol store path
		bool							m_swapEndian;
		bool							m_64bit;
		rmem::ToolChain::Enum			m_toolchain;
		ChunkAllocator<MemoryOperation> m_operationPool;
		StackAllocator					m_stackPool;
		rtm_vector<MemoryOperation*>	m_operations;
		rtm_vector<MemoryOperation*>	m_operationsInvalid;

		MemoryStats						m_statsGlobal;			///< Memory statistics for global range
		MemoryStats						m_statsSnapshot;		///< Memory statistics for selected snapshot
		rtm_vector<MemoryStatsTimed>	m_timedStats;

		rtm_vector<rdebug::ModuleInfo>	m_moduleInfos;			///< Module information data
		char*							m_modulePathBuffer;
		uint32_t						m_modulePathBufferPtr;

		StackTraceHashType				m_stackTracesHash;			///< map of stack traces, key is a stack trace hash
		rtm_vector<StackTrace*>			m_stackTraces;

		MemoryGroupsHashType			m_operationGroups;
		rtm_vector<GraphEntry>			m_usageGraph;			///< memory usage graph data
		StackTraceTree					m_stackTraceTree;		///< stack trace tree
		MemoryTagTree					m_tagTree;		///< Global tag tree
		MemoryMarkersHashType			m_memoryMarkers;
		HeapsType						m_Heaps;
		uint64_t						m_currentHeap;
		rdebug::ModuleInfo*				m_currentModule;
		rtm_vector<MemoryMarkerTime>	m_memoryMarkerTimes;
		uint64_t						m_CPUFrequency;
		rtm_vector<MemoryOperation*>	m_memoryLeaks;			/// List of allocations without matching free
		LoadProgress					m_loadProgressCallback;
		void*							m_loadProgressCustomData;
		
		uint64_t						m_minTime;
		uint64_t						m_maxTime;

		bool							m_filteringEnabled;
		FilterDescription				m_filter;

	public:

		enum LoadResult
		{
			LoadSuccess,
			LoadFail,
			LoadPartial
		};

		Capture();
		~Capture();

		LoadResult loadBin(const char* _path);
		void setLoadProgressCallback(void* _cd, LoadProgress _cb) { m_loadProgressCustomData = _cd; m_loadProgressCallback = _cb; }
		void clearData();
		bool is64bit() { return m_64bit; }
		void buildAnalyzeData(uintptr_t _symResolver);

		rtm_vector<rdebug::ModuleInfo>&	getModuleInfos() { return m_moduleInfos; }

		/// Capture file logging functions
		bool			saveLog(const char* _path, uintptr_t _symResolver);
		bool			saveGroupsLog(const char* _path, eGroupSort _sorting, uintptr_t _symResolver);
		bool			saveGroupsLogXML(const char* _path, eGroupSort _sorting, uintptr_t _symResolver);

		/// Capture file filtering functions
		void			setFilteringEnabled(bool inState);
		bool			getFilteringEnabled() const { return m_filteringEnabled; }
		bool			isInFilter(MemoryOperation* _op);
		void			selectHistogramBin(uint32_t _index);
		uint32_t		getSelectHistogramBin() const { return m_filter.m_histogramIndex; }
		void			deselectHistogramBin();
		void			selectTag(uint32_t _tagHash);
		void			deselectTag();
		void			selectThread(uint64_t _threadID);
		void			deselectThread();
		void			setLeakedOnly(bool _leaked);
		void			setSnapshot(uint64_t _minTime, uint64_t _maxTime);
		uint64_t		getSnapshotTimeMin() const { return m_filter.m_minTimeSnapshot; }
		uint64_t		getSnapshotTimeMax() const { return m_filter.m_maxTimeSnapshot; }
		
		uint64_t							getMinTime() const { return m_minTime; }
		uint64_t							getMaxTime() const { return m_maxTime; }
		float								getFloatTime(uint64_t _time) { return CPU::time(_time, m_CPUFrequency); }
		uint64_t							getClocksFromTime(float _time) { return (uint64_t)(_time*m_CPUFrequency); }
		const MemoryStats&					getGlobalStats() const { return m_statsGlobal; }
		const MemoryStats&					getSnapshotStats() const { return m_statsSnapshot; }
		void								getGraphAtTime(uint64_t _time, GraphEntry& _entry);
		const rtm_vector<MemoryMarkerTime>& getMemoryMarkers() const { return m_memoryMarkerTimes; }
		const MemoryTagTree&				getTagTree() const { return m_tagTree; }
		const StackTraceTree&				getStackTraceTree() const { return m_stackTraceTree; }
		const StackTraceTree&				getStackTraceTreeFiltered() const { return m_filter.m_stackTraceTree; }
		const rtm_vector<MemoryOperation*>& getMemoryOps() const { return m_operations; }
		const rtm_vector<MemoryOperation*>& getMemoryOpsInvalid() const { return m_operationsInvalid; }
		const rtm_vector<MemoryOperation*>& getMemoryOpsFiltered() const { return m_filter.m_operations; }
		const MemoryGroupsHashType&			getMemoryGroups() const { return m_operationGroups; }
		const MemoryGroupsHashType&			getMemoryGroupsFiltered() const { return m_filter.m_operationGroups; }
		rmem::ToolChain::Enum				getToolchain() { return m_toolchain; }
		HeapsType&							getHeaps() { return m_Heaps; }
		void								setCurrentHeap(uint64_t _handle) { m_currentHeap = _handle; }
		void								setCurrentModule(rdebug::ModuleInfo* _module) { m_currentModule = _module; }

	private:
		bool		loadModuleInfo(BinLoader& _loader, uint64_t inFileSize);
		bool		setLinksAndRemoveInvalid(uint64_t inMinMarkerTime);
		void		addModule(const char* inName, uint64_t inModBase, uint64_t inModSize);
		void		calculateGlobalStats();
		void		calculateSnapshotStats();
		bool		verifyGlobalStats();
		void		calculateFilteredData();
		uint32_t	getIndexBefore(uint64_t _time, uint32_t& outTimedIndex) const;
		uint32_t	getIndexAfter(uint64_t _time, uint32_t& outTimedIndex) const;
		void		GetRangedStats(MemoryStats& ioStats, uint32_t inMinIdx, uint32_t inMaxIdx);
		void		addMemoryTag(char* inTagName, uint32_t _tagHash, uint32_t _parentTagHash);
		void		addToMemoryGroups(MemoryGroupsHashType& ioGroups, MemoryOperation* _op, uint64_t _liveBlocks, uint64_t _liveSize);
		void		addToStackTraceTree(StackTraceTree& ioTree, MemoryOperation* _op, StackTrace::Scope _offset);
		void		writeGlobalStats(FILE* inFile);
};

} // namespace rtm

#endif // __RTM_MTUNER_CAPTURE_H__
