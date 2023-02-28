// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ToStringSystemError.hpp

   File Description  :  Include for converting system-related exceptions to
							   string.

   Revision History  :  1998-04-08 --- Implementation in MlbDev/Utility in
                                       file Utility/Utility_Exception.hpp.
                           Michael L. Brock
                        2023-02-22 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1986 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__ToStringSystemError_hpp__HH

#define HH__MLB__Utility__ToStringSystemError_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file ToStringSystemError.hpp

   \brief   Functions which convert system errors to strings.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string ToStringSystemError(int err_code,
	const std::string &err_text, bool with_message = true);
API_UTILITY std::string ToStringSystemError(int err_code,
	const char *err_text = nullptr, bool with_message = true);
API_UTILITY std::string ToStringSystemError(const std::string &err_text,
	bool with_message = true);
API_UTILITY std::string ToStringSystemError(const char *err_text = nullptr,
	bool with_message = true);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__ToStringSystemError_hpp__HH

