//--------------------------------------------------------------------------//
/// Copyright (c) 2019 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/grouplistwidget.h>
#include <MTuner/src/capturecontext.h>

struct GroupColumn
{
	enum Enum
	{
		Type,
		Heap,
		Size,
		Count,
		CountPeak,
		CountPeakPercent,
		Alignment,
		GroupSize,
		GroupPeakSize,
		GroupPeakSizePercent,
		Live,

		ColumnCount = rtm::MemoryOperationGroup::INDEX_MAPPINGS
	};
};

class GroupTableSource : public BigTableSource
{
	private:
		CaptureContext*	m_context;
		GroupList*		m_list;
		uint32_t		m_numColumns;
		uint32_t		m_numRows;

		rtm_vector<rtm::MemoryOperationGroup*>	m_allGroups;
		const rtm::MemoryStats*					m_stats;

		GroupMapping	m_groupMappings[GroupColumn::ColumnCount];
		GroupMapping*	m_currentGroupMapping;

		uint32_t		m_currentColumn;
		Qt::SortOrder	m_sortOrder;

	public:
		GroupTableSource(CaptureContext* _capture, GroupList* _list);
		virtual ~GroupTableSource() {}

		void prepareData();

		virtual QStringList	getHeaderInfo(int32_t& _sortCol, Qt::SortOrder& _sortOrder, QList<int>& _widths);
		virtual uint32_t	getNumberOfRows();
		virtual	QString		getItem(uint32_t _index, int32_t _column, QColor*, bool*);
		virtual void 		getItem(uint32_t _index, void**);
		virtual Qt::AlignmentFlag	getAlignment(uint32_t _index);
		virtual uint32_t	getItemIndex(void* _item);
		virtual void 		sortColumn(uint32_t _columnIndex, Qt::SortOrder _sortOrder);
		GroupMapping*		getGroupMapping(int _index) { return &m_groupMappings[_index]; }

		void saveState(QSettings& _settings);
};

#if RTM_PLATFORM_WINDOWS && RTM_COMPILER_MSVC

#pragma warning (push)
#pragma warning (disable:4211) // redefined extern to static
static bool __uncaught_exception() { return true; }
#pragma warning (pop)

#include <ppl.h>

// concurrency::parallel_radixsort Type
struct pSortType
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortType(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint8_t operator()(const uint32_t _val) const { return (*m_allGroups)[_val]->m_operations[0]->m_operationType; } 
};

// concurrency::parallel_radixsort Heap
struct pSortHeap
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortHeap(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint64_t operator()(const uint32_t _val) const { return (*m_allGroups)[_val]->m_operations[0]->m_allocatorHandle; } 
};

// concurrency::parallel_radixsort Size
struct pSortSize
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortSize(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const { return (*m_allGroups)[_val]->m_maxSize; } 
};

// concurrency::parallel_radixsort Count
struct pSortCount
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortCount(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const { return (*m_allGroups)[_val]->m_count; } 
};

// concurrency::parallel_radixsort Count peak
struct pSortCountPeak
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortCountPeak(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const { return (*m_allGroups)[_val]->m_liveCountPeak; } 
};

// concurrency::parallel_radixsort Count peak percent
struct pSortCountPeakPercent
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortCountPeakPercent(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const
	{
		rtm::MemoryOperationGroup* grp = (*m_allGroups)[_val];
		if (grp->m_liveCountPeakGlobal)
			return float(grp->m_liveCountPeak * 10000) / float(grp->m_liveCountPeakGlobal);
		else
			return 0;
	}
};

// concurrency::parallel_radixsort Alignment
struct pSortAlignment
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortAlignment(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint8_t operator()(const uint32_t _val) const { return (*m_allGroups)[_val]->m_operations[0]->m_alignment; } 
};

// concurrency::parallel_radixsort Group size
struct pSortGroupSize
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortGroupSize(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const
	{
		rtm::MemoryOperationGroup* grp = (*m_allGroups)[_val];
		return grp->m_liveSize;
	} 
};

// concurrency::parallel_radixsort Group size
struct pSortGroupSizePeak
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortGroupSizePeak(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const
	{
		rtm::MemoryOperationGroup* grp = (*m_allGroups)[_val];
		return grp->m_peakSize;
	} 
};

