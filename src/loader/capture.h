//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNERLOADER_BINLOADER_H__
#define __RTM_MTUNERLOADER_BINLOADER_H__

#include <rdebug/inc/rdebug.h>
#include <rbase/inc/cpu.h>

namespace rtm {

class BinLoader;

struct GraphEntry
{
	uint64_t	m_usage;
	uint64_t	m_numLiveBlocks;
};

//--------------------------------------------------------------------------
/// Memory tracking binary file loader
//--------------------------------------------------------------------------
class Capture
{
	public:
		typedef void (*LoadProgress)(void* inCustomData, float inProgress, const char* inMessage);
		typedef rtm_unordered_map<uint32_t, StackTrace*,uint32_t_hash,uint32_t_equal>	StackTraceHashType;
		typedef rtm_unordered_map<uint32_t, MemoryOperationGroup,uint32_t_hash,uint32_t_equal> MemoryGroupsHashType;
		typedef rtm_unordered_map<uint32_t, MemoryMarkerEvent,uint32_t_hash,uint32_t_equal> MemoryMarkersHashType;
		typedef rtm_unordered_map<uint64_t, rtm_string> HeapsType;

	private:
		rtm_string									m_LoadedFile;			///< Symbol store path
		bool										m_SwapEndian;
		bool										m_64bit;
		rmem::ToolChain::Enum						m_Toolchain;
		ChunkAllocator<MemoryOperation>				m_OperationPool;
		StackAllocator								m_StackPool;
		rtm_vector<MemoryOperation*>				m_operations;
																			/// malloc -> realloc -> realloc -> free
		MemoryStats									m_StatsGlobal;			///< Memory statistics for global range
		MemoryStats									m_StatsSnapshot;		///< Memory statistics for selected snapshot
		rtm_vector<MemoryStatsTimed>				m_TimedStats;

		// symbols

		rtm_vector<rdebug::ModuleInfo>				m_moduleInfos;			///< Module information data
		char*										m_modulePathBuffer;
		uint32_t									m_modulePathBufferPtr;

		// ----

		StackTraceHashType							m_StackTraces;			///< map of stack traces, key is a stack trace hash
		MemoryGroupsHashType						m_OperationGroups;
		rtm_vector<GraphEntry>						m_UsageGraph;			///< memory usage graph data
		StackTraceTree								m_StackTraceTree;		///< stack trace tree
		MemoryTagTree								m_TagTreeGlobal;		///< Global tag tree
		//MemoryTagTree								m_TagTreeSnapshot;		///< Selected snapshot tag tree
		MemoryMarkersHashType						m_MemoryMarkers;
		HeapsType									m_Heaps;
		uint64_t									m_CurrentHeap;
		rtm_vector<MemoryMarkerTime>				m_MemoryMarkerTimes;
		uint64_t									m_CPUFrequency;
		uint64_t									m_MinTime;
		uint64_t									m_MaxTime;
		uint64_t									m_MinTimeSnapshot;
		uint64_t									m_MaxTimeSnapshot;
		uint32_t									m_SelectedHistogramIndex;
		uint32_t									m_SelectedTagHash;
		uint64_t									m_SelectedThreadId;
		rtm_vector<MemoryOperation*>				m_MemoryLeaks;			/// List of allocations without matching free
		LoadProgress								m_LoadProgressCallback;
		void*										m_LoadProgressCustomData;
		
		bool										m_FilteringEnabled;
		rtm_vector<MemoryOperation*>				m_OperationsFiltered;
		MemoryGroupsHashType						m_OperationGroupsFiltered;
		StackTraceTree								m_StackTraceTreeFiltered;
		MemoryTagTree								m_TagTreeFiltered;

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
		void setLoadProgressCallback(void* _cd, LoadProgress _cb) { m_LoadProgressCustomData = _cd; m_LoadProgressCallback = _cb; }
		void clearData();
		bool is64bit() { return m_64bit; }
		void buildAnalyzeData(uintptr_t _symResolver);

		rtm_vector<rdebug::ModuleInfo>&	getModuleInfos() { return m_moduleInfos; }


