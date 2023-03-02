// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ToStringRadix.hpp

   File Description  :  Maximum radix digits for two's complement integers.

   Revision History  :  1998-04-08 --- Creation as ValueToStringRadix()
                                       function templates.
                           Michael L. Brock
                        2023-01-04 --- Implemented as more-general function
                                       templates name ToStringRadix().
                           Michael L. Brock

      Copyright Michael L. Brock 1998 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__ToStringRadix_hpp__HH

#define HH__MLB__Utility__ToStringRadix_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file ToStringRadix.hpp

   \brief   The ToStringRadix[Bin|Oct|Dec|Hex]() functions header.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/IntegralValueMaxLength.hpp>

#include <bitset>
#include <iomanip>
#include <sstream>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4826)
# endif // # if _MSC_VER < 1400

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline std::string ToStringBin(const DatumType &datum,
		char prefix_char = '\0', char pad_char = '\0')
{
	const unsigned long long tmp_datum = ((const unsigned long long) datum);
	std::ostringstream       tmp_text;

#if defined(_Windows) && !defined(__MINGW32__)
# pragma warning(push)
# pragma warning(disable:4244)
#endif // #if defined(_Windows) && !defined(__MINGW32__)

	if (prefix_char)
		tmp_text << '0' << prefix_char;

	if (pad_char)
		tmp_text << std::setfill(pad_char) <<
			std::setw(static_cast<std::streamsize>(
				IntegralValueMaxLengthBin<DatumType>()));

	tmp_text <<
		std::bitset<sizeof(datum) * CHAR_BIT>(tmp_datum);

#if defined(_Windows) && !defined(__MINGW32__)
# pragma warning(pop)
#endif // #if defined(_Windows) && !defined(__MINGW32__)

	return(tmp_text.str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline std::string ToStringOct(const DatumType &datum,
		char prefix_char = '\0', char pad_char = '\0')
{
	const unsigned long long tmp_datum = ((const unsigned long long) datum);
	std::ostringstream       tmp_text;

	if (prefix_char)
		tmp_text << '0' << prefix_char;

	if (pad_char)
		tmp_text << std::setfill(pad_char) <<
			std::setw(static_cast<std::streamsize>(
				IntegralValueMaxLengthOct<DatumType>()));

	tmp_text << std::oct << tmp_datum;

	return(tmp_text.str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline std::string ToStringDec(const DatumType &datum,
		char prefix_char = '\0', char pad_char = '\0')
{
	const unsigned long long tmp_datum = ((const unsigned long long) datum);
	std::ostringstream       tmp_text;

	if (prefix_char)
		tmp_text << '0' << prefix_char;

	if (pad_char)
		tmp_text << std::setfill(pad_char) <<
			std::setw(static_cast<std::streamsize>(
				IntegralValueMaxLengthDec<DatumType>()));

	tmp_text << tmp_datum;

	return(tmp_text.str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline std::string ToStringHex(const DatumType &datum,
		char prefix_char = '\0', char pad_char = '\0')
{
	//	Yep, that's a C-style cast. The other functions do the same...
	const unsigned long long tmp_datum = ((const unsigned long long) datum);
	std::ostringstream       tmp_text;

	if (prefix_char)
		tmp_text << '0' << prefix_char;

	if (pad_char)
		tmp_text << std::setfill(pad_char) <<
			std::setw(static_cast<std::streamsize>(
				IntegralValueMaxLengthHex<DatumType>()));

	tmp_text << std::hex << tmp_datum;

	return(tmp_text.str());
}
// ////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
# pragma warning(pop)
# endif // # if _MSC_VER < 1400

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__ToStringRadix_hpp__HH

