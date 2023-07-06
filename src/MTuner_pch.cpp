//--------------------------------------------------------------------------//
/// Copyright (c) 2023 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <MTuner_pch.h>

#define RTM_LIBHANDLER_DEFINE
#include <rbase/inc/libhandler.h>

namespace mtuner {

bool init(rtmLibInterface* _libInterface)
{
	g_allocator = _libInterface ? _libInterface->m_memory : 0;
	g_errorHandler = _libInterface ? _libInterface->m_error : 0;
	return true;
}

void shutDown()
{
}

} // namespace mtuner
