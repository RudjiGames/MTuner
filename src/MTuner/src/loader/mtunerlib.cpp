//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/loader/mtunerlib.h>
#include <MTuner/src/loader/util.h>

#if RTM_PLATFORM_WINDOWS
#include <windows.h>
#include <Objbase.h>
#endif

namespace rtm {

#if RTM_PLATFORM_WINDOWS

static int	s_COM_Cnt	= 0;
static bool	s_COM_Init	= false;

bool mtunerLoaderInit(bool _MTuner)
{
	// MTuner will initialize COM
	if ((s_COM_Cnt == 0) && (_MTuner == false))
	{
		HRESULT hr = CoInitializeEx(NULL,COINIT_SPEED_OVER_MEMORY);
		if (FAILED(hr))
			return false;
		s_COM_Init = true;
	}
	s_COM_Cnt++;
	return true;
}

bool mtunerLoaderShutDown()
{
	if ((--s_COM_Cnt == 0) && (s_COM_Init))
	{
		CoUninitialize();
		s_COM_Init = false;
		return true;
	}
	return true;
}

#else // RTM_PLATFORM_WINDOWS

bool mtunerLoaderInit(bool /*_MTuner*/)		{ return true; }
bool mtunerLoaderShutDown()				{ return true; }

#endif // RTM_PLATFORM_WINDOWS

void MemoryStats::setPeaksToCurrent()
{
	m_memoryUsagePeak	= m_memoryUsage;
	m_overheadPeak		= m_overhead;
	for (uint32_t i=0; i<NUM_HISTOGRAM_BINS; i++)
	{
		m_histogram[i].m_sizePeak		= m_histogram[i].m_size;
		m_histogram[i].m_overheadPeak	= m_histogram[i].m_overhead;
		m_histogram[i].m_countPeak		= m_histogram[i].m_count;
	}
}

void MemoryStats::setPeaksFrom(MemoryStatLocalPeak& _peaks)
{
	m_memoryUsagePeak	= _peaks.m_memoryUsagePeak;
	m_overheadPeak		= _peaks.m_overheadPeak;
	for (uint32_t i=0; i<NUM_HISTOGRAM_BINS; i++)
	{
		m_histogram[i].m_sizePeak		= _peaks.m_HistogramPeak[i].m_sizePeak;
		m_histogram[i].m_overheadPeak	= _peaks.m_HistogramPeak[i].m_overheadPeak;
		m_histogram[i].m_countPeak		= _peaks.m_HistogramPeak[i].m_countPeak;
	}
}

//--------------------------------------------------------------------------
/// Finds memory tag in the tree
//--------------------------------------------------------------------------
bool tagFind(MemoryTagTree& _rootTag, uint32_t _hash, MemoryTagTree*& _result, MemoryTagTree*& _prevTag)
{
	if (_prevTag)
	{
		if (_prevTag->m_hash == _hash)
		{
			_result = _prevTag;
			return true;
		}
	}

	_result = &_rootTag;
	if (_rootTag.m_hash == _hash)
	{
		_prevTag = &_rootTag;
		return true;
	}
	else
	{
		MemoryTagTree::ChildMap::iterator it = _rootTag.m_children.begin();
		MemoryTagTree::ChildMap::iterator end = _rootTag.m_children.end();
		while (it != end)
		{
			if (tagFind(*it->second, _hash, _result, _prevTag))
			{
				RTM_ASSERT(_result->m_hash == _prevTag->m_hash, "");
				return true;
			}
			++it;
		}
	}
	return false;
}

bool tagInsert(MemoryTagTree* _rootTag, MemoryTagTree* _tag, uint32_t _parentTagHash)
{
	if (_rootTag->m_hash == _parentTagHash)
	{
		_tag->m_parent = _rootTag;
		_rootTag->m_children[_tag->m_hash] = _tag;
		return true;

	}
	else
	{
		MemoryTagTree::ChildMap::iterator it = _rootTag->m_children.begin();
		MemoryTagTree::ChildMap::iterator end = _rootTag->m_children.end();
		while (it != end)
		{
			if (tagInsert(it->second,_tag,_parentTagHash))
				return true;
			++it;
		}
		return false;
	}
}

static inline void addOpToTag(MemoryTagTree* _tag, int64_t _size, int64_t _overhead, MemoryOperation* _op)
{
	_tag->m_usage += _size;
	if (_tag->m_usage > _tag->m_usagePeak)
		_tag->m_usagePeak = _tag->m_usage;

	_tag->m_overhead += _overhead;
	if (_tag->m_overhead > _tag->m_overheadPeak)
		_tag->m_overheadPeak = _tag->m_overhead;

	_tag->m_operationCount[_op->m_operationType]++;

	if (_tag->m_parent)
		addOpToTag(_tag->m_parent, _size, _overhead, _op);
}

void tagAddOp(MemoryTagTree& _rootTag, MemoryOperation* _op, MemoryTagTree*& _prevTag)
{
	MemoryTagTree* tag;
	tagFind(_rootTag, _op->m_tag, tag, _prevTag);

	int64_t size = _op->m_allocSize;
	int64_t overhead = _op->m_overhead;

	switch (_op->m_operationType)
	{
		case rmem::LogMarkers::OpAlloc:
		case rmem::LogMarkers::OpCalloc:
		case rmem::LogMarkers::OpAllocAligned:
			break;

		case rmem::LogMarkers::OpFree:
			{
				size = -size;
				overhead = -overhead;
			}
			break;

		case rmem::LogMarkers::OpReallocAligned:
		case rmem::LogMarkers::OpRealloc:
			{
				MemoryTagTree* tagPrev;
				if (_op->m_chainPrev)
				{
					tagFind(_rootTag, _op->m_chainPrev->m_tag, tagPrev, _prevTag);

					int64_t sizePrev = _op->m_chainPrev->m_allocSize;
					int64_t overheadPrev = _op->m_chainPrev->m_overhead;

					sizePrev = -sizePrev;
					overheadPrev = -overheadPrev;

					addOpToTag(tagPrev, sizePrev, overheadPrev, _op->m_chainPrev);
				}
			}
			break;
	};

	addOpToTag(tag, size, overhead, _op);
}

void tagTreeDestroy(MemoryTagTree& _rootTag)
{
	MemoryTagTree::ChildMap::iterator it = _rootTag.m_children.begin();
	MemoryTagTree::ChildMap::iterator end = _rootTag.m_children.end();
	while (it != end)
	{
		MemoryTagTree* ct = it->second;
		tagTreeDestroy(*ct);
		delete ct;
		++it;
	}
	_rootTag.m_children.clear();
}

void destroyStackTree(StackTraceTree& _tree)
{
	StackTraceTree::ChildNodes::iterator it = _tree.m_children.begin();
	StackTraceTree::ChildNodes::iterator end = _tree.m_children.end();

	while (it != end)
	{
		StackTraceTree& ct = *it;
		destroyStackTree(ct);
		++it;
	}

	_tree.m_children.clear();

	_tree.m_memUsage = 0;
	_tree.m_memUsagePeak = 0;
	_tree.m_overhead = 0;
	_tree.m_overheadPeak = 0;
	_tree.m_parent = NULL;
}

} // namespace rtm
