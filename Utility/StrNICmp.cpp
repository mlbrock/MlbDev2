// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StrNICmp.cpp

   File Description  :  Case-insensitive length limited string comparison
                        functions.

   Revision History  :  1986-10-27 --- Creation in C strfuncs library.
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

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/StrNICmp.hpp>

#ifndef __GNUC__
# include <string.h>
#else
# include <strings.h>
#endif // #ifndef __GNUC__

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
int StrNICmp(const char *ptr_1, const char *ptr_2, std::size_t data_length)
{
#ifndef __GNUC__
# ifdef _MSC_VER
	return(::_strnicmp(ptr_1, ptr_2, data_length));
#else
	return(::strnicmp(ptr_1, ptr_2, data_length));
# endif // # ifdef _MSC_VER
#else
	return(::strncasecmp(ptr_1, ptr_2, data_length));
#endif // #ifndef __GNUC__
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int Utility_strnicmp(const char *ptr_1, const char *ptr_2,
	std::size_t data_length)
{
	return(StrNICmp(ptr_1, ptr_2, data_length));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

