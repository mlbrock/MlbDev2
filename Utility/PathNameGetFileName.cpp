// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  PathNameGetFileName.cpp

   File Description  :  Implementation of the path name slash support.

   Revision History  :  1985-10-23 --- Creation in genfuncs/genfuncs.h.
                           Michael L. Brock
                        1998-04-08 --- Modified for use with C++.
                           Michael L. Brock
                        2023-01-12 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1985 - 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/PathNameGetFileName.hpp>

#include <cstring>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
const char *GetFileNamePortion(const char *in_string)
{
#ifdef _Windows
	const char *break_char = strrchr(in_string, '/');
	break_char = std::max<const char *>(break_char, strrchr(in_string,  '\\'));
	break_char = std::max<const char *>(break_char, strrchr(in_string,  ':'));
#elif _VMS_
	const char *break_char = strrchr(in_string, ']');
#else
	const char *break_char = strrchr(in_string, '/');
#endif // #ifdef _Windows

	return((break_char == NULL) ? in_string : (break_char + 1));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string GetFileNamePortion(const std::string &in_string)
{
	return(GetFileNamePortion(in_string.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

