//--------------------------------------------------------------------------//
/// Copyright 2025 Milos Tosic. All Rights Reserved.                       ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/capturecontext.h>
#include <rbase/inc/widechar.h>
#include <rdebug/inc/rdebug.h>

CaptureContext::CaptureContext()
{
	m_symbolResolver	= 0;
	m_capture			= new rtm::Capture();
	m_toolchain			= rmem::ToolChain::Unknown;
	m_binLoaderView		= 0;
}

CaptureContext::~CaptureContext()
{
	if (m_symbolResolver)
	{
		rdebug::symbolResolverDelete((uintptr_t)m_symbolResolver);
		m_symbolResolver = 0;
	}
}

void CaptureContext::setupResolver(rdebug::Toolchain& _tc, std::string& _executable, rdebug::module_load_cb _callback, void* _data)
{
	switch (_tc.m_type)
	{
		case rdebug::Toolchain::MSVC:
			{
				std::string symbolStorePath = _tc.m_toolchainPath;
				size_t len = symbolStorePath.length();
				if (len)
				while (--len)
				{
					if (symbolStorePath.c_str()[len] == L'\\') break;
					if (symbolStorePath.c_str()[len] == L'/') break;
				}

				if (len)
				{
					char buffer[2048];
					strcpy(buffer, symbolStorePath.c_str());
					buffer[len+1] = L'\0';
					m_symbolStoreDName = buffer;
				}
				else
				{
					m_symbolStoreDName = "";
				}
			}
			break;
		case rdebug::Toolchain::GCC:
		case rdebug::Toolchain::PS3SNC:
		case rdebug::Toolchain::PS4:
		case rdebug::Toolchain::PS5:
		case rdebug::Toolchain::Unknown:
			break;
	};

	m_symbolResolver = rdebug::symbolResolverCreate(m_capture->getModuleInfos().data(), (uint32_t)m_capture->getModuleInfos().size(), _executable.c_str(), _callback, _data);
}

void CaptureContext::resolveStackFrame(uint64_t _address, rdebug::StackFrame& _frame)
{
	if (m_symbolResolver)
		rdebug::symbolResolverGetFrame(m_symbolResolver, _address, &_frame);
}
