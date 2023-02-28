// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name			:	AnyToString.hpp

	File Description	:	Basic include file for the date/time support logic.

   Revision History	:	1998-04-08 --- Creation of original AnyToString()
												   function templates.
									Michael L. Brock
   							2023-01-06 --- Change names of core functions to
													ToString() and make AnyToString()
												   forward to those functions.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2023.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__AnyToString_hpp__HH

#define HH__MLB__Utility__AnyToString_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file AnyToString.hpp

	\brief	The AnyToString functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/ToString.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	inline std::string AnyToString(const DataType &datum)
{
	return(ToString(datum));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__AnyToString_hpp__HH
