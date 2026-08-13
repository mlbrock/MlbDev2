// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  EmitRuledBuffer.hpp

   File Description  :  Header file for the EmitRuledBuffer functions.

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

#ifndef HH__MLB__Utility__EmitRuledBuffer_hpp__HH

#define HH__MLB__Utility__EmitRuledBuffer_hpp__HH  1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <cstdint>
#include <string>
#include <vector>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////

enum class ErbFlags : uint32_t {
	None         = 0x00,
	NoCEscSeqs   = 0x01,
	UseHexNul    = 0x02,
	Use8BitAscii = 0x04,
	HexRule      = 0x08,
	RuleOnTop    = 0x10,
	CEscSeqE     = 0x20,
	Mask         = NoCEscSeqs   |
					   UseHexNul    |
						Use8BitAscii |
						HexRule      |
						RuleOnTop    |
					   CEscSeqE,
	Default      = None
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
/*
	Support for the ErbFlags enumeration ...
*/
std::underlying_type_t<ErbFlags> ToType(ErbFlags src);

ErbFlags    operator & (ErbFlags lhs, ErbFlags rhs);
ErbFlags    operator | (ErbFlags lhs, ErbFlags rhs);
ErbFlags    operator ^ (ErbFlags lhs, ErbFlags rhs);

bool        Bool(ErbFlags src);
bool        IsSet(ErbFlags src);
bool        IsValid(ErbFlags src);
bool        CheckIsValid(ErbFlags src);
std::string ToString(ErbFlags src, bool check_is_valid = false);

std::ostream & operator << (std::ostream &o_str, const ErbFlags &datum);
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
/*
	The various EmitRuledBuffer() function overloads ...
*/
std::vector<std::string> EmitRuledBuffer(std::size_t src_length,
	const char *src_ptr, unsigned long long start_offset = 0,
	ErbFlags flags = ErbFlags::Default);
std::vector<std::string> EmitRuledBuffer(const char *src_ptr,
	unsigned long long start_offset = 0, ErbFlags flags = ErbFlags::Default);
std::vector<std::string> EmitRuledBuffer(const char *begin_ptr,
	const char *end_ptr, unsigned long long start_offset = 0,
	ErbFlags flags = ErbFlags::Default);
std::vector<std::string> EmitRuledBuffer(const std::string &src,
	unsigned long long start_offset = 0, ErbFlags flags = ErbFlags::Default);
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__EmitRuledBuffer_hpp__HH

