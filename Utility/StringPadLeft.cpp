// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringPadLeft.hpp

   File Description  :  Implementation of the left-pad string functions.

   Revision History  :  1993-10-02 --- Creation.
                           Michael L. Brock
                        2023-01-12 --- Migration to C++ MlbDev2/Utility.
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

#include <Utility/StringPadLeft.hpp>

#include <iomanip>
#include <sstream>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
std::string &PadLeft(const std::string &in_string, std::string &out_string,
	std::size_t pad_length, char pad_char)
{
	if (in_string.size() >= static_cast<std::string::size_type>(pad_length))
		out_string.assign(in_string, 0, pad_length);
	else {
		std::ostringstream o_str;
		o_str << std::right << std::setfill(pad_char) <<
			std::setw(static_cast<std::streamsize>(pad_length)) << in_string;
		out_string = o_str.str();
	}

	return(out_string);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string PadLeft(const std::string &in_string, std::size_t pad_length,
	char pad_char)
{
	std::string out_string;

	return(PadLeft(in_string, out_string, pad_length, pad_char));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

