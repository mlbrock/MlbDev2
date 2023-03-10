// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ThrowErrno.cpp

   File Description  :  Support for throwing errno-related exceptions.

   Revision History  :  1998-04-08 --- Implementation in MlbDev/Utility in
                                       file Utility/SystemError.cpp.
                           Michael L. Brock
                        2023-02-22 --- Migration to C++ MlbDev2/Utility.
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

#include <Utility/ThrowErrno.hpp>

#include <Utility/ToStringErrno.hpp>

#include <system_error>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrno(int err_code, const std::string &err_text)
{
	ThrowErrno(err_code, err_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrno(int err_code, const char *err_text)
{
	throw std::system_error(std::error_code(err_code, std::generic_category()),
		ToStringErrno(err_code, err_text, false));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrno(const std::string &err_text)
{
	ThrowErrno(err_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrno(const char *err_text)
{
	ThrowErrno(errno, err_text);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

#include <iostream>

// ////////////////////////////////////////////////////////////////////////////
void TEST_Run()
{
	using namespace MLB::Utility;

	for (int err_code = 0; err_code < 200; ++err_code) {
		const char  *err_text = "Test me";
		std::string  msg_error(ToStringErrno(err_code, err_text, true));
		std::cout << "STRING: [" << msg_error << "] ..." << std::flush;
		try {
			ThrowErrno(err_code, "Test me");
		}
		catch (const std::exception &except) {
			std::string  msg_except(except.what());
			if (msg_except == msg_error)
				std::cout << " MATCHES";
			else
				std::cout << " DIFFERS\n" << "        [" << except.what() << ']';
		}
		std::cout << std::endl;
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		TEST_Run();
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

