// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ToStreamSystemError.cpp

   File Description  :  Logic for streaming system-related exceptions text.

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

#include <Utility/ToStreamSystemError.hpp>

#include <sstream>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::ostream &ToStreamSystemError(std::ostream &o_str,
	const std::error_condition &err_cond, const char *err_text,
	bool with_message)
{
	o_str << 
		(((err_text != NULL) && *err_text) ? err_text : "Error") <<
		": " << err_cond.category().name() << " error code " <<
		err_cond.value();

	if (with_message)
		o_str << ": " << err_cond.message();

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream &ToStreamSystemError(std::ostream &o_str, int err_code,
	const char *err_text, bool with_message)
{
	return(ToStreamSystemError(o_str,
		std::system_category().default_error_condition(err_code),
		err_text, with_message));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

