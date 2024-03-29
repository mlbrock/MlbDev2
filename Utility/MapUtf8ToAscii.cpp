// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  MapUtf8ToAscii.cpp

   File Description  :  Logic for mapping UTF-8 sequences within strings to
                        single characters.

   Revision History  :  2018-05-02 --- Creation.
                           Michael L. Brock
                        2023-02-25 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 2018 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/MapUtf8ToAscii.hpp>

#include <boost/algorithm/string.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace {

// ////////////////////////////////////////////////////////////////////////////
const Utf8MapEntry UTF8To7BitAsciiList[] = {
	Utf8MapEntry("\xE2\x80\x98", "'"),	// U+2018 (LEFT SINGLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\x99", "'"),	// U+2019 (RIGHT SINGLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\x9C", "\""),	// U+201C (LEFT DOUBLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\x9D", "\""),	// U+201D (RIGHTT DOUBLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\xA2", "."),	// U+2022 (BULLET)
	Utf8MapEntry("\xE2\x80\x93", "-") 	// U+2013 (EN DASH)
};
const std::size_t  UTF8To7BitAsciiCount  =
	sizeof(UTF8To7BitAsciiList) / sizeof(UTF8To7BitAsciiList[0]);
//	----------------------------------------------------------------------------
const Utf8MapEntry UTF8To8BitAsciiList[] = {
	Utf8MapEntry("\xE2\x80\x98", "�"),	// U+2018 (LEFT SINGLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\x99", "�"),	// U+2019 (RIGHT SINGLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\x9C", "�"),	// U+201C (LEFT DOUBLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\x9D", "�"),	// U+201D (RIGHTT DOUBLE QUOTATION MARK)
	Utf8MapEntry("\xE2\x80\xA2", "�"),	// U+2022 (BULLET)
	Utf8MapEntry("\xE2\x80\x93", "�")	// U+2013 (EN DASH)
};
const std::size_t  UTF8To8BitAsciiCount  =
	sizeof(UTF8To8BitAsciiList) / sizeof(UTF8To8BitAsciiList[0]);
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
std::string &MapUtf8ToAsciiInPlace(const std::size_t map_count,
	const Utf8MapEntry *map_list,  std::string &src)
{
	if (src.empty())
		return(src);

	for (std::size_t count_1 = 0; count_1 < map_count; ++count_1)
		boost::replace_all(src, map_list[count_1].first,
			map_list[count_1].second);

	return(src);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string MapUtf8ToAscii(const std::size_t map_count,
	const Utf8MapEntry *map_list,  const std::string &src)
{
	std::string dst(src);

	return(MapUtf8ToAsciiInPlace(map_count, map_list, dst));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &MapUtf8ToAscii7InPlace(std::string &src)
{
	return(MapUtf8ToAsciiInPlace(UTF8To7BitAsciiCount,
		UTF8To7BitAsciiList, src));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string MapUtf8ToAscii7(const std::string &src)
{
	return(MapUtf8ToAscii(UTF8To7BitAsciiCount, UTF8To7BitAsciiList, src));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &MapUtf8ToAscii8InPlace(std::string &src)
{
	return(MapUtf8ToAsciiInPlace(UTF8To8BitAsciiCount,
		UTF8To8BitAsciiList, src));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string MapUtf8ToAscii8(const std::string &src)
{
	return(MapUtf8ToAscii(UTF8To8BitAsciiCount, UTF8To8BitAsciiList, src));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

