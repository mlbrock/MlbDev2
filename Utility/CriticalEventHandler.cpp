// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  CriticalEventHandler.cpp

   File Description  :  Implementation of critical event handling.

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

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/CriticalEventHandler.hpp>

#include <Utility/ThrowErrno.hpp>

#include <stdexcept>
#include <string>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
alignas(64) std::atomic_bool CriticalEventHandler::event_flag_ = false;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
CriticalEventHandler::CriticalEventHandler()
	:handlers_list_()
{
	std::set<int> signal_set = { SIGINT, SIGTERM };

	InstallHandlers(signal_set);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
CriticalEventHandler::~CriticalEventHandler()
{
	while (!handlers_list_.empty()) {
		::signal(handlers_list_.back().first, handlers_list_.back().second);
		handlers_list_.pop_back();
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void CriticalEventHandler::SetFlag()
{
	event_flag_ = true;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool CriticalEventHandler::GetFlag() const
{
	return(event_flag_.load());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void CriticalEventHandler::InstallHandlers(std::set<int> &signal_list)
{
	try {
		handlers_list_.reserve(handlers_list_.size() + signal_list.size());
		while (!signal_list.empty()) {
			SignalFuncType return_code =
				::signal(*signal_list.begin(), SignalHandler);
			if (return_code == SIG_ERR)
				ThrowErrno("Attempt to install a signal handler for signal "
					"number " + std::to_string(*signal_list.begin()) +
					" failed with return code " +
					std::to_string(reinterpret_cast<int64_t>(return_code)) +
					" ('SIG_ERR')");
			handlers_list_.
				push_back(SignalHandlerItem(*signal_list.begin(), return_code));
			signal_list.erase(signal_list.begin());
		}
	}
	catch (const std::exception &except) {
		throw std::runtime_error("Attempt to initialize an instance of class "
			"'CriticalEventHandler' failed: " + std::string(except.what()));
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void CriticalEventHandler::SignalHandler(int /* signal_number */)
{
	event_flag_ = true;
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

#include <Utility/Sleep.hpp>

#include <iostream>

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		MLB::Utility::CriticalEventHandler event_handler;
		std::cout << "Waiting for SIGINT or SIGTERM to exit ..." << std::flush;
		while (!event_handler.GetFlag())
			MLB::Utility::SleepMilliSecs(100);
		std::cout << " exiting due to receipt of a signal.\n" << std::endl;
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

