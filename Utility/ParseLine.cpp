// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ParseLine.cpp

   File Description  :  Implementation of line-feed terminated parsing.
 
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

#include <Utility/ParseLine.hpp>

#include <Utility/ArgCheck.hpp>

#include <charconv>
#include <climits>
#include <cstring>
#include <ios>
#include <stdexcept>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
const std::string EscapeList_Raw("\0\a\b\n\f\r\t\v", 8);
const std::string EscapeList_Map("0abnfrtv");
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
#ifndef _MSC_VER
const std::string EscapeList_Raw_With_E("\0\a\b\n\f\r\t\v\e");
const std::string EscapeList_Map_With_E("0abnfrtve");
#endif // #ifndef _MSC_VER
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string XLateEscapeChars(const std::string_view &src,
	const std::string &chars_raw = EscapeList_Raw,
	const std::string &chars_map = EscapeList_Map);
std::string XLateEscapeChars(const std::string &src,
	const std::string &chars_raw = EscapeList_Raw,
	const std::string &chars_map = EscapeList_Map);
std::string XLateEscapeChars(const char *src, std::size_t src_length,
	const std::string &chars_raw = EscapeList_Raw,
	const std::string &chars_map = EscapeList_Map);
std::string XLateEscapeChars(const char *src,
	const std::string &chars_raw = EscapeList_Raw,
	const std::string &chars_map = EscapeList_Map);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string XLateEscapeChars(const std::string_view &src,
	const std::string &chars_raw, const std::string &chars_map)
{
	std::string dst;
	char        hex_buffer[(CHAR_BIT * sizeof(unsigned char)) + 1];

	if (!src.empty()) {
		for (const char &this_char : src) {
			if (::isprint(this_char))
				dst.push_back(this_char);
			else {
				std::size_t raw_idx = std::string::npos;
				if ((!chars_raw.empty()) && (!chars_map.empty())) {
					raw_idx = chars_raw.find(this_char);
					if (raw_idx != std::string::npos) {
						if (raw_idx < chars_map.size()) {
							dst += '\\';
							dst += chars_map[raw_idx];
						}
						else
							raw_idx = std::string::npos;
					}
				}
				if (raw_idx == std::string::npos) {
					uint32_t ascii_val          = static_cast<unsigned int>(
						static_cast<unsigned char>(this_char));
					std::to_chars_result result = std::to_chars(hex_buffer,
						hex_buffer + sizeof(hex_buffer) - 1, ascii_val, 16);
					if (result.ec != std::errc())
						throw std::invalid_argument(
							std::make_error_code(result.ec).message());
					*result.ptr  = '\0';
					dst         += "\\0x";
					dst         += hex_buffer;
				}
			}
		}
	}

	return(dst);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string XLateEscapeChars(const std::string &src,
	const std::string &chars_raw, const std::string &chars_map)
{
	return(XLateEscapeChars(std::string_view(src), chars_raw, chars_map));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string XLateEscapeChars(const char *src, std::size_t src_length,
	const std::string &chars_raw, const std::string &chars_map)
{
	return(XLateEscapeChars(std::string_view(src, src_length),
		chars_raw, chars_map));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string XLateEscapeChars(const char *src,
	const std::string &chars_raw, const std::string &chars_map)
{
	return(XLateEscapeChars(ThrowIfEmpty(src, "String source pointer"),
		(src) ? ::strlen(src) : 0, chars_raw, chars_map));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

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
std::string_view ParseLineState::ParseLineSingle()
{
	std::string_view dst;

	if (IsEnd())
		return(dst);

	if (current_offset_ >= src_data_.size()) {
		at_end_flag_ = true;
		return(dst);
	}

	std::size_t end_idx = src_data_.find('\n', current_offset_);

	if (end_idx != std::string::npos) {
		std::size_t next_idx = end_idx;
		if ((src_data_[end_idx] == '\n') && (end_idx > current_offset_) &&
			 (src_data_[end_idx - 1] == '\r'))
			--end_idx;
		std::string_view(src_data_.data() + current_offset_,
			end_idx - current_offset_).swap(dst);
		current_offset_ = next_idx + 1;
	}
	else {
		std::string_view(src_data_.data() + current_offset_,
			src_data_.size() - current_offset_).swap(dst);
		current_offset_ = src_data_.size();
		at_end_flag_    = true;
	}

	++line_index_;
	line_offset_ = current_offset_;

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

#include <iostream>
#include <iomanip>
#include <vector>

namespace {

// ////////////////////////////////////////////////////////////////////////////
const std::vector<std::string> TEST_TestList =
{
	"A,B,C\n"
	"\n"
	",\r\n"
	",,\n"
	",,A\n"
	",,A,B\n"
	",,A,\tB,,,\n"
	",,A,B,,,C"
	,
	"The quick brown fox\njumped over the lazy dog."
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_RunTest()
{
	using namespace MLB::Utility;

	for (const std::string &this_element : TEST_TestList) {
		std::cout << EmitterSep('=');
		std::cout << "INPUT   :\n" <<
			XLateEscapeChars(this_element) << std::endl;
		ParseLineState line_state(this_element);
		while (!line_state.IsEnd()) {
			std::cout << EmitterSep('-');
			std::size_t      line_index = line_state.GetLineIndex();
			std::string_view this_line(line_state.ParseLineSingle());
			std::cout << "   " << std::setw(5) << ++line_index
				<< ": [" << this_line << "]\n";
		}
		std::cout << EmitterSep('=') << std::endl;
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