// concurrency::parallel_radixsort Group size peak percent
struct pSortGroupSizePeakPercent
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortGroupSizePeakPercent(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const
	{
		rtm::MemoryOperationGroup* grp = (*m_allGroups)[_val];
		if (grp->m_peakSizeGlobal)
			return float(grp->m_peakSize * 10000) / float(grp->m_peakSizeGlobal);
		else
			return 0;
	}
};

// concurrency::parallel_radixsort Live count
struct pSortLive 
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortLive(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline uint32_t operator()(const uint32_t _val) const { return (*m_allGroups)[_val]->m_liveCount; } 
};

// concurrency::parallel_radixsort Live count
struct pSetGroupMappings
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSetGroupMappings(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline void operator()(const GroupMapping* inGroupMapping) const
	{
		const uint32_t col = inGroupMapping->m_columnIndex;
		const uint32_t num = (uint32_t)(*m_allGroups).size();
		for (uint32_t i=0; i<num; ++i)
		{
			uint32_t idx = inGroupMapping->m_sortedIdx[i];
			rtm::MemoryOperationGroup* group = (*m_allGroups)[idx];
			group->m_indexMappings[col] = i;
		}
	} 
};

#else

struct pSortTypeNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortTypeNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const { return (*m_allGroups)[_val1]->m_operations[0]->m_operationType < (*m_allGroups)[_val2]->m_operations[0]->m_operationType; }
};

struct pSortHeapNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortHeapNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const { return (*m_allGroups)[_val1]->m_operations[0]->m_allocatorHandle < (*m_allGroups)[_val2]->m_operations[0]->m_allocatorHandle; }
};

struct pSortSizeNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortSizeNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const { return (*m_allGroups)[_val1]->m_maxSize< (*m_allGroups)[_val2]->m_maxSize; }
};

struct pSortCountNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortCountNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const { return (*m_allGroups)[_val1]->m_count < (*m_allGroups)[_val2]->m_count; }
};

struct pSortCountPeakNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortCountPeakNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const { return (*m_allGroups)[_val1]->m_liveCountPeak < (*m_allGroups)[_val2]->m_liveCountPeak; }
};

struct pSortCountPeakPercentNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortCountPeakPercentNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const
	{
		rtm::MemoryOperationGroup* grp1 = (*m_allGroups)[_val1];
		rtm::MemoryOperationGroup* grp2 = (*m_allGroups)[_val2];

		return float(grp1->m_liveCountPeak * grp2->m_liveCountPeakGlobal) < float(grp2->m_liveCountPeak * grp1->m_liveCountPeakGlobal);
	}
};

struct pSortAlignmentNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortAlignmentNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const { return (*m_allGroups)[_val1]->m_operations[0]->m_alignment < (*m_allGroups)[_val2]->m_operations[0]->m_alignment; }
};

struct pSortGroupSizeNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortGroupSizeNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const
	{
		rtm::MemoryOperationGroup* grp1 = (*m_allGroups)[_val1];
		rtm::MemoryOperationGroup* grp2 = (*m_allGroups)[_val2];
		return (grp1->m_liveSize) < (grp2->m_liveSize);
	}
};

struct pSortGroupSizePeakNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortGroupSizePeakNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const
	{
		rtm::MemoryOperationGroup* grp1 = (*m_allGroups)[_val1];
		rtm::MemoryOperationGroup* grp2 = (*m_allGroups)[_val2];
		return (grp1->m_peakSize) < (grp2->m_peakSize);
	}
};

struct pSortGroupSizePeakPercentNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortGroupSizePeakPercentNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const
	{
		rtm::MemoryOperationGroup* grp1 = (*m_allGroups)[_val1];
		rtm::MemoryOperationGroup* grp2 = (*m_allGroups)[_val2];

		return grp1->m_peakSize * grp2->m_peakSizeGlobal < grp2->m_peakSize * grp1->m_peakSizeGlobal;
	}
};

struct pSortLiveNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSortLiveNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline bool operator()(const uint32_t _val1, const uint32_t _val2) const { return (*m_allGroups)[_val1]->m_liveCount < (*m_allGroups)[_val2]->m_liveCount; }
};

struct pSetGroupMappingsNVC
{
	rtm_vector<rtm::MemoryOperationGroup*>* m_allGroups;
	pSetGroupMappingsNVC(rtm_vector<rtm::MemoryOperationGroup*>& _groups) : m_allGroups(&_groups) {}

