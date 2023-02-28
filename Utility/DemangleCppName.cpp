// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  DemangleCppName.cpp

   File Description  :  Implementation of the C++ demangle functions.

   Revision History  :  2015-07-20 --- Original logic implemented in file
                                       MlbDev/Utility/BackTrace.cpp.
                           Michael L. Brock
                        2016-08-07 --- Separated implementation into file
                                       MlbDev/Utility/DemangleCppName.cpp.
                           Michael L. Brock
                        2023-01-13 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 2015 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/DemangleCppName.hpp>

#ifdef __linux__
# include <execinfo.h>
# include <cxxabi.h>
# include <memory>
#endif // #ifdef __linux__

#include <cstring>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
std::string DemangleCppName(const char *src)
{
#ifdef __linux__
	int                   status_code;
	std::unique_ptr<char> final_name(
		abi::__cxa_demangle(src, NULL, NULL, &status_code));

	return((!status_code) ? std::string(final_name.get()) : src);
#else
	return(src);
#endif // #ifdef __linux__
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string DemangleCppName(const std::string &src)
{
	return(DemangleCppName(src.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string DemangleTypeInfoName(const char *src)
{
	return(DemangleCppName(src));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string DemangleTypeInfoName(const std::string &src)
{
	return(DemangleTypeInfoName(src.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

namespace {

// ////////////////////////////////////////////////////////////////////////////
std::string DemangledCppNameToBasic_Helper(const char *src)
{
	std::string work_buffer(src);

	if (work_buffer.empty())
		return(work_buffer);

	char *tmp_src = const_cast<char *>(work_buffer.c_str());
	char *end_ptr = tmp_src + work_buffer.size();

	if (end_ptr[-1] == '>') {
		--end_ptr;
		std::size_t nesting_depth = 0;
		while (end_ptr > tmp_src) {
			if (*end_ptr == '>')
				++nesting_depth;
			else if (*end_ptr == '<')
				--nesting_depth;
			if (!nesting_depth)
				break;
			--end_ptr;
		}
		if (nesting_depth)
			return(tmp_src);
		*end_ptr = '\0';
	}

	char *colon_ptr = ::strrchr(tmp_src, ':');
	char *space_ptr = ::strrchr(tmp_src, ' ');
	char *max_ptr   = (std::max)(colon_ptr, space_ptr);

	return(std::string((max_ptr) ? (max_ptr + 1) : tmp_src, end_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
std::string DemangledCppNameToBasic(const char *src)
{
	return(DemangledCppNameToBasic_Helper(src));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string DemangledCppNameToBasic(const std::string &src)
{
	return(DemangledCppNameToBasic(src.c_str()));
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

#include <Utility/EmitterSep.hpp>

#include <iostream>
#include <set>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType> void TEST_SingleType()
{
	using namespace MLB::Utility;

	std::cout << EmitterSep('=');
	std::cout << "Size          : " << sizeof(DatumType) << '\n';
	std::string typeid_name(typeid(DatumType).name());
	std::cout << "TypeId Name   : " << typeid_name << '\n';
	std::string demangled_name(DemangleCppName(typeid_name));
	std::cout << "Demangled Name: " << demangled_name << '\n';
	std::string basic_name(DemangledCppNameToBasic(demangled_name));
	std::cout << "Basic Name    : " << basic_name << '\n';
	std::cout << EmitterSep('=') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DatumType> void TEST_SingleType(const DatumType &datum)
{
	using namespace MLB::Utility;

	std::cout << EmitterSep('=');
	std::cout << "Size          : " << sizeof(datum) << '\n';
	std::string typeid_name(typeid(datum).name());
	std::cout << "TypeId Name   : " << typeid_name << '\n';
	std::string demangled_name(DemangleCppName(typeid_name));
	std::cout << "Demangled Name: " << demangled_name << '\n';
	std::string basic_name(DemangledCppNameToBasic(demangled_name));
	std::cout << "Basic Name    : " << basic_name << '\n';
	std::cout << EmitterSep('=') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

//namespace {

// ////////////////////////////////////////////////////////////////////////////
struct MyStruct {
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class MyClass {
public:
	struct MyStructInner {
	};

	MyStructInner GetAStringInner_Instanced(int /* value */ = 666) const &&
	{
		return(MyStructInner());
	}

	static MyStructInner GetAStringInner_FreeStanding(int /* value */ = 666)
	{
		return(MyStructInner());
	}
};
// ////////////////////////////////////////////////////////////////////////////

//} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main();
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_MultipleTypes()
{
	TEST_SingleType<int>();
	TEST_SingleType<double>();
	TEST_SingleType<std::string>();
	TEST_SingleType<std::ostream>();
	TEST_SingleType<std::set<std::string> >();
	TEST_SingleType<std::vector<std::string> >();
	TEST_SingleType<std::vector<std::set<std::string> > >();

	TEST_SingleType<>(&main);
	TEST_SingleType<>(&MyClass::GetAStringInner_Instanced);
	TEST_SingleType<>(&MyClass::GetAStringInner_FreeStanding);
	TEST_SingleType<MyStruct>();
	TEST_SingleType<MyClass>();
	TEST_SingleType<MyClass::MyStructInner>();
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		TEST_MultipleTypes();
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

