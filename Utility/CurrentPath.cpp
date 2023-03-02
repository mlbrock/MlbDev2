// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  CurrentPath.cpp

   File Description  :  Implementation of functions to get and set the
                        current working directory.

   Revision History  :  1998-04-08 --- Creation
                           Michael L. Brock
                        2023-01-09 --- Migration to C++ MlbDev2/Utility.
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

#include <Utility/CurrentPath.hpp>

#include <Utility/HostName.hpp>
#include <Utility/ThrowErrno.hpp>
#include <Utility/ThrowSystemError.hpp>

#include <stdexcept>

#ifdef _MSC_VER
# include <direct.h>
#elif defined(__linux__)
# include <unistd.h>
#endif // #ifdef _MSC_VER

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::string GetCurrentPath()
{
	char datum[2 + MaxHostNameLength + 1 + (MaxPathNameLength * 3) + 1 + 1];

	return(GetCurrentPath(datum, sizeof(datum) - 1));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *GetCurrentPath(char *path_name, std::size_t path_name_length)
{
	char *return_ptr = getcwd(path_name, static_cast<int>(path_name_length));

	if (return_ptr == NULL)
		ThrowErrno("Invocation of 'getcwd()' failed");

	return(return_ptr);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SetCurrentPath(const char *new_path)
{
	if (new_path == NULL)
		throw std::invalid_argument("Invocation of 'SetCurrentPath()' with a "
			"destination path name argument equal to 'NULL'.");

#if _Windows
	if (!::SetCurrentDirectoryA(new_path))
		ThrowSystemError("Invocation of 'SetCurrentDirectoryA()' for path "
			"name '" + std::string(new_path) + "' failed");
#else
	if (::chdir(new_path) != 0)
		ThrowErrno("Invocation of 'chdir()' for path name '" +
			std::string(new_path) + "' failed");
#endif // _Windows
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SetCurrentPath(const std::string &new_path)
{
	SetCurrentPath(new_path.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

