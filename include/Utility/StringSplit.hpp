// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringSplit.hpp

   File Description  :  Function prototypes for split string functions.

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

#ifndef HH__MLB__Utility__StringSplit_hpp__HH

#define HH__MLB__Utility__StringSplit_hpp__HH   1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file    StringSplit.hpp

   \brief   The MLB Utility C++ split string functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::vector<std::string> &SplitString(const std::string &in_string,
	const std::string &find_string, std::vector<std::string> &out_list,
	std::string::size_type start_pos = 0, bool discard_empty_sections = false);
API_UTILITY std::vector<std::string>  SplitString(const std::string &in_string,
	const std::string &find_string, std::string::size_type start_pos = 0,
	bool discard_empty_sections_flag = false);
// IMPL NOTE: For name compatibility with the old MlbDef/Utility
API_UTILITY std::vector<std::string>  GetSplit(const std::string &in_string,
	const std::string &find_string, std::string::size_type start_pos = 0,
	bool discard_empty_sections_flag = false);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__StringSplit_hpp__HH

