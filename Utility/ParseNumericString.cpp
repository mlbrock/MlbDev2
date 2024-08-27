// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ParseNumericString.cpp

   File Description  :  Test harness for the ParseNumericString.hpp header.
 
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

#define PARSE_NUMERIC_STRING_TEST

#include <Utility/ParseNumericString.hpp>

// ////////////////////////////////////////////////////////////////////////////

#ifdef PARSE_NUMERIC_STRING_TEST_COMPILE_TEST_SIMPLE
// ////////////////////////////////////////////////////////////////////////////
int main()
{
	using namespace MLB::Utility;

	int argv_value;

	MLB::Utility::ParseNumericString("12345", argv_value, true);

	return(0);
}
// ////////////////////////////////////////////////////////////////////////////
#else

#include <iomanip>
#include <iostream>

// ////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int return_code = EXIT_SUCCESS;

	std::cout << "Test routine for 'ParseNumericString()'" << std::endl;
	std::cout << "---- ------- --- ----------------------" <<
		std::endl << std::endl;

	using namespace MLB::Utility;

	try {
		if (argc > 1) {
			for (int count_1 = 1; count_1 < argc; ++count_1) {
				std::cout << "SRC=[" << std::setw(20) << argv[count_1] <<
					"]--->DST=[";
				const char *argv_ptr = argv[count_1];
				while (*argv_ptr && (::isspace(*argv_ptr) || (*argv_ptr != '-')))
					++argv_ptr;
				try {
					if (*argv_ptr == '-') {
						int64_t argv_value;
						ParseNumericString(argv[count_1], argv_value, true);
						std::cout << std::setw(20) << argv_value;
					}
					else {
						uint64_t argv_value;
						ParseNumericString(argv[count_1], argv_value, true);
						std::cout << std::setw(20) << argv_value;
					}
					std::cout << "]: PASSED";
				}
				catch (const std::exception &except) {
					std::cout << std::setw(20) << "" << "]: FAILED: " <<
						except.what();
				}
				std::cout << std::endl;
			}
		}
		else {
			TEST_WidestTypeInfo();
			std::cerr << '\n';
			TEST_ParseType();
			std::cerr << '\n';
		}
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

