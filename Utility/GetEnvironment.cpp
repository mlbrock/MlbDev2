// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  GetEnvironment.cpp

   File Description  :  Implementation of logic to retrieve the environment.

   Revision History  :  1993-10-02 --- Creation
                           Michael L. Brock
                        2023-01-09 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1993 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/GetEnvironment.hpp>

#include <Utility/ExceptionRethrow.hpp>

#include <memory>
#include <sstream>

#ifndef _MSC_VER
# include <unistd.h>
#elif (_MSC_VER < 1900)
# include <Windows.h>
#else
# pragma warning(push)
# pragma warning(disable:5039)
# include <Windows.h>
# pragma warning(pop)
#endif // #ifndef _MSC_VER

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::string::size_type GetEnvStringSeparatorIndex(const std::string &env_string)
{
	std::string::size_type sep_position = env_string.find('=');

	if (sep_position == std::string::npos) {
		std::ostringstream error_text;
		error_text << "The environment string '" << env_string <<
			"' does not contain an equals sign.";
		throw std::invalid_argument(error_text.str());
	}

	if (sep_position == 0) {
		std::ostringstream error_text;
		error_text << "The environment string '" << env_string <<
			"' does not contain an environment variable name (that is, the "
			"equals sign is the first character of the string).";
		throw std::invalid_argument(error_text.str());
	}

	return(sep_position);
}
// ////////////////////////////////////////////////////////////////////////////

#ifdef _Windows

