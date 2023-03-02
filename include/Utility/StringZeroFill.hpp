// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringZeroFill.hpp

   File Description  :  Function prototypes for the zero-fill string functions.

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

#ifndef HH__MLB__Utility__StringZeroFill_hpp__HH

#define HH__MLB__Utility__StringZeroFill_hpp__HH   1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file    StringZeroFill.hpp

   \brief   The MLB Utility C++ zero-fill string functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/StringPad.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	inline std::string ZeroFill(const DataType &in_datum, std::size_t pad_length)
{
	return(ZeroFill(AnyToString(in_datum), pad_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	inline std::string &ZeroFill(const DataType &in_datum,
		std::string &out_string, std::size_t pad_length)
{
	return(ZeroFill(AnyToString(in_datum), out_string, pad_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <>
	inline std::string &ZeroFill<std::string>(const std::string &in_datum,
		std::string &out_string, std::size_t pad_length)
{
	return(PadLeft(in_datum, out_string, pad_length, '0'));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <>
	inline std::string ZeroFill<std::string>(const std::string &in_datum,
		std::size_t pad_length)
{
	std::string out_string;

	return(ZeroFill(in_datum, out_string, pad_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
//	Specialization for bool because AnyToString<bool>() returns the text string
//	'true' or 'false'.
template <>
	inline std::string &ZeroFill<bool>(const bool &in_datum,
		std::string &out_string, std::size_t pad_length)
{
/*
	return(ZeroFill(AnyToString(static_cast<int>(in_datum)), out_string,
		pad_length));
*/
	//	IMPL NOTE: Always coerce 'true' to the same integer equivalent value.
	return(ZeroFill(AnyToString((in_datum) ? 1 : 0), out_string, pad_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
//	Specialization for bool because AnyToString<bool>() returns the text string
//	'true' or 'false'.
template <>
	inline std::string ZeroFill<bool>(const bool &in_datum,
		std::size_t pad_length)
{
/*
	return(ZeroFill(AnyToString(static_cast<int>(in_datum)), pad_length));
*/
	//	IMPL NOTE: Always coerce 'true' to the same integer equivalent value.
	return(ZeroFill(AnyToString((in_datum) ? 1 : 0), pad_length));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__StringZeroFill_hpp__HH