	inline void operator()(const GroupMapping* inGroupMapping) const
	{
		const uint32_t col = inGroupMapping->m_columnIndex;
		const uint32_t num = (uint32_t)(*m_allGroups).size();
		for (uint32_t i = 0; i<num; ++i)
		{
			uint32_t idx = inGroupMapping->m_sortedIdx[i];
			rtm::MemoryOperationGroup* group = (*m_allGroups)[idx];
			group->m_indexMappings[col] = i;
		}
	}
};

#endif

GroupTableSource::GroupTableSource(CaptureContext* _context, GroupList* _list ) :
	m_context(_context),
	m_list(_list)
{
	prepareData();
}

void GroupTableSource::prepareData()
{
	bool filterEnabled = m_list->getFilteringState();
	
	m_stats = &m_context->m_capture->getGlobalStats();
	const rtm::MemoryGroupsHashType* groups = &m_context->m_capture->getMemoryGroups();
	if (filterEnabled)
	{
		m_stats = &m_context->m_capture->getSnapshotStats();
		groups	= &m_context->m_capture->getMemoryGroupsFiltered();
	}

	m_numColumns	= GroupColumn::ColumnCount;
	m_numRows		= (uint32_t)groups->size();
	m_currentGroupMapping	= NULL;
	m_sortOrder				= Qt::DescendingOrder;

	// populate array of groups
	uint32_t numItems = getNumberOfRows();
	m_allGroups.clear();
	m_allGroups.reserve(numItems);
	rtm::MemoryGroupsHashType::const_iterator it = groups->begin();
	rtm::MemoryGroupsHashType::const_iterator end = groups->end();
	while (it != end)
	{
		rtm::MemoryOperationGroup* ptr = (rtm::MemoryOperationGroup*)&it->second;
		m_allGroups.push_back(ptr);
		++it;
	}

	// init index arrays for columns
	const uint32_t numCols = m_numColumns;
	
	for (uint32_t i=0; i<numCols; ++i)
	{
		m_groupMappings[i].m_sortedIdx.clear();
		m_groupMappings[i].m_sortedIdx.resize(numItems);
		m_groupMappings[i].m_columnIndex = i;
		m_groupMappings[i].m_allGroups = &m_allGroups;
	}

	uint32_t* dst = m_groupMappings[0].m_sortedIdx.data();
	for (uint32_t i=0; i<numItems; ++i)
		dst[i] = i;

	for (uint32_t i=1; i<numCols; ++i)
		memcpy(m_groupMappings[i].m_sortedIdx.data(), m_groupMappings[0].m_sortedIdx.data(), sizeof(uint32_t)*numItems);

	// sort index arrays
#if RTM_PLATFORM_WINDOWS && RTM_COMPILER_MSVC

	pSortType psType(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::Type].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Type].m_sortedIdx.end(), psType );
	
	pSortHeap psHeap(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::Heap].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Heap].m_sortedIdx.end(), psHeap );
	
	pSortSize psSize(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::Size].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Size].m_sortedIdx.end(), psSize );

	pSortCount psCount(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::Count].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Count].m_sortedIdx.end(), psCount );

	pSortCountPeak psCountPeak(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::CountPeak].m_sortedIdx.begin(), m_groupMappings[GroupColumn::CountPeak].m_sortedIdx.end(), psCountPeak );

	pSortCountPeakPercent psCountPeakPercent(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::CountPeakPercent].m_sortedIdx.begin(), m_groupMappings[GroupColumn::CountPeakPercent].m_sortedIdx.end(), psCountPeakPercent);

	pSortAlignment psAlignment(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::Alignment].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Alignment].m_sortedIdx.end(), psAlignment );

	pSortGroupSize psGroupSize(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::GroupSize].m_sortedIdx.begin(), m_groupMappings[GroupColumn::GroupSize].m_sortedIdx.end(), psGroupSize );

	pSortGroupSizePeak psGroupSizePeak(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::GroupPeakSize].m_sortedIdx.begin(), m_groupMappings[GroupColumn::GroupPeakSize].m_sortedIdx.end(), psGroupSizePeak );

	pSortGroupSizePeakPercent psGroupSizePeakPercent(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::GroupPeakSizePercent].m_sortedIdx.begin(), m_groupMappings[GroupColumn::GroupPeakSizePercent].m_sortedIdx.end(), psGroupSizePeakPercent);

	pSortLive psLive(m_allGroups);
	concurrency::parallel_radixsort(m_groupMappings[GroupColumn::Live].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Live].m_sortedIdx.end(), psLive );

	pSetGroupMappings psSetMappings(m_allGroups);
	rtm_vector<GroupMapping*> mappings;
	mappings.reserve(GroupColumn::ColumnCount);
	for (uint32_t i=0; i<GroupColumn::ColumnCount; ++i)
		mappings.push_back(&m_groupMappings[i]);
	Concurrency::parallel_for_each(mappings.begin(), mappings.end(), psSetMappings);