namespace {

// ////////////////////////////////////////////////////////////////////////////
std::string GetWinEnvironmentBuffer()
{
	std::string env_buffer;

#ifdef UNICODE

	std::shared_ptr<wchar_t> original_ptr(::GetEnvironmentStrings(),
		::FreeEnvironmentStrings);

	const wchar_t *begin_ptr = original_ptr.get();
	const wchar_t *end_ptr   = begin_ptr;

	while (*end_ptr != L'\0') {
		if (*++end_ptr == L'\0')
			end_ptr++;
	}

	int src_length = static_cast<int>(end_ptr - begin_ptr + 1);
	int dst_length = ::WideCharToMultiByte(CP_ACP, 0, begin_ptr,
		src_length, NULL, 0, NULL, NULL);

	if (dst_length < 1) {
		std::ostringstream error_text;
		error_text << "The wide character string can not be converted: The "
			"attempt to determine the ANSI equivalent length returned " <<
			dst_length << ".";
		throw std::logic_error(error_text.str());
	}

	std::string(static_cast<std::size_t>(dst_length), '\0').swap(env_buffer);

	if (!::WideCharToMultiByte(CP_ACP, 0, begin_ptr, src_length,
		const_cast<char *>(env_buffer.c_str()), dst_length, NULL, NULL ))
		throw std::logic_error("Attempt to convert a Unicode environment buffer "
			"failed.");

#else

	std::shared_ptr<char>  original_ptr(::GetEnvironmentStrings(),
		::FreeEnvironmentStrings);
	const char              *begin_ptr = original_ptr.get();
	const char              *curr_ptr  = begin_ptr;

	if (begin_ptr) {
		while (*curr_ptr)
			curr_ptr += ::strlen(curr_ptr) + 1;
		std::string(begin_ptr,
			static_cast<std::size_t>((curr_ptr - begin_ptr) + 1)).
			swap(env_buffer);
	}

#endif // #ifdef UNICODE

	return(env_buffer);
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

#endif // #ifdef _Windows

// ////////////////////////////////////////////////////////////////////////////
void GetEnvironment(EnvpList &env_list)
{
	EnvpList tmp_env_list;

#ifdef _Windows
	try {
		std::string  env_string(GetWinEnvironmentBuffer());
		const char  *env_strings_ptr = env_string.c_str();
		if (env_string.empty())
			throw std::runtime_error("Unable to get a pointer to the list of "
				"environment strings.");
		//	If returned pointer pointers to ASCII NUL, then no environment.
		if (*env_strings_ptr) {
			//	First few strings returned by GetEnvironmentStrings() are drive
			//	letter settings which are distinguished by beginning with an
			//	equals sign ('='). We skip over them...
			while (*env_strings_ptr && (*env_strings_ptr == '='))
				env_strings_ptr += ::strlen(env_strings_ptr) + 1;
			//	Now we can extract the environment strings...
			while (*env_strings_ptr) {
				tmp_env_list.push_back(env_strings_ptr);
				env_strings_ptr += ::strlen(env_strings_ptr) + 1;
			}
		}
	}
	catch (const std::exception &except) {
		Rethrow(except, "Unable to retrieve the Windows environment "
			"variables: " + std::string(except.what()));
	}
#else
	char **env_ptr = environ;

	if (env_ptr == NULL)
		throw std::runtime_error("Unable to get the list of environment "
			"strings.");

	while (*env_ptr != NULL)
		tmp_env_list.push_back(*env_ptr++);
#endif // #ifdef _Windows

	env_list.swap(tmp_env_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
EnvpList GetEnvironment()
{
	EnvpList env_list;

	GetEnvironment(env_list);

	return(env_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void CheckEnvironment(const EnvpList &envp_list)
{
	unsigned int             count_1 = 0;
	EnvpList::const_iterator iter_b(envp_list.begin());
	EnvpList::const_iterator iter_e(envp_list.end());

	while (iter_b != iter_e) {
		try {
			GetEnvStringSeparatorIndex(*iter_b);
		}
		catch (const std::exception &except) {
			std::ostringstream error_text;
			error_text << "The environment string at index " << count_1 <<
				" is invalid: " << except.what();
			Rethrow(except, error_text.str());
		}
		++iter_b;
		++count_1;
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void EnvpListToEnvElementList(const EnvpList &envp_list,
	EnvElementList &env_element_list)
{
	EnvElementList tmp_env_element_list;

	tmp_env_element_list.reserve(envp_list.size());

	EnvpList::const_iterator iter_b(envp_list.begin());
	EnvpList::const_iterator iter_e(envp_list.end());

	while (iter_b != iter_e) {
		tmp_env_element_list.push_back(EnvElement(*iter_b));
		++iter_b;
	}

	env_element_list.swap(tmp_env_element_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
EnvElementList EnvpListToEnvElementList(const EnvpList &envp_list)
{
	EnvElementList env_element_list;

	EnvpListToEnvElementList(envp_list, env_element_list);

	return(env_element_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void EnvElementListToEnvpList(const EnvElementList &env_element_list,
	EnvpList &envp_list)
{
	EnvpList tmp_envp_list;

	tmp_envp_list.reserve(env_element_list.size());

	EnvElementList::const_iterator iter_b(env_element_list.begin());
	EnvElementList::const_iterator iter_e(env_element_list.end());

	while (iter_b != iter_e) {
		tmp_envp_list.push_back(iter_b->env_name_ + "=" + iter_b->env_value_);
		++iter_b;
	}

	envp_list.swap(tmp_envp_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
EnvpList EnvElementListToEnvpList(const EnvElementList &env_element_list)
{
	EnvpList envp_list;

	EnvElementListToEnvpList(env_element_list, envp_list);

	return(envp_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void EnvpListToEnvElementSet(const EnvpList &envp_list,
	EnvElementSet &env_element_list)
{
	EnvElementSet tmp_env_element_list;

	EnvpList::const_iterator iter_b(envp_list.begin());
	EnvpList::const_iterator iter_e(envp_list.end());

	while (iter_b != iter_e) {
		tmp_env_element_list.insert(EnvElement(*iter_b));
		++iter_b;
	}

	env_element_list.swap(tmp_env_element_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
EnvElementSet EnvpListToEnvElementSet(const EnvpList &envp_list)
{
	EnvElementSet env_element_list;

	EnvpListToEnvElementSet(envp_list, env_element_list);

	return(env_element_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void EnvElementSetToEnvpList(const EnvElementSet &env_element_list,
	EnvpList &envp_list)
{
	EnvpList tmp_envp_list;

	tmp_envp_list.reserve(env_element_list.size());

	EnvElementSet::const_iterator iter_b(env_element_list.begin());
	EnvElementSet::const_iterator iter_e(env_element_list.end());

	while (iter_b != iter_e) {
		tmp_envp_list.push_back(iter_b->env_name_ + "=" + iter_b->env_value_);
		++iter_b;
	}

	envp_list.swap(tmp_envp_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
EnvpList EnvElementSetToEnvpList(const EnvElementSet &env_element_list)
{
	EnvpList envp_list;

	EnvElementSetToEnvpList(env_element_list, envp_list);

	return(envp_list);
}
// ////////////////////////////////////////////////////////////////////////////

namespace {

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	These won't be merged if 'merge_smart_flag' is 'true'...
// ////////////////////////////////////////////////////////////////////////////
const char         *EnvMergeExcludeSmartList[] = {
#ifdef _Windows
	"ALLUSERSPROFILE",
	"APPDATA",
	"CLASSPATH",
	"CommonProgramFiles",
	"COMPUTERNAME",
	"ComSpec",
	"HOMEDRIVE",
	"HOMEPATH",
	"LOGONSERVER",
	"NUMBER_OF_PROCESSORS",
	"OS",
	"PATHEXT",
	"PROCESSOR_ARCHITECTURE",
	"PROCESSOR_IDENTIFIER",
	"PROCESSOR_LEVEL",
	"PROCESSOR_REVISION",
	"ProgramFiles",
	"SystemDrive",
	"SystemRoot",
	"TEMP",
	"TMP",
	"USERDOMAIN",
	"USERNAME",
	"USERPROFILE",
	"windir"
#else
	"HOSTNAME",
	"TERM",
	"SHELL",
	"WINDOWID",
	"USER",
	"PWD",
	"HOME",
	"LOGNAME",
	"DISPLAY"
#endif // #ifdef _Windows
};
const unsigned int  EnvMergeExcludeSmartCount  =
	sizeof(EnvMergeExcludeSmartList) / sizeof(EnvMergeExcludeSmartList[0]);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	These will be intelligently combined if 'merge_path_flag' is 'true'...
// ////////////////////////////////////////////////////////////////////////////
const char         *EnvMergeExcludePathList[] = {
#ifdef _Windows
	"INCLUDE",
	"LIB",
	"Os2LibPath",
	"Path"
#else
	"MANPATH",
	"PATH"
#endif // #ifdef _Windows
};
const unsigned int  EnvMergeExcludePathCount  =
	sizeof(EnvMergeExcludePathList) / sizeof(EnvMergeExcludePathList[0]);
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
void MergeEnvironment(const EnvpList &base_env, const EnvpList &added_env,
	EnvpList &result_env, bool merge_smart_flag, bool merge_path_flag)
{
	//	CODE NOTE: To be implemented.
	if (merge_path_flag)
		throw std::invalid_argument("The 'merge_path_flag' to 'MLB::Utility::"
			"MergeEnvironment()' is not yet supported.");

	if (!merge_smart_flag) {
		EnvElementSet base_set;
		EnvpListToEnvElementSet(base_env, base_set);
		EnvpList::const_iterator iter_added_b(added_env.begin());
		EnvpList::const_iterator iter_added_e(added_env.end());
		while (iter_added_b != iter_added_e) {
			EnvElement tmp_added(*iter_added_b);
			if (base_set.find(tmp_added) == base_set.end())
				base_set.insert(tmp_added);
			++iter_added_b;
		}
		EnvElementSetToEnvpList(base_set, result_env);
	}
	else {
		EnvElementSet added_set;
		EnvpListToEnvElementSet(added_env, added_set);
		unsigned int count_1;
		if (!merge_path_flag) {
			for (count_1 = 0; count_1 < EnvMergeExcludePathCount; ++count_1) {
				EnvElementSetIter iter_f(added_set.find(
					EnvElement(EnvMergeExcludePathList[count_1], "")));
				if (iter_f != added_set.end())
					added_set.erase(iter_f);
			}
		}
		for (count_1 = 0; count_1 < EnvMergeExcludeSmartCount; ++count_1) {
			EnvElementSetIter iter_f(added_set.find(
				EnvElement(EnvMergeExcludeSmartList[count_1], "")));
			if (iter_f != added_set.end())
				added_set.erase(iter_f);
		}
		EnvpList tmp_added_env;
		EnvElementSetToEnvpList(added_set, tmp_added_env);
		MergeEnvironment(base_env, tmp_added_env, result_env, false,
			merge_path_flag);
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
EnvpList MergeEnvironment(const EnvpList &base_env, const EnvpList &added_env,
	bool merge_smart_flag, bool merge_path_flag)
{
	EnvpList envp_list;

	MergeEnvironment(base_env, added_env, envp_list, merge_smart_flag,
		merge_path_flag);

	return(envp_list);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#ifdef TEST_MAIN

#include <iostream>

#include <Utility/EmitterSep.hpp>
#include <Utility/AnyToString.hpp>

#include <cstdlib>
#include <iterator>

using namespace MLB::Utility;

// ////////////////////////////////////////////////////////////////////////////
const char         *TEST_BaseEnvList[] = {
	"SomeBaseEnv1=SomeValue1",
	"SomeBaseEnv2=SomeValue2",
	"path=/Base/Path1:/Base/Path2"
};
const unsigned int  TEST_BaseEnvCount  =
	sizeof(TEST_BaseEnvList) / sizeof(TEST_BaseEnvList[0]);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const char         *TEST_AddedEnvList[] = {
	"SomeAddedEnv1=SomeValue1",
	"SomeAddedEnv2=SomeValue2",
	"path=/Added/Path1:/Added/Path2"
};
const unsigned int  TEST_AddedEnvCount  =
	sizeof(TEST_AddedEnvList) / sizeof(TEST_AddedEnvList[0]);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_Populate(unsigned int src_count, const char **src_list,
	EnvpList &dst_list)
{
	unsigned int count_1;
	EnvpList tmp_list;

	for (count_1 = 0; count_1 < src_count; ++count_1)
		tmp_list.push_back(src_list[count_1]);

	dst_list.swap(tmp_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_RunTest(const EnvpList &base_env, const EnvpList &added_env,
	bool merge_smart_flag, bool merge_path_flag)
{
	std::cout << std::setfill('=') << std::setw(79) << "" <<
		std::setfill(' ') << std::endl;
	std::cout << std::setfill('=') << std::setw(79) << "" <<
		std::setfill(' ') << std::endl;
	std::cout << "Merge Smart Flag: " << AnyToString(merge_smart_flag) <<
		std::endl;
	std::cout << "Merge Path Flag : " << AnyToString(merge_path_flag) <<
		std::endl;
	std::cout << std::setfill('-') << std::setw(79) << "" <<
		std::setfill(' ') << std::endl;
	std::cout << "Base List:" << std::endl;
	std::cout << "---- ----:" << std::endl;
	std::copy(base_env.begin(), base_env.end(),
		std::ostream_iterator<EnvpList::value_type>(std::cout, "\n"));
	std::cout << std::setfill('-') << std::setw(79) << "" << std::endl;
	std::cout << "Added List:" << std::endl;
	std::cout << "----- ----:" << std::endl;
	std::copy(added_env.begin(), added_env.end(),
		std::ostream_iterator<EnvpList::value_type>(std::cout, "\n"));
	std::cout << std::setfill('=') << std::setw(79) << "" <<
		std::setfill(' ') << std::endl;

	EnvpList result_env;
	MergeEnvironment(base_env, added_env, result_env, merge_smart_flag,
		merge_path_flag);

	std::cout << std::setfill('-') << std::setw(79) << "" <<
		std::setfill(' ') << std::endl;
	std::cout << "Result List:" << std::endl;
	std::cout << "------ ----:" << std::endl;
	std::copy(result_env.begin(), result_env.end(),
		std::ostream_iterator<EnvpList::value_type>(std::cout, "\n"));
	std::cout << std::setfill('=') << std::setw(79) << "" <<
		std::setfill(' ') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_DumpEnv()
{
	std::cout << EmitterSep('=');
	std::cout << "Complete Environment:\n";
	std::cout << EmitterSep('-');

	EnvpList real_env(GetEnvironment());

	std::copy(real_env.begin(), real_env.end(),
		std::ostream_iterator<EnvpList::value_type>(std::cout, "\n"));

	std::cout << EmitterSep('=') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		EnvpList base_env;
		TEST_Populate(TEST_BaseEnvCount, TEST_BaseEnvList, base_env);
		EnvpList added_env;
		TEST_Populate(TEST_AddedEnvCount, TEST_AddedEnvList, added_env);
		TEST_RunTest(base_env, added_env, false, false);
		TEST_RunTest(base_env, added_env, true, false);
		TEST_DumpEnv();
	}
	catch (const std::exception &except) {
		std::cerr << std::endl << std::endl << "ERROR: " << except.what() <<
			std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

