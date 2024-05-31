//--------------------------------------------------------------------------//
/// Copyright 2023 Milos Tosic. All Rights Reserved.                       ///
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
	std::string				m_symbolStoreDName;
	rmem::ToolChain::Enum	m_toolchain;
	BinLoaderView*			m_binLoaderView;

	CaptureContext();
	~CaptureContext();

	void		setupResolver(rdebug::Toolchain& _tc, std::string& _executable, rdebug::module_load_cb _callback, void* _data);
	std::string	getSymbolStoreDir() const { return m_symbolStoreDName; }
	void		resolveStackFrame(uint64_t _address, rdebug::StackFrame& ioFrame);
};

#endif // RTM_MTUNER_CAPTURE_CONTEXT_H
