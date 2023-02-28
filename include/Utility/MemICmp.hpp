// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	MemICmp.hpp

   File Description	:	Include file for case-insensitive memory comparison
								functions.

	Revision History	:	1986-10-27 --- Creation in the C strfuncs library.
   								Michael L. Brock
								1998-04-08 --- Migration to C++ MlbDev/Utility.
									Michael L. Brock
								2023-01-13 --- Migration to C++ MlbDev2/Utility.
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2023.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__MemICmp_hpp__HH

#define HH__MLB__Utility__MemICmp_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file MemICmp.hpp

	\brief	The case-insensitive memory comparison functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <cstddef>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY int MemICmp(const void *ptr_1, const void *ptr_2,
	std::size_t data_length);
// IMPL NOTE: For name compatibility with the old MlbDef/Utility
API_UTILITY int Utility_memicmp(const void *ptr_1, const void *ptr_2,
	std::size_t data_length);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__MemICmp_hpp__HH
