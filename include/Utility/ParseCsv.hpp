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

#include <Utility/ReadFile.hpp>
#include <Utility/StringTrim.hpp>

#include <stdexcept>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
class ParseCsvControl
{
public:
	ParseCsvControl(const std::string &value_sep_list = ",");

	inline bool IsLineSep(char in_char) const
	{
		return(in_char == '\n');
	}

	inline bool IsValueSep(char in_char) const
	{
		return(value_sep_list_.find_first_of(in_char, 0) != std::string::npos);
	}

	inline std::size_t GetNextLineIndex(const std::string_view &src_data,
		std::size_t current_offset = 0) const
	{
		return(src_data.find_first_of(line_sep_list_, current_offset));
	}

	inline std::size_t GetNextSepIndex(const std::string_view &src_line,
		std::size_t current_offset = 0) const
	{
		return(src_line.find_first_of(value_sep_list_, current_offset));
	}

private:
	std::string line_sep_list_;
	std::string value_sep_list_;
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

private:
	std::string_view src_line_;
	std::size_t      current_offset_;
	bool             at_end_flag_;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class ParseLineState
{
public:
	ParseLineState(std::string_view src_data_);
	ParseLineState(const std::string &src_data_);

	bool IsEnd() const
	{
		return(at_end_flag_);
	}

	std::size_t GetLineIndex() const
	{
		return(line_index_);
	}

	std::string_view ParseLineSingle(
		const ParseCsvControl &parse_control = ParseCsvControl());

private:
	std::string_view src_data_;
	std::size_t      line_index_;
	std::size_t      line_offset_;
	std::size_t      current_offset_;
	bool             at_end_flag_;
};
// ////////////////////////////////////////////////////////////////////////////

/*
// ////////////////////////////////////////////////////////////////////////////
using ValueOffset   = uint64_t;

using ValueCsvList  = std::vector<ValueOffset>;

//using ValueLineList = std::vector<ValueOffset>;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class ParseLineData
{
public:
	ParseLineData(const ParseCsvControl &parse_control,
		const std::string_view &src_data);
	ParseLineData(const ParseCsvControl &parse_control,
		const std::string &src_data);
	ParseLineData(const ParseCsvControl &parse_control,
		std::string &&src_data);
	ParseLineData(const ParseCsvControl &parse_control,
		const char *src_data);
	ParseLineData(const ParseCsvControl &parse_control,
		const char *src_data, std::size_t src_length);
	ParseLineData(const std::string &src_file,
		const ParseCsvControl &parse_control = ParseCsvControl());

private:
	using StringSPtr    = std::shared_ptr<std::string>;
	using ValueLineList = std::vector<ValueOffset>;

	ParseCsvControl  parse_control_;
	StringSPtr       src_data_;
	std::string_view src_data_view_;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename ConfigDatum, typename ConfigItemMap>
	void ParseCsv(ConfigDatum &cfg_datum, const ConfigItemMap &cfg_map,
		const std::string &file_name)
{
	try {
		ParseCfgLines(cfg_datum, cfg_map, ReadFileLines(file_name));
	}
	catch (const std::exception &except) {
		throw std::runtime_error("Unable to parse configuration file '" +
			file_name + "': " + std::string(except.what()));
	}
}
// ////////////////////////////////////////////////////////////////////////////
*/

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__GetCmdLineArg_hpp__HH

