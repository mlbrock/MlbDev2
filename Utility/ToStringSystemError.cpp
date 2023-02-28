// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ToStringSystemError.cpp

   File Description  :  Logic to convert system-related exceptions to string.

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

#include <Utility/ToStringSystemError.hpp>

#include <Utility/GetSystemErrorCode.hpp>
#include <Utility/ToStreamSystemError.hpp>

#include <sstream>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::string ToStringSystemError(int err_code, const std::string &err_text,
	bool with_message)
{
	return (ToStringSystemError(err_code, err_text.c_str(), with_message));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string ToStringSystemError(int err_code, const char *err_text,
	bool with_message)
{
	std::ostringstream o_str;

	ToStreamSystemError(o_str, err_code, err_text, with_message);

	return(o_str.str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string ToStringSystemError(const std::string &err_text,
	bool with_message)
{
	return(ToStringSystemError(GetSystemErrorCode(), err_text, with_message));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string ToStringSystemError(const char *err_text, bool with_message)
{
	return(ToStringSystemError(GetSystemErrorCode(), err_text, with_message));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

