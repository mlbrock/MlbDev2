// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name			:	TimeSpec.hpp

   File Description	:	Definition of the TimeSpec class.

   Revision History	:	1994-05-21 --- Added to C genfuncs.h include file.
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

#ifndef HH__MLB__Utility__TimeSpec_hpp__HH

#define HH__MLB__Utility__TimeSpec_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file TimeSpec.hpp

   \brief	The TimeSpec class definition include file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/TimeVal.hpp>

#include <string>

#if defined(_MSC_VER)
# if (_MSC_VER < 1900)
struct timespec {
	time_t tv_sec;
	long   tv_nsec;
};
# endif // # if (_MSC_VER < 1900)
#else
# include <unistd.h>
#endif // # if defined(_MSC_VER)

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
/**
	\brief A wrapper class around \c struct \c timespec.

	The wrapper is implemented by public inheritance from \c struct \c timespec ,
	so substitutability is supported.
*/
struct API_UTILITY TimeSpec : public timespec {
	TimeSpec();
	explicit TimeSpec(time_t in_secs, long in_nsecs = 0L);
	explicit TimeSpec(const timespec &in_time);
	explicit TimeSpec(const timeval &in_time);
	explicit TimeSpec(const std::string &in_date);
	~TimeSpec();

	bool operator <  (const TimeSpec &other) const;
	bool operator >  (const TimeSpec &other) const;
	bool operator <= (const TimeSpec &other) const;
	bool operator >= (const TimeSpec &other) const;
	bool operator == (const TimeSpec &other) const;
	bool operator != (const TimeSpec &other) const;

	int  Compare(const TimeSpec &other) const;

	TimeSpec &SetToNow();
	TimeSpec &SetToMinimumValue();
	TimeSpec &SetToMaximumValue();

	bool IsZero() const;

	TimeSpec &AddSeconds(int secs_to_add);
	TimeSpec &AddMilliseconds(int msecs_to_add);
	TimeSpec &AddMicroseconds(int usecs_to_add);
	TimeSpec &AddNanoseconds(int nsecs_to_add);

	void swap(TimeSpec &other);

	char        *ToString(char *buffer,
		std::size_t max_length = Length_TimeSpec) const;
	std::string  ToString(std::size_t max_length = Length_TimeSpec) const;
	std::string &ToString(std::string &out_string,
		std::size_t max_length = Length_TimeSpec) const;

	char        *ToStringLocal(char *buffer,
		std::size_t max_length = Length_TimeSpec) const;
	std::string  ToStringLocal(std::size_t max_length = Length_TimeSpec) const;
	std::string &ToStringLocal(std::string &out_string,
		std::size_t max_length = Length_TimeSpec) const;

	char        *ToStringInterval(char *buffer,
		std::size_t max_length = LengthInterval_TimeSpec) const;
	std::string  ToStringInterval(
		std::size_t max_length = LengthInterval_TimeSpec) const;
	std::string &ToStringInterval(std::string &out_string,
		std::size_t max_length = LengthInterval_TimeSpec) const;

	TimeT   ToTimeT() const;
	TimeVal ToTimeVal() const;

	unsigned long long ToTicks() const;
	unsigned long long ToNanoseconds() const;

	double GetDouble() const;
	double GetDoubleEquivalent() const;
	double GetDoubleTicks() const;

	signed long long GetDifferenceTicks(const TimeSpec &other) const;
	double           GetDifferenceTicksDouble(const TimeSpec &other) const;
	double           GetDifferenceDouble(const TimeSpec &other) const;
	TimeSpec         GetDifference(const TimeSpec &other) const;
	TimeSpec         GetDifferenceAbs(const TimeSpec &other) const;

	static signed long long GetDifferenceTicks(const TimeSpec &lhs,
		const TimeSpec &rhs);
	static double           GetDifferenceTicksDouble(const TimeSpec &lhs,
		const TimeSpec &rhs);
	static double           GetDifferenceDouble(const TimeSpec &lhs,
		const TimeSpec &rhs);
	static TimeSpec         GetDifference(const TimeSpec &lhs,
		const TimeSpec &rhs);
	static TimeSpec         GetDifferenceAbs(const TimeSpec &lhs,
		const TimeSpec &rhs);

	const struct timespec &GetUnderlyingRef() const
	{
		return(*this);
	}
	struct timespec &GetUnderlyingRef()
	{
		return(*this);
	}
	struct timespec GetUnderlying() const
	{
		return(*this);
	}

	static TimeSpec FromString(const std::string &in_date);
	static TimeSpec FromString(const char *in_date);
	static TimeSpec FromNanoseconds(unsigned long long nsecs);

	static TimeSpec Now();

	//	Used to support a C-style interface...
	static int      Compare(const TimeSpec *lhs, const TimeSpec *rhs);

	static TimeSpec GetMinimumValue();
	static TimeSpec GetMaximumValue();

private:
	char *FormatString(const TimeTM &in_tm, char *buffer,
		std::size_t max_length = Length_TimeSpec) const;
	char *FormatStringInterval(char *buffer,
		std::size_t max_length = LengthInterval_TimeSpec) const;
	char *AppendFractionalPortion(std::size_t idx, char *buffer) const;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::ostream & operator << (std::ostream &o_str,
	const TimeSpec &datum);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__TimeSpec_hpp__HH

