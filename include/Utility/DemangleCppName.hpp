// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  DemangleCppName.hpp

   File Description  :  Prototypes of the C++ demangle functions.

   Revision History  :  2015-07-20 --- Original logic implemented in file
                                       MlbDev/Utility/BackTrace.cpp.
                           Michael L. Brock
                        2016-08-07 --- Separated implementation into file
                                       MlbDev/Utility/DemangleCppName.cpp.
                           Michael L. Brock
                        2023-01-13 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 2015 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__DemangleCppName_hpp__HH

#define HH__MLB__Utility__DemangleCppName_hpp__HH  1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file DemangleCppName.hpp

   \brief   The C++ demangle function prototypes.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string DemangleCppName(const char *src);
API_UTILITY std::string DemangleCppName(const std::string &src);

API_UTILITY std::string DemangleTypeInfoName(const char *src);
API_UTILITY std::string DemangleTypeInfoName(const std::string &src);

API_UTILITY std::string DemangledCppNameToBasic(const char *src);
API_UTILITY std::string DemangledCppNameToBasic(const std::string &src);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__DemangleCppName_hpp__HH

