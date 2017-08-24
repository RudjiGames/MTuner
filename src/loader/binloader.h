//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNERLOADER_STREAM_H__
#define __RTM_MTUNERLOADER_STREAM_H__

#include <vector>

namespace rtm {

class BinLoader
{
	FILE*		m_file;
	bool		m_compressed;
	uint8_t*	m_srcData;
	int32_t		m_srcDataSize;
	uint8_t*	m_data;
	int32_t		m_dataSize;
	int32_t		m_dataAvailable;
	int32_t		m_dataPos;
	uint64_t	m_bytesRead;

public:
	BinLoader(FILE* _file, bool _compressed);
	~BinLoader();

	bool eof();
	uint64_t tell();
	int read(void* _ptr, size_t _size);

	template <typename T>
	int readVar(T& _var)
	{
		return read(&_var, sizeof(T));
	}

private:
	bool loadChunk();
};

} // namespace rtm

#endif // __RTM_MTUNERLOADER_STREAM_H__
