// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  GetSystemErrorCode.cpp

   File Description  :  Support for retrieving a system error code.

   Revision History  :  1998-04-08 --- Implementation in MlbDev/Utility in
                                       file Utility/SystemError.cpp.
                           Michael L. Brock
                        2023-02-22 --- Migration to C++ MlbDev2/Utility.
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

#include <Utility/GetSystemErrorCode.hpp>

#if (!defined(_MSC_VER)) && (!defined(Windows))
# include <errno.h>
#elif (_MSC_VER < 1900)
# include <Windows.h>
#else
# pragma warning(push)
# pragma warning(disable:5039)
# include <Windows.h>
# pragma warning(pop)
#endif // #if (!defined(_MSC_VER)) && (!defined(Windows))

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
int GetSystemErrorCode()
{
#if (!defined(_MSC_VER)) && (!defined(Windows))
	return(errno);
#else
	return(static_cast<int>(::GetLastError()));
#endif // #if (!defined(_MSC_VER)) && (!defined(Windows))
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

