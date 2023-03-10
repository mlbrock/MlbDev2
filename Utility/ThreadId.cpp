// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ThreadId.cpp

   File Description  :  Implementation of the portable thread id function.

   Revision History  :  1998-04-08 --- Creation.
                           Michael L. Brock
                        2023-01-07 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1998 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/ThreadId.hpp>

#ifdef __MSDOS__
#elif _Windows
# if defined(_MSC_VER) && (_MSC_VER < 1900)
#  include <Windows.h>
# else
#  pragma warning(push)
#  pragma warning(disable:5039)
#  include <Windows.h>
#  pragma warning(pop)
# endif // if defined(_MSC_VER) && (_MSC_VER < 1900)
#elif defined(__linux__)
# include <unistd.h>
# include <sys/syscall.h>
#elif MBCOMPAT_THREAD_MODEL_UI
# include <thread.h>
#else
# include <pthread.h>
#endif // #ifdef __MSDOS__

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
ThreadId CurrentThreadId()
{
#ifdef __MSDOS__
	return(static_cast<ThreadId>(1));
#elif _Windows
	return(static_cast<ThreadId>(::GetCurrentThreadId()));
#elif defined(__linux__)
	return(static_cast<ThreadId>(::syscall(SYS_gettid)));
#elif MBCOMPAT_THREAD_MODEL_UI
	return(static_cast<ThreadId>(::thr_self()));
#else
	return(static_cast<ThreadId>(::pthread_self()));
#endif /* #ifdef __MSDOS__ */
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
		std::cout << "CurrentThreadId(): " << CurrentThreadId() << std::endl;
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

