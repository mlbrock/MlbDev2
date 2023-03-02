// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  EmitterCommentCpp.hpp

   File Description  :  Definition of the EmitterCommentCpp class.

   Revision History  :  2016-02-18 --- Creation.
                           Michael L. Brock
                        2023-01-09 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 2016 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__EmitterCommentCpp_hpp__HH

#define HH__MLB__Utility__EmitterCommentCpp_hpp__HH   1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/EmitterSep.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
template <typename CharType = char>
	class basic_EmitterCommentCpp : public basic_EmitterSep<CharType> {
public:
	typedef CharType type;

	explicit basic_EmitterCommentCpp(CharType sep_char = '/',
		std::size_t sep_length = 79, bool end_line = true)
		:basic_EmitterSep<CharType>(sep_char,
			((sep_length < 3) ? 3 : sep_length) - 3, end_line)
	{
	}
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
typedef basic_EmitterCommentCpp<char> EmitterCommentCpp;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename CharType>
	inline typename IoCharInfo<CharType>::ostream_type & operator << (
		typename IoCharInfo<CharType>::ostream_type &o_str,
		const basic_EmitterCommentCpp<CharType> &datum)
{
	o_str << "// " << static_cast<const basic_EmitterSep<CharType> &>(datum);

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__EmitterCommentCpp_hpp__HH

