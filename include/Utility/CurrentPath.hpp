// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	CurrentPath.hpp

   File Description	:	Function prototypes for functions to get and set the
							   current working directory.

	Revision History	:	1998-04-08 --- Creation
									Michael L. Brock
                        2023-01-09 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

		Copyright Michael L. Brock 1998 - 2023.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__CurrentPath_hpp__HH

#define HH__MLB__Utility__CurrentPath_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file CurrentPath.hpp

	\brief	The current working directory functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string>

#ifndef _MSC_VER
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <unistd.h>
# endif // # ifdef __linux__
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
#ifdef _Windows
const std::size_t MaxPathNameLength = _MAX_PATH;
#elif __MSDOS__
const std::size_t MaxPathNameLength = 255;
#elif sun
const std::size_t MaxPathNameLength = MAXPATHLEN;
#else
const std::size_t MaxPathNameLength = PATH_MAX;
#endif // #ifdef _Windows
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string  GetCurrentPath();
API_UTILITY char        *GetCurrentPath(char *path_name,
	std::size_t path_name_length);

API_UTILITY void SetCurrentPath(const char *new_path);
API_UTILITY void SetCurrentPath(const std::string &new_path);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__CurrentPath_hpp__HH

