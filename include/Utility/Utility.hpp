// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  Utility.hpp

   File Description  :  Include file for utility library.

   Revision History  :  1998-04-08 --- Creation.
                           Michael L. Brock
                        2023-01-04 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1998 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__Utility_hpp__HH

#define HH__MLB__Utility__Utility_hpp__HH 1

#define MLB__LIB__Utility

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file Utility.hpp

   \brief   The MLB Utility header file.

   Contains general-purpose and utility classes and definitions.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <mbcompat.h>

#if defined(__MINGW32__)
# define _WIN32_WINNT 0x0500
#endif // #if defined(__MINGW32__)

#ifdef MLB__LIB__Utility___NOT
# ifdef UTILITY_DLL_EXPORTS
#  define API_UTILITY      MB_LIB_EXPORT
# else
#  define API_UTILITY      MB_LIB_IMPORT
# endif // #ifdef UTILITY_DLL_EXPORTS
#else
# define API_UTILITY
#endif // #ifdef MLB__LIB__Utility___NOT

   // Define MB_LIB_THIS_SIDE to be the {im|ex}port side for shared libs...
#ifdef MB_LIB_THIS_SIDE
#undef MB_LIB_THIS_SIDE
#endif // #ifdef MB_LIB_THIS_SIDE
#define MB_LIB_THIS_SIDE   API_UTILITY

// ////////////////////////////////////////////////////////////////////////////

/**
	\namespace MLB

	\brief The Michael L. Brock namespace.
*/
namespace MLB {

/**
	\namespace MLB::Utility

	\brief The Utility namespace.
*/
namespace Utility {

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__Utility_hpp__HH

