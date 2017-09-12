//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/loader/capture.h>
#include <MTuner/src/loader/binloader.h>
#include <MTuner/src/loader/util.h>
#include <rbase/inc/endianswap.h>
#include <rbase/inc/path.h>
#include <rbase/inc/winchar.h>
#include <rdebug/inc/rdebug.h>

#include <type_traits>

#if RTM_PLATFORM_WINDOWS && RTM_COMPILER_MSVC

#pragma warning (push)
#pragma warning (disable:4530) // exceptions not used
#pragma warning (disable:4211) // redefined extern to static

static bool __uncaught_exception() { return true; }
#include <ppl.h>

struct pSortOpsTime
{
	rtm_vector<rtm::MemoryOperation*>* m_allOps;
	pSortOpsTime(rtm_vector<rtm::MemoryOperation*>& _ops) : m_allOps(&_ops) {}

	inline uint64_t operator()(const rtm::MemoryOperation* _val) const
	{
		return _val->m_operationTime;
	}
};

#pragma warning (pop)

#endif // RTM_PLATFORM_WINDOWS && RTM_COMPILER_MSVC

namespace rtm {

static inline uint64_t stackTraceGetHash(uint64_t* _backTrace, uint32_t _numEntries)
{
	uint64_t hash = 0;
	for (uint32_t i=0; i<_numEntries; ++i)
		hash += _backTrace[i];
	return hash;
}

static inline bool stackTraceCompare(uint64_t* _e1, uint64_t _c1, uint64_t* _e2, uint64_t _c2)
{
	if (_c1 != _c2)
		return false;
	const int cnt = (int)_c1;
	for (int i=0; i<cnt; ++i)
		if (_e1[i] != _e2[i])
			return false;
	return true;
}

static uint32_t getGranularityMask(uint64_t _ops)
{
	uint32_t granularity = 2048;
	if (_ops > 1024*1024)
		granularity = 4096;
	if (_ops > 10*1024*1024)
		granularity = 8192;
	return granularity - 1;
}

inline bool psTime(MemoryOperation* inOp1, MemoryOperation* inOp2)
{
	return inOp1->m_operationTime < inOp2->m_operationTime;
}

template <uint32_t Len>
inline uint32_t	ReadString(char _string[Len], BinLoader& _loader, bool _swapEndian, uint8_t _xor = 0)
{
	uint32_t len;
	if (_loader.readVar(len) != 1)
		return 0;

	if (_swapEndian)
		len = Endian::swap(len);

	if (len < Len)
	{
		_loader.read(_string, sizeof(char) * len);
		uint8_t* xBuff = (uint8_t*)_string;
		for (uint32_t i=0; i<sizeof(char)*len; i++)
			xBuff[i] = xBuff[i] ^ _xor;
		_string[len] = (char)'\0';
		return (uint32_t)(len*sizeof(char) + sizeof(uint32_t));
	}
	_string[0] = (char)'\0';
	return sizeof(len);
}

template <uint32_t Len>
inline uint32_t	ReadString(char16_t _string[Len], BinLoader& _loader, bool _swapEndian, uint8_t _xor = 0)
{
	uint32_t len;
	if (_loader.readVar(len) != 1)
		return 0;

	if (_swapEndian)
		len = Endian::swap(len);

	if (len < Len)
	{
		_loader.read(_string, sizeof(char16_t) * len);
		uint8_t* xBuff = (uint8_t*)_string;
		for (uint32_t i=0; i<sizeof(char16_t)*len; i++)
			xBuff[i] = xBuff[i] ^ _xor;
		_string[len] = (char16_t)'\0';
		return (uint32_t)(len*sizeof(char16_t) + sizeof(uint32_t));
	}
	_string[0] = (char16_t)'\0';
	return sizeof(len);
}

//--------------------------------------------------------------------------
///
//--------------------------------------------------------------------------
static inline uint32_t calcGroupHash(MemoryOperation* _op)
{
	struct hash
	{
		uint64_t h1;
		uint64_t h2;
		uint32_t h3;
		uint16_t h4, h5;
	};
	hash h;
	h.h1 = (uint64_t)_op->m_stackTrace;
	h.h2 = _op->m_allocatorHandle;
	h.h3 = _op->m_allocSize;
	h.h4 = _op->m_operationType;
	h.h5 = _op->m_alignment;
	return hashMurmur3(&h, sizeof(hash));
}

static inline void addHeap(HeapsType& _heaps, uint64_t _heap)
{
	if (_heaps.find(_heap) == _heaps.end())
		_heaps[_heap] = "";
}

//--------------------------------------------------------------------------
/// Capture constructor
//--------------------------------------------------------------------------
Capture::Capture()
{
	m_modulePathBuffer			= 0;
	m_modulePathBufferPtr		= 0;

	m_loadProgressCallback		= NULL;
	m_loadProgressCustomData	= NULL;

	clearData();
}

//--------------------------------------------------------------------------
/// Capture destructor
//--------------------------------------------------------------------------
Capture::~Capture()
{
	clearData();
}

//--------------------------------------------------------------------------
/// Clears all previously loaded data
//--------------------------------------------------------------------------
void Capture::clearData()
{
	m_filteringEnabled = false;
	m_swapEndian	= false;
	m_64bit			= false;

	m_loadedFile.clear();
	m_operationPool.Reset();
	m_stackPool.Reset();
	m_operations.clear();
	m_statsGlobal.Reset();
	m_statsSnapshot.Reset();

	// symbols

	m_moduleInfos.clear();
	if (m_modulePathBuffer)
	{
		delete[] m_modulePathBuffer;
		m_modulePathBuffer = 0;
	}

	m_modulePathBufferPtr = 0;

	// -----

	m_stackTraces.clear();
	m_timedStats.clear();

	m_minTime = 0;
	m_maxTime = 0;

	m_filter.m_minTimeSnapshot	= 0;
	m_filter.m_maxTimeSnapshot	= 0;
	m_filter.m_histogramIndex	= 0xffffffff;
	m_filter.m_tagHash			= 0;
	m_filter.m_threadID			= 0;

	m_usageGraph.clear();

	m_memoryMarkers.clear();
	m_memoryMarkerTimes.clear();

	m_Heaps.clear();
	m_currentHeap = (uint64_t)-1;


	tagTreeDestroy(m_tagTree);
	destroyStackTree(m_stackTraceTree);
}

//--------------------------------------------------------------------------
#define VERIFY_READ_SIZE(x)				\
	if (1 != loader.readVar(x))			\
	{									\
		loadSuccess = false;			\
		break;							\
	}

#define VERIFY_MARKER(m,v)				\
	if (m != v)							\
	{									\
		loadSuccess = false;			\
		break;							\
	}

Capture::LoadResult Capture::loadBin(const char* _path)
{
	clearData();

	m_loadedFile = _path;

#if RTM_PLATFORM_WINDOWS
	rtm::MultiToWide path(_path);
	FILE* f  = _wfopen(path.m_ptr, L"rb");
#else
	FILE *f = fopen(_path, "r");
#endif

	if (!f)
		return Capture::LoadFail;

#if RTM_PLATFORM_WINDOWS
	_fseeki64(f, 0, SEEK_END);
	uint64_t fileSize = (uint64_t)_ftelli64(f);
	_fseeki64(f, 0, SEEK_SET);
#elif RTM_PLATFORM_LINUX
	fseeko64(f, 0, SEEK_END);
	uint64_t fileSize = (uint64_t)ftello64(f);
	fseeko64(f, 0, SEEK_SET);
#endif

	uint32_t compressSignature;
	fread(&compressSignature, 1, sizeof(uint32_t), f);
#if RTM_PLATFORM_WINDOWS
	_fseeki64(f, 0, SEEK_SET);
#elif RTM_PLATFORM_LINUX
	fseeko64(f, 0, SEEK_SET);
#endif

	bool isCompressed = ((compressSignature == 0x23234646) || compressSignature == Endian::swap(uint32_t(0x23234646)));

	BinLoader loader(f, isCompressed);

	uint64_t fileSizeOver100 = fileSize/100;

	uint8_t endianess;
	uint8_t pointerSize;
	uint8_t verHigh;
	uint8_t verLow;
	uint8_t toolChain;
	uint64_t cpuFrequency;

	size_t headerItems = 0;
	headerItems += loader.readVar(endianess);
	headerItems += loader.readVar(pointerSize);
	headerItems += loader.readVar(verHigh);
	headerItems += loader.readVar(verLow);
	headerItems += loader.readVar(toolChain);
	headerItems += loader.readVar(cpuFrequency);

	if (headerItems != 6)
		return Capture::LoadFail;

	if (verHigh > 1)
		return Capture::LoadFail;

	if (verLow > 2)
		return Capture::LoadFail;

#if RTM_LITTLE_ENDIAN
	m_swapEndian	= (endianess == 0xff) ? true : false;
#else
	m_swapEndian	= (endianess == 0xff) ? false : true;
#endif

	m_64bit			= (pointerSize == 64) ? true : false;
	m_toolchain		= (rmem::ToolChain::Enum)toolChain;

	if (m_swapEndian)
		cpuFrequency = Endian::swap(cpuFrequency);
	m_CPUFrequency = cpuFrequency;

	printf("Load bin:\n  version %d.%d\n  %s endian\n  %sbit\n",
			verHigh,
			verLow,
			m_swapEndian ? "Big" : "Little",
			m_64bit ? "64" : "32" );

	if (!loadSymbolInfo(loader, fileSize))
	{
		clearData();
		return Capture::LoadFail;
	}

	bool loadSuccess = true;

	rtm_unordered_map<uint64_t, rtm_vector<uint32_t>>  perThreadTagStack;

	uint64_t nextProgressPoint = 0;
	uint64_t minMarkerTime = (uint64_t)-1;

	for (;loadSuccess;)
	{
		if (loader.eof())
			break;

		uint8_t	marker;
		if (loader.readVar(marker) == 0)
			break;

		uint64_t pos = loader.tell();
		if ((pos > nextProgressPoint) && m_loadProgressCallback)
		{
			nextProgressPoint += fileSizeOver100;
			float percent = float(pos) / fileSizeOver100;
			m_loadProgressCallback(m_loadProgressCustomData, percent, "Loading capture file...");
		}

		switch (marker)
		{
			case rmem::LogMarkers::OpAlloc:
			case rmem::LogMarkers::OpAllocAligned:
			case rmem::LogMarkers::OpCalloc:
			case rmem::LogMarkers::OpFree:
			case rmem::LogMarkers::OpRealloc:
			case rmem::LogMarkers::OpReallocAligned:
				{
					// read memory op
					MemoryOperation* op = m_operationPool.Alloc();

					if (loader.readVar(op->m_allocatorHandle) != 1)
					{
						loadSuccess = false;
						break;
					}

					op->m_operationType	= marker;
					op->m_alignment		= 255;

					uint8_t bitIndex;
					size_t itemsRead = 0;

					switch (marker)
					{
						case rmem::LogMarkers::OpAlloc:
						case rmem::LogMarkers::OpCalloc:
							itemsRead += loader.readVar(op->m_threadID);
							if (m_64bit)
								itemsRead += loader.readVar(op->m_pointer);
							else
							{
								uint32_t ptr;
								itemsRead += loader.readVar(ptr);
								op->m_pointer = ptr;
							}
							itemsRead += loader.readVar(op->m_operationTime);
							itemsRead += loader.readVar(op->m_allocSize);
							itemsRead += loader.readVar(op->m_overhead);

							loadSuccess = itemsRead == 5;
							break;

						case rmem::LogMarkers::OpRealloc:
							itemsRead += loader.readVar(op->m_threadID);
							if (m_64bit)
							{
								itemsRead += loader.readVar(op->m_pointer);
								itemsRead += loader.readVar(op->m_previousPointer);
							}
							else
							{
								uint32_t ptr;
								itemsRead += loader.readVar(ptr);
								op->m_pointer = ptr;
								itemsRead += loader.readVar(ptr);
								op->m_previousPointer = ptr;
							}
							itemsRead += loader.readVar(op->m_operationTime);
							itemsRead += loader.readVar(op->m_allocSize);
							itemsRead += loader.readVar(op->m_overhead);

							loadSuccess = itemsRead == 6;
							break;

						case rmem::LogMarkers::OpAllocAligned:
							itemsRead += loader.readVar(op->m_threadID);
							if (m_64bit)
								itemsRead += loader.readVar(op->m_pointer);
							else
							{
								uint32_t ptr;
								itemsRead += loader.readVar(ptr);
								op->m_pointer = ptr;
							}
							itemsRead += loader.readVar(op->m_operationTime);
							itemsRead += loader.readVar(bitIndex);
							op->m_alignment = bitIndex;
							itemsRead += loader.readVar(op->m_allocSize);
							itemsRead += loader.readVar(op->m_overhead);

							loadSuccess = itemsRead == 6;
							break;

						case rmem::LogMarkers::OpFree:
							itemsRead += loader.readVar(op->m_threadID);
							if (m_64bit)
								itemsRead += loader.readVar(op->m_pointer);
							else
							{
								uint32_t ptr;
								itemsRead += loader.readVar(ptr);
								op->m_pointer = ptr;
							}
							itemsRead += loader.readVar(op->m_operationTime);

							loadSuccess = itemsRead == 3;
							break;

						case rmem::LogMarkers::OpReallocAligned:
							itemsRead += loader.readVar(op->m_threadID);
							if (m_64bit)
							{
								itemsRead += loader.readVar(op->m_pointer);
								itemsRead += loader.readVar(op->m_previousPointer);
							}
							else
							{
								uint32_t ptr;
								itemsRead += loader.readVar(ptr);
								op->m_pointer = ptr;
								itemsRead += loader.readVar(ptr);
								op->m_previousPointer = ptr;
							}
							itemsRead += loader.readVar(op->m_operationTime);
							itemsRead += loader.readVar(bitIndex);
							op->m_alignment = bitIndex;
							itemsRead += loader.readVar(op->m_allocSize);
							itemsRead += loader.readVar(op->m_overhead);

							loadSuccess = itemsRead == 7;
							break;
					};

					if (!loadSuccess)
						break;

					if (m_swapEndian)
					{
						op->m_allocatorHandle		= Endian::swap(op->m_allocatorHandle);
						op->m_threadID				= Endian::swap(op->m_threadID);
						op->m_operationTime			= Endian::swap(op->m_operationTime);
						op->m_allocSize				= Endian::swap(op->m_allocSize);
						op->m_overhead				= Endian::swap(op->m_overhead);

						if (m_64bit)
						{
							op->m_pointer			= Endian::swap(op->m_pointer);
							op->m_previousPointer	= Endian::swap(op->m_previousPointer);
						}
						else
						{
							uint32_t actualPtr		= (uint32_t)op->m_pointer;
							actualPtr				= Endian::swap(actualPtr);
							op->m_pointer			= (uint64_t)actualPtr;

							actualPtr				= (uint32_t)op->m_previousPointer;
							actualPtr				= Endian::swap(actualPtr);
							op->m_previousPointer	= (uint64_t)actualPtr;
						}
					}

					uint64_t backTrace64[512];
					uint32_t backTrace32[512];

					//
					// handle stack trace compression/hashing
					//
					bool readFullStack = false;

					uint32_t stackTraceHash = 0;
					uint32_t numFrames32 = 0;
					uint16_t numFrames16 = 0;

					// read back trace
					uint8_t stackTraceTag;
					VERIFY_READ_SIZE(stackTraceTag)

					if (stackTraceTag == rmem::EntryTags::Exists)
					{
						VERIFY_READ_SIZE(stackTraceHash)
					}
					else
					if (stackTraceTag == rmem::EntryTags::Add)
					{
						VERIFY_READ_SIZE(numFrames16)
						readFullStack = true;
					}
					else
					if (stackTraceTag == rmem::EntryTags::Full)
					{
						VERIFY_READ_SIZE(numFrames16)
						readFullStack = true;
					}
					else
					{
						loadSuccess = false;
						break;
					}

					if (m_swapEndian)
						numFrames16 = Endian::swap(numFrames16);

					numFrames32 = numFrames16;
					if (numFrames32 > 512)
					{
						loadSuccess = false;
						break;
					}

					if (m_swapEndian && stackTraceHash)
						stackTraceHash = Endian::swap(stackTraceHash);

					StackTrace* st = NULL;

					if (readFullStack)
					{
						if (m_64bit)
						{
							for (uint32_t i=0; i<numFrames32; ++i)
								if (loader.readVar(backTrace64[i]) != 1)
								{
									loadSuccess = false;
									break;
								}

							if (!loadSuccess)
								break;

							if (m_swapEndian)
								for (uint32_t i=0; i<numFrames32; i++)
									backTrace64[i] = Endian::swap(backTrace64[i]);

							if (!stackTraceHash)
								stackTraceHash = (uint32_t)stackTraceGetHash( backTrace64, numFrames32 );
						}
						else
						{
							for (uint32_t i=0; i<numFrames32; ++i)
								if (loader.readVar(backTrace32[i]) != 1)
								{
									loadSuccess = false;
									break;
								}

							if (!loadSuccess)
								break;

							if (m_swapEndian)
								for (uint32_t i=0; i<numFrames32; i++)
									backTrace32[i] = Endian::swap(backTrace32[i]);

							for (uint32_t i=0; i<numFrames32; i++)
								backTrace64[i] = (uint64_t)backTrace32[i];

							if (!stackTraceHash)
								stackTraceHash = (uint32_t)stackTraceGetHash( backTrace64, numFrames32 );
						}

						bool allocateAndAdd = true;

						StackTraceHashType::iterator it = m_stackTraces.find(stackTraceHash);
						if (it != m_stackTraces.end())
						{
							StackTrace* s = it->second;
							if (stackTraceCompare(s->m_entries, s->m_numEntries, backTrace64, numFrames32))
							{
								allocateAndAdd = false;
								st = s;
							}
						}

						if (allocateAndAdd)
						{
							st = (StackTrace*)m_stackPool.Alloc((uint32_t)(sizeof(StackTrace) + ((numFrames32*4)-1)*sizeof(uint64_t)));
							st->m_next = (StackTrace**)m_stackPool.Alloc((uint32_t)(sizeof(StackTrace*) * (numFrames32+1)));
							memset(st->m_next, 0, sizeof(StackTrace*) * (numFrames32+1));
							memcpy(&st->m_entries[0], backTrace64, numFrames32*sizeof(uint64_t));
							memset(&st->m_entries[numFrames32*2], 0xff, numFrames32 * 2 * sizeof(uint64_t));
							st->m_numEntries = (uint64_t)numFrames32;
							m_stackTraces[stackTraceHash] = st;
						}
					}
					else
					{
						// STACK_TRACE_EXISTS
						st = m_stackTraces[stackTraceHash];
					}

					if (!st)
					{
						loadSuccess = false;
						break;
					}

					// get tag for this operation
					uint32_t tag = 0;
					if (isAlloc(op->m_operationType))
					{
						rtm_vector<uint32_t>& tagStack = perThreadTagStack[op->m_threadID];
						const size_t ss = tagStack.size();
						if (ss)
							tag = tagStack[ss-1];
					}

					// fill the rest of mem op struct
					op->m_stackTrace		= st;
					op->m_chainPrev			= NULL;
					op->m_chainNext			= NULL;
					op->m_tag				= (uint16_t)(tag & 0xffff);
					op->m_isValid			= 1;

					m_operations.push_back(op);

					HeapsType::iterator it = m_Heaps.find(op->m_allocatorHandle);
					if (it == m_Heaps.end())
					{
						char buff[512];
#if RTM_COMPILER_MSVC
						sprintf(buff, "0x%llx", op->m_allocatorHandle);
#else
						sprintf(buff, "0x%lux", op->m_allocatorHandle);
#endif
						m_Heaps[op->m_allocatorHandle] = buff;
					}
				}
				break;

			case rmem::LogMarkers::RegisterTag:
				{
					char tagName[1024];
					char tagParentName[1024];
					uint32_t tagHash;
					uint32_t tagParentHash = 0;

					ReadString<1024>(tagName, loader, m_swapEndian);
					ReadString<1024>(tagParentName, loader, m_swapEndian);
					VERIFY_READ_SIZE(tagHash)
					if (strlen(tagParentName) != 0)
					{
						VERIFY_READ_SIZE(tagParentHash)
					}

					if (m_swapEndian)
					{
						tagHash			= Endian::swap(tagHash);
						tagParentHash	= Endian::swap(tagParentHash);
					}

					addMemoryTag(tagName,tagHash,tagParentHash);
				}
				break;

			case rmem::LogMarkers::EnterTag:
				{
					uint32_t tagHash;
					uint64_t threadID;

					VERIFY_READ_SIZE(tagHash)
					VERIFY_READ_SIZE(threadID)

					if (m_swapEndian)
					{
						tagHash		= Endian::swap(tagHash);
						threadID	= Endian::swap(threadID);
					}

					rtm_vector<uint32_t>& tagStack = perThreadTagStack[threadID];
					tagStack.push_back(tagHash);
				}
				break;

			case rmem::LogMarkers::LeaveTag:
				{
					uint32_t tagHash;
					uint64_t threadID;

					VERIFY_READ_SIZE(tagHash)
					VERIFY_READ_SIZE(threadID)

					if (m_swapEndian)
					{
						tagHash		= Endian::swap(tagHash);
						threadID	= Endian::swap(threadID);
					}

					rtm_vector<uint32_t>& tagStack = perThreadTagStack[threadID];
					tagStack.pop_back();
				}
				break;

			case rmem::LogMarkers::RegisterMarker:
				{
					char markerName[1024];
					uint32_t markerNameHash;
					uint32_t markerColor;

					ReadString<1024>(markerName, loader, m_swapEndian);
					VERIFY_READ_SIZE(markerNameHash)
					VERIFY_READ_SIZE(markerColor)

					if (m_swapEndian)
					{
						markerNameHash	= Endian::swap(markerNameHash);
						markerColor		= Endian::swap(markerColor);
					}

					MemoryMarkerEvent me;
					me.m_color		= markerColor;
					me.m_name		= markerName;
					me.m_nameHash	= markerNameHash;
					m_memoryMarkers[markerNameHash] = me;
				}
				break;

			case rmem::LogMarkers::Marker:
				{
					uint32_t markerNameHash;
					uint64_t threadID;
					uint64_t time;

					VERIFY_READ_SIZE(markerNameHash)
					VERIFY_READ_SIZE(threadID)
					VERIFY_READ_SIZE(time)

					if (m_swapEndian)
					{
						markerNameHash	= Endian::swap(markerNameHash);
						threadID		= Endian::swap(threadID);
						time			= Endian::swap(time);
					}

					if (minMarkerTime > time)
						minMarkerTime = time;

					MemoryMarkerEvent* evt = &m_memoryMarkers[markerNameHash];
					RTM_ASSERT(evt != NULL, "");

					MemoryMarkerTime mt;
					mt.m_threadID	= threadID;
					mt.m_event		= evt;
					mt.m_time		= time;
					m_memoryMarkerTimes.push_back(mt);
				}
				break;

			case rmem::LogMarkers::Module:
				{
					uint8_t sz;
					uint64_t modBase;
					uint32_t modSize;
					VERIFY_READ_SIZE(sz);
					char modName[1024];
					if (sz == 1)
					{
						ReadString<1024>(modName, loader, m_swapEndian);
					}
					else
					{
						char16_t modNameC[1024];
						ReadString<1024>(modNameC, loader, m_swapEndian);
						strcpy(modName, QString::fromUtf16(modNameC).toUtf8().constData());
					}

					VERIFY_READ_SIZE(modBase);
					VERIFY_READ_SIZE(modSize);

					if (m_swapEndian)
					{
						modBase = Endian::swap(modBase);
						modSize = Endian::swap(modSize);
					}

					addModule(modName, modBase, modSize);
				}
				break;

			case rmem::LogMarkers::Allocator:
				{
					char		allocatorName[1024];
					uint64_t	allocatorHandle;

					ReadString<1024>(allocatorName, loader, m_swapEndian);
					VERIFY_READ_SIZE(allocatorHandle);
					if (m_swapEndian)
						allocatorHandle = Endian::swap(allocatorHandle);

					m_Heaps[allocatorHandle] = allocatorName;
				}
				break;

			default:
				loadSuccess = false;
				break;
		};
	}

	// tolerate invalid data at the end of file
	Capture::LoadResult loadResult = Capture::LoadSuccess;
	if (loadSuccess == false)
	{
		uint64_t pos = loader.tell();
		if ((fileSize - pos < 1000) || (m_operations.size() > 0))
		{
			loadResult	= Capture::LoadPartial;
			loadSuccess	= true;
		}
	}

	fclose(f);

	if (loadSuccess == false)
	{
		if (m_loadProgressCallback)
			m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Error reading .MTuner file!");

		clearData();
		return Capture::LoadFail;
	}

	if (m_loadProgressCallback)
		m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Sorting...");

#if RTM_PLATFORM_WINDOWS && RTM_COMPILER_MSVC
	pSortOpsTime psTime(m_operations);
	concurrency::parallel_radixsort(m_operations.begin(), m_operations.end(), psTime);
#else
	std::stable_sort(m_operations.begin(), m_operations.end(), psTime);
#endif

	if (!setLinksAndRemoveInvalid(minMarkerTime))
	{
		if (m_loadProgressCallback)
			m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Invalid data in .MTuner file!");

		clearData();
		return Capture::LoadFail;
	}

	calculateGlobalStats();

	if (!verifyGlobalStats())
	{
		if (m_loadProgressCallback)
			m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Invalid data in .MTuner file!");

		clearData();
		return Capture::LoadFail;
	}

	return loadResult;
}

//--------------------------------------------------------------------------
///
//--------------------------------------------------------------------------
void Capture::setFilteringEnabled(bool inState)
{
	m_filteringEnabled = inState;
	if (m_filteringEnabled)
		calculateFilteredData();
}

//--------------------------------------------------------------------------
/// Returns true if operation is inside the filtering criteria
//--------------------------------------------------------------------------
bool Capture::isInFilter(MemoryOperation* _op)
{
	if (!m_filteringEnabled)
		return true;

	if ((m_currentHeap != (uint64_t)-1) && (_op->m_allocatorHandle != m_currentHeap))
		return false;

	if ((m_filter.m_histogramIndex != (uint32_t)-1) && (m_filter.m_histogramIndex != getHistogramBinIndex(_op->m_allocSize)))
		return false;

	if ((m_filter.m_tagHash != 0) && (m_filter.m_tagHash != _op->m_tag))
		return false;

	if ((m_filter.m_threadID != 0) && (m_filter.m_threadID != _op->m_threadID))
		return false;

	if (_op->m_operationTime < m_filter.m_minTimeSnapshot)
		return false;

	if (_op->m_operationTime > m_filter.m_maxTimeSnapshot)
		return false;

	return true;
}

//--------------------------------------------------------------------------
/// Selects the bin for snapshot filtering
//--------------------------------------------------------------------------
void Capture::selectHistogramBin(uint32_t _index)
{
	if (_index != m_filter.m_histogramIndex)
	{
		m_filter.m_histogramIndex = _index;
		calculateSnapshotStats();
	}
}

//--------------------------------------------------------------------------
/// Removes the histogram bin filter
//--------------------------------------------------------------------------
void Capture::deselectHistogramBin()
{
	if (m_filter.m_histogramIndex != 0xffffffff)
	{
		m_filter.m_histogramIndex = 0xffffffff;
		calculateSnapshotStats();
	}
}

//--------------------------------------------------------------------------
/// Selects the tag for snapshot filtering
//--------------------------------------------------------------------------
void Capture::selectTag(uint32_t _tagHash)
{
	if (_tagHash != m_filter.m_tagHash)
	{
		m_filter.m_tagHash = _tagHash;
		calculateSnapshotStats();
	}
}

//--------------------------------------------------------------------------
/// Removes the tag filter
//--------------------------------------------------------------------------
void Capture::deselectTag()
{
	if (m_filter.m_tagHash != 0xffffffff)
	{
		m_filter.m_tagHash = 0xffffffff;
		calculateSnapshotStats();
	}
}

//--------------------------------------------------------------------------
/// Selects the thread for snapshot filtering
//--------------------------------------------------------------------------
void Capture::selectThread( uint64_t inThread )
{
	if (inThread != m_filter.m_threadID)
	{
		m_filter.m_threadID = inThread;
		calculateSnapshotStats();
	}
}

//--------------------------------------------------------------------------
/// Removes the thread filter
//--------------------------------------------------------------------------
void Capture::deselectThread()
{
	if (m_filter.m_threadID != 0)
	{
		m_filter.m_threadID = 0;
		calculateSnapshotStats();
	}
}

//--------------------------------------------------------------------------
/// Sets the selected snapshot rage
//--------------------------------------------------------------------------
void Capture::setSnapshot(uint64_t _minTime, uint64_t _maxTime)
{
	if (_minTime < m_minTime)
		return;

	if (_maxTime > m_maxTime)
		return;

	if ((m_filter.m_minTimeSnapshot != _minTime) ||
		(m_filter.m_maxTimeSnapshot != _maxTime))
	{
		m_filter.m_minTimeSnapshot = _minTime;
		m_filter.m_maxTimeSnapshot = _maxTime;

		calculateSnapshotStats();
	}
}

//--------------------------------------------------------------------------
/// Returns memory usage at specified time
//--------------------------------------------------------------------------
void Capture::getGraphAtTime(uint64_t _time, GraphEntry& _entry)
{
	uint32_t tIdx;
	uint32_t idx = getIndexBefore(_time,tIdx);
	_entry = m_usageGraph[idx];
}

//--------------------------------------------------------------------------
/// Loads symbol information
//--------------------------------------------------------------------------
bool Capture::loadSymbolInfo(BinLoader& _loader, uint64_t _fileSize)
{
	uint32_t symbolInfoSize;
	_loader.readVar(symbolInfoSize);

	if (m_swapEndian)
		symbolInfoSize = Endian::swap(symbolInfoSize);

	int64_t symSize = (int64_t)symbolInfoSize;
	while (symSize > 0)
	{
		char16_t exePath[1024];

		uint64_t modBase;
		uint64_t modSize;

		size_t bytesRead = 0;
		bytesRead += ReadString<1024>(exePath, _loader, m_swapEndian, 0x23);
		if (bytesRead == sizeof(uint32_t))
			break;

		bytesRead += sizeof(uint64_t) * _loader.readVar(modBase);
		bytesRead += sizeof(uint64_t) * _loader.readVar(modSize);

		QByteArray executablePath = QString::fromUtf16((const ushort*)exePath).toUtf8();
		rtm::pathRemoveRelative(executablePath.data());

		if (m_swapEndian)
		{
			modBase = Endian::swap(modBase);
			modSize = Endian::swap(modSize);
		}

		addModule(executablePath.constData(), modBase, modSize);

		if (m_loadProgressCallback)
		{
			uint64_t pos = _loader.tell();

			float percent = float(pos)*100.0f / float(_fileSize);
			char message[2048];
			strcpy(message, "Loading symbols ");
			strcat(message, executablePath.constData());
			m_loadProgressCallback(m_loadProgressCustomData, percent, message);
		}

		symSize -= bytesRead;
	}

	return symSize == 0;
}

//--------------------------------------------------------------------------
/// Builds stack trace trees and group operations by type/call stack/size
//--------------------------------------------------------------------------
void Capture::buildAnalyzeData(uintptr_t _symResolver)
{
	RTM_ASSERT(_symResolver != 0, "Invalid symbol resolver!");

	// get stack traces unique IDs
	StackTraceHashType::iterator it  = m_stackTraces.begin();
	StackTraceHashType::iterator end = m_stackTraces.end();

	const uint32_t numStackTraces = (uint32_t)m_stackTraces.size();
	uint32_t nextProgressPoint = 0;
	uint32_t numOpsOver100 = numStackTraces/100;
	uint32_t idx = 0;

	while (it != end)
	{
		StackTrace* st = it->second;
		
		int numFrames = (int)st->m_numEntries;

		bool countSkippable = true;
		int skip = 0;

		for (int i=0; i<numFrames; ++i)
		{
			bool currentSymbolInMTunerDLL = true;
			st->m_entries[i + numFrames] = rdebug::symbolResolverGetAddressID(_symResolver, st->m_entries[i], &currentSymbolInMTunerDLL);

			if (!currentSymbolInMTunerDLL)
				countSkippable = false;

			if (countSkippable)
				++skip;
		}

		// remove mtunerdll from the top of call stack
		if (skip)
		{
			const uint32_t newCount = numFrames - skip;
			for (uint32_t i=0; i<newCount; ++i)
				st->m_entries[i]			= st->m_entries[i + skip];

			for (uint32_t i=0; i<newCount; ++i)
				st->m_entries[i + newCount]	= st->m_entries[i + numFrames + skip];

			memset(&st->m_entries[newCount*2], 0xff, newCount*2*sizeof(uint64_t));
			st->m_numEntries = newCount;
		}
	
		st->m_addedToTree[0] = 0;
		++it;

		if ((idx > nextProgressPoint) && m_loadProgressCallback)
		{
			nextProgressPoint += numOpsOver100;
			float percent = float(idx) / float(numOpsOver100);
			m_loadProgressCallback(m_loadProgressCustomData, percent, "Generating unique symbol IDs...");
		}
		++idx;
	}

	MemoryTagTree* prevTag = NULL;

	const uint32_t numOps = (uint32_t)m_operations.size();
	nextProgressPoint = 0;
	numOpsOver100 = numOps/100;
	
	for (uint32_t i=0; i<numOps; i++)
	{
		if ((i > nextProgressPoint) && m_loadProgressCallback)
		{
			nextProgressPoint += numOpsOver100;
			float percent = float(i) / float(numOpsOver100);
			m_loadProgressCallback(m_loadProgressCustomData, percent, "Building analysis data...");
		}

		MemoryOperation* op = m_operations[i];

		if (op->m_chainNext)
		{
			if (op->m_chainNext->m_tag == 0)
				op->m_chainNext->m_tag = op->m_tag;
		}
		else
		{
			bool isFreed = op->m_operationType == rmem::LogMarkers::OpFree;
			isFreed = isFreed || ((op->m_operationType == rmem::LogMarkers::OpRealloc) && (op->m_allocSize == 0));
			isFreed = isFreed || ((op->m_operationType == rmem::LogMarkers::OpReallocAligned) && (op->m_allocSize == 0));

			if (!isFreed)
				m_memoryLeaks.push_back(op);
		}

		// add to memory groups
		addToMemoryGroups(m_operationGroups, op);

		// add to call stack tree
 		addToStackTraceTree(m_stackTraceTree, op, StackTrace::GlobalOffset);

		// add to tag tree
		tagAddOp(m_tagTree, op, prevTag);

		// add to heaps list
		addHeap(m_Heaps, op->m_allocatorHandle);
	}

	if (m_loadProgressCallback)
		m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Done!");
}

//--------------------------------------------------------------------------
/// Links operations that are performed on the same address/memory block
//--------------------------------------------------------------------------
bool Capture::setLinksAndRemoveInvalid(uint64_t inMinMarkerTime)
{
	rtm_unordered_map<uint64_t, MemoryOperation*> opMap;
	uint32_t numOps = (uint32_t)m_operations.size();
	uint32_t nextProgressPoint = 0;
	uint32_t numOpsOver100 = numOps/100;

	for (uint32_t i=0; i<numOps; i++)
	{
		MemoryOperation* op = m_operations[i];

		if ((i > nextProgressPoint) && m_loadProgressCallback)
		{
			nextProgressPoint += numOpsOver100;
			float percent = float(i) / float(numOpsOver100);
			m_loadProgressCallback(m_loadProgressCustomData, percent, "Processing...");
		}

		RTM_ASSERT(op->m_chainPrev == NULL, "");
		RTM_ASSERT(op->m_chainNext == NULL, "");

		switch (op->m_operationType)
		{
		case rmem::LogMarkers::OpAlloc:
		case rmem::LogMarkers::OpCalloc:
		case rmem::LogMarkers::OpAllocAligned:
			{
				rtm_unordered_map<uint64_t, MemoryOperation*>::iterator it = opMap.find(op->m_pointer);
				if (it == opMap.end())
				{
					opMap[op->m_pointer] = op;
				}
				else
				{
					MemoryOperation* oldOp = it->second;
					oldOp->m_isValid = 0;

					opMap[op->m_pointer] = op;
				}
			}
			break;

		case rmem::LogMarkers::OpRealloc:
		case rmem::LogMarkers::OpReallocAligned:
			{
				// ako vec postoji op koji pokazuje na isti blok
				rtm_unordered_map<uint64_t, MemoryOperation*>::iterator it = opMap.find(op->m_pointer);
				if (it != opMap.end())
				{
					// onda op mora da bude realloc koji vraca blok na istoj lokaciji
					if (op->m_previousPointer != op->m_pointer)
					{
						op->m_isValid = 0;
						continue;
					}

					opMap.erase(it);
				}

				MemoryOperation* oldOp = NULL;

				// ako postoji prethodni pointer onda mora da postoji op u mapi sa tim rezultatom - rezultat moze da bude isti
				if (op->m_previousPointer)
				{
					rtm_unordered_map<uint64_t, MemoryOperation*>::iterator itP = opMap.find(op->m_previousPointer);
					if (itP == opMap.end())
					{
						op->m_isValid = 0; // mora da postoji op u mapi sa tim rezultatom
						continue;
					}
					else
						oldOp = itP->second;

					if (op->m_pointer != op->m_previousPointer) // izbaciti prethodni blok jer jer realociran
						opMap.erase(itP);
				}

				if (oldOp)
				{
					op->m_chainPrev = oldOp;
					oldOp->m_chainNext = op;
				}

				opMap[op->m_pointer] = op;
			}
			break;

		case rmem::LogMarkers::OpFree:
			{
				rtm_unordered_map<uint64_t, MemoryOperation*>::iterator it = opMap.find(op->m_pointer);
				if (it == opMap.end())
				{
					op->m_isValid = 0;
				}
				else
				{
					MemoryOperation* oldOp = it->second;
					RTM_ASSERT(oldOp->m_operationType != rmem::LogMarkers::OpFree, "");

					oldOp->m_chainNext = op;
					op->m_chainPrev = oldOp;
					op->m_allocSize	= oldOp->m_allocSize;
					op->m_overhead	= oldOp->m_overhead;

					opMap.erase(it);
				}
			}
			break;
		};
	}

	/// Remove invalid operations
	rtm_vector<MemoryOperation*>::iterator newEnd = std::remove_if( m_operations.begin(), m_operations.end(), isInvalid );
	size_t newSize = newEnd -  m_operations.begin();
	m_operations.resize(newSize);

	// get time range
	numOps = (uint32_t)m_operations.size();
	
	if (numOps == 0)
		return false;

	m_minTime = m_operations[0]->m_operationTime;
	if (m_minTime > inMinMarkerTime)
		m_minTime = inMinMarkerTime;
	m_maxTime = m_operations[numOps-1]->m_operationTime;

	m_filter.m_minTimeSnapshot = m_minTime;
	m_filter.m_maxTimeSnapshot = m_maxTime;

	if (m_loadProgressCallback)
		m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Processing...");

	return true;
}

//--------------------------------------------------------------------------
/// Find module information corresponding to the given address
//--------------------------------------------------------------------------
bool Capture::findModule(uint64_t inAddress, rdebug::ModuleInfo& outInfo)
{
	size_t numModules = m_moduleInfos.size();
	for (size_t i=0; i<numModules; i++)
	{
		rdebug::ModuleInfo& info = m_moduleInfos[i];
		if (info.checkAddress(inAddress))
		{
			outInfo = info;
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------------
/// Adds module to list of infos
//--------------------------------------------------------------------------
void Capture::addModule(const char* _path, uint64_t inModBase, uint64_t inModSize)
{
	char exePath[1024];
	strcpy(exePath, _path);

	if (!m_modulePathBuffer)
	{
		m_modulePathBuffer = new char[128*1024];
		m_modulePathBufferPtr = 0;
	}
	
	size_t numModules = m_moduleInfos.size();
	for (size_t i=0; i<numModules; i++)
	{
		rdebug::ModuleInfo& info = m_moduleInfos[i];
		if (strcmp(info.m_modulePath, _path) == 0)
		{
			if (inModBase == info.m_baseAddress)
				return;
		}
	}

	char* moduleName = strstr(exePath, "/");
	if (!moduleName)
		moduleName = strstr(exePath, "\\");
	char* nextSlash = 0;
	do {
		if (moduleName)
		{
			nextSlash = strstr(moduleName, "/");
			if (!nextSlash)
				nextSlash = strstr(moduleName, "\\");
		}
		if (nextSlash != NULL)
			moduleName = nextSlash+1;
	} while (nextSlash);

	if (moduleName == NULL)
		return;

	strcpy(&m_modulePathBuffer[m_modulePathBufferPtr], _path);

	rdebug::ModuleInfo info;
	info.m_baseAddress	= inModBase;
	info.m_size			= inModSize;
	strcpy(info.m_modulePath, &m_modulePathBuffer[m_modulePathBufferPtr]);
	m_modulePathBufferPtr += (uint32_t)strlen(_path)+1;

	m_moduleInfos.push_back(info);
}

//--------------------------------------------------------------------------
/// Calculates statistics for entire binary
//--------------------------------------------------------------------------
void Capture::calculateGlobalStats()
{
	if (m_loadProgressCallback)
		m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Calculating stats...");

	memset(&m_statsGlobal, 0, sizeof(MemoryStats));
	
	MemoryStatsLocalPeak localPeak;
	memset(&localPeak, 0, sizeof(MemoryStatsLocalPeak));

	const size_t numOps = m_operations.size();

	uint32_t timedGranularityMask = getGranularityMask(numOps);

	for (size_t i=0; i<numOps; i++)
	{
		MemoryOperation* op = m_operations[i];
		
		if ((i & timedGranularityMask) == 0)
		{
			MemoryStatsTimed st;
			st.m_time			= op->m_operationTime;
			st.m_operationIndex	= (uint32_t)i;
			st.m_localPeak		= localPeak;
			st.m_stats			= m_statsGlobal;
			m_timedStats.emplace_back(st);

			// reset local peak structure
			memset(&localPeak, 0, sizeof(MemoryStatsLocalPeak));
		}

		++m_statsGlobal.m_numberOfOperations;

		switch (op->m_operationType)
		{
		case rmem::LogMarkers::OpAlloc:
		case rmem::LogMarkers::OpCalloc:
		case rmem::LogMarkers::OpAllocAligned:
			{
				const uint32_t binIdx = fillStats_Alloc(op, m_statsGlobal);

				// update local peak struct
				localPeak.m_memoryUsagePeak							= Max(localPeak.m_memoryUsagePeak, m_statsGlobal.m_memoryUsage);
				localPeak.m_overheadPeak							= Max(localPeak.m_overheadPeak, m_statsGlobal.m_overhead);
				localPeak.m_numberOfLiveBlocksPeak					= Max(localPeak.m_numberOfLiveBlocksPeak, m_statsGlobal.m_numberOfLiveBlocks);
				localPeak.m_HistogramPeak[binIdx].m_sizePeak		= Max(localPeak.m_HistogramPeak[binIdx].m_sizePeak, m_statsGlobal.m_histogram[binIdx].m_size);
				localPeak.m_HistogramPeak[binIdx].m_overheadPeak	= Max(localPeak.m_HistogramPeak[binIdx].m_overheadPeak, m_statsGlobal.m_histogram[binIdx].m_overhead);
				localPeak.m_HistogramPeak[binIdx].m_countPeak		= Max(localPeak.m_HistogramPeak[binIdx].m_countPeak, m_statsGlobal.m_histogram[binIdx].m_count);
			}
			break;

		case rmem::LogMarkers::OpRealloc:
		case rmem::LogMarkers::OpReallocAligned:
			{
				const uint32_t binIdx = fillStats_ReAlloc(op, m_statsGlobal);

				// update local peak struct
				localPeak.m_memoryUsagePeak							= Max(localPeak.m_memoryUsagePeak, m_statsGlobal.m_memoryUsage);
				localPeak.m_overheadPeak							= Max(localPeak.m_overheadPeak, m_statsGlobal.m_overhead);
				localPeak.m_numberOfLiveBlocksPeak					= Max(localPeak.m_numberOfLiveBlocksPeak, m_statsGlobal.m_numberOfLiveBlocks);
				localPeak.m_HistogramPeak[binIdx].m_sizePeak		= Max(localPeak.m_HistogramPeak[binIdx].m_sizePeak, m_statsGlobal.m_histogram[binIdx].m_size);
				localPeak.m_HistogramPeak[binIdx].m_overheadPeak	= Max(localPeak.m_HistogramPeak[binIdx].m_overheadPeak, m_statsGlobal.m_histogram[binIdx].m_overhead);
				localPeak.m_HistogramPeak[binIdx].m_countPeak		= Max(localPeak.m_HistogramPeak[binIdx].m_countPeak, m_statsGlobal.m_histogram[binIdx].m_count);
			}
			break;

		case rmem::LogMarkers::OpFree:
			{
				fillStats_Free(op, m_statsGlobal);
			}
			break;
		};

		GraphEntry entry;
		entry.m_usage			= m_statsGlobal.m_memoryUsage;
		entry.m_numLiveBlocks	= m_statsGlobal.m_numberOfLiveBlocks;
		m_usageGraph.emplace_back(entry);
	}

	MemoryStatsTimed st;
	st.m_time		= m_operations[m_operations.size()-1]->m_operationTime;
	st.m_operationIndex	= (uint32_t)(m_operations.size()-1);
	st.m_localPeak	= localPeak;
	st.m_stats		= m_statsGlobal;
	m_timedStats.push_back(st);

	m_statsSnapshot = m_statsGlobal;

	if (m_loadProgressCallback)
		m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Loading complete!");
}

bool Capture::verifyGlobalStats()
{
	if (m_statsGlobal.m_memoryUsage		& UINT64_C(0x8000000000000000)) return false;
	if (m_statsGlobal.m_memoryUsagePeak	& UINT64_C(0x8000000000000000))	return false;
	if (m_statsGlobal.m_overhead				& UINT32_C(0x80000000))	return false;
	if (m_statsGlobal.m_overheadPeak			& UINT32_C(0x80000000))	return false;
	if (m_statsGlobal.m_numberOfOperations		& UINT32_C(0x80000000))	return false;
	if (m_statsGlobal.m_numberOfAllocations		& UINT32_C(0x80000000))	return false;
	if (m_statsGlobal.m_numberOfReAllocations	& UINT32_C(0x80000000))	return false;
	if (m_statsGlobal.m_numberOfFrees			& UINT32_C(0x80000000))	return false;
	if (m_statsGlobal.m_numberOfLiveBlocks		& UINT32_C(0x80000000))	return false;

	for (unsigned i=0; i<MemoryStats::NUM_HISTOGRAM_BINS; ++i)
	{
		if (m_statsGlobal.m_histogram[i].m_size		& UINT64_C(0x8000000000000000)) return false;
		if (m_statsGlobal.m_histogram[i].m_sizePeak	& UINT64_C(0x8000000000000000)) return false;
		if (m_statsGlobal.m_histogram[i].m_overhead			& UINT32_C(0x80000000))	return false;
		if (m_statsGlobal.m_histogram[i].m_overheadPeak		& UINT32_C(0x80000000))	return false;
		if (m_statsGlobal.m_histogram[i].m_count			& UINT32_C(0x80000000))	return false;
		if (m_statsGlobal.m_histogram[i].m_countPeak		& UINT32_C(0x80000000))	return false;
	}

	return true;
}

//--------------------------------------------------------------------------
/// Calculates filtered data
//--------------------------------------------------------------------------
void Capture::calculateFilteredData()
{
	StackTraceHashType::iterator it  = m_stackTraces.begin();
	StackTraceHashType::iterator end = m_stackTraces.end();

	const uint32_t numStackTraces = (uint32_t)m_stackTraces.size();
	uint32_t nextProgressPoint = 0;
	uint32_t numOpsOver100 = numStackTraces/100;
	uint32_t idx = 0;

	while (it != end)
	{
		StackTrace* st = it->second;
		st->m_addedToTree[1] = 0;
		memset(&st->m_entries[st->m_numEntries*3], 0xff, (size_t)st->m_numEntries*sizeof(uint64_t));

		++it;

		if ((idx > nextProgressPoint) && m_loadProgressCallback)
		{
			nextProgressPoint += numOpsOver100;
			float percent = float(idx) / float(numOpsOver100);
			m_loadProgressCallback(m_loadProgressCustomData, percent, "Fixing up stack traces...");
		}
		++idx;
	}


	uint32_t minTimedIdx;
	uint32_t maxTimedIdx;
	const uint32_t minTimeOpIndex = getIndexBefore(m_filter.m_minTimeSnapshot,minTimedIdx);
	const uint32_t maxTimeOpIndex = getIndexBefore(m_filter.m_maxTimeSnapshot,maxTimedIdx) + 1;
	
	m_filter.m_operations.clear();
	m_filter.m_operations.reserve(maxTimeOpIndex - minTimeOpIndex);

	m_filter.m_operationGroups.clear();

	destroyStackTree(m_filter.m_stackTraceTree);

	const uint32_t numOps = maxTimeOpIndex - minTimeOpIndex;
	nextProgressPoint = minTimeOpIndex;
	numOpsOver100 = numOps/100;

	MemoryTagTree* prevTag = NULL;

	for (uint32_t i=minTimeOpIndex; i<=maxTimeOpIndex; i++)
	{
		MemoryOperation* op = m_operations[i];
		
		if ((i > nextProgressPoint) && m_loadProgressCallback)
		{
			float percent = float(i-minTimedIdx) / float(numOpsOver100);
			m_loadProgressCallback(m_loadProgressCustomData, percent, "Building filtered data...");
		}
		
		if (!isInFilter(op))
			continue;

		m_filter.m_operations.push_back(op);

		// add to memory groups
		addToMemoryGroups(m_filter.m_operationGroups, op);

		// add to call stack tree
		addToStackTraceTree(m_filter.m_stackTraceTree, op, StackTrace::FilterOffset);

		// add to tag tree
		tagAddOp(m_filter.m_tagTree, op, prevTag);
	}

	if (m_loadProgressCallback)
		m_loadProgressCallback(m_loadProgressCustomData, 100.0f, "Done!");
}

//--------------------------------------------------------------------------
/// Returns the index of first operation before the given time
//--------------------------------------------------------------------------
uint32_t Capture::getIndexBefore(uint64_t _time, uint32_t& _outTimedIndex) const
{
	uint32_t tsIdx = 0;
	int32_t tsIdxMin = 0;
	int32_t tsIdxMax = (uint32_t)m_timedStats.size()-1;
	
	if (tsIdxMax == 1)
		tsIdx = 1;
	else
	{
		while (tsIdxMax > tsIdxMin)
		{
			uint32_t tsIdxMid = (tsIdxMin + tsIdxMax) / 2;

			if (m_timedStats[tsIdxMid].m_time < _time)
				tsIdxMin = tsIdxMid;
			else
				tsIdxMax = tsIdxMid;

			if (tsIdxMax-tsIdxMin == 1)
			{
				tsIdx = tsIdxMax;
				break;
			}
		}
	}

	uint32_t startIdx = m_timedStats[tsIdx-1].m_operationIndex;
	uint32_t endIdx = m_timedStats[tsIdx].m_operationIndex + 1;
	
	_outTimedIndex = tsIdx - 1;

	while (endIdx > startIdx)
	{
		uint32_t idxMid = (startIdx + endIdx) / 2;

		if (m_operations[idxMid]->m_operationTime >= _time)
			endIdx = idxMid;
		else
			startIdx = idxMid;

		if (endIdx-startIdx == 1)
		{
			if (m_operations[startIdx]->m_operationTime >= _time)
				return (startIdx == 0) ? startIdx : startIdx - 1;
			else
				return endIdx - 1;
		}
	}

	RTM_ASSERT(false, "Should not reach here!");
	return 0;
}

uint32_t Capture::getIndexAfter(uint64_t _time, uint32_t& _outTimedIndex) const
{
	uint32_t tsIdx = 0;
	int32_t tsIdxMin = 0;
	int32_t tsIdxMax = (uint32_t)m_timedStats.size()-1;
	
	while (tsIdxMax > tsIdxMin)
	{
		uint32_t tsIdxMid = (tsIdxMin + tsIdxMax) / 2;

		if (m_timedStats[tsIdxMid].m_time < _time)
			tsIdxMin = tsIdxMid;
		else
			tsIdxMax = tsIdxMid;

		if (tsIdxMax-tsIdxMin == 1)
		{
			tsIdx = tsIdxMax;
			break;
		}
	}

	uint32_t startIdx = m_timedStats[tsIdx-1].m_operationIndex;
	uint32_t endIdx = m_timedStats[tsIdx].m_operationIndex + 1;
	
	_outTimedIndex = tsIdx - 1;

	while (endIdx > startIdx)
	{
		uint32_t idxMid = (startIdx + endIdx) / 2;

		if (m_operations[idxMid]->m_operationTime >= _time)
			endIdx = idxMid;
		else
			startIdx = idxMid;

		if (endIdx-startIdx == 1)
		{
			if (m_operations[startIdx]->m_operationTime >= _time)
				return startIdx + 1;
			else
				return endIdx;
		}
	}

	RTM_ASSERT(false, "Should not reach here!");
	return 0;
}

//--------------------------------------------------------------------------
/// Calculates statistics for the selected time slice
//--------------------------------------------------------------------------
void Capture::calculateSnapshotStats()
{
	uint32_t minTimedIdx;
	uint32_t maxTimedIdx;
	uint32_t minTimeOpIndex = getIndexBefore(m_filter.m_minTimeSnapshot, minTimedIdx);
	uint32_t maxTimeOpIndex = getIndexAfter(m_filter.m_maxTimeSnapshot, maxTimedIdx);
	
	if (minTimeOpIndex != 0)
		minTimeOpIndex++;

	MemoryStats startStats = m_timedStats[minTimedIdx].m_stats; 
	m_statsSnapshot = startStats;

	// check if it's fully manual 
	if (maxTimedIdx - minTimedIdx < 2)
	{
		const uint32_t startIndex = m_timedStats[minTimedIdx].m_operationIndex;
		GetRangedStats(m_statsSnapshot, startIndex, minTimeOpIndex);
		m_statsSnapshot.setPeaksToCurrent();

		GetRangedStats(m_statsSnapshot, minTimeOpIndex, maxTimeOpIndex);

		m_statsSnapshot.m_numberOfOperations	-= startStats.m_numberOfOperations;
		m_statsSnapshot.m_numberOfAllocations	-= startStats.m_numberOfAllocations;
		m_statsSnapshot.m_numberOfFrees			-= startStats.m_numberOfFrees;
		m_statsSnapshot.m_numberOfReAllocations	-= startStats.m_numberOfReAllocations;
	}
	else
	{
		const uint32_t startIndex1	= m_timedStats[minTimedIdx].m_operationIndex;
		RTM_ASSERT(startIndex1 <= minTimeOpIndex, "");
		GetRangedStats(startStats, startIndex1, minTimeOpIndex);
		m_statsSnapshot = startStats;
		m_statsSnapshot.setPeaksToCurrent();
		GetRangedStats(m_statsSnapshot, minTimeOpIndex, m_timedStats[minTimedIdx+1].m_operationIndex);

		MemoryStatsLocalPeak localPeak;
		localPeak.m_memoryUsagePeak = m_statsSnapshot.m_memoryUsage;
		localPeak.m_overheadPeak	= m_statsSnapshot.m_overhead;
		for (uint32_t i=0; i<MemoryStats::NUM_HISTOGRAM_BINS; i++)
		{
			localPeak.m_HistogramPeak[i].m_sizePeak		= m_statsSnapshot.m_histogram[i].m_sizePeak;
			localPeak.m_HistogramPeak[i].m_overheadPeak	= m_statsSnapshot.m_histogram[i].m_overheadPeak;
			localPeak.m_HistogramPeak[i].m_countPeak	= m_statsSnapshot.m_histogram[i].m_countPeak;
		}
		
		for (uint32_t t=minTimedIdx+2; t<=maxTimedIdx; t++)
		{
			MemoryStatsLocalPeak& peakT = m_timedStats[t].m_localPeak;

			localPeak.m_memoryUsagePeak	= Max(localPeak.m_memoryUsagePeak, peakT.m_memoryUsagePeak);
			localPeak.m_overheadPeak	= Max(localPeak.m_overheadPeak, peakT.m_overheadPeak);

			for (uint32_t i=0; i<MemoryStats::NUM_HISTOGRAM_BINS; i++)
			{
				localPeak.m_HistogramPeak[i].m_sizePeak		= Max(localPeak.m_HistogramPeak[i].m_sizePeak, peakT.m_HistogramPeak[i].m_sizePeak);
				localPeak.m_HistogramPeak[i].m_overheadPeak	= Max(localPeak.m_HistogramPeak[i].m_overheadPeak, peakT.m_HistogramPeak[i].m_overheadPeak);
				localPeak.m_HistogramPeak[i].m_countPeak	= Max(localPeak.m_HistogramPeak[i].m_countPeak, peakT.m_HistogramPeak[i].m_countPeak);
			}
		}

		m_statsSnapshot.setPeaksFrom(localPeak);
		MemoryStatsTimed& ts = m_timedStats[maxTimedIdx];
		const uint32_t startIndex2	= ts.m_operationIndex;

		m_statsSnapshot.m_memoryUsage			= ts.m_stats.m_memoryUsage;
		m_statsSnapshot.m_overhead				= ts.m_stats.m_overhead;
		m_statsSnapshot.m_numberOfOperations	= ts.m_stats.m_numberOfOperations - startStats.m_numberOfOperations;
		m_statsSnapshot.m_numberOfAllocations	= ts.m_stats.m_numberOfAllocations - startStats.m_numberOfAllocations;
		m_statsSnapshot.m_numberOfFrees			= ts.m_stats.m_numberOfFrees - startStats.m_numberOfFrees;
		m_statsSnapshot.m_numberOfReAllocations	= ts.m_stats.m_numberOfReAllocations - startStats.m_numberOfReAllocations;
		m_statsSnapshot.m_numberOfLiveBlocks	= ts.m_stats.m_numberOfLiveBlocks;

		for (uint32_t i=0; i<MemoryStats::NUM_HISTOGRAM_BINS; i++)
		{
			m_statsSnapshot.m_histogram[i].m_size		= ts.m_stats.m_histogram[i].m_size;
			m_statsSnapshot.m_histogram[i].m_overhead	= ts.m_stats.m_histogram[i].m_overhead;
			m_statsSnapshot.m_histogram[i].m_count		= ts.m_stats.m_histogram[i].m_count;
		}

		GetRangedStats(m_statsSnapshot, startIndex2, maxTimeOpIndex+1);
	}
}

//--------------------------------------------------------------------------
/// Calculates the stats inside the given range
//--------------------------------------------------------------------------
void Capture::GetRangedStats(MemoryStats& _stats, uint32_t _minIdx, uint32_t _maxIdx)
{
	const uint32_t minIdx = _minIdx;
	const uint32_t maxIdx = _maxIdx;

	for (size_t i=minIdx; i<maxIdx; i++)
	{
		MemoryOperation* op = m_operations[i];
		
		++_stats.m_numberOfOperations;

		switch (op->m_operationType)
		{
		case rmem::LogMarkers::OpAlloc:
		case rmem::LogMarkers::OpCalloc:
		case rmem::LogMarkers::OpAllocAligned:
			fillStats_Alloc( op, _stats );
			break;

		case rmem::LogMarkers::OpRealloc:
		case rmem::LogMarkers::OpReallocAligned:
			fillStats_ReAlloc(op, _stats);
			break;

		case rmem::LogMarkers::OpFree:
			fillStats_Free(op, _stats);
			break;
		};
	}
}

//--------------------------------------------------------------------------
/// Registers memory tag with the loader
//--------------------------------------------------------------------------
void Capture::addMemoryTag(char* _tagName, uint32_t _tagHash, uint32_t _parentTagHash)
{
	MemoryTagTree* mtt = new MemoryTagTree();
	mtt->m_hash		= _tagHash;
	mtt->m_name		= _tagName;
	if (!tagInsert(&m_tagTree, mtt, _parentTagHash))
		delete mtt;
}

//--------------------------------------------------------------------------
/// Adds operation to memory groups
//--------------------------------------------------------------------------
void Capture::addToMemoryGroups(rtm_unordered_map<uint32_t, MemoryOperationGroup,uint32_t_hash,uint32_t_equal>& _groups, MemoryOperation* _op)
{
	switch (_op->m_operationType)
	{
		case rmem::LogMarkers::OpAlloc:
		case rmem::LogMarkers::OpCalloc:
		case rmem::LogMarkers::OpAllocAligned:
			{
				uint32_t groupHash = calcGroupHash(_op);
				MemoryOperationGroup& group = _groups[groupHash];
				group.m_operations.push_back(_op);
				group.m_count++;
				group.m_liveCount++;
				group.m_liveCountPeak = Max(group.m_liveCountPeak, group.m_liveCount);
			}
			break;

		case rmem::LogMarkers::OpFree:
			{
				MemoryOperation* prevOp = _op->m_chainPrev;
				uint32_t groupHash;
				if (isInFilter(prevOp))
				{
					groupHash = calcGroupHash(prevOp);
					MemoryOperationGroup& prevGroup = _groups[groupHash];
					prevGroup.m_liveCount--;
				}
				groupHash = calcGroupHash(_op);
				MemoryOperationGroup& group = _groups[groupHash];
				group.m_operations.push_back(_op);
				group.m_count++;
			}
			break;

		case rmem::LogMarkers::OpReallocAligned:
		case rmem::LogMarkers::OpRealloc:
			{
				MemoryOperation* prevOp = _op->m_chainPrev;
				uint32_t groupHash;
				if (prevOp)
				{
					if (isInFilter(prevOp))
					{
						groupHash = calcGroupHash(prevOp);
						MemoryOperationGroup& prevGroup = _groups[groupHash];
						prevGroup.m_liveCount--;
					}
				}
				groupHash = calcGroupHash(_op);
				MemoryOperationGroup& group = _groups[groupHash];
				group.m_operations.push_back(_op);
				group.m_count++;
				group.m_liveCount++;
				group.m_liveCountPeak = Max(group.m_liveCountPeak, group.m_liveCount);
			}
			break;
	};
}

static void addToTree(StackTraceTree* _root, StackTrace* _trace, int64_t _size, int32_t _overhead, StackTrace::Enum _offset, StackTraceTree::Enum _opType)
{
	const int32_t numFrames = (int32_t)_trace->m_numEntries;
	int32_t currFrame = numFrames;
	StackTraceTree* currNode = _root;
	
	currNode->m_memUsage		+= _size;
	currNode->m_memUsagePeak	= Max(currNode->m_memUsage, currNode->m_memUsagePeak);

	currNode->m_overhead		+= _overhead;
	currNode->m_overheadPeak	= Max(currNode->m_overhead, currNode->m_overheadPeak);

	if (_opType != StackTraceTree::COUNT)
		++currNode->m_opCount[_opType];

	// add stack trace to root node
	_trace->m_next[0] = _root->m_stackTraceList;
	_root->m_stackTraceList = _trace;

	while (--currFrame >= 0)
	{
		int32_t depth = numFrames-currFrame;

		const uint64_t currUniqueID = _trace->m_entries[currFrame+numFrames];

		uint64_t& currUniqueIDIdx	= _trace->m_entries[currFrame+numFrames*_offset];

		StackTraceTree* nextNode = 0;

		if (currUniqueIDIdx == (uint64_t)-1)
		{
			size_t numChildren = currNode->m_children.size();
			size_t found = numChildren;
			for (size_t i=0; i<numChildren; i++)
			{
				if (currNode->m_children[i].m_addressID == currUniqueID)
				{
					found			= i;
					currUniqueIDIdx	= (uint64_t)i;
					break;
				}
			}

			if (found == numChildren)
			{
				// not found
				StackTraceTree newNode;
				newNode.m_parent	= currNode;
				newNode.m_addressID	= currUniqueID;
				newNode.m_depth		= depth;
				currNode->m_children.emplace_back(newNode);
				currUniqueIDIdx	= (uint64_t)(currNode->m_children.size() - 1);
				nextNode = &currNode->m_children[numChildren];
			}
			else
				nextNode = &currNode->m_children[found];
		}
		else
			nextNode = &currNode->m_children[(unsigned int)currUniqueIDIdx];

		currNode = nextNode;

		if (_trace->m_addedToTree[_offset-2] < depth)
		{
			_trace->m_next[depth] = currNode->m_stackTraceList;
			currNode->m_stackTraceList = _trace;
			_trace->m_addedToTree[_offset-2] = depth;
		}

		currNode->m_memUsage		+= _size;
		currNode->m_memUsagePeak	= Max(currNode->m_memUsage, currNode->m_memUsagePeak);

		currNode->m_overhead		+= _overhead;
		currNode->m_overheadPeak	= Max(currNode->m_overhead, currNode->m_overheadPeak);

		if (_opType != StackTraceTree::COUNT)
			++currNode->m_opCount[_opType];
	}
}

void Capture::addToStackTraceTree(StackTraceTree& _tree, MemoryOperation* _op, StackTrace::Enum _offset)
{
	switch (_op->m_operationType)
	{
		case rmem::LogMarkers::OpAlloc:
		case rmem::LogMarkers::OpCalloc:
		case rmem::LogMarkers::OpAllocAligned:
			{
				addToTree(&_tree, _op->m_stackTrace, _op->m_allocSize, _op->m_overhead, _offset, StackTraceTree::ALLOC);
			}
			break;

		case rmem::LogMarkers::OpFree:
			{
				MemoryOperation* prevOp = _op->m_chainPrev;
				RTM_ASSERT(prevOp != NULL, "");

				if (isInFilter(prevOp))
					addToTree(&_tree, prevOp->m_stackTrace, -(int64_t)prevOp->m_allocSize, -(int32_t)prevOp->m_overhead, _offset, StackTraceTree::FREE);
				else
					addToTree(&_tree, prevOp->m_stackTrace, 0, 0, _offset, StackTraceTree::FREE);
			}
			break;

		case rmem::LogMarkers::OpReallocAligned:
		case rmem::LogMarkers::OpRealloc:
			{
				MemoryOperation* prevOp = _op->m_chainPrev;
				if (prevOp)
				{
					if (isInFilter(prevOp))
						addToTree(&_tree, prevOp->m_stackTrace, -(int64_t)prevOp->m_allocSize, -(int32_t)prevOp->m_overhead, _offset, StackTraceTree::COUNT);
				}
				addToTree(&_tree, _op->m_stackTrace, _op->m_allocSize, _op->m_overhead, _offset, StackTraceTree::REALLOC);
			}
			break;
	};
}

} // namespace rtm
