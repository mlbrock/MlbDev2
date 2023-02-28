// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name			:	StringLowerCase.hpp

   File Description	:	Function prototypes for lower-case string functions.

	Revision History	:	1993-10-02 --- Creation.
									Michael L. Brock
                        2023-01-12 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

		Copyright Michael L. Brock 1998 - 2023.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


#ifndef HH__MLB__Utility__StringLowerCase_hpp__HH

#define HH__MLB__Utility__StringLowerCase_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file 	StringLowerCase.hpp

	\brief	The MLB Utility C++ lower-case string functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string  &LowerCase(const std::string &in_string,
	std::string &out_string);
API_UTILITY  std::string  LowerCase(const std::string &in_string);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__StringUpperCase_hpp__HH

