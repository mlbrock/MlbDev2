// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  CheckCmdLineArgs.cpp

   File Description  :  Implementation of command line argument check
                        functions.

   Revision History  :  1998-04-08 --- Creation.
                           Michael L. Brock
                        2023-02-27 --- Migration to C++ MlbDev2/Utility.
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

#include <Utility/CheckCmdLineArgs.hpp>

#include <stdexcept>
#include <string>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
void CheckCmdLineArgList(int argc, char **argv)
{
	if (argc < 0)
		throw std::invalid_argument("Invalid argument count (" +
			std::to_string(argc) + ") --- the minimum is 0.");
	else if (argv == NULL)
		throw std::invalid_argument("Invalid argument list (NULL).");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void CheckCmdLineArgList(int argc, char **argv, int first_index)
{
	CheckCmdLineSource(first_index, argc, argv);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void CheckCmdLineSource(int current_index, int argc, char **argv)
{
	CheckCmdLineArgList(argc, argv);

	if (current_index < 0)
		throw std::invalid_argument("The specified argument list index " +
			std::to_string(current_index) + " is invalid --- minimum valid "
			"index is 0.");
	else if (current_index >= argc)
		throw std::invalid_argument("The specified argument list index " +
			std::to_string(current_index) + " is invalid --- the argument count "
			" is " + std::to_string(argc) + ".");
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

