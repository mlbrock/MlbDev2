// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	MemICmp.cpp

	File Description	:	Case-insensitive memory comparison functions.

   Revision History	:	1986-10-27 --- Creation in C strfuncs library.
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
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/MemICmp.hpp>

#ifndef __GNUC__
# include <memory.h>
#else
# include <cctype>
#endif // #ifndef __GNUC__

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
int MemICmp(const void *ptr_1, const void *ptr_2, std::size_t data_length)
{
#ifndef __GNUC__
# ifdef _MSC_VER
	return(::_memicmp(ptr_1, ptr_2, data_length));
# else
	return(::memicmp(ptr_1, ptr_2, data_length));
# endif // # ifdef _MSC_VER
#else
	const signed char *tp_1 = static_cast<const signed char *>(ptr_1);
	const signed char *tp_2 = static_cast<const signed char *>(ptr_2);

	while (data_length--) {
		if (::toupper(*tp_1) != ::toupper(*tp_2))
			return((*reinterpret_cast<const unsigned char *>(tp_1) <
					  *reinterpret_cast<const unsigned char *>(tp_2)) ? -1 : 1);
		++tp_1;
		++tp_2;
	}

	return(0);
#endif // #ifndef __GNUC__
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int Utility_memicmp(const void *ptr_1, const void *ptr_2,
	std::size_t data_length)
{
	return(MemICmp(ptr_1, ptr_2, data_length));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

