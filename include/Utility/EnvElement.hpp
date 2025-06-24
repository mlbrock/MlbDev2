// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  EnvElement.hpp

   File Description  :  Definition of the EnvElement class.

   Revision History  :  1993-10-02 --- Creation
                           Michael L. Brock
                        2023-01-09 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1993 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__EnvElement_hpp__HH

#define HH__MLB__Utility__EnvElement_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file EnvElement.hpp

   \brief   The MLB environment variable element header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <set>
#include <string>
#include <vector>

#include <boost/config.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
struct API_UTILITY EnvElement {
	         EnvElement();
	explicit EnvElement(const std::string &env_string);
	         EnvElement(const std::string &env_name,
		const std::string &env_value);

#if defined(BOOST_CXX_VERSION) && (BOOST_CXX_VERSION >= 201703L)
	constexpr auto operator <=> (const EnvElement &other) const = default;
	constexpr bool operator ==  (const EnvElement &other) const = default;
#else
	bool operator < (const EnvElement &other) const;
#endif // #if defined(BOOST_CXX_VERSION) && (BOOST_CXX_VERSION >= 201703L)

	std::string &ToString(std::string &out_string) const;
	std::string  ToString() const;

	std::string env_name_;
	std::string env_value_;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::ostream & operator << (std::ostream &o_str,
	const EnvElement &datum);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
typedef std::vector<EnvElement>        EnvElementList;
typedef EnvElementList::iterator       EnvElementListIter;
typedef EnvElementList::const_iterator EnvElementListIterC;

typedef std::set<EnvElement>           EnvElementSet;
typedef EnvElementSet::iterator        EnvElementSetIter;
typedef EnvElementSet::const_iterator  EnvElementSetIterC;

typedef std::vector<std::string>       EnvpList;
typedef EnvpList::iterator             EnvpListIter;
typedef EnvpList::const_iterator       EnvpListIterC;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string::size_type
	GetEnvStringSeparatorIndex(const std::string &env_string);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__EnvElement_hpp__HH

