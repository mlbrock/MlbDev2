// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ParseCsv.cpp

   File Description  :  Implementation of comma-separated-value parsing.
 
   Revision History  :  2024-12-28 --- Creation.
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

#include <Utility/ParseCsv.hpp>

#include <Utility/ArgCheck.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
ParseCsvControl::ParseCsvControl(const std::string &value_sep_list)
	:line_sep_list_("\n")
	,value_sep_list_(ThrowIfEmpty(value_sep_list,
		"The value separator character list"))
{
	if (value_sep_list_.find_first_of(line_sep_list_) != std::string::npos)
		throw std::invalid_argument("The specified value separator list "
			"contains at least one line separator character.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseCsvState::ParseCsvState(std::string_view src_line)
	:src_line_(src_line)
	,current_offset_(0)
	,at_end_flag_(false)
{
	ThrowIfNull(src_line_.data(), "Source data pointer");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseCsvState::ParseCsvState(const std::string &src_line)
	:ParseCsvState(std::string_view(src_line.data(), src_line.size()))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseCsvColList &ParseCsvState::ParseCsvLine(ParseCsvColList &col_list,
	const ParseCsvControl &parse_control)
{
	col_list.clear();

	if (IsEnd())
		return(col_list);

	while (current_offset_ <= src_line_.size()) {
		if (current_offset_ == src_line_.size()) {
			col_list.push_back(std::string_view());
			current_offset_ = src_line_.size();
			at_end_flag_    = true;
			break;
		}
		std::size_t end_idx =
			parse_control.GetNextSepIndex(src_line_, current_offset_);
		if (end_idx != std::string::npos) {
			col_list.emplace_back(src_line_.data() + current_offset_,
				end_idx - current_offset_);
			current_offset_ = end_idx + 1;
		}
		else {
			col_list.emplace_back(src_line_.data() + current_offset_,
				src_line_.size() - current_offset_);
			current_offset_ = src_line_.size();
			at_end_flag_    = true;
			break;
		}
	}

	return(col_list);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseCsvColList ParseCsvState::ParseCsvLine(
	const ParseCsvControl &parse_control)
{
	ParseCsvColList col_list;

	return(ParseCsvLine(col_list, parse_control));
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
#include <iomanip>

namespace {

// ////////////////////////////////////////////////////////////////////////////
const std::vector<std::string> TEST_TestList =
{
	"A,B,C",
	"",
	",",
	",,",
	",,A",
	",,A,B",
	",,A,B,,,",
	",,A,B,,,C"
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_RunTest()
{
	using namespace MLB::Utility;

	ParseCsvColList col_list;

	for (const std::string &this_element : TEST_TestList) {
		std::cout <<
			EmitterSep((&this_element == &TEST_TestList.front()) ? '=' : '-');
		std::cout << "INPUT   : [" << this_element << "]" << std::endl;
		ParseCsvState csv_state(this_element);
		std::size_t   col_index = 0;
		csv_state.ParseCsvLine(col_list);
		for (const auto &this_col : col_list)
			std::cout << "   " << std::setw(5) << col_index++
				<< ": [" << this_col << "]\n";
	}

	std::cout << EmitterSep('=') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	try {
		TEST_RunTest();
	}
	catch (const std::exception &except) {
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