#else
	std::stable_sort(m_groupMappings[GroupColumn::Type].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Type].m_sortedIdx.end(), pSortTypeNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::Heap].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Heap].m_sortedIdx.end(), pSortHeapNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::Size].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Size].m_sortedIdx.end(), pSortSizeNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::Count].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Count].m_sortedIdx.end(), pSortCountNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::CountPeak].m_sortedIdx.begin(), m_groupMappings[GroupColumn::CountPeak].m_sortedIdx.end(), pSortCountPeakNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::CountPeakPercent].m_sortedIdx.begin(), m_groupMappings[GroupColumn::CountPeakPercent].m_sortedIdx.end(), pSortCountPeakPercentNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::Alignment].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Alignment].m_sortedIdx.end(), pSortAlignmentNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::GroupSize].m_sortedIdx.begin(), m_groupMappings[GroupColumn::GroupSize].m_sortedIdx.end(), pSortGroupSizeNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::GroupPeakSize].m_sortedIdx.begin(), m_groupMappings[GroupColumn::GroupPeakSize].m_sortedIdx.end(), pSortGroupSizePeakNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::GroupPeakSizePercent].m_sortedIdx.begin(), m_groupMappings[GroupColumn::GroupPeakSizePercent].m_sortedIdx.end(), pSortGroupSizePeakPercentNVC(m_allGroups));

	std::stable_sort(m_groupMappings[GroupColumn::Live].m_sortedIdx.begin(), m_groupMappings[GroupColumn::Live].m_sortedIdx.end(), pSortLiveNVC(m_allGroups));

	pSetGroupMappingsNVC psSetMappings(m_allGroups);
	rtm_vector<GroupMapping*> mappings;
	mappings.reserve(GroupColumn::ColumnCount);
	for (uint32_t i = 0; i<GroupColumn::ColumnCount; ++i)
		mappings.push_back(&m_groupMappings[i]);
	std::for_each(mappings.begin(), mappings.end(), psSetMappings);

#endif

	m_currentGroupMapping = &m_groupMappings[GroupColumn::GroupPeakSize];
}

QStringList	GroupTableSource::getHeaderInfo(int32_t& _sortCol, Qt::SortOrder& _sortOrder, QList<int>& _widths)
{
	QStringList header;
	header	<< QObject::tr("Type")
			<< QObject::tr("Heap")
			<< QObject::tr("Block size")
			<< QObject::tr("Total count")
			<< QObject::tr("Live peak count")
			<< QObject::tr("Peak count") + " %"
			<< QObject::tr("Alignment")
			<< QObject::tr("Size")
			<< QObject::tr("Peak size")
			<< QObject::tr("Peak size") + " %"
			<< QObject::tr("Leaked");

	_widths << 40
			<< 90
			<< 100
			<< 90
			<< 90
			<< 75
			<< 65
			<< 120
			<< 80
			<< 75
			<< 90;
	_sortCol = m_currentColumn;
	_sortOrder = m_sortOrder;
	return header;
}

uint32_t GroupTableSource::getNumberOfRows()
{
	return m_numRows;
}

