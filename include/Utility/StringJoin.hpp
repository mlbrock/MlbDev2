// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringJoin.hpp

   File Description  :  Function templates for join string functions.

   Revision History  :  1993-10-02 --- Creation.
                           Michael L. Brock
                        2023-01-12 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1998 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__StringJoin_hpp__HH

#define HH__MLB__Utility__StringJoin_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file    StringJoin.hpp

   \brief   The MLB Utility C++ xxx string functions header file.
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
template <typename ContainerType>
	std::string &JoinString(std::string &out_string,
		const ContainerType &container, const std::string separator_string = "")
{
	std::string                            tmp_string;
	typename ContainerType::const_iterator iter_b(container.begin());
	typename ContainerType::const_iterator iter_e(container.end());

	while (iter_b != iter_e) {
		tmp_string += *iter_b;
		++iter_b;
		if ((!separator_string.empty()) && (iter_b != iter_e))
			tmp_string += separator_string;
	}

	return(out_string.assign(tmp_string));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename ContainerType>
	std::string JoinString(const ContainerType &container,
		const std::string separator_string = "")
{
	std::string out_string;

	return(JoinString(out_string, container, separator_string.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__StringJoin_hpp__HH

