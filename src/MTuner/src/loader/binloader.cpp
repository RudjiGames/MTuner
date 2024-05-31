//--------------------------------------------------------------------------//
/// Copyright 2024 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/loader/binloader.h>
#include <rmem/src/rmem_hook.h>
#include <rbase/inc/endianswap.h>

#define LZ4_DISABLE_DEPRECATE_WARNINGS
#include <rmem/3rd/lz4-r191/lz4.h>
#include <rmem/3rd/lz4-r191/lz4.c>

#if RTM_COMPILER_MSVC
#pragma intrinsic (memcpy)
#endif // RTM_COMPILER_MSVC

namespace rtm {

BinLoader::BinLoader(FILE* _file, bool _compressed) :
	m_file(_file)
{
	m_compressed	= _compressed;
	m_bytesRead		= 0;
	m_srcData		= new uint8_t[rmem::MemoryHook::BufferSize];
	m_srcDataSize	= rmem::MemoryHook::BufferSize;
	m_data			= new uint8_t[rmem::MemoryHook::BufferSize];
	m_dataPos		= 0;
	m_dataSize		= rmem::MemoryHook::BufferSize;
	m_dataAvailable	= 0;

	if (_compressed)
		loadChunk();
}

BinLoader::~BinLoader()
{
	delete[] m_data;
	delete[] m_srcData;
}

bool BinLoader::eof()
{
	if (m_compressed)
		return (m_dataPos == m_dataAvailable);

	return (feof(m_file) != 0);
}

uint64_t BinLoader::tell()
{
	if (m_compressed)
		return m_bytesRead + m_dataPos;
	else
		return fileTell();
}

uint64_t BinLoader::fileTell()
{
#if RTM_PLATFORM_WINDOWS
	uint64_t pos = (uint64_t)_ftelli64(m_file);
#elif RTM_PLATFORM_LINUX
	uint64_t pos = (uint64_t)ftello64(m_file);
#elif RTM_PLATFORM_OSX
	uint64_t pos = (uint64_t)ftello(m_file);
#endif
	return pos;
}

int BinLoader::read(void* _ptr, size_t _size)
{
	if (!m_compressed)
		return (int)fread(_ptr, _size, 1, m_file);

	const int32_t bytesLeft = m_dataAvailable - m_dataPos;

	if (bytesLeft > (int32_t)_size)
	{
		memcpy(_ptr, &m_data[m_dataPos], _size);
		m_dataPos	+= (int32_t)_size;
		return 1;
	}
	else
	{
		uint8_t* dst = (uint8_t*)_ptr;
		if (bytesLeft)
		{
			memcpy(dst, &m_data[m_dataPos], bytesLeft);
			m_dataPos	+= bytesLeft;
		}

		dst += bytesLeft;

		const int32_t remaining = (int32_t)_size - bytesLeft;

		if (m_dataPos == m_dataAvailable)
		{
			m_bytesRead += m_dataAvailable;
			if (!loadChunk())
				return (remaining == 0) ? 1 : 0;
			m_dataPos = 0;
		}

		if (remaining > 0)
		{
			memcpy(dst, &m_data[m_dataPos], remaining);
			m_dataPos	+= remaining;
		}
		return 1;
	}
}

bool BinLoader::loadChunk()
{
	uint32_t sig, size;
	size_t e = fread(&sig, sizeof(uint32_t), 1, m_file);
	if (e != 1)
		return false;

	if (!((sig == 0x23234646) || sig == Endian::swap(uint32_t(0x23234646))))
		return false;

	e = fread(&size, sizeof(uint32_t), 1, m_file);
	if (e == 0)
		return false;

	if (sig == Endian::swap(uint32_t(0x23234646)))
		size = Endian::swap(size);

	if (m_srcDataSize < (int32_t)size)
	{
		delete[] m_srcData;
		m_srcData = new uint8_t[size];
		m_srcDataSize = size;
	}

	e = fread(m_srcData, 1, size, m_file);

	if (e != size)
		return false;

	m_dataAvailable = -1;
	while (m_dataAvailable < 0)
	{
		m_dataAvailable = LZ4_decompress_safe((const char*)m_srcData, (char*)m_data, size, m_dataSize);
		if (m_dataAvailable < 0)
		{
			delete[] m_data;
			m_dataSize *= 2;
			m_data = new uint8_t[m_dataSize];
		}
	}

	return true;
}

} // namespace rtm
