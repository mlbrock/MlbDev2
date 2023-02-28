// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringOneSpace.cpp

   File Description  :  Implementation of multiple-space-to-one-space string
                        functions.

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

#include <Utility/StringOneSpace.hpp>

#include <Utility/StringCharsToOneChar.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace {

// ////////////////////////////////////////////////////////////////////////////
struct OneSpaceFunctor {
	bool operator () (std::string::value_type in_char) const
	{
		return(::isspace(in_char) != 0);
	}
};
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
std::string &OneSpace(const std::string &in_string, std::string &out_string)
{
	return(MultipleCharsToOneChar(in_string, out_string,
		OneSpaceFunctor(),' '));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string OneSpace(const std::string &in_string)
{
	std::string out_string;

	return(OneSpace(in_string, out_string));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

