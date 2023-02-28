// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	ProcessId.cpp

	File Description	:	Implementation of the portable process id function.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock
                        2023-01-05 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

		Copyright Michael L. Brock 1998 - 2023.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/ProcessId.hpp>

#ifndef _MSC_VER
# include <unistd.h>
#elif (_MSC_VER < 1900)
# include <Windows.h>
#else
# pragma warning(push)
# pragma warning(disable:5039)
# include <Windows.h>
# pragma warning(pop)
#endif // #ifndef _MSC_VER

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
ProcessId CurrentProcessId()
{
#ifdef __MSDOS__
	//	CODE NOTE: Fix me! --- Should return the PSP value.
	return(static_cast<ProcessId>(4096));
#elif _Windows
	return(static_cast<ProcessId>(::GetCurrentProcessId()));
#else
	return(static_cast<ProcessId>(::getpid()));
#endif // #ifdef __MSDOS__
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#ifdef TEST_MAIN

#include <cstdlib>
#include <iostream>

using namespace MLB::Utility;

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		std::cout << "CurrentProcessId(): " << CurrentProcessId() << std::endl;
	}
	catch (const std::exception &except) {
		std::cout << std::endl;
		std::cout << "Regression test error: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

