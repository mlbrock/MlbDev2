// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ParseLine.hpp

   File Description  :  Include file for line-feed terminated parsing.

   Revision History  :  2024-12-28 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__ParseLine_hpp__HH

#define HH__MLB__Utility__ParseLine_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file ParseLine.hpp

   \brief   The line-feed terminated parsing header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <string_view>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
class ParseLineState;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class ParseLineData
{
public:
	explicit ParseLineData(std::string_view line_data = std::string_view(),
		std::size_t line_index = 0, std::size_t line_offset = 0);
	         ParseLineData(std::string_view line_data,
		const ParseLineState &line_state);

	std::ostream &ToStream(std::ostream &o_str) const;
	std::ostream &ToStreamXLate(std::ostream &o_str) const;

	std::string_view line_data_;
	std::size_t      line_index_;
	std::size_t      line_offset_;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const ParseLineData &datum);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class ParseLineState
{
public:
	explicit ParseLineState(std::string_view src_data);
	explicit ParseLineState(const std::string &src_data);
	explicit ParseLineState(const char *src_data, std::size_t src_length);
	explicit ParseLineState(const char *src_data);

	/** Returns \e true if the entire source data has been parsed. */
	bool IsEnd() const;

	/** Returns the index of the last logical line parsed. */
	std::size_t GetLineIndex() const;
	/** Returns the source offset of the last logical line parsed. */
	std::size_t GetLineOffset() const;
	/** Returns the source offset of the next character to be parsed. */
	std::size_t GetCurrentOffset() const;

	/** Parses the next logical line and returns it. */
	std::string_view              ParseLineSingle();
	/** Parses all remaining lines into a vector. */
	std::vector<std::string_view> ParseLines();
	/** Parses all remaining lines and their location info into a vector. */
	std::vector<ParseLineData>    ParseLinesWithInfo();

private:
	std::string_view src_data_;
	std::size_t      line_index_;
	std::size_t      line_offset_;
	std::size_t      current_offset_;
	bool             at_end_flag_;
};
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__ParseLine_hpp__HH

