// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ParseCsv.hpp

   File Description  :  Include file for comma-separated-value parsing.

   Revision History  :  2024-12-28 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__ParseCsv_hpp__HH

#define HH__MLB__Utility__ParseCsv_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file ParseCsv.hpp

   \brief   The comma-separated-value parsing header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string>
#include <string_view>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
class ParseCsvControl
{
public:
	ParseCsvControl(const std::string &value_sep_list = ",",
		const std::string &line_sep_list = "\n", bool enable_crlf = true);

	inline bool IsLineSep(char in_char) const
	{
		return(in_char == '\n');
	}

	inline bool IsValueSep(char in_char) const
	{
		return(value_sep_list_.find_first_of(in_char, 0) != std::string::npos);
	}

	inline std::size_t GetNextSepIndex(const std::string_view &src_line,
		std::size_t current_offset = 0) const
	{
		return(src_line.find_first_of(value_sep_list_, current_offset));
	}

	std::size_t GetValueEnd(const std::string_view &src_line,
		std::size_t current_offset = 0) const;

private:
	std::string value_sep_list_;
	std::string line_sep_list_;
	bool        enable_crlf_;
	std::size_t max_nested_lines_;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
using ParseCsvColList = std::vector<std::string_view>;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class ParseCsvState
{
public:
	ParseCsvState(std::string_view src_line);
	ParseCsvState(const std::string &src_line);

	bool IsEnd() const
	{
		return(at_end_flag_);
	}

	ParseCsvColList &ParseCsvLine(ParseCsvColList &col_list,
		const ParseCsvControl &parse_control = ParseCsvControl());
	ParseCsvColList  ParseCsvLine(
		const ParseCsvControl &parse_control = ParseCsvControl());

	ParseCsvColList &ParseCsvLine_NEW(ParseCsvColList &col_list,
		const ParseCsvControl &parse_control = ParseCsvControl());
	ParseCsvColList  ParseCsvLine_NEW(
		const ParseCsvControl &parse_control = ParseCsvControl());

private:
	std::string_view src_line_;
	std::size_t      current_offset_;
	bool             at_end_flag_;
};
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__ParseCsv_hpp__HH

