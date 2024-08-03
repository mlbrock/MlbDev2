// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ResolveCmdLineArg.cpp

   File Description  :  Implementation of regex-based command line argument
								retrieval functions.

   Revision History  :  2023-04-16 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/ResolveCmdLineArg.hpp>

#include <Utility/CheckCmdLineArgs.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
int ResolveCmdLineArg(const boost::regex &arg_regex, int argc,
	char **argv, int current_index, int min_added_args, int max_added_args)
{
	CheckCmdLineArgList(argc, argv, current_index);

	if (min_added_args < 0)
		throw std::invalid_argument("The minimum number of added arguments (" +
			std::to_string(min_added_args) + ") is invalid.");
	else if (max_added_args < 0)
		throw std::invalid_argument("The maximum number of added arguments (" +
			std::to_string(max_added_args) + ") is invalid.");
	else if (max_added_args < min_added_args)
		throw std::invalid_argument("The maximum number of added arguments (" +
			std::to_string(max_added_args) + ") is less than the minimum number "
			"of added arguments (" + std::to_string(min_added_args) + ").");

	int consumed_count = 0;

	try {
		if (boost::regex_search(argv[current_index], arg_regex)) {
			consumed_count = 1;
			int remaining_count = argc - current_index - 1;
			if (min_added_args > remaining_count)
				throw std::invalid_argument("The minimum number of added "
					"parameters (" + std::to_string(min_added_args) + ") is less "
					"than the number of parameters remaining (" +
					std::to_string(remaining_count) + ").");
			consumed_count += (max_added_args > min_added_args) ?
				std::min(max_added_args, remaining_count) : min_added_args;
		}
	}
	catch (const std::exception &except) {
		throw std::invalid_argument("An error occurred while matching "
			"parameter '" + std::string(argv[current_index]) + "' at index " +
			std::to_string(current_index) + ": " + std::string(except.what()));
	}

	return(consumed_count);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int ResolveCmdLineArg(const boost::regex &arg_regex, int argc,
	char **argv, int current_index, int min_added_args)
{
	return(ResolveCmdLineArg(arg_regex, argc, argv, current_index,
		min_added_args, min_added_args));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int ResolveCmdLineArg(const boost::regex &arg_regex, int argc,
	char **argv, int current_index)
{
	return(ResolveCmdLineArg(arg_regex, argc, argv, current_index, 0, 0));
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

#include <Utility/GetCmdLineArgRegex.hpp>
#include <Utility/StringJoin.hpp>

#include <iomanip>
#include <iostream>

namespace {

// ////////////////////////////////////////////////////////////////////////////
const char *TEST_ArgV[] =
{
	 "ProgramName"
	,"Param1"
	,"Param2"
	,"Param3"
	,"--Test"
	,"Param5"
	,"Param6"
	,"Param7"
};
const int   TEST_ArgC   = sizeof(TEST_ArgV) / sizeof(TEST_ArgV[0]);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_ResolveCmdLineArg(int argc, char **argv,
	const std::string &arg_pattern, const boost::regex &arg_regex)
{
	using namespace MLB::Utility;

	std::cout << "argc=" << argc << '\n';
	std::cout << "argv=" << JoinString(
		std::vector<std::string>(argv, argv + argc), " ") << '\n';

	int arg_idx;

	if ((arg_idx = GetCmdLineArgIdx(arg_regex, argc, argv)) < 0)
		throw std::runtime_error("INTERNAL ERROR: Parameter pattern '" +
			arg_pattern + "' was not located on the command line.");

	std::cout << "\nWill test parameter variations using pattern '" <<
		arg_pattern << "' ...\n\n";

	std::size_t unexpected_count = 0;
	int         args_left = argc - arg_idx - 1;

	for (int min_added = 0; min_added <= (args_left + 1); ++min_added) {
		for (int max_added = min_added; max_added <= (args_left + 1);
			++max_added) {
			bool expect_error = (min_added >= (args_left + 1));
			std::cout << " >>> arg_idx=" << std::setw(4) << arg_idx <<
				" / min_added=" << std::setw(4) << min_added <<
				" / max_added=" << std::setw(4) << max_added;
			int         used_count    = 0;
			bool        expected_flag = true;
			std::string result_string;
			try {
				used_count = ResolveCmdLineArg(arg_regex, argc, argv, arg_idx,
						min_added, max_added);
				expected_flag = !expect_error;
				result_string = "SUCCESS";
			}
			catch (const std::exception &except) {
				expected_flag = expect_error;
				result_string = std::string("FAILURE: ") +
					std::string(except.what());
			}
			std::cout << " / used_count=" << std::setw(4) << used_count <<
				": " << ((expected_flag) ? "  " : "UN") << "EXPECTED " <<
				result_string << std::endl;
			unexpected_count += (expected_flag) ? 0 : 1;
		}
	}

	std::cout << '\n';

	if (unexpected_count)
		throw std::runtime_error("Test failed --- there was/were " +
			std::to_string(unexpected_count) + " unexpected test results.");
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int return_code = EXIT_SUCCESS;

	try {
		int          arg_idx = -1;
		std::string  arg_pattern("-?-TEST");
		boost::regex arg_regex(arg_pattern,
			boost::regex_constants::perl | boost::regex_constants::icase);
		if ((argc > 1) &&
			 ((arg_idx = MLB::Utility::GetCmdLineArgIdx(
			arg_regex, argc, argv)) > -1))
			TEST_ResolveCmdLineArg(argc, argv, arg_pattern, arg_regex);
		else
			TEST_ResolveCmdLineArg(TEST_ArgC,
				const_cast<char **>(TEST_ArgV), arg_pattern, arg_regex);
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

