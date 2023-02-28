// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	HostName.cpp

   File Description	:	Implementation of functions to get and set the
   							host name.

	Revision History	:	1998-04-08 --- Creation.
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
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/HostName.hpp>

#include <Utility/ThrowErrno.hpp>
#include <Utility/ThrowSystemError.hpp>

#include <cstring>

#ifdef __linux__
# include <unistd.h>
#endif // # ifdef __linux__

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::string GetHostName()
{
	char datum[MaxHostNameLength + 1];

	return(GetHostName(datum, sizeof(datum) - 1));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *GetHostName(char *host_name, std::size_t host_name_length)
{
#ifdef _Windows
	// Under Windows, the length must include space for the ASCII 0
	std::size_t out_host_name_length = host_name_length + 1;

	if (::GetComputerNameA(host_name,
		reinterpret_cast<LPDWORD>(&out_host_name_length)) == 0)
		ThrowSystemError("Invocation of 'GetComputerNameA()' failed");
#else
# ifndef __MSDOS__
	if (::gethostname(host_name, host_name_length) != 0)
		ThrowErrno("Invocation of 'gethostname()' failed");
# else
	if (host_name_length < ::strlen("MS-DOS-Machine"))
		throw std::exception("Unable to get the host name because the "
			"minimum length of the string is 14.");
	else
		::strcpy(host_name, "MS-DOS-Machine");
# endif // # ifndef __MSDOS__
#endif // #ifdef _Windows

	return(host_name);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string GetHostNameCanonical()
{
	return(ConvertHostNameToCanonical(GetHostName()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SetHostName(const std::string &host_name)
{
	SetHostName(host_name.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SetHostName(const char *host_name)
{
#ifdef _Windows
	if (::SetComputerNameA(host_name) == 0)
		ThrowSystemError("Invocation of 'SetComputerNameA()' failed");
#else
# ifndef __MSDOS__
	if (::sethostname(host_name, ::strlen(host_name)) != 0)
		ThrowErrno("Invocation of 'sethostname()' failed");
# endif // # ifndef __MSDOS__
#endif // #ifdef _Windows
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string ConvertHostNameToCanonical(const std::string &host_name)
{
	std::string            tmp_host_name = host_name;
	std::string::size_type dot_index     = tmp_host_name.find_first_of('.');

	if (dot_index != std::string::npos)
		tmp_host_name.erase(dot_index);

/*
	// CODE NOTE: MUST FIX ME!!!
	return(LowerCase(Trim(tmp_host_name)));
*/
	return(tmp_host_name);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#ifdef TEST_MAIN

#include <iostream>

using namespace MLB::Utility;

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		std::cout << "GetHostName(): " << GetHostName() << std::endl;
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

