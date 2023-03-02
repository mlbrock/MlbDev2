// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringCharsToOneChar.hpp

   File Description  :  Function prototypes for mapping sub-strings to a
                        single character string functions.

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

#ifndef HH__MLB__Utility__StringCharsToOneChar_hpp__HH

#define HH__MLB__Utility__StringCharsToOneChar_hpp__HH   1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file    StringCharsToOneChar.hpp

   \brief   The MLB Utility C++ sub-string mapping functions header file.
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
struct API_UTILITY MultipleCharsToOneCharGenericFunctor {
	explicit MultipleCharsToOneCharGenericFunctor(const char *multi_chars,
		std::size_t multi_chars_length = 0);

	bool operator () (std::string::value_type in_char) const;

	const char  *multi_chars_;
	std::size_t  multi_chars_length_;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename ResolutionFunctor>
	inline std::string &MultipleCharsToOneChar(const std::string &in_string,
		std::string &out_string, const ResolutionFunctor &resolver,
		std::string::value_type single_char)
{
	if (in_string.empty())
		out_string.clear();
	else {
		bool                        in_multi_flag = false;
		std::string                 tmp_string(in_string.size(), '*');
		std::string::const_iterator iter_b(in_string.begin());
		std::string::const_iterator iter_e(in_string.end());
		std::string::iterator       iter_o(tmp_string.begin());
		for ( ; iter_b != iter_e; ++iter_b) {
			if (!resolver(*iter_b)) {
				*iter_o++ = *iter_b;
				in_multi_flag = false;
			}
			else if (!in_multi_flag) {
				*iter_o++ = single_char;
				in_multi_flag = true;
			}
		}
		out_string.assign(tmp_string, 0,
			static_cast<std::size_t>(iter_o - tmp_string.begin()));
	}

	return(out_string);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename ResolutionFunctor>
	inline std::string MultipleCharsToOneChar(const std::string &in_string,
		const ResolutionFunctor &resolver, std::string::value_type single_char)
{
	std::string out_string;

	return(MultipleCharsToOneChar(in_string, out_string, resolver, single_char));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string &MultipleCharsToOneChar(const std::string &in_string,
	std::string &out_string, const char *multiple_chars,
	std::string::value_type single_char);
API_UTILITY std::string  MultipleCharsToOneChar(const std::string &in_string,
	const char *multiple_chars, std::string::value_type single_char);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__StringCharsToOneChar_hpp__HH

