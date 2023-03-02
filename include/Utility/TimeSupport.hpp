// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  TimeSupport.hpp

   File Description  :  Basic include file for the date/time support logic.

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

#ifndef HH__MLB__Utility__TimeSupport_hpp__HH

#define HH__MLB__Utility__TimeSupport_hpp__HH   1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file TimeSupport.hpp

   \brief   The date/time support logic header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <ctime>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
   // Unadorned time:
   //    hh:mm:ss
const std::size_t Length_Time_Basic         = 2 + 1 + 2 + 1 + 2;

   // Simplest of all:
   //    YYYY-MM-DD
const std::size_t Length_Date_Basic         = 4 + 1 + 2 + 1 + 2;

   //    dddddd
const std::size_t Length_Days_Basic         = 6;

   // Same as above plus a space followed by the eight-character time:
   //    YYYY-MM-DD hh:mm:ss
const std::size_t Length_TimeTM             = Length_Date_Basic + 1 + Length_Time_Basic;

   // The result of a call to asctime() without the trailing line-feed:
   //    Www Mmm dd hh::mm::ss YYYY
const std::size_t Length_TimeTM_AscTimeSane = 3 + 1 + 3 + 1 + 2 + 1 + Length_Time_Basic + 1 + 4;

   // The result of a call to asctime() with the trailing line-feed:
   //    Www Mmm dd hh::mm::ss YYYY\n
const std::size_t Length_TimeTM_AscTime     = Length_TimeTM_AscTimeSane + 1;

   // Same as above, no difference:
   //    YYYY-MM-DD hh:mm:ss
const std::size_t Length_TimeT              = Length_TimeTM;
   //    YYYY-MM-DD hh:mm:ss
const std::size_t LengthInterval_TimeT      = Length_Days_Basic + 1 + Length_Time_Basic;

   // Same as above plus a period followed by the number of milliseconds:
   //    YYYY-MM-DD hh:mm:ss.mmm
const std::size_t Length_TimeB              = Length_TimeTM + 1 + 3;
   //    dddddd hh:mm:ss.mmm
const std::size_t LengthInterval_TimeB      = Length_Days_Basic + 1 + Length_Time_Basic + 1 + 3;

   // Same as above plus a period followed by the number of microseconds:
   //    YYYY-MM-DD hh:mm:ss.uuuuuu
const std::size_t Length_TimeVal            = Length_TimeTM + 1 + 6;
   //    dddddd hh:mm:ss.uuuuuu
const std::size_t LengthInterval_TimeVal    = Length_Days_Basic + 1 + Length_Time_Basic + 1 + 6;

   // As above, but with a period followed by the number of nanoseconds instead:
   //    YYYY-MM-DD hh:mm:ss.nnnnnnnnn
const std::size_t Length_TimeSpec           = Length_TimeTM + 1 + 9;
   //    dddddd hh:mm:ss.nnnnnnnnn
const std::size_t LengthInterval_TimeSpec   = Length_Days_Basic + 1 + Length_Time_Basic + 1 + 9;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY void ParseFromString(const char *in_date, time_t &out_secs,
	long &out_fractional, long fractional_places);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__TimeSupport_hpp__HH