extern QString formatPercentageView(uint64_t _num, uint64_t _total, bool _countAndPct = true);
QString GroupTableSource::getItem(uint32_t _index, int32_t _column, QColor*, bool*)
{
	uint32_t index = _index;
	if (m_sortOrder == Qt::DescendingOrder)
		index = m_numRows - index - 1;
	uint32_t idx = m_currentGroupMapping->m_sortedIdx[index];
	rtm::MemoryOperationGroup* group = m_allGroups[idx];

	QLocale locale;

	switch (_column)
	{
		case GroupColumn::Type:
		{
			static QString	typeName[rmem::LogMarkers::OpCount] = {
				QObject::tr("Alloc"),
				QObject::tr("Alloc aligned"),
				QObject::tr("Calloc"),
				QObject::tr("Free"),
				QObject::tr("Realloc"),
				QObject::tr("Realloc aligned")
			};

			return typeName[group->m_operations[0]->m_operationType];
		}
	
		case GroupColumn::Heap:
			{
				rtm::HeapsType& heaps = m_context->m_capture->getHeaps();
				rtm::HeapsType::iterator it = heaps.find(group->m_operations[0]->m_allocatorHandle);
				if (it != heaps.end())
					return it->second.c_str();
				else
					return "0x" + QString::number(group->m_operations[0]->m_allocatorHandle, 16);
			}
		
		case GroupColumn::Size:
			if (group->m_maxSize != group->m_minSize)
				return locale.toString(group->m_minSize) + '-' + locale.toString(group->m_maxSize);
			else
				return locale.toString(group->m_minSize);
	
		case GroupColumn::Count:
			return formatPercentageView(group->m_count, m_stats->m_numberOfOperations);
	
		case GroupColumn::CountPeak:
			return locale.toString(group->m_liveCountPeak);

		case GroupColumn::CountPeakPercent:
			return formatPercentageView(group->m_liveCountPeak, group->m_liveCountPeakGlobal, false);

		case GroupColumn::Alignment:
		{
			if (group->m_operations[0]->m_alignment == 255)
				return QObject::tr("Default");
			else
				return QString::number(1 << group->m_operations[0]->m_alignment);
		}

		case GroupColumn::GroupSize:
			return formatPercentageView(group->m_liveSize, m_stats->m_memoryUsage);
	
		case GroupColumn::GroupPeakSize:
			return locale.toString(group->m_peakSize);

		case GroupColumn::GroupPeakSizePercent:
			return formatPercentageView(group->m_peakSize, group->m_peakSizeGlobal, false);

		case GroupColumn::Live:
			return formatPercentageView(group->m_liveCount, m_stats->m_numberOfLiveBlocks);
	};

	return "";
}

void GroupTableSource::getItem(uint32_t _index, void** _pointer)
{
	if (_index == 0xffffffff)
		return;

	uint32_t index = _index;
	if (m_sortOrder == Qt::DescendingOrder)
		index = m_numRows - index - 1;
	uint32_t idx = m_currentGroupMapping->m_sortedIdx[index];
	*_pointer = m_allGroups[idx];
}

Qt::AlignmentFlag GroupTableSource::getAlignment(uint32_t _index)
{
	switch (_index)
	{
	case GroupColumn::Count:
	case GroupColumn::CountPeak:
	case GroupColumn::CountPeakPercent:
	case GroupColumn::Alignment:
	case GroupColumn::GroupSize:
	case GroupColumn::GroupPeakSize:
	case GroupColumn::GroupPeakSizePercent:
	case GroupColumn::Live:
		return Qt::AlignRight;
	};

	return Qt::AlignLeft;
}

uint32_t GroupTableSource::getItemIndex(void* _item)
{
	uint32_t mappingIdx = m_currentGroupMapping->m_columnIndex;
	uint32_t index = ((rtm::MemoryOperationGroup*)_item)->m_indexMappings[mappingIdx];
	if (m_sortOrder == Qt::DescendingOrder)
		index = m_numRows - index - 1;
	return index;
}

void GroupTableSource::sortColumn(uint32_t _columnIndex, Qt::SortOrder _sortOrder)
{
	m_currentColumn	= _columnIndex;
	m_sortOrder		= _sortOrder;

	m_currentGroupMapping = &m_groupMappings[_columnIndex];
}

void GroupTableSource::saveState(QSettings& _settings)
{
	_settings.setValue("groupListSortColumn", m_currentColumn);
	_settings.setValue("groupListSortOrder", (int)m_sortOrder);
}

GroupList::GroupList(QWidget* _parent, Qt::WindowFlags _flags) :
	QWidget(_parent, _flags)
{
	ui.setupUi(this);

	m_context			= NULL;
	m_tableSource		= NULL;
	m_enableFiltering	= false;
	m_lastRange[0]		= 0;
	m_lastRange[1]		= 1;
	m_groupList			= findChild<BigTable*>("bigTableWidget");
	connect(m_groupList, SIGNAL(itemSelected(void*)), this, SLOT(selectionChanged(void*)));
	connect(m_groupList, SIGNAL(itemRightClicked(void*,const QPoint&)), this, SLOT(groupRightClick(void*,const QPoint&)));
}

GroupList::~GroupList()
{
	if (m_tableSource)
		delete m_tableSource;
}

