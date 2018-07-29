//--------------------------------------------------------------------------//
/// Copyright (c) 2018 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>
#include <MTuner/src/capturecontext.h>
#include <rbase/inc/winchar.h>
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

void CaptureContext::setToolchain(rdebug::Toolchain& _tc, rtm_string& _executable)
{
	switch (_tc.m_type)
	{
		case rdebug::Toolchain::MSVC:
			{
				m_symbolStorePath = _tc.m_toolchainPath;
				size_t len = m_symbolStorePath.length();
				if (len)
				while (--len)
				{
					if (m_symbolStorePath.c_str()[len] == L'\\') break;
					if (m_symbolStorePath.c_str()[len] == L'/') break;
				}

				if (len)
				{
					const char* fname = &m_symbolStorePath.c_str()[len+1];
					m_symbolStoreFName = fname;
					char buffer[512];
					strcpy(buffer, m_symbolStorePath.c_str());
					buffer[len+1] = L'\0';
					m_symbolStoreDName = buffer;
				}
				else
				{
					m_symbolStoreFName = "Unknown";
					m_symbolStoreDName = "";
				}
			}
			break;
		case rdebug::Toolchain::GCC:
		case rdebug::Toolchain::PS3SNC:
		case rdebug::Toolchain::PS4:
		case rdebug::Toolchain::Unknown:
			break;
	};

	m_symbolResolver = rdebug::symbolResolverCreate(m_capture->getModuleInfos().data(), (uint32_t)m_capture->getModuleInfos().size(), &_tc, _executable.c_str());
}

void CaptureContext::resolveStackFrame(uint64_t _address, rdebug::StackFrame& _frame)
{
	if (m_symbolResolver)
		rdebug::symbolResolverGetFrame(m_symbolResolver, _address, &_frame);
}
