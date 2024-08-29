// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  ParseCfgFile.hpp

   File Description  :  Include file for configuration file parsing.

   Revision History  :  2023-03-03 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__ParseCfgFile_hpp__HH

#define HH__MLB__Utility__ParseCfgFile_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file ParseCfgFile.hpp

   \brief   The configuration file parsing header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/ParseCfgItem.hpp>

#include <Utility/ReadFile.hpp>
#include <Utility/StringTrim.hpp>

#include <stdexcept>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
bool GetParseCfgLineComponents(const std::string &src_line,
	std::string &dst_name, std::string &dst_value);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename ConfigDatum, typename ConfigItemMap>
	void ParseCfgLines(ConfigDatum &cfg_datum, const ConfigItemMap &cfg_map,
		const std::vector<std::string> &src_lines)
{
	std::size_t line_number = 0;

	for (const auto &this_line : src_lines) {
		++line_number;
		try {
/*
			const char *line_ptr = this_line.c_str();
			while (*line_ptr && ::isspace(*line_ptr))
				++line_ptr;
			if (*line_ptr && (*line_ptr != '#')) {
				const char *equal_ptr = ::strchr(line_ptr, '=');
				if (equal_ptr == line_ptr)
					throw std::invalid_argument("Configuration line does not "
						"have a name before the '=' separator between name and "
						"value.");
				std::string item_name(Trim(std::string(line_ptr, equal_ptr)));
				std::string item_value(Trim(std::string(equal_ptr + 1)));
*/
			std::string item_name;
			std::string item_value;
			if (GetParseCfgLineComponents(this_line, item_name, item_value)) {
				typename ConfigItemMap::const_iterator iter_f(
					cfg_map.find(item_name));
				if (iter_f != cfg_map.end())
					iter_f->second(cfg_datum, item_value);
				else
					throw std::invalid_argument("No configuration specification "
						"could be located for configuration name '" +
						item_name + "'.");
			}
		}
		catch (const std::exception &except) {
			throw std::invalid_argument("Failed to parse line number " +
				std::to_string(line_number) + " ('" + src_lines[line_number - 1] +
				"'): " + std::string(except.what()));
		}
	}
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename ConfigDatum, typename ConfigItemMap>
	void ParseCfgFile(ConfigDatum &cfg_datum, const ConfigItemMap &cfg_map,
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

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__GetCmdLineArg_hpp__HH