void GroupList::changeEvent(QEvent* _event)
{
	QWidget::changeEvent(_event);
	if (_event->type() == QEvent::LanguageChange)
		ui.retranslateUi(this);
}

void GroupList::setContext(CaptureContext* _context)
{
	m_context = _context;
	m_tableSource = new GroupTableSource(m_context,this);
	m_groupList->setSource(m_tableSource);

	m_tableSource->sortColumn(m_savedColumn, m_savedOrder);
	m_groupList->getHeader()->setSortIndicator(m_savedColumn, m_savedOrder);

	if (m_headerState.size())
		m_groupList->getHeader()->restoreState(m_headerState);

	setFilteringState(false);
	m_groupList->resetView();
	sortingDoneUsage();
	sortingDonePeakUsage();
	sortingDonePeakCount();
	sortingDoneLeaks();
}

void GroupList::setFilteringState(bool _state)
{
	m_enableFiltering = _state;
	m_tableSource->prepareData();
	m_groupList->resetView();

	sortingDoneUsage();
	sortingDonePeakUsage();
	sortingDonePeakCount();
	sortingDoneLeaks();
}

bool GroupList::getFilteringState() const
{
	return m_enableFiltering;
}

void GroupList::loadState(QSettings& _settings, const QString& _name, bool _resetGeometry)
{
	m_savedColumn = GroupColumn::GroupPeakSize;
	m_savedOrder = Qt::DescendingOrder;

	m_settingsGroupName = _name;
	_settings.beginGroup(m_settingsGroupName);
	if (_settings.contains("groupListSortColumn") && !_resetGeometry)
	{
		m_savedColumn = _settings.value("groupListSortColumn").toInt();
		m_savedOrder = (Qt::SortOrder)_settings.value("groupListSortOrder").toInt();
		m_headerState = _settings.value("groupListHeaderState").toByteArray();
	}
	_settings.endGroup();
}

void GroupList::saveState(QSettings& _settings)
{
	if (m_tableSource)
	{
		_settings.beginGroup(m_settingsGroupName);
		m_tableSource->saveState(_settings);
		_settings.setValue("groupListHeaderState", m_groupList->getHeader()->saveState());
		_settings.endGroup();
	}
}

void GroupList::selectionChanged(void* _item)
{
	rtm::MemoryOperationGroup* group = (rtm::MemoryOperationGroup*)_item;

	if (group->m_count == 1)
	{
		emit highlightTime(group->m_operations[0]->m_operationTime);
	}
	else
	{
		size_t len = group->m_operations.size();
		uint64_t mn = group->m_operations[0]->m_operationTime;
		uint64_t mx = group->m_operations[len-1]->m_operationTime;
		emit highlightRange(mn, mx);
	}

	emit setStackTrace(&(group->m_operations[0]->m_stackTrace), 1);
}

void GroupList::groupRightClick(void* _item, const QPoint& _pos)
{
	rtm::MemoryOperationGroup* group = (rtm::MemoryOperationGroup*)_item;
	size_t last = group->m_operations.size();
	if (last> 0) --last;
	m_lastRange[0] = group->m_operations[0]->m_operationTime;
	m_lastRange[1] = group->m_operations[last]->m_operationTime;

	m_selectAction =  new QAction(QString(tr("Select group range")),this);
	connect(m_selectAction, SIGNAL(triggered()), this, SLOT(selectTriggered()));

	m_contextMenu = new QMenu();
	m_contextMenu->addAction(m_selectAction);
	m_contextMenu->exec(_pos);
}

void GroupList::sortingDoneUsage()
{
	emit usageSortingDone(m_tableSource->getGroupMapping(GroupColumn::GroupSize));
}

void GroupList::sortingDonePeakUsage()
{
	emit peakUsageSortingDone(m_tableSource->getGroupMapping(GroupColumn::GroupPeakSize));
}

void GroupList::sortingDonePeakCount()
{
	emit peakCountSortingDone(m_tableSource->getGroupMapping(GroupColumn::CountPeak));
}

void GroupList::sortingDoneLeaks()
{
	emit leaksSortingDone(m_tableSource->getGroupMapping(GroupColumn::Live));
}

void GroupList::selectTriggered()
{
	m_contextMenu = 0;
	m_enableFiltering = false;
	if (m_lastRange[1])
		emit selectRange(m_lastRange[0], m_lastRange[1]);

	m_lastRange[0] = 0;
	m_lastRange[1] = 0;
}