		bool			saveLog(const char* _path, uintptr_t _symResolver);
		bool			saveGroupsLog(const char* _path, eGroupSort _sorting, uintptr_t _symResolver);
		bool			saveGroupsLogXML(const char* _path, eGroupSort _sorting, uintptr_t _symResolver);
		void			setFilteringEnabled(bool inState);
		bool			getFilteringEnabled() const { return m_FilteringEnabled; }
		bool			isInFilter(MemoryOperation* _op);
		void			selectHistogramBin(uint32_t _index);
		uint32_t		getSelectHistogramBin() const { return m_SelectedHistogramIndex; }
		void			deselectHistogramBin();
		void			selectTag(uint32_t _tagHash);
		void			deselectTag();
		void			selectThread(uint64_t _threadID);
		void			deselectThread();
		void			setSnapshot(uint64_t _minTime, uint64_t _maxTime);
		uint64_t		getMinTime() const { return m_MinTime; }
		uint64_t		getMaxTime() const { return m_MaxTime; }
		uint64_t		getMinTimeSnapshot() const { return m_MinTimeSnapshot; }
		uint64_t		getMaxTimeSnapshot() const { return m_MaxTimeSnapshot; }
		float			getFloatTime(uint64_t _time) { return CPU::time(_time, m_CPUFrequency); }
		uint64_t		getClocksFromTime(float _time) { return (uint64_t)(_time*m_CPUFrequency); }
		const MemoryStats&	getGlobalStats() const { return m_StatsGlobal; }
		const MemoryStats&	getSnapshotStats() const { return m_StatsSnapshot; }
		void			getGraphAtTime(uint64_t _time, GraphEntry& _entry);
		const rtm_vector<MemoryMarkerTime>& getMemoryMarkers() const { return m_MemoryMarkerTimes; }
		const MemoryTagTree& getTagTree() const { return m_TagTreeGlobal; }
		const StackTraceTree&	getStackTraceTree() const { return m_StackTraceTree; }
		const StackTraceTree&	getStackTraceTreeFiltered() const { return m_StackTraceTreeFiltered; }
		uint32_t		getNumberOfOperations() const { return (uint32_t)m_operations.size(); }
		MemoryOperation*	getOperation(uint32_t _index) const { return m_operations[_index]; }
		const rtm_vector<MemoryOperation*>& getMemoryOps() const { return m_operations; }
		const rtm_vector<MemoryOperation*>& getMemoryOpsFiltered() const { return m_OperationsFiltered; }
		const MemoryGroupsHashType& getMemoryGroups() const { return m_OperationGroups; }
		const MemoryGroupsHashType& getMemoryGroupsFiltered() const { return m_OperationGroupsFiltered; }
		rmem::ToolChain::Enum		getToolchain() { return m_Toolchain; }
		HeapsType&		getHeaps() { return m_Heaps; }
		void			setCurrentHeap(uint64_t inHandle) { m_CurrentHeap = inHandle; }

	private:
		bool		LoadSymbolInfo(BinLoader& _loader, uint64_t inFileSize );
		bool		SetLinksAndRemoveInvalid(uint64_t inMinMarkerTime);
		bool		FindModule(uint64_t inAddress, rdebug::ModuleInfo& outInfo);
		void		AddModule(const char* inName, uint64_t inModBase, uint64_t inModSize);
		void		CalculateGlobalStats();
		bool		verifyGlobalStats();
		void		CalculateFilteredData();
		uint32_t	getIndexBefore(uint64_t _time, uint32_t& outTimedIndex) const;
		uint32_t	GetIndexAfter(uint64_t _time, uint32_t& outTimedIndex) const;
		void		CalculateSnapshotStats();
		void		GetRangedStats(MemoryStats& ioStats, uint32_t inMinIdx, uint32_t inMaxIdx);
		void		AddMemoryTag(char* inTagName, uint32_t _tagHash, uint32_t _parentTagHash);
		void		addToMemoryGroups(MemoryGroupsHashType& ioGroups, MemoryOperation* _op);
		void		addToStackTraceTree(StackTraceTree& ioTree, MemoryOperation* _op, StackTrace::Enum _offset);
		void		CollapseStackTraceTree();
		void		WriteGlobalStats(FILE* inFile);
};

} // namespace rtm

#endif // __RTM_MTUNERLOADER_BINLOADER_H__
