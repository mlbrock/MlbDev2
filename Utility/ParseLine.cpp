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
#include <Utility/XLateEscapeChars.hpp>

#include <algorithm>

#include <charconv>
#include <climits>
#include <cstring>
#include <iomanip>
#include <ios>
#include <stdexcept>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(std::string_view line_data,
	std::size_t line_index, std::size_t line_offset)
	:line_data_(line_data)
	,line_index_(line_index)
	,line_offset_(line_offset)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineData::ParseLineData(std::string_view line_data,
	const ParseLineState &line_state)
	:ParseLineData(line_data, line_state.GetLineIndex(),
		line_state.GetLineOffset())
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream &ParseLineData::ToStream(std::ostream &o_str) const
{
	o_str << std::setw(5) << line_index_ << '/' << std::setw(5) <<
		line_offset_ << ": [" << line_data_ << ']';

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream &ParseLineData::ToStreamXLate(std::ostream &o_str) const
{
	o_str << std::setw(5) << line_index_ << '/' << std::setw(5) <<
		line_offset_ << ": [" << XLateEscapeChars(line_data_) << ']';

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const ParseLineData &datum)
{
	return(datum.ToStreamXLate(o_str));
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
ParseLineState::ParseLineState(const char *src_ptr)
	:ParseLineState(ThrowIfNull(src_ptr, "Source data pointer"),
		(src_ptr) ? ::strlen(src_ptr) : 0)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
ParseLineState::ParseLineState(const char *src_ptr, std::size_t src_length)
	:ParseLineState(std::string_view(src_ptr, src_length))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool ParseLineState::IsEnd() const
{
	return(at_end_flag_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::size_t ParseLineState::GetLineIndex() const
{
	return(line_index_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::size_t ParseLineState::GetLineOffset() const
{
	return(line_offset_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::size_t ParseLineState::GetCurrentOffset() const
{
	return(current_offset_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::size_t ParseLineState::GetRemainingLines() const
{
	if (IsEnd() || (current_offset_ >= src_data_.size()))
		return(0);

	return(static_cast<std::size_t>(std::count(
		src_data_.cbegin() + static_cast<std::ptrdiff_t>(current_offset_),
		src_data_.cend(), '\n') + 1));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string_view ParseLineState::GetSourceData() const
{
	return(src_data_);
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

	if (current_offset_) {
		++line_index_;
		line_offset_ = current_offset_;
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

	return(dst);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::vector<std::string_view> ParseLineState::ParseLines()
{
	std::vector<std::string_view> dst;
	std::size_t                   remaining_lines = GetRemainingLines();

	if (remaining_lines) {
		dst.reserve(remaining_lines);
		while (!IsEnd())
			dst.emplace_back(ParseLineSingle());
	}

	return(dst);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::vector<ParseLineData> ParseLineState::ParseLinesWithInfo()
{
	std::vector<ParseLineData> dst;
	std::size_t                remaining_lines = GetRemainingLines();

	if (remaining_lines) {
		dst.reserve(remaining_lines);
		while (!IsEnd()) {
			std::string_view this_line(ParseLineSingle());
			dst.emplace_back(this_line, GetLineIndex(), GetLineOffset());
		}
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

#include <iostream>

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
		std::cout << "INPUT      : [" <<
			XLateEscapeChars(this_element) << ']' << std::endl;
		ParseLineState line_state(this_element.c_str());
		std::cout << "ELEMENTS   : " <<
			line_state.GetRemainingLines() << std::endl;
		while (!line_state.IsEnd()) {
			std::cout << EmitterSep('-');
			std::string_view this_line(line_state.ParseLineSingle());
			std::cout << std::setw(5) << line_state.GetLineIndex() << '/' <<
				std::setw(5) << line_state.GetLineOffset() << ": [" <<
				XLateEscapeChars(this_line) << "]\n";
		}
#if 0
		std::cout << EmitterSep('+');
		ParseLineState test_state(this_element.c_str());
		for (const auto &this_line : test_state.ParseLinesWithInfo())
			std::cout << this_line << '\n';
#endif // #if 0
		std::cout << EmitterSep('=') << std::endl;
	}
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		TEST_RunTest();
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return (return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

