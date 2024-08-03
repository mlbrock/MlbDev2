// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ParseCfgFile.cpp

   File Description  :  Configuration file parsing implementation.
 
   Revision History  :  2023-03-03 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Include necessary header files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/ParseCfgFile.hpp>

#include <iostream>
#include <iomanip>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
bool GetParseCfgLineComponents(const std::string &src_line,
	std::string &dst_name, std::string &dst_value)
{
	const char *line_ptr = src_line.c_str();

	while (*line_ptr && ::isspace(*line_ptr))
		++line_ptr;

	if ((!(*line_ptr)) || (*line_ptr == '#'))
		return(false);

	const char *equal_ptr = ::strchr(line_ptr, '=');

	if (equal_ptr == line_ptr)
		throw std::invalid_argument("Configuration line does not "
			"have a name before the '=' separator between name and value.");

	dst_name  = Trim(std::string(line_ptr, equal_ptr));
	dst_value = Trim(std::string(equal_ptr + 1));

	return(true);
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
#include <Utility/StringPadRight.hpp>
#include <Utility/XLateToHuman.hpp>

namespace {

// ////////////////////////////////////////////////////////////////////////////
struct TestClass_1
{
	using MyParseCfgItemFunc     = MLB::Utility::ParseCfgItemFunc<TestClass_1>;
	using MyParseCfgItemMap	     = MLB::Utility::ParseCfgItemMapI<TestClass_1>;
	using MyParseCfgItemMapIterC = MyParseCfgItemMap::const_iterator;

	void TestItem(const std::string &item_name, const std::string &item_value)
	{
		const MyParseCfgItemMap &item_map(GetItemMap());

		MyParseCfgItemMapIterC
			iter_f(item_map.find(item_name));

		if (iter_f != item_map.end()) {
			iter_f->second(*this, item_value);
		}
		else
			std::cout << "Item '" << item_name << "' not found.\n";
	}

	static const MyParseCfgItemMap& GetItemMap()
	{
		using namespace MLB::Utility;

		static const MyParseCfgItemMap item_map =
		{
			 DEF_CfgItem(TestClass_1, datum_bool_)
			,DEF_CfgItem(TestClass_1, datum_sint_)
			,DEF_CfgItem(TestClass_1, datum_string_)
		};

		return (item_map);
	}

	bool        datum_bool_	  = false;
	int         datum_sint_   = 42;
	std::string datum_string_ = "*EMPTY*"; 
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ShowValues(const TestClass_1 &datum, const std::string &info)
{
	std::cout << info << ":datum_bool_  =[" <<
		MLB::Utility::XLateToHuman(datum.datum_bool_) << "]\n";
	std::cout << info << ":datum_sint_  =[" <<
		MLB::Utility::XLateToHuman(datum.datum_sint_) << "]\n";
	std::cout << info << ":datum_string_=[" <<
		MLB::Utility::XLateToHuman(datum.datum_string_) << "]\n";
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_TestClass_1()
{
	using namespace MLB::Utility;

	TestClass_1 my_test;

	std::cout << EmitterSep('=');

	ShowValues(my_test, "001");
	std::cout << EmitterSep('-');

	my_test.TestItem("datum_bool_", "YES");
	my_test.TestItem("datum_sint_", "11111");
	my_test.TestItem("datum_string_", "Test string #1");
	ShowValues(my_test, "002");
	std::cout << EmitterSep('-');

	my_test.TestItem("datum_bool_", "NO");
	my_test.TestItem("datum_sint_", "22222");
	my_test.TestItem("datum_string_", "Test string #2");
	ShowValues(my_test, "003");
	std::cout << EmitterSep('-');

	my_test.TestItem("datum_bool_", "ON");
	my_test.TestItem("datum_sint_", "33333");
	my_test.TestItem("datum_string_", "Test string #3");
	ShowValues(my_test, "004");

	std::cout << EmitterSep('=') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
struct TestClass_2
{
	using MyParseCfgItemFunc = MLB::Utility::ParseCfgItemFunc<TestClass_2>;
	using MyParseCfgItemMap	 = MLB::Utility::ParseCfgItemMapI<TestClass_2>;

	TestClass_2()
		:ActiveFlag(false)
		,MinimumValue(0)
		,MaximumValue(100)
		,DirectoryName("./")
		,BigSInt(-1)
		,BigUInt(1)
		,PriceAmount(0.789)
		,UserName()
		,Password()
	{
	}

	TestClass_2(const std::vector<std::string> &cfg_list)
		:TestClass_2()
	{
		MLB::Utility::ParseCfgLines(*this, GetItemMap(), cfg_list);
	}

	TestClass_2(const std::string &cfg_file_name)
		:TestClass_2()
	{
		MLB::Utility::ParseCfgFile(*this, GetItemMap(), cfg_file_name);
	}

	void EmitMemberValues(std::ostream &o_str = std::cout) const
	{
		using namespace MLB::Utility;

		o_str << PadRight("ActiveFlag",    15) << ": " <<
			XLateToHuman(ActiveFlag)    << '\n';
		o_str << PadRight("MinimumValue",  15) << ": " <<
			XLateToHuman(MinimumValue)  << '\n';
		o_str << PadRight("MaximumValue",  15) << ": " <<
			XLateToHuman(MaximumValue)  << '\n';
		o_str << PadRight("DirectoryName", 15) << ": " <<
			XLateToHuman(DirectoryName) << '\n';
		o_str << PadRight("BigSInt",       15) << ": " <<
			XLateToHuman(BigSInt)       << '\n';
		o_str << PadRight("BigUInt",       15) << ": " <<
			XLateToHuman(BigUInt)       << '\n';
		o_str << PadRight("PriceAmount",   15) << ": " <<
			XLateToHuman(PriceAmount)   << '\n';
		o_str << PadRight("UserName",      15) << ": " <<
			XLateToHuman(UserName)      << '\n';
		o_str << PadRight("Password",      15) << ": " <<
			XLateToHuman(Password)      << '\n';
	}

	static const MyParseCfgItemMap &GetItemMap()
	{
		using namespace MLB::Utility;

		static const MyParseCfgItemMap item_map =
		{
			 DEF_CfgItem(TestClass_2, ActiveFlag)
			,DEF_CfgItem(TestClass_2, MinimumValue)
			,DEF_CfgItem(TestClass_2, MaximumValue)
			,DEF_CfgItem(TestClass_2, DirectoryName)
			,DEF_CfgItem(TestClass_2, BigSInt)
			,DEF_CfgItem(TestClass_2, BigUInt)
			,DEF_CfgItem(TestClass_2, PriceAmount)
			,DEF_CfgItem(TestClass_2, UserName)
			,DEF_CfgItem(TestClass_2, Password)
		};

		return (item_map);
	}

	bool        ActiveFlag;
	int         MinimumValue;
	int         MaximumValue;
	std::string DirectoryName;
	int64_t     BigSInt;
	uint64_t    BigUInt;
	double      PriceAmount;
	std::string UserName;
	std::string Password;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const char        *TEST_TestClass_2_List[] =
{
	 "# ##### Here's a comment ..."
	,"ActiveFlag=YES"
	,"   MinimumValue       =-42"
	,""
	,"MaximumValuE=           42"
	,"DirectoryName=/usr/local"
	,"               "
	,"               # ##### Another comment"
	,"BigSInt=-9223372036854775808"
	,"BigUInt=18446744073709551616"
	,"PriceAmount=123.456"
	,"UserName=mlbrock"
	,"Password=password"
};
const std::size_t  TEST_TestClass_2_Count  =
	sizeof(TEST_TestClass_2_List) / sizeof(TEST_TestClass_2_List[0]);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_TestClass_2()
{
	using namespace MLB::Utility;

	std::cout << EmitterSep('=');
	TestClass_2().EmitMemberValues();

	TestClass_2 my_test(std::vector<std::string>(TEST_TestClass_2_List,
		TEST_TestClass_2_List + TEST_TestClass_2_Count));

	std::cout << EmitterSep('-');

	my_test.EmitMemberValues();
	std::cout << EmitterSep('=') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	try {
		TEST_TestClass_1();
		TEST_TestClass_2();
	}
	catch (const std::exception &except) {
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

