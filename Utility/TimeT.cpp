// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  TimeT.cpp

   File Description  :  Implementation of the TimeT class.

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

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/TimeT.hpp>

#include <Utility/nstrcpy.hpp>
#include <Utility/TimeTM.hpp>

#include <limits>

// ////////////////////////////////////////////////////////////////////////////

// Note: TimeT::AddSecondsInternal() is implemented in Time.cpp.

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
TimeT::TimeT()
	:datum_(time(NULL))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT::TimeT(const time_t &in_time)
	:datum_(in_time)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT::TimeT(const std::string &in_date)
	:datum_(FromString(in_date).datum_)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT::~TimeT()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeT::operator <  (const TimeT &other) const
{
	return(Compare(this, &other) <  0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeT::operator >  (const TimeT &other) const
{
	return(Compare(this, &other) >  0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeT::operator <= (const TimeT &other) const
{
	return(Compare(this, &other) <= 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeT::operator >= (const TimeT &other) const
{
	return(Compare(this, &other) >= 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeT::operator == (const TimeT &other) const
{
	return(Compare(this, &other) == 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeT::operator != (const TimeT &other) const
{
	return(Compare(this, &other) != 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int TimeT::Compare(const TimeT &other) const
{
	return(Compare(this, &other));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT &TimeT::SetToNow()
{
	datum_ = time(NULL);

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT &TimeT::SetToMinimumValue()
{
	datum_ = static_cast<time_t>(0);

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT &TimeT::SetToMaximumValue()
{
	datum_ = std::numeric_limits<time_t>::max();

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeT::IsZero() const
{
	return(datum_ == 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT &TimeT::AddMilliseconds(int msecs_to_add)
{
	return(AddSeconds(msecs_to_add / 1000));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT &TimeT::AddMicroseconds(int usecs_to_add)
{
	return(AddSeconds(usecs_to_add / 1000000));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT &TimeT::AddNanoseconds(int nsecs_to_add)
{
	return(AddSeconds(nsecs_to_add / 1000000000));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeT::ToString(char *buffer, std::size_t max_length) const
{
	return(FormatString(TimeTM::TimeUTC(datum_), buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string TimeT::ToString(std::size_t max_length) const
{
	char buffer[Length_TimeT + 1];

	return(ToString(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &TimeT::ToString(std::string &out_string,
	std::size_t max_length) const
{
	char buffer[Length_TimeT + 1];

	return(out_string.assign(ToString(buffer, max_length)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeT::ToStringLocal(char *buffer, std::size_t max_length) const
{
	return(FormatString(TimeTM::TimeLocal(datum_), buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string TimeT::ToStringLocal(std::size_t max_length) const
{
	char buffer[Length_TimeT + 1];

	return(ToStringLocal(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &TimeT::ToStringLocal(std::string &out_string,
	std::size_t max_length) const
{
	char buffer[Length_TimeT + 1];

	return(out_string.assign(ToStringLocal(buffer, max_length)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeT::ToStringInterval(char *buffer, std::size_t max_length) const
{
	return(FormatStringInterval(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string TimeT::ToStringInterval(std::size_t max_length) const
{
	char buffer[LengthInterval_TimeT + 1];

	return(ToStringInterval(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &TimeT::ToStringInterval(std::string &out_string,
	std::size_t max_length) const
{
	char buffer[LengthInterval_TimeT + 1];

	return(out_string.assign(ToStringInterval(buffer, max_length)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT TimeT::FromString(const char *in_date)
{
	TimeT out_date(0);
	long  out_fractional;

	ParseFromString(in_date, out_date.datum_, out_fractional, 0);

	return(out_date);	
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT TimeT::FromString(const std::string &in_date)
{
	return(FromString(in_date.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT TimeT::Now()
{
	return(TimeT(time(NULL)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int TimeT::Compare(const TimeT *lhs, const TimeT *rhs)
{
	return(
		((int) (lhs->datum_  > rhs->datum_)  ?  1 :
				((lhs->datum_  < rhs->datum_)  ? -1 : 0)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT TimeT::GetMinimumValue()
{
	TimeT tmp_datum(0);

	return(tmp_datum.SetToMinimumValue());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT TimeT::GetMaximumValue()
{
	TimeT tmp_datum(0);

	return(tmp_datum.SetToMaximumValue());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeT::FormatString(const TimeTM &in_tm, char *buffer,
	std::size_t max_length) const
{
	if (max_length < Length_TimeT) {
		char tmp_buffer[Length_TimeT + 1];
		return(nstrcpy(buffer, FormatString(in_tm, tmp_buffer), max_length));
	}

	//	This gets YYYY-MM-DD hh:mm:ss
	in_tm.ToString(buffer);

	return(buffer);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeT::FormatStringInterval(char *buffer, std::size_t max_length) const
{
	if (max_length < LengthInterval_TimeT) {
		char tmp_buffer[LengthInterval_TimeT + 1];
		return(nstrcpy(buffer, FormatStringInterval(tmp_buffer), max_length));
	}

	//	This gets the number of days...
	unsigned long all_secs = static_cast<unsigned long>(datum_);
	unsigned long days     = (all_secs / (24L * 60L * 60L)) % 1000000L;
	unsigned long hours    = (all_secs % (60L * 60L * 24L)) / (60L * 60L);
	unsigned long minutes  = (all_secs % (60L * 60L)) / 60L;
	unsigned long secs     = all_secs % 60L;

	buffer[0]  = ((char) ('0' + ((char) ((days %    1000000L) / 100000L))));
	buffer[1]  = ((char) ('0' + ((char) ((days %     100000L) / 10000L))));
	buffer[2]  = ((char) ('0' + ((char) ((days %      10000L) / 1000L))));
	buffer[3]  = ((char) ('0' + ((char) ((days %       1000L) / 100L))));
	buffer[4]  = ((char) ('0' + ((char) ((days %        100L) / 10L))));
	buffer[5]  = ((char) ('0' + ((char)  (days %         10L))));

	buffer[6]  = ' ';
	buffer[7]  = ((char) ('0' + ((char) (hours / 10L))));
	buffer[8]  = ((char) ('0' + ((char) (hours % 10L))));
	buffer[9]  = ':';
	buffer[10] = ((char) ('0' + ((char) (minutes / 10L))));
	buffer[11] = ((char) ('0' + ((char) (minutes % 10L))));
	buffer[12] = ':';
	buffer[13] = ((char) ('0' + ((char) (secs / 10L))));
	buffer[14] = ((char) ('0' + ((char) (secs % 10L))));
	buffer[15] = '\0';

	return(buffer);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const TimeT &datum)
{
	char tmp_buffer[Length_TimeT + 1];

	o_str <<
		datum.ToString(tmp_buffer, sizeof(tmp_buffer) - 1);

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

