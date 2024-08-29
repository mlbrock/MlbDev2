// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringSplit.hpp

   File Description  :  Implementation of split string functions.

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

#include <Utility/StringSplit.hpp>

#include <algorithm>
#include <deque>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
std::vector<std::string> &SplitString(const std::string &in_string,
	const std::string &find_string, std::vector<std::string> &out_list,
	std::string::size_type start_pos, bool discard_empty_sections)
{
	std::deque<std::string> tmp_list;
	std::string::size_type  in_length   = in_string.size();
	std::string::size_type  find_length = find_string.size();

	if (!find_length) {
		out_list.clear();
		return(out_list);
	}

	//	Append to the list any separator-delimited sub-string sections.
	while (start_pos < in_length) {
		std::string::size_type found_pos = in_string.find(find_string, start_pos);
		if (found_pos == std::string::npos)
			break;
		if ((!discard_empty_sections) || (found_pos != start_pos))
			tmp_list.push_back(in_string.substr(start_pos, found_pos - start_pos));
		start_pos = found_pos + find_length;
	}

	//	There may be a trailing sub-string; if so, grab it...
	if ((start_pos <= in_length) &&
		((!discard_empty_sections) || (start_pos < in_length)))
		tmp_list.push_back(in_string.substr(start_pos));

	out_list.assign(tmp_list.begin(), tmp_list.end());

	return(out_list);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::vector<std::string> SplitString(const std::string &in_string,
	const std::string &find_string, std::string::size_type start_pos,
	bool discard_empty_sections_flag)
{
	std::vector<std::string> out_list;

	return(SplitString(in_string, find_string, out_list, start_pos,
		discard_empty_sections_flag));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::vector<std::string> GetSplit(const std::string &in_string,
	const std::string &find_string, std::string::size_type start_pos,
	bool discard_empty_sections_flag)
{
/*
	std::vector<std::string> out_list;

	return(SplitString(in_string, find_string, out_list, start_pos,
		discard_empty_sections_flag));
*/
	return(SplitString(in_string, find_string, start_pos,
		discard_empty_sections_flag));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

