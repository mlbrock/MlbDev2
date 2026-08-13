// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  EmitRuledBuffer.cpp

   File Description  :  Logic to emit a ruled buffer.

   Revision History  :  2017-10-13 --- Creation in the MlbDev Utility library.
                           Michael L. Brock
                        2026-08-12 --- Added to the MlbDev2 Utility library.
                           Michael L. Brock

      Copyright Michael L. Brock 2017 - 2026.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////
 
// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/EmitRuledBuffer.hpp>

#include <Utility/ToStringRadix.hpp>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ostream>
#include <numeric>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace {

//	////////////////////////////////////////////////////////////////////////////
const std::vector<std::pair<ErbFlags, std::string> > ErbFlags_List =
{
	{ ErbFlags::NoCEscSeqs,		"NoCEscSeqs" 	},
	{ ErbFlags::UseHexNul,		"UseHexNul" 	},
	{ ErbFlags::Use8BitAscii,	"Use8BitAscii" },
	{ ErbFlags::HexRule,     	"HexRule" 		},
	{ ErbFlags::RuleOnTop,		"RuleOnTop"		},
	{ ErbFlags::CEscSeqE,    	"CEscSeqE"		}
};
//	////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

//	////////////////////////////////////////////////////////////////////////////
std::underlying_type_t<ErbFlags> ToType(ErbFlags src)
{
	return(static_cast<std::underlying_type_t<ErbFlags> >(src));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool operator ! (ErbFlags src)
{
	return(!IsSet(src));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ErbFlags operator & (ErbFlags lhs, ErbFlags rhs)
{
	return(static_cast<ErbFlags>(ToType(lhs) & ToType(rhs)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ErbFlags operator | (ErbFlags lhs, ErbFlags rhs)
{
	return(static_cast<ErbFlags>(ToType(lhs) | ToType(rhs)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ErbFlags operator ^ (ErbFlags lhs, ErbFlags rhs)
{
	return(static_cast<ErbFlags>(ToType(lhs) ^ ToType(rhs)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsSet(ErbFlags src)
{
	return(src != ErbFlags::None);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsValid(ErbFlags src)
{
	return((!IsSet(src)) || (!IsSet(src & ErbFlags::Mask)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool CheckIsValid(ErbFlags src)
{
	if (!IsValid(src))
		throw std::invalid_argument("Specified ErbFlags value (" +
			std::to_string(ToType(src)) + " = " + ToStringHex(ToType(src), 'x') +
			") is invalid.");

	return(true);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string ToString(ErbFlags src, bool check_is_valid)
{
	if (!IsSet(src))
		return("None");

	if (check_is_valid)
		CheckIsValid(src);

	std::string dst;

	for (const auto &erb_flag_info : ErbFlags_List) {
		if (IsSet(src & erb_flag_info.first)) {
			if (!dst.empty())
				dst += " | ";
			dst += erb_flag_info.second;
			src  = src ^ erb_flag_info.first;
		}
	}

	if (IsSet(src)) {
		if (!dst.empty())
			dst += " | ";
		dst += "?" + std::to_string(ToType(src)) + "?";
	}

	return(dst);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const ErbFlags &datum)
{
	o_str << ToString(datum, false);

	return(o_str);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	****************************************************************************
//	****************************************************************************
//	****************************************************************************
//	////////////////////////////////////////////////////////////////////////////

namespace {

//	////////////////////////////////////////////////////////////////////////////
/*
	If the CEscSeqE flag is not set, we won't use the first character of
	the two C-language sequence strings below.
*/
const char *MyCSequenceSrc = "\x1b\a\b\t\n\v\f\r\\";
const char *MyCSequenceDst = "eabtnvfr\\";

const char *MyHexDigitList = "0123456789abcdef";
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void HandleRule(std::vector<std::string> &dst, std::size_t curr_index,
	std::size_t &next_rule, unsigned long long start_offset, int flags)
{
	if (curr_index != next_rule)
		return;

	unsigned long long rule_fixed = start_offset + next_rule;
	char               rule_buffer[1 + 8 + 1];

	if (!(flags & ErbFlag_HexRule))
		::sprintf(rule_buffer, "%s%llu",
			(rule_fixed < 100000000) ? "" : "?", rule_fixed % 100000000);
	else if (rule_fixed < 0x100000000)
		::sprintf(rule_buffer, "%llx", rule_fixed);
	else
		::sprintf(rule_buffer, "?%8.8llx", rule_fixed % 0x100000000);

	std::size_t dst_1_pad = (dst[0].size() - dst[1].size()) - 1;
	std::size_t dst_2_pad = (dst[0].size() - dst[2].size()) -
		((::strlen(rule_buffer) / 2) + 1);

	dst[1]    += std::string(dst_1_pad, ' ') + '|';
	dst[2]    += std::string(dst_2_pad, ' ') + rule_buffer;
	next_rule += 10;
}
//	////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

//	////////////////////////////////////////////////////////////////////////////
/*

     123456789 123456789 123456789 123456789 123456789 123456789 123456789
         |         |         |         |         |         |         |
0123456789012345678901234567890123456789012345678901234567890123456789012345678
*/
//	////////////////////////////////////////////////////////////////////////////
std::vector<std::string> EmitRuledBuffer(std::size_t src_length,
	const char *src_ptr, unsigned long long start_offset, int flags)
{
	std::vector <std::string> dst(3);

	if (src_length < 1)
		return(dst);

	bool        use_c_sequences = !(flags & ErbFlag_NoCEscSeqs);
	bool        use_simple_nul  = !(flags & ErbFlag_UseHexNul);
	bool        use_8bit_ascii  = ((flags & ErbFlag_Use8BitAscii) != 0);
	const char *my_c_seq_src    = MyCSequenceSrc;
	const char *my_c_seq_dst    = MyCSequenceDst;

	if (!(flags & ErbFlag_CEscSeqE)) {
		++my_c_seq_src;
		++my_c_seq_dst;
	}

	dst[0].reserve(src_length);
	dst[1].reserve(src_length);
	dst[2].reserve(src_length);

	std::size_t  curr_index = 0;
	std::size_t  rule_adj   = (start_offset % 10ULL);
	std::size_t  next_rule  = 10 + ((rule_adj) ? (10 - rule_adj) : 0);
	const char  *c_seq_ptr;

	while (curr_index < src_length) {
		if (curr_index == next_rule)
			HandleRule(dst, curr_index, next_rule, start_offset, flags);
		if ((*src_ptr > -1) && ::isprint(*src_ptr) && (*src_ptr != '\\'))
			dst[0] += *src_ptr;
		else if (use_c_sequences && *src_ptr &&
			((c_seq_ptr = ::strchr(my_c_seq_src, *src_ptr)) != NULL)) {
			dst[0] += '\\';
			dst[0] += my_c_seq_dst[c_seq_ptr - my_c_seq_src];
		}
		else if ((!(*src_ptr)) && use_simple_nul)
			dst[0] += "\\0";
		else if (use_8bit_ascii &&
			(static_cast<unsigned char>(*src_ptr) > 127))
			dst[0] += *src_ptr;
		else {
			dst[0] += "\\x";
			dst[0] += MyHexDigitList[(*src_ptr >> 4) & 0x0f];
			dst[0] += MyHexDigitList[*src_ptr & 0x0f];
		}
		++src_ptr;
		++curr_index;
	}

	if (curr_index == next_rule)
		HandleRule(dst, curr_index, next_rule, start_offset, flags);

	if (flags & ErbFlag_RuleOnTop)
		std::reverse(dst.begin(), dst.end());

	return(dst);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::vector<std::string> EmitRuledBuffer(const char *src_ptr,
	unsigned long long start_offset, int flags)
{
	return(EmitRuledBuffer(::strlen(src_ptr), src_ptr, start_offset, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::vector<std::string> EmitRuledBuffer(const char *begin_ptr,
	const char *end_ptr, unsigned long long start_offset, int flags)
{
	return(EmitRuledBuffer((end_ptr > begin_ptr) ?
		static_cast<std::size_t>(end_ptr - begin_ptr) : 0, begin_ptr,
		start_offset, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::vector<std::string> EmitRuledBuffer(const std::string &src,
	unsigned long long start_offset, int flags)
{
	return(EmitRuledBuffer(src.size(), src.c_str(), start_offset, flags));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

//	////////////////////////////////////////////////////////////////////////////
//	****************************************************************************
//	****************************************************************************
//	****************************************************************************
//	////////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

#include <Utility/EmitterSep.hpp>
#include <Utility/GetCmdLineHelp.hpp>
#include <Utility/ReadFile.hpp>

#include <iomanip>
#include <iostream>

using namespace MLB::Utility;

namespace {

//	////////////////////////////////////////////////////////////////////////////
void TEST_EmitStringContents(const std::string &src,
	unsigned long long start_offset = 0, int flags = ErbFlag_Default)
{
	std::vector<std::string> dst(EmitRuledBuffer(src, start_offset, flags));

	std::cout
		<< EmitterSep('-')
		<< "Offset: " << std::setw(10) << start_offset << " / "
		<< "Flags: " << std::setw(3) << flags << " = 0x"
		<< std::hex << flags << std::dec << " = "
		<< ToString(static_cast<ErbFlags>(flags)) << '\n';

	for (std::size_t count_1 = 0; count_1 < dst.size(); ++count_1) 
		std::cout << dst[count_1] << '\n';

	std::cout << std::flush;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void TEST_EmitFileContents(const std::string &file_name,
	unsigned long long start_offset = 0, int flags = ErbFlag_Default)
{
	std::string file_data(ReadFileData(file_name));

	TEST_EmitStringContents(file_data, start_offset, flags);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
/*
A line\nFollowed by another line.
          |         |         |
         10        20        30
A line\nAnother line with embedded \x7f high-ASCII \xff characters.
          |         |         |            |            |         |
         10        20        30           40           50        60
12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
         |         |         |         |         |         |         |         |         |         |         |
        10        20        30        40        50        60        70        80        90        100       110
*/
const char *TEST_DoStandAloneTestsList[] = {
	"A line\nFollowed by another line.",
	"A line\nAnother line with embedded \x7f"" high-ASCII \xff characters.",
	"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
	NULL
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void TEST_DoStandAloneTests()
{
	const char **list_ptr = TEST_DoStandAloneTestsList;

	while (*list_ptr++) {
		std::cout
			<< EmitterSep('=')
			<< EmitterSep('=')
			<< "String: \"" << EmitRuledBuffer(list_ptr[-1])[0] << "\"\n";
		TEST_EmitStringContents(list_ptr[-1],          0);
		TEST_EmitStringContents(list_ptr[-1],          0, ErbFlag_NoCEscSeqs);
		TEST_EmitStringContents(list_ptr[-1],          0, ErbFlag_UseHexNul);
		TEST_EmitStringContents(list_ptr[-1],          0, ErbFlag_Use8BitAscii);
		TEST_EmitStringContents(list_ptr[-1],          0, ErbFlag_HexRule);
		TEST_EmitStringContents(list_ptr[-1],          0, ErbFlag_RuleOnTop);
		TEST_EmitStringContents(list_ptr[-1],        100);
		TEST_EmitStringContents(list_ptr[-1],        100, ErbFlag_HexRule);
		TEST_EmitStringContents(list_ptr[-1], 4294967275);
		TEST_EmitStringContents(list_ptr[-1], 4294967275, ErbFlag_HexRule);
		TEST_EmitStringContents(list_ptr[-1], 0xfffffffe);
		TEST_EmitStringContents(list_ptr[-1], 0xfffffffe, ErbFlag_HexRule);
		std::cout << EmitterSep('=') << std::endl;
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::vector<ErbFlags> GetAllErbFlagCombos()
{
	std::vector<std::underlying_type_t<ErbFlags> > tmp(ToType(ErbFlags::Mask) + 1);

	std::iota(tmp.begin(), tmp.end(), ToType(ErbFlags::None));

	std::vector<ErbFlags> dst(tmp.size());

	std::transform(tmp.begin(), tmp.end(), dst.begin(),
		[](uint32_t val) { return(static_cast<ErbFlags>(val)); });
	
	return(dst);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void TEST_AllErbFlagCombos()
{
	char                  raw[] = "Data\n SLASH=\\ ESC=\x1b NUL=\0 BIG=\xD1";
	std::vector<ErbFlags> all_flags(GetAllErbFlagCombos());
	std::string           datum(raw, sizeof(raw) - 1);

	std::cout
		<< '\n'
		<< EmitterSep('=')
		<< "All ErbFlags Combinations:\n";

	for (const auto &this_element : all_flags)
		TEST_EmitStringContents(datum, 0, ToType(this_element));

	std::cout << EmitterSep('=') << std::endl;
}
//	////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

//	////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	std::cout << "Test routine for 'EmitRuledBuffer()'" << std::endl;
	std::cout << "---- ------- --- -------------------" << std::endl;

	int return_code = EXIT_SUCCESS;

	if (HasCmdLineHelp(argc, argv, 1)) {
		std::cout << "USAGE: " << std::endl <<
			"   " << argv[0] << " " <<
			"[ <file-name> [ <file-name> ... ] ]" << std::endl << std::endl;
		exit(EXIT_SUCCESS);
	}

	try {
		if (argc > 1) {
			for (int count_1 = 1; count_1 < argc; ++count_1)
				TEST_EmitFileContents(argv[count_1]);
		}
		else
			TEST_DoStandAloneTests();
	}
	catch (const std::exception &except) {
		std::cerr << std::endl << "ERROR: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	TEST_AllErbFlagCombos();

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

