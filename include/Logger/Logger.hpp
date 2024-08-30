// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Logger Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  Logger.hpp

   File Description  :  Header file for the Logger library.

   Revision History  :  1993-10-02 --- Creation of predecessor 'mlog' facility.
                           Michael L. Brock
                        2005-01-02 --- New ostream-based log model.
                           Michael L. Brock
                        2023-01-05 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1993 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__Logger_hpp__HH

#define HH__MLB__Utility__Logger_hpp__HH 1

#define MLB__LIB__Logger

// ////////////////////////////////////////////////////////////////////////////
/**
   \file    LogManager.hpp

   \brief   The header file for the Logger library.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#ifdef MLB__LIB__Logger___NOT
# ifdef LOGGER_DLL_EXPORTS
#  define API_LOGGER      MB_LIB_EXPORT
# else
#  define API_LOGGER      MB_LIB_IMPORT
# endif // #ifdef LOGGER_DLL_EXPORTS
#else
# define API_LOGGER
#endif // #ifdef MLB__LIB__Logger___NOT

   // Define MB_LIB_THIS_SIDE to be the {im|ex}port side for shared libs...
#ifdef MB_LIB_THIS_SIDE
#undef MB_LIB_THIS_SIDE
#endif // #ifdef MB_LIB_THIS_SIDE
#define MB_LIB_THIS_SIDE   API_LOGGER

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__Logger_hpp__HH

