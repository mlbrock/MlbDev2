// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  GetCmdLineArg.cpp

   File Description  :  Implementation of command line argument retrieval
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

#include <Utility/GetCmdLineArg.hpp>

#include <Utility/StrICmp.hpp>

#include <cstring>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
int GetCmdLineArgIdx(const char *target_arg, int argc, char **argv,
	bool case_sensitive, int first_index)
{
	int (*cmp_func)(const char *, const char *) =
		(case_sensitive) ? ::strcmp : Utility_stricmp;

	for (int arg_index = first_index; arg_index < argc; ++arg_index) {
		if (!(*cmp_func)(target_arg, argv[arg_index]))
			return(arg_index);
	}

	return(-1);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const char *GetCmdLineArgPtr(const char *target_arg, int argc, char **argv,
	bool case_sensitive, int first_index)
{
	int arg_index =
		GetCmdLineArgIdx(target_arg, argc, argv, case_sensitive, first_index);

	return((arg_index < 0) ? nullptr : argv[arg_index]);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const char *HasCmdLineArg(const char *target_arg, int argc, char **argv,
	bool case_sensitive, int first_index)
{
	return(GetCmdLineArgPtr(target_arg, argc, argv, case_sensitive,
		first_index));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

