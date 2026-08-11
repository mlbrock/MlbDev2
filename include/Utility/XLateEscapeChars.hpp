// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  XLateEscapeChars.hpp

   File Description  :  Include file for escape character translation.

   Revision History  :  2024-12-28 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__XLateEscapeChars_hpp__HH

#define HH__MLB__Utility__XLateEscapeChars_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file XLateEscapeChars.hpp

   \brief   The translate escape characters.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string_view>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
const std::string &GetEscapeListRaw();
const std::string &GetEscapeListMap();

/*
	The following two functions provide raw <-> map lists which include the
	raw ASCII escape character (decimal 27, octal 33, hex 1B) mapped to the
	sequence '\e'.

	This escape sequence is supported by gcc/g++, clang, and tcc, but is not
	a part of the C or C++ standards.
*/
const std::string &GetEscapeListRawWithEsc();
const std::string &GetEscapeListMapWithEsc();
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string XLateEscapeChars(const std::string_view &src,
	const std::string &chars_raw = GetEscapeListRaw(),
	const std::string &chars_map = GetEscapeListMap());
std::string XLateEscapeChars(const std::string &src,
	const std::string &chars_raw = GetEscapeListRaw(),
	const std::string &chars_map = GetEscapeListMap());
std::string XLateEscapeChars(const char *src, std::size_t src_length,
	const std::string &chars_raw = GetEscapeListRaw(),
	const std::string &chars_map = GetEscapeListMap());
std::string XLateEscapeChars(const char *src,
	const std::string &chars_raw = GetEscapeListRaw(),
	const std::string &chars_map = GetEscapeListMap());
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__XLateEscapeChars_hpp__HH

