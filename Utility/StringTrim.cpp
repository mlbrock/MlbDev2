// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringTrim.hpp

   File Description  :  Implementation of trim string functions.

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

#include <Utility/StringTrim.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	//////////////////////////////////////////////////////////////////////////
std::string &TrimString(const std::string &in_string,
	std::string &out_string, const std::string &trim_char_list)
{
	out_string = in_string;

	out_string.erase(out_string.find_last_not_of(trim_char_list) + 1);

	return(out_string.erase(0, out_string.find_first_not_of(trim_char_list)));
}
//	//////////////////////////////////////////////////////////////////////////

//	//////////////////////////////////////////////////////////////////////////
std::string Trim(const std::string &in_string,
	const std::string &trim_char_list)
{
	std::string out_string;

	return(TrimString(in_string, out_string, trim_char_list));
}
//	//////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

