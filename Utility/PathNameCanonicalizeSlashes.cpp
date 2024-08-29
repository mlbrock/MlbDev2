// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  PathNameCanonicalizeSlashes.cpp

   File Description  :  Canonicalize paths support.

   Revision History  :  1996-01-02 --- Canonicalize logic genfuncs/expfpath.c.
                           Michael L. Brock
                        1998-04-08 --- Modified for use with C++.
                           Michael L. Brock
                        2024-08-04 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1996 - 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/PathNameCanonicalizeSlashes.hpp>

#include <Utility/CurrentPath.hpp>
#include <Utility/PathNameSlash.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::string CanonicalizePathNameSlashes(const std::string &path_name_in)
{
	char datum[MaxPathNameLength + 1 + 1];
	
	return(CanonicalizePathNameSlashes(path_name_in.c_str(), datum));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *CanonicalizePathNameSlashes(const char *path_name_in, char *path_name_out)
{
	const char *tmp_ptr_i = path_name_in;
	char       *tmp_ptr_o = path_name_out;

	while (*tmp_ptr_i) {
		if (!IsPathNameSlash(*tmp_ptr_i))
			*tmp_ptr_o++ = *tmp_ptr_i++;
		else {
			*tmp_ptr_o++ = GetPathNameSlashCanonical();
			++tmp_ptr_i;
#if _Windows
			// Need to keep '\\' to support '\\<computer-name>\<path-name>'...
			while (*tmp_ptr_i && IsPathNameSlash(*tmp_ptr_i) &&
				(static_cast<unsigned int>(tmp_ptr_i - path_name_in) > 1))
#else
			while (*tmp_ptr_i && IsPathNameSlash(*tmp_ptr_i))
#endif // _Windows
				++tmp_ptr_i;
		}
	}

	*tmp_ptr_o = '\0';

	return(path_name_out);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#ifdef TEST_MAIN

#include <Utility/CurrentPath.hpp>
#include <Utility/PathNameGetDirectory.hpp>
#include <Utility/PathNameGetExtension.hpp>
#include <Utility/PathNameGetFileName.hpp>

#include <iostream>

namespace {

// ////////////////////////////////////////////////////////////////////////////
void TEST_CanonicalizePathNameSlashes(const std::string &path_name)
{
	using namespace MLB::Utility;

	std::string path_canon(CanonicalizePathNameSlashes(path_name));

	std::cout << "Path Source   : " << path_name                      << '\n';
	std::cout << "Path Canonical: " << path_canon                     << '\n';
	std::cout << "Path Directory: " << GetDirNamePortion(path_canon)  << '\n';
	std::cout << "Path Base Name: " << GetFileNamePortion(path_canon) << '\n';
	std::cout << "Path Extension: " << GetExtension(path_canon)       << '\n';
	std::cout << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int return_code = EXIT_SUCCESS;

	using namespace MLB::Utility;

	try {
		if (argc > 1) {
			for (int arg_idx = 1; arg_idx < argc; ++arg_idx)
				TEST_CanonicalizePathNameSlashes(argv[arg_idx]);
		}
		else
			TEST_CanonicalizePathNameSlashes(GetCurrentPath() + "/");
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

