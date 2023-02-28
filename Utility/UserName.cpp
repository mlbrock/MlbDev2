// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  UserName.cpp

   File Description  :  Implementation of the portable user name functions.

   Revision History  :  1998-04-08 --- Creation.
                           Michael L. Brock
                        2023-01-09 --- Migration to C++ MlbDev2/Utility.
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

#include <Utility/UserName.hpp>

#include <Utility/ThrowErrno.hpp>
#include <Utility/ThrowSystemError.hpp>

#include <cstring>
#include <stdexcept>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::string GetCurrentUserName()
{
	char datum[UserNameLength + 1];

	return(GetCurrentUserName(datum, sizeof(datum) - 1));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *GetCurrentUserName(char *user_name, std::size_t user_name_length)
{
#ifdef __MSDOS__
	if (user_name_length < ::strlen("MSDOS"))
	  throw std::invalid_argument("Unable to get user name because the length "
			"of the provided buffer (" + std::to_string(user_name_length) +
			") was less than that required (" +
			std::to_string(::strlen("MSDOS")) + ").");

	::strcpy(user_name, "MSDOS");
#elif _Windows
	// Under Windows, the length must include space for the ASCII 0
	std::size_t out_user_name_length = user_name_length + 1;

	if (::GetUserNameA(user_name,
		reinterpret_cast<LPDWORD>(&out_user_name_length)) == 0)
		ThrowSystemError("Invocation of 'GetUserName()' failed");
#else
# if _POSIX_PTHREAD_SEMANTICS
	struct passwd  pentry;
	struct passwd *pentry_ptr;
	char           buffer[2047 + 1];
	int            result_errno;

	if ((result_errno = ::getpwuid_r(getuid(), &pentry, buffer, sizeof(buffer),
		&pentry_ptr)) != 0)
		ThrowErrno(result_errno,
			"Invocation of 'getpwuid_r()' failed");
# else
	struct passwd *pentry_ptr;

	if ((pentry_ptr = ::getpwuid(getuid())) == NULL)
		ThrowErrno("Invocation of 'getpwuid()' failed");
# endif // # if _POSIX_PTHREAD_SEMANTICS
	if (pentry_ptr->pw_name == NULL)
		throw std::invalid_argument("Password entry member 'pw_name' is "
			"'NULL'.");

	std::size_t pw_name_length = ::strlen(pentry_ptr->pw_name);

	if (user_name_length < pw_name_length)
		throw std::invalid_argument("Unable to get user name because the length "
			 "of the provided buffer (" + std::to_string(user_name_length) +
			 ") was less than that required (" +
			 std::to_string(::strlen("MSDOS")) + ").");

	::strcpy(user_name, pentry_ptr->pw_name);
#endif // #ifdef __MSDOS__

	return(user_name);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#ifdef TEST_MAIN

#include <cstdlib>
#include <iostream>

using namespace MLB::Utility;

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		std::cout << "GetCurrentUserName(): " << GetCurrentUserName() <<
			std::endl;
	}
	catch (const std::exception &except) {
		std::cout << std::endl;
		std::cout << "Regression test error: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

