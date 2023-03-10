// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  LogTestSupport.hpp

   File Description  :  Function prototypes for shared log tests.

   Revision History  :  2005-01-02 --- Creation
                           Michael L. Brock
                        2023-02-25 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 2005 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__LogTestSupport_hpp__HH

#define HH__MLB__Utility__LogTestSupport_hpp__HH   1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file LogTestSupport.hpp

   \brief   Function prototypes for shared log tests.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/LogHandler.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY void TEST_MultiLineOperation();
API_UTILITY void TEST_IsolationThreadProc();
API_UTILITY void TEST_Isolation();
API_UTILITY void TEST_NoEOL();
API_UTILITY void TEST_StressLines();
API_UTILITY void TEST_StressSize();

API_UTILITY void TEST_TestControl(LogHandlerPtr my_log_handler,
	bool stress_lines = false);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__LogTestSupport_hpp__HH

