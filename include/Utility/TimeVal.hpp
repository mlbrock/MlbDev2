// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name			:	TimeVal.hpp

   File Description	:	Definition of the TimeVal class.

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

#ifndef HH__MLB__Utility__TimeVal_hpp__HH

#define HH__MLB__Utility__TimeVal_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file TimeVal.hpp

   \brief	The TimeVal class definition include file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/TimeT.hpp>
#include <Utility/TimeTM.hpp>

#include <cstring>
#include <ostream>

#ifndef _MSC_VER
# include <sys/time.h>
#elif (_MSC_VER < 1900)
# include <WinSock2.h>
#else
# pragma warning(push)
# pragma warning(disable:5039)
# include <WinSock2.h>
# pragma warning(pop)
#endif // #ifndef _MSC_VER

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
/**
	\brief A wrapper class around \c struct \c timeval.

	The wrapper is implemented by public inheritance from \c struct \c timeval ,
	so substitutability is supported.
*/
struct API_UTILITY TimeVal : public timeval {
	         TimeVal();
	explicit TimeVal(time_t in_secs, long in_usecs = 0L);
	explicit TimeVal(const timeval &in_time);
	explicit TimeVal(const std::string &in_date);

	~TimeVal();

	bool operator <  (const TimeVal &other) const;
	bool operator >  (const TimeVal &other) const;
	bool operator <= (const TimeVal &other) const;
	bool operator >= (const TimeVal &other) const;
	bool operator == (const TimeVal &other) const;
	bool operator != (const TimeVal &other) const;

	int  Compare(const TimeVal &other) const;

	TimeVal &SetToNow();
	TimeVal &SetToMinimumValue();
	TimeVal &SetToMaximumValue();

	bool IsZero() const;

	TimeVal &AddSeconds(int secs_to_add);
	TimeVal &AddMilliseconds(int msecs_to_add);
	TimeVal &AddMicroseconds(int usecs_to_add);
	TimeVal &AddNanoseconds(int nsecs_to_add);

	void swap(TimeVal &other);

	char        *ToString(char *buffer,
		std::size_t max_length = Length_TimeVal) const;
	std::string  ToString(std::size_t max_length = Length_TimeVal) const;
	std::string &ToString(std::string &out_string,
		std::size_t max_length = Length_TimeVal) const;

	char        *ToStringLocal(char *buffer,
		std::size_t max_length = Length_TimeVal) const;
	std::string  ToStringLocal(std::size_t max_length = Length_TimeVal) const;
	std::string &ToStringLocal(std::string &out_string,
		std::size_t max_length = Length_TimeVal) const;

	char        *ToStringInterval(char *buffer,
		std::size_t max_length = LengthInterval_TimeVal) const;
	std::string  ToStringInterval(
		std::size_t max_length = LengthInterval_TimeVal) const;
	std::string &ToStringInterval(std::string &out_string,
		std::size_t max_length = LengthInterval_TimeVal) const;

	TimeT   ToTimeT() const;

	unsigned long long ToTicks() const;
	unsigned long long ToMicroseconds() const;

	double GetDouble() const;
	double GetDoubleEquivalent() const;
	double GetDoubleTicks() const;

	signed long long GetDifferenceTicks(const TimeVal &other) const;
	double           GetDifferenceTicksDouble(const TimeVal &other) const;
	double           GetDifferenceDouble(const TimeVal &other) const;
	TimeVal          GetDifference(const TimeVal &other) const;
	TimeVal          GetDifferenceAbs(const TimeVal &other) const;

	static signed long long GetDifferenceTicks(const TimeVal &lhs,
		const TimeVal &rhs);
	static double           GetDifferenceTicksDouble(const TimeVal &lhs,
		const TimeVal &rhs);
	static double           GetDifferenceDouble(const TimeVal &lhs,
		const TimeVal &rhs);
	static TimeVal          GetDifference(const TimeVal &lhs,
		const TimeVal &rhs);
	static TimeVal          GetDifferenceAbs(const TimeVal &lhs,
		const TimeVal &rhs);

	const struct timeval &GetUnderlyingRef() const
	{
		return(*this);
	}
	struct timeval &GetUnderlyingRef()
	{
		return(*this);
	}
	struct timeval GetUnderlying() const
	{
		return(*this);
	}

	static TimeVal FromString(const std::string &in_date);
	static TimeVal FromString(const char *in_date);
	static TimeVal FromMicroseconds(unsigned long long usecs);

	static TimeVal Now();

	//	Used to support a C-style interface...
	static int     Compare(const TimeVal *lhs, const TimeVal *rhs);

	static TimeVal GetMinimumValue();
	static TimeVal GetMaximumValue();

private:
	char *FormatString(const TimeTM &in_tm, char *buffer,
		std::size_t max_length = Length_TimeVal) const;
	char *FormatStringInterval(char *buffer,
		std::size_t max_length = LengthInterval_TimeVal) const;
	char *AppendFractionalPortion(std::size_t idx, char *buffer) const;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::ostream & operator << (std::ostream &o_str,
	const TimeVal &datum);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__TimeVal_hpp__HH

