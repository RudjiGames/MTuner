//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_UTIL_H
#define RTM_MTUNER_UTIL_H

#include <rbase/inc/uint32_t.h>
#include <rbase/inc/hash.h>
#include <MTuner/src/loader/mtunerlib.h>

namespace rtm {

/// Returns true if operation type is allocation
static inline bool isAlloc(uint16_t _op)
{
	return (_op != rmem::LogMarkers::OpFree);
}

/// Sets memory operation to invalid state
static inline void setInvalid(MemoryOperation* _op)
{
	_op->m_isValid = 0;
}

/// Returns true if operation is invalid
static inline bool isInvalid(MemoryOperation* _op)
{
	return _op->m_isValid == 0;
}

//--------------------------------------------------------------------------
/// Returns the index of the histogram bin based on allocation size
//--------------------------------------------------------------------------
static inline uint8_t getHistogramBinIndex(uint32_t _size)
{
	const uint32_t binPow2 = uint32_nextpow2( _size );
	const uint32_t clampPow2 = uint32_imax(binPow2, MemoryStats::MIN_HISTOGRAM_SIZE);
	const uint32_t trailingZ = uint32_cnttz(clampPow2);
	const uint32_t binIdx = trailingZ - MemoryStats::HISTOGRAM_BIN_SHIFT;
	return (uint8_t)(uint32_imin( binIdx, MemoryStats::NUM_HISTOGRAM_BINS - 1 ) & 0xff);
}

//--------------------------------------------------------------------------
/// Fills memory statistics structure for alloc family of functions
//--------------------------------------------------------------------------
static inline uint32_t fillStats_Alloc(MemoryOperation* _op, MemoryStats& _stats)
{
	_stats.m_memoryUsage		+= _op->m_allocSize;
	_stats.m_memoryUsagePeak	= qMax(_stats.m_memoryUsage, _stats.m_memoryUsagePeak);

	_stats.m_overhead			+= _op->m_overhead;
	_stats.m_overheadPeak		= qMax(_stats.m_overhead, _stats.m_overheadPeak);

	++_stats.m_numberOfLiveBlocks;
	_stats.m_numberOfLiveBlocksPeak = qMax(_stats.m_numberOfLiveBlocks, _stats.m_numberOfLiveBlocksPeak);

	++_stats.m_numberOfAllocations;

	const uint32_t binIdx = getHistogramBinIndex(_op->m_allocSize);

	_stats.m_histogram[binIdx].m_count		+= 1;
	_stats.m_histogram[binIdx].m_size		+= _op->m_allocSize;
	_stats.m_histogram[binIdx].m_overhead	+= _op->m_overhead;

	_stats.m_histogram[binIdx].m_countPeak		= qMax(_stats.m_histogram[binIdx].m_countPeak, _stats.m_histogram[binIdx].m_count);
	_stats.m_histogram[binIdx].m_sizePeak		= qMax(_stats.m_histogram[binIdx].m_sizePeak, _stats.m_histogram[binIdx].m_size);
	_stats.m_histogram[binIdx].m_overheadPeak	= qMax(_stats.m_histogram[binIdx].m_overheadPeak, _stats.m_histogram[binIdx].m_overhead);

	return binIdx;
}

//--------------------------------------------------------------------------
/// Fills memory statistics structure for realloc family of functions
//--------------------------------------------------------------------------
static inline uint32_t fillStats_ReAlloc(MemoryOperation* _op, MemoryStats& _stats)
{
	MemoryOperation* prevOp = _op->m_chainPrev;

	_stats.m_memoryUsage		+= _op->m_allocSize;
	if (prevOp)
		_stats.m_memoryUsage	-= prevOp->m_allocSize;
	_stats.m_memoryUsagePeak	= qMax(_stats.m_memoryUsage, _stats.m_memoryUsagePeak);

	_stats.m_overhead			+= _op->m_overhead;
	if (prevOp)
		_stats.m_overhead		-= prevOp->m_overhead;
	_stats.m_overheadPeak		= qMax(_stats.m_overhead, _stats.m_overheadPeak);

	++_stats.m_numberOfReAllocations;

	const uint32_t binIdx = getHistogramBinIndex(_op->m_allocSize);

	_stats.m_histogram[binIdx].m_count			+= 1;
	_stats.m_histogram[binIdx].m_size			+= _op->m_allocSize;
	_stats.m_histogram[binIdx].m_overhead		+= _op->m_overhead;

	if (prevOp)
	{
		const uint32_t binIdxPrev = getHistogramBinIndex(prevOp->m_allocSize);

		_stats.m_histogram[binIdxPrev].m_count		-= 1;
		_stats.m_histogram[binIdxPrev].m_size		-= prevOp->m_allocSize;
		_stats.m_histogram[binIdxPrev].m_overhead	-= prevOp->m_overhead;
	}
	else
	{
		// if there is no previous block or if we didn't free the block using realloc - increase live count
		if (_op->m_pointer != 0)
		{
			++_stats.m_numberOfLiveBlocks;
			_stats.m_numberOfLiveBlocksPeak = qMax(_stats.m_numberOfLiveBlocks, _stats.m_numberOfLiveBlocksPeak);
		}
	}
	
	_stats.m_histogram[binIdx].m_countPeak		= qMax(_stats.m_histogram[binIdx].m_countPeak, _stats.m_histogram[binIdx].m_count);
	_stats.m_histogram[binIdx].m_sizePeak		= qMax(_stats.m_histogram[binIdx].m_sizePeak, _stats.m_histogram[binIdx].m_size);
	_stats.m_histogram[binIdx].m_overheadPeak	= qMax(_stats.m_histogram[binIdx].m_overheadPeak, _stats.m_histogram[binIdx].m_overhead);

	return binIdx;
}

//--------------------------------------------------------------------------
/// Fills memory statistics structure for free function
//--------------------------------------------------------------------------
static inline void fillStats_Free(MemoryOperation* _op, MemoryStats& _stats)
{
	_stats.m_memoryUsage	-= _op->m_allocSize;
	_stats.m_overhead		-= _op->m_overhead;
				
	++_stats.m_numberOfFrees;
	--_stats.m_numberOfLiveBlocks;

	const uint32_t binIdx = getHistogramBinIndex(_op->m_allocSize);
	
	_stats.m_histogram[binIdx].m_count		-= 1;
	_stats.m_histogram[binIdx].m_size		-= _op->m_allocSize;
	_stats.m_histogram[binIdx].m_overhead	-= _op->m_overhead;
}

} // namespace rtm

#endif // RTM_MTUNER_UTIL_H
