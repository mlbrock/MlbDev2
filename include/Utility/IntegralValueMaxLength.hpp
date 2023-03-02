// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  IntegralValueMaxLength.hpp

   File Description  :  Maximum radix digits for two's complement integers.

   Revision History  :  1998-04-08 --- Creation
                           Michael L. Brock
                        2023-01-04 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1998 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__IntegralValueMaxLength_hpp__HH

#define HH__MLB__Utility__IntegralValueMaxLength_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file IntegralValueMaxLength.hpp

   \brief   The IntegralValueMaxLength[Bin|Oct|Dec|Hex]() functions header.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <climits>
#include <limits>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline constexpr std::size_t IntegralValueMaxLengthBin()
{
	return(sizeof(DatumType) * CHAR_BIT);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline constexpr std::size_t IntegralValueMaxLengthOct()
{
	return(((sizeof(DatumType) * CHAR_BIT) / 3) +
			(((sizeof(DatumType) * CHAR_BIT) % 3) ? 1 : 0));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline constexpr std::size_t IntegralValueMaxLengthDecUnsigned()
{
	switch (sizeof(DatumType)) {
		case    1:	//	   8 bits
			return(3);
		case    2:	//	  16 bits
			return(5);
		case    4:	//	  32 bits
			return(10);
		case    8:	//	  64 bits
			return(20);
		case   16:	//	 128 bits
			return(39);
		case   32:	//	 256 bits
			return(78);
		case   64:	//	 512 bits
			return(155);
		case  128:	//	1024 bits
			return(309);
		case  256:	//	2048 bits
			return(617);
		case  512:	//	4096 bits
			return(1234);
		case 1024:	//	8192 bits
			return(2467);
	}

	// An approximation
	return(((sizeof(DatumType) % 2) ? ((((sizeof(DatumType) - 1) / 2) * 5) + 3):
		((sizeof(DatumType) / 2) * 5)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
/// Only the decimal function adjusts for potential signedness of DatumType.
template <typename DatumType>
	inline constexpr std::size_t IntegralValueMaxLengthDec()
{
/*
	switch (sizeof(DatumType)) {
		case    1:	//	   8 bits
			return(((std::numeric_limits<DatumType>::is_signed) ? 1 : 0) + 3);
		case    2:	//	  16 bits
			return(((std::numeric_limits<DatumType>::is_signed) ? 1 : 0) + 5);
		case    4:	//	  32 bits
			return(((std::numeric_limits<DatumType>::is_signed) ? 1 : 0) + 10);
		case    8:	//	  64 bits
			return(20);
		case   16:	//	 128 bits
			return(((std::numeric_limits<DatumType>::is_signed) ? 1 : 0) + 39);
		case   32:	//	 256 bits
			return(78);
		case   64:	//	 512 bits
			return(155);
		case  128:	//	1024 bits
			return(309);
		case  256:	//	2048 bits
			return(((std::numeric_limits<DatumType>::is_signed) ? 1 : 0) + 617);
		case  512:	//	4096 bits
			return(1234);
		case 1024:	//	8192 bits
			return(2467);
	}

	// An approximation
	return(((sizeof(DatumType) % 2) ? ((((sizeof(DatumType) - 1) / 2) * 5) + 3):
		((sizeof(DatumType) / 2) * 5)) +
		((std::numeric_limits<DatumType>::is_signed) ? 1 : 0));
*/
	switch (sizeof(DatumType)) {
		case    1:	//	   8 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>() + 1);
		case    2:	//	  16 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>() + 1);
		case    4:	//	  32 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>() + 1);
		case    8:	//	  64 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>());
		case   16:	//	 128 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>() + 1);
		case   32:	//	 256 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>());
		case   64:	//	 512 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>());
		case  128:	//	1024 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>());
		case  256:	//	2048 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>() + 1);
		case  512:	//	4096 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>());
		case 1024:	//	8192 bits
			return(IntegralValueMaxLengthDecUnsigned<DatumType>());
	}

	// An approximation
	return(IntegralValueMaxLengthDecUnsigned<DatumType>() +
		((sizeof(DatumType) % 2) ? 0 : 1));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType>
	inline constexpr std::size_t IntegralValueMaxLengthHex()
{
	return(((sizeof(DatumType) * CHAR_BIT) / 4) +
			(((sizeof(DatumType) * CHAR_BIT) % 4) ? 1 : 0));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__IntegralValueMaxLength_hpp__HH

