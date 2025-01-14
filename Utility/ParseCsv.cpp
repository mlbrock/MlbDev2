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
ParseCsvControl::ParseCsvControl(const std::string &value_sep_list,
	const std::string &line_sep_list, bool enable_crlf)
	:value_sep_list_(ThrowIfEmpty(value_sep_list,
		"The CSV parser value separator character list"))
	,line_sep_list_("\n")
	,enable_crlf_(enable_crlf)
	,max_nested_lines_(0)
{
	if (value_sep_list_.empty())
		throw std::invalid_argument("The specified value separator list "
			"is empty.");

	if (value_sep_list_.find_first_of(line_sep_list_) != std::string::npos)
		throw std::invalid_argument("The specified value separator list "
			"contains at least one line separator character.");

	if (line_sep_list_.empty())
		throw std::invalid_argument("The specified line separator list "
			"is empty.");

	if (line_sep_list_.find_first_of(value_sep_list_) != std::string::npos)
		throw std::invalid_argument("The specified line separator list "
			"contains at least one value separator character.");

	if (enable_crlf && (line_sep_list_.find('\n') == std::string::npos))
		throw std::invalid_argument("The specified line separator list "
			"does not contain a line-feed character, but the enable CRLF flag "
			"is set to 'true'.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::size_t ParseCsvControl::GetValueEnd(const std::string_view &src_line,
	std::size_t current_offset) const
{
	if (current_offset >= src_line.size())
		throw std::invalid_argument("Invocation of ParseCsvState::GetValueEnd()"
			" with a source datum length of " + std::to_string(src_line.size()) +
			" and a current offset of " + std::to_string(current_offset) + ".");

//	if (++current_offset == src_line.size())
//		return(current_offset - 1);

	std::size_t start_offset = current_offset;
	std::size_t last_offset  = src_line.size() - 1;

	while (current_offset <= last_offset) {
		char this_char = src_line[current_offset];
		if ((this_char == '"') || (this_char == '\'')) {
			char        quote_char   = this_char;
			bool        in_quote     = true;
			std::size_t quote_offset = current_offset;
			while (++current_offset <= last_offset) {
				this_char = src_line[current_offset];
				if (this_char == quote_char) {
					// Is this a quoted by doubling ('' or "") quote char?
					if ((current_offset - 1) == quote_offset) {
						in_quote = false;
						break;
					}
					if ((current_offset < last_offset) &&
						 (src_line[current_offset - 1] == quote_char))
						++current_offset;
					else {
						// If not, it's the end of the quote.
						in_quote = false;
						if (current_offset == last_offset)
							return(current_offset);
						break;
					}
				}
			}
			if (in_quote)
				throw std::invalid_argument("Unterminated quote character: "
					"opening of quote was at index " +
					std::to_string(quote_offset) + ".");
			++current_offset;
		}
		else if (IsValueSep(this_char)) {
			return(current_offset);
		}
		else if (IsLineSep(this_char))
			return(current_offset);
		else
			++current_offset;
	}

	return(current_offset);
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

// ////////////////////////////////////////////////////////////////////////////
ParseCsvColList &ParseCsvState::ParseCsvLine_NEW(ParseCsvColList &col_list,
	const ParseCsvControl &parse_control)
{
	col_list.clear();

	if (IsEnd())
		return(col_list);

	while (current_offset_ <= src_line_.size()) {
		if (current_offset_ == src_line_.size()) {
			col_list.push_back(std::string_view());
			at_end_flag_ = true;
			break;
		}
		std::size_t start_idx = current_offset_;
		std::size_t end_idx   =
			parse_control.GetValueEnd(src_line_, current_offset_);
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
ParseCsvColList ParseCsvState::ParseCsvLine_NEW(
	const ParseCsvControl &parse_control)
{
	ParseCsvColList col_list;

	return(ParseCsvLine_NEW(col_list, parse_control));
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
#include <Utility/XLateEscapeChars.hpp>

#include <iostream>
#include <iomanip>

namespace {

// ////////////////////////////////////////////////////////////////////////////
const std::vector<std::string> TEST_TestList =
{
//"A\"\"B",
//"A\"\"\"\"B",
"A\nB",
"A'\n'B",
"A,,',,\n,,',,B",
"A,'B','C,,'',,D',E",
	"A,B,C,,",
	"",
	",",
	",,",
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

// ////////////////////////////////////////////////////////////////////////////
void TEST_RunTest_NEW()
{
	using namespace MLB::Utility;

	ParseCsvColList col_list;

	for (const std::string &this_element : TEST_TestList) {
		std::cout <<
			EmitterSep((&this_element == &TEST_TestList.front()) ? '=' : '-');
		std::cout << "INPUT   : [" << XLateEscapeChars(this_element)
			<< "]" << std::endl;
		ParseCsvState csv_state(this_element);
		std::size_t   col_index = 0;
		csv_state.ParseCsvLine_NEW(col_list);
		for (const auto &this_col : col_list)
			std::cout << "   " << std::setw(5) << col_index++
				<< ": [" << XLateEscapeChars(this_col) << "]\n";
	}

	std::cout << EmitterSep('=') << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	try {
		TEST_RunTest_NEW();
	}
	catch (const std::exception &except) {
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

