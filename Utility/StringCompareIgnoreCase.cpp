// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  StringCompareIgnoreCase.cpp

   File Description  :  Implementation of case-insensitive string comparison
                        functions.

   Revision History  :  1993-10-02 --- Creation.
                           Michael L. Brock
                        2023-01-12 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1993 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/StringCompareIgnoreCase.hpp>

#include <Utility/MemICmp.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
int StringCompareIgnoreCase(const std::string &lhs, const std::string &rhs)
{
	int cmp = MemICmp(lhs.c_str(), rhs.c_str(),
		(std::min)(lhs.size(), rhs.size()));

	return((cmp) ? cmp : ((lhs.size() < rhs.size()) ? -1 :
								((lhs.size() > rhs.size()) ? 1 : 0)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// IMPL NOTE: For name compatibility with the old MlbDef/Utility
int CompareStringIgnoreCase(const std::string &lhs, const std::string &rhs)
{
	return(StringCompareIgnoreCase(lhs, rhs));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

