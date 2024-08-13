// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  CriticalEventHandler.hpp

   File Description  :  Include file for critical event handling.

   Revision History  :  1994-07-28 Creation in C genfuncs library as sighandl.c
                           Michael L. Brock
                        1998-04-08 --- Revision for the MlbDev Utility library.
                           Michael L. Brock
                        2024-08-10 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1994 - 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__CriticalEventHandler_hpp__HH

#define HH__MLB__Utility__CriticalEventHandler_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file CriticalEventHandler.hpp

   \brief   The critical event handling header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <atomic>
#include <functional>
#include <set>
#include <vector>

#include <signal.h>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
class CriticalEventHandler
{
public:
	CriticalEventHandler();

	~CriticalEventHandler();

	static void SetFlag();

	static bool GetFlag();

private:
#ifndef _MSC_VER
	using SignalFuncType        = sighandler_t;
#else
	using SignalFuncType        = _crt_signal_t;
#endif // #ifndef _MSC_VER

	using SignalHandlerItem     = std::pair<int, SignalFuncType>;
	using SignalHandlerItemList = std::vector<SignalHandlerItem>;

	SignalHandlerItemList handlers_list_;

	alignas(64) static std::atomic_bool event_flag_;

	void InstallHandlers(std::set<int> &signal_list);

	static void SignalHandler(int signal);
};
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__CriticalEventHandler_hpp__HH

