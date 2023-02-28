// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	ReadFile.hpp

   File Description	:	Function prototypes of logic for the reading of
								operating system file contents.

	Revision History	:	1998-04-08 --- Creation
									Michael L. Brock
                        2023-01-05 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

		Copyright Michael L. Brock 1998 - 2023.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__ReadFile_hpp__HH

#define HH__MLB__Utility__ReadFile_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file ReadFile.hpp

	\brief	The page aize functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string              &ReadFileData(
	const std::string &file_name, std::string &file_data);
API_UTILITY std::string               ReadFileData(
	const std::string &file_name);
API_UTILITY std::vector<std::string> &ReadFileLines(
	const std::string &file_name, std::vector<std::string> &file_lines);
API_UTILITY std::vector<std::string>  ReadFileLines(
	const std::string &file_name);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__ReadFile_hpp__HH
