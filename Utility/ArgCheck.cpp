// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ArgCheck.cpp

   File Description  :  Test harness for the ArgCheck.hpp header.
 
                        Does not product an object file for the library.

   Revision History  :  2024-07-30 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Include necessary header files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/ArgCheck.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>

// ////////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

namespace {

// ////////////////////////////////////////////////////////////////////////////
#define MLB_ArgCheck_ShowCall(func_name, func_args)								\
	{																								\
		std::ostringstream o_str;															\
		o_str << #func_name << #func_args ;												\
		std::cout																				\
			<< std::left << std::setw(60) << o_str.str() << std::right << '='	\
			<< (func_name func_args) << '\n';											\
	}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_Run()
{
	using namespace MLB::Utility;

	try {
		const int   int_val       = 42;
		const int  *int_ptr_null  = NULL;
		const char *char_ptr      = "Something";
		const char *char_ptr_null = NULL;
		MLB_ArgCheck_ShowCall(IsNull, (&int_val))
		MLB_ArgCheck_ShowCall(IsNull, (int_ptr_null))
		MLB_ArgCheck_ShowCall(IsNull, (char_ptr))
		MLB_ArgCheck_ShowCall(IsNull, (char_ptr_null))

		MLB_ArgCheck_ShowCall(NullToString, (char_ptr, "*REPLACE*"))
		MLB_ArgCheck_ShowCall(NullToString, (char_ptr_null, "*REPLACE*"))
		MLB_ArgCheck_ShowCall(NullToString, ("A String", "*REPLACE*"))
		MLB_ArgCheck_ShowCall(NullToString, ("", "*REPLACE*"))

		MLB_ArgCheck_ShowCall(NullOrEmptyToString, (char_ptr, "*REPLACE*"))
		MLB_ArgCheck_ShowCall(NullOrEmptyToString, (char_ptr_null, "*REPLACE*"))
		MLB_ArgCheck_ShowCall(NullOrEmptyToString, ("A String", "*REPLACE*"))
		MLB_ArgCheck_ShowCall(NullOrEmptyToString, ("", "*REPLACE*"))
	}
	catch (const std::exception &except) {
		std::cerr << std::endl << std::endl << "ERROR: " << except.what() <<
			std::endl;
	}
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	std::cout << "Test routine for 'ArgCheck()'" << std::endl;
	std::cout << "---- ------- --- ------------" << std::endl << std::endl;

	try {
		TEST_Run();
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << std::endl << std::endl << "ERROR: " << except.what() <<
			std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

