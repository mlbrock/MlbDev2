// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  TimeVal.cpp

   File Description  :  Implementation of the TimeVal class.

   Revision History  :  1994-05-21 --- Added to C genfuncs lib as timeval.c
                           Michael L. Brock
                        1998-04-08 --- Revision for the MlbDev Utility library.
                           Michael L. Brock
                        2022-10-01 --- Added to MlbDev3 Utility library.
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

#include <Utility/TimeVal.hpp>

#include <Utility/AnyToString.hpp>
#include <Utility/ExceptionRethrow.hpp>
#include <Utility/nstrcpy.hpp>
#include <Utility/TimeSpec.hpp>
#include <Utility/TimeT.hpp>
#include <Utility/TimeTM.hpp>

#include <cmath>
#include <limits>

// ////////////////////////////////////////////////////////////////////////////

// Note: TimeVal::AddSecondsInternal() is implemented in Time.cpp.

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
TimeVal::TimeVal()
{
	*this = TimeVal::Now();
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal::TimeVal(time_t in_secs, long in_usecs)
{
	tv_sec  = static_cast<long>(in_secs);
	tv_usec = in_usecs;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal::TimeVal(const timeval &in_time)
	:timeval(in_time)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal::TimeVal(const std::string &in_date)
	:timeval(FromString(in_date))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal::~TimeVal()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeVal::operator <  (const TimeVal &other) const
{
	return(Compare(this, &other) <  0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeVal::operator >  (const TimeVal &other) const
{
	return(Compare(this, &other) >  0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeVal::operator <= (const TimeVal &other) const
{
	return(Compare(this, &other) <= 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeVal::operator >= (const TimeVal &other) const
{
	return(Compare(this, &other) >= 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeVal::operator == (const TimeVal &other) const
{
	return(Compare(this, &other) == 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeVal::operator != (const TimeVal &other) const
{
	return(Compare(this, &other) != 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int TimeVal::Compare(const TimeVal &other) const
{
	return(Compare(this, &other));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal &TimeVal::SetToNow()
{
	Now().swap(*this);

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal &TimeVal::SetToMinimumValue()
{
	tv_sec  = 0;
	tv_usec = 0;

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal &TimeVal::SetToMaximumValue()
{
	tv_sec  = std::numeric_limits<long>::max();
	tv_usec = 999999;

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool TimeVal::IsZero() const
{
	return((tv_sec == 0) && (tv_usec == 0));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal &TimeVal::AddMilliseconds(int msecs_to_add)
{
	int secs_to_add = msecs_to_add / 1000;
	int new_usec    = tv_usec + ((msecs_to_add % 1000) * 1000);

	if (new_usec >= 1000000) {
		secs_to_add += new_usec / 1000000;
		new_usec    %= 1000000;
	}
	else if (new_usec < 0) {
		secs_to_add += -1 + (new_usec / 1000000);
		new_usec     = 1000000 + (new_usec % 1000000);
	}

	if (secs_to_add) {
		try {
			AddSeconds(secs_to_add);
		}
		catch (const std::exception &except) {
			Rethrow(except, "Unable to add the requested number of milliseconds "
				"(" + AnyToString(msecs_to_add) + "): " +
				std::string(except.what()));
		}
	}

	tv_usec = new_usec;

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal &TimeVal::AddMicroseconds(int usecs_to_add)
{
	int secs_to_add = usecs_to_add / 1000000;
	int new_usec    = tv_usec + (usecs_to_add % 1000000);

	if (new_usec >= 1000000) {
		secs_to_add += new_usec / 1000000;
		new_usec    %= 1000000;
	}
	else if (new_usec < 0) {
		secs_to_add += -1 + (new_usec / 1000000);
		new_usec     = 1000000 + (new_usec % 1000000);
	}

	if (secs_to_add) {
		try {
			AddSeconds(secs_to_add);
		}
		catch (const std::exception &except) {
			Rethrow(except, "Unable to add the requested number of microseconds "
				"(" + AnyToString(usecs_to_add) + "): " +
				std::string(except.what()));
		}
	}

	tv_usec = new_usec;

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal &TimeVal::AddNanoseconds(int nsecs_to_add)
{
	return(AddMicroseconds(nsecs_to_add / 1000));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TimeVal::swap(TimeVal &other)
{
	std::swap(tv_sec, other.tv_sec);
	std::swap(tv_usec, other.tv_usec);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeVal::ToString(char *buffer, std::size_t max_length) const
{
	return(FormatString(TimeTM::TimeUTC(tv_sec), buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string TimeVal::ToString(std::size_t max_length) const
{
	char buffer[Length_TimeVal + 1];

	return(ToString(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &TimeVal::ToString(std::string &out_string,
	std::size_t max_length) const
{
	char buffer[Length_TimeVal + 1];

	return(out_string.assign(ToString(buffer, max_length)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeVal::ToStringLocal(char *buffer, std::size_t max_length) const
{
	return(FormatString(TimeTM::TimeLocal(tv_sec), buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string TimeVal::ToStringLocal(std::size_t max_length) const
{
	char buffer[Length_TimeVal + 1];

	return(ToStringLocal(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &TimeVal::ToStringLocal(std::string &out_string,
	std::size_t max_length) const
{
	char buffer[Length_TimeVal + 1];

	return(out_string.assign(ToStringLocal(buffer, max_length)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeVal::ToStringInterval(char *buffer, std::size_t max_length) const
{
	return(FormatStringInterval(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string TimeVal::ToStringInterval(std::size_t max_length) const
{
	char buffer[LengthInterval_TimeVal + 1];

	return(ToStringInterval(buffer, max_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &TimeVal::ToStringInterval(std::string &out_string,
	std::size_t max_length) const
{
	char buffer[LengthInterval_TimeVal + 1];

	return(out_string.assign(ToStringInterval(buffer, max_length)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeT TimeVal::ToTimeT() const
{
	return(TimeT(tv_sec));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
unsigned long long TimeVal::ToTicks() const
{
	return(ToMicroseconds());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
unsigned long long TimeVal::ToMicroseconds() const
{
	return((static_cast<unsigned long long>(tv_sec) *
		static_cast<unsigned long long>(1000000)) +
		static_cast<unsigned long long>(tv_usec));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
double TimeVal::GetDouble() const
{
	return(GetDoubleEquivalent());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
double TimeVal::GetDoubleEquivalent() const
{
	return(static_cast<double>(tv_sec) +
		(static_cast<double>(tv_usec) / 1000000.0));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
double TimeVal::GetDoubleTicks() const
{
	return((static_cast<double>(tv_sec) * 1000000.0) +
		static_cast<double>(tv_usec));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
signed long long TimeVal::GetDifferenceTicks(const TimeVal &other) const
{
	return(GetDifferenceTicks(*this, other));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
double TimeVal::GetDifferenceTicksDouble(const TimeVal &other) const
{
	return(GetDifferenceTicksDouble(*this, other));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
double TimeVal::GetDifferenceDouble(const TimeVal &other) const
{
	return(GetDifferenceDouble(*this, other));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::GetDifference(const TimeVal &other) const
{
	return(GetDifference(*this, other));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::GetDifferenceAbs(const TimeVal &other) const
{
	return(GetDifferenceAbs(*this, other));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
signed long long TimeVal::GetDifferenceTicks(const TimeVal &lhs,
	const TimeVal &rhs)
{
	return(static_cast<signed long long>(lhs.ToMicroseconds()) -
		static_cast<signed long long>(rhs.ToMicroseconds()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
double TimeVal::GetDifferenceTicksDouble(const TimeVal &lhs, const TimeVal &rhs)
{
	return(lhs.GetDoubleTicks() - rhs.GetDoubleTicks());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
double TimeVal::GetDifferenceDouble(const TimeVal &lhs, const TimeVal &rhs)
{
	return(lhs.GetDoubleEquivalent() - rhs.GetDoubleEquivalent());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::GetDifference(const TimeVal &lhs, const TimeVal &rhs)
{
	double tmp_double = GetDifferenceTicksDouble(lhs, rhs);

	return(TimeVal(static_cast<long>(tmp_double / 1000000.0),
		static_cast<long>(fmod(tmp_double, 1000000.0))));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::GetDifferenceAbs(const TimeVal &lhs, const TimeVal &rhs)
{
	return((lhs >= rhs) ? GetDifference(lhs, rhs) :
		GetDifference(rhs, lhs));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::FromString(const char *in_date)
{
	TimeVal out_date(0, 0);
	time_t  tv_sec;	//	Because it's OS-specific sizeof(time_t) != sizeof(long)

	ParseFromString(in_date, tv_sec, out_date.tv_usec, 6);

	out_date.tv_sec = static_cast<long>(tv_sec);

	return(out_date);	
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::FromString(const std::string &in_date)
{
	return(TimeVal::FromString(in_date.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::FromMicroseconds(unsigned long long usecs)
{
	return(TimeVal(static_cast<time_t>(usecs /
		static_cast<unsigned long long>(1000000)),
		static_cast<long>(usecs % static_cast<unsigned long long>(1000000))));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::Now()
{
	return(TimeSpec::Now().ToTimeVal());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int TimeVal::Compare(const TimeVal *lhs, const TimeVal *rhs)
{
	return(
		((int) (lhs->tv_sec  > rhs->tv_sec)  ?  1 :
				((lhs->tv_sec  < rhs->tv_sec)  ? -1 :
				((lhs->tv_usec > rhs->tv_usec) ?  1 :
				((lhs->tv_usec < rhs->tv_usec) ? -1 : 0)))));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::GetMinimumValue()
{
	TimeVal tmp_datum(0, 0);

	return(tmp_datum.SetToMinimumValue());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
TimeVal TimeVal::GetMaximumValue()
{
	TimeVal tmp_datum(0, 0);

	return(tmp_datum.SetToMaximumValue());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeVal::FormatString(const TimeTM &in_tm, char *buffer,
	std::size_t max_length) const
{
	if (max_length < Length_TimeVal) {
		char tmp_buffer[Length_TimeVal + 1];
		return(nstrcpy(buffer, FormatString(in_tm, tmp_buffer),
			max_length));
	}

	//	This gets YYYY-MM-DD hh:mm:ss
	in_tm.ToString(buffer);

	return(AppendFractionalPortion(Length_TimeT, buffer));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeVal::FormatStringInterval(char *buffer, std::size_t max_length) const
{
	if (max_length < LengthInterval_TimeVal) {
		char tmp_buffer[LengthInterval_TimeVal + 1];
		return(nstrcpy(buffer, FormatStringInterval(tmp_buffer), max_length));
	}

	//	This gets dddddd hh:mm:ss
	TimeT tmp_time_t(tv_sec);
	tmp_time_t.ToStringInterval(buffer);

	return(AppendFractionalPortion(LengthInterval_TimeT, buffer));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *TimeVal::AppendFractionalPortion(std::size_t idx, char *buffer) const
{
	//	Sanity insurance
	unsigned long usecs = static_cast<unsigned long>(this->tv_usec) % 1000000L;

	//	Now append the period followed by the number of microseconds
	buffer[idx++] = '.';
	buffer[idx++] = ((char) ('0' + ((char)  (usecs / 100000L))));
	buffer[idx++] = ((char) ('0' + ((char) ((usecs % 100000L) / 10000L))));
	buffer[idx++] = ((char) ('0' + ((char) ((usecs % 10000L) / 1000L))));
	buffer[idx++] = ((char) ('0' + ((char) ((usecs % 1000L) / 100L))));
	buffer[idx++] = ((char) ('0' + ((char) ((usecs % 100L) / 10L))));
	buffer[idx++] = ((char) ('0' + ((char)  (usecs % 10L))));
	buffer[idx]   = '\0';

	return(buffer);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const TimeVal &datum)
{
	char tmp_buffer[Length_TimeVal + 1];

	o_str <<
		datum.ToString(tmp_buffer, sizeof(tmp_buffer) - 1);

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

