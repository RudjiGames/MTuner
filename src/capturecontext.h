//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef RTM_MTUNER_CAPTURE_CONTEXT_H
#define RTM_MTUNER_CAPTURE_CONTEXT_H

#include <MTuner/src/loader/capture.h>

class BinLoaderView;

struct CaptureContext
{
	rtm::Capture*			m_capture;
	uintptr_t				m_symbolResolver;
	rtm_string				m_symbolStorePath;
	rtm_string				m_symbolStoreFName;
	rtm_string				m_symbolStoreDName;
	rtm_string				m_addr2Line;
	rmem::ToolChain::Enum	m_toolchain;
	BinLoaderView*			m_binLoaderView;

	CaptureContext();
	~CaptureContext();

	void		setToolchain(rdebug::Toolchain& _tc);
	rtm_string	getSymbolStoreDir() const { return m_symbolStoreDName; }
	void		resolveStackFrame(uint64_t _address, rdebug::StackFrame& ioFrame);
};

#endif // RTM_MTUNER_CAPTURE_CONTEXT_H
