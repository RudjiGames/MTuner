//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_BINLOADER_H
#define RTM_MTUNER_BINLOADER_H

namespace rtm {

class BinLoader
{
	uint8_t*	m_srcData;
	uint8_t*	m_data;
	int32_t		m_srcDataSize;
	int32_t		m_dataSize;
	int32_t		m_dataAvailable;
	int32_t		m_dataPos;
	uint64_t	m_bytesRead;
	FILE*		m_file;
	bool		m_compressed;

public:
	BinLoader(FILE* _file, bool _compressed);
	~BinLoader();

	bool eof();
	uint64_t tell();
	uint64_t fileTell();
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

#endif // RTM_MTUNER_BINLOADER_H
