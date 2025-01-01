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

#include <iostream>
#include <iomanip>

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
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
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
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineState::ParseLineState(std::string_view src_data)
	:src_data_(src_data)
	,line_index_(0)
	,line_offset_(0)
	,current_offset_(0)
	,at_end_flag_(false)
{
	ThrowIfNull(src_data_.data(), "Source data pointer");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineState::ParseLineState(const std::string &src_data)
	:ParseLineState(std::string_view(src_data.data(), src_data.size()))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

/*
// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(const ParseCsvControl &parse_control,
	const std::string_view &src_data)
	:parse_control_(parse_control)
	,src_data_()
	,src_data_view_(src_data)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(const ParseCsvControl &parse_control,
	const std::string &src_data)
	:parse_control_(parse_control)
	,src_data_(src_data)
	,src_data_view_(src_data_)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(const ParseCsvControl &parse_control,
	std::string &&src_data)
	:parse_control_(parse_control)
	,src_data_(src_data)
	,src_data_view_(src_data_)
{
}
// ////////////////////////////////////////////////////////////////////////////

namespace {

// ////////////////////////////////////////////////////////////////////////////
const char *ResolveSrcDataPointer(const char *src_data)
{
	return(ThrowIfNull(src_data, "Source data pointer"));
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(const ParseCsvControl &parse_control,
	const char *src_data, std::size_t src_length)
	:ParseLineData(parse_control,
		std::string_view(ResolveSrcDataPointer(src_data), src_length))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(const ParseCsvControl &parse_control,
	const char *src_data)
	:ParseLineData(parse_control,
		ResolveSrcDataPointer(src_data), (src_data) ? ::strlen(src_data) : 0)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(const std::string &src_file,
	const ParseCsvControl &parse_control)
	:ParseLineData(parse_control, std::move(ReadFile(src_file)))
{
}
// ////////////////////////////////////////////////////////////////////////////
*/

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
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string_view ParseLineState::ParseLineSingle(
	const ParseCsvControl &parse_control)
{
	std::string_view dst;

	if (IsEnd())
		return(dst);

	if (current_offset_ >= src_data_.size()) {
		at_end_flag_ = true;
		return(dst);
	}

	std::size_t end_idx =
		parse_control.GetNextSepIndex(src_data_, current_offset_);

	if (end_idx != std::string::npos) {
		std::size_t next_idx = end_idx;
		if ((src_data_[end_idx] == '\n') && (end_idx > current_offset_) &&
			 (src_data_[end_idx - 1] == '\r'))
			--end_idx;
	}
	else {
		std::string_view(src_data_.data() + current_offset_,
			src_data_.size() - current_offset_).swap(dst);
		current_offset_ = src_data_.size();
		at_end_flag_    = true;
	}

	return(dst);
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

#include <charconv>
#include <climits>
#include <cstring>

namespace {

// ////////////////////////////////////////////////////////////////////////////
const char EscapeList_Ascii[]  = "\0\a\b\f\r\t\v";
const char EscapeList_Symbol[] = "0abfrtv";
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string XLateToEscape(const std::string &src)
{
	std::string dst;
	char        hex_buffer[(CHAR_BIT * sizeof(unsigned char)) + 1];

	if (!src.empty()) {
		for (const char &this_char : src) {
			if (::isprint(this_char))
				dst.push_back(this_char);
			else {
				const char *escaped_ptr = ::strchr(EscapeList_Ascii, this_char);
				if (escaped_ptr)
					dst += "\\" + EscapeList_Symbol[escaped_ptr - EscapeList_Ascii];
				else {
					uint32_t ascii_val          = static_cast<unsigned int>(
						static_cast<unsigned char>(this_char));
					std::to_chars_result result = std::to_chars(hex_buffer,
						hex_buffer + sizeof(hex_buffer) - 1, ascii_val, 16);
					if (result.ec != std::errc())
						throw std::invalid_argument(
							std::make_error_code(result.ec).message());
					*result.ptr  = '\0';
					dst         += "\\x";
					dst         += hex_buffer;
				}
			}
		}
	}

	return(dst);
}
// ////////////////////////////////////////////////////////////////////////////

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
		std::cout << "INPUT :[" << this_element << "]" << std::endl;
		ParseCsvState csv_state(this_element);
		std::size_t   col_index = 0;
		csv_state.ParseCsvLine(col_list);
		for (const auto &this_col : col_list)
			std::cout << "   " << std::setw(5) << col_index++
				<< ": [" << this_col << "]\n";
		std::cout << EmitterSep('-');
	}
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

