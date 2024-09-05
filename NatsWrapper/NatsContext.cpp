// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB NatsWrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  NatsContext.cpp

   File Description  :  Implementation of the NatsContext class.

   Revision History  :  2024-08-17 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <NatsWrapper/NatsContext.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace NatsWrapper {

// ////////////////////////////////////////////////////////////////////////////
NatsContext::NatsContext(int spin_wait)
{
	NatsWrapper_THROW_IF_NOT_OK(::nats_Open, (spin_wait))
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsContext::~NatsContext()
{
	::nats_Close();
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace NatsWrapper

} // namespace MLB

#if 0
// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

#include <Utility/Sleep.hpp>

#include <iostream>

using namespace MLB::Utility;
using namespace MLB::NatsWrapper;

namespace {

// ////////////////////////////////////////////////////////////////////////////
const NatsWrapper TEST_SectionList[] =
{
	 NatsWrapper( 0,                1234,      1, 0, 0, 0, 0, 0, "Header")
	,NatsWrapper( 0, sizeof(NatsWrapper),      8, 0, 0, 0, 0, 0, "Section List")
	,NatsWrapper( 0,                   4,      6, 0, 0, 0, 0, 0, "Type Info")
	,NatsWrapper( 0,                 150, 112233, 0, 0, 0, 0, 0, "Info List All")
	,NatsWrapper( 0,                 987, 112233, 0, 0, 0, 0, 0, "Info Serial")
	,NatsWrapper( 0,                 150,   1024, 0, 0, 0, 0, 0, "Info List Sub")
	,NatsWrapper( 0,                  64,   1024, 0, 0, 0, 0, 0, "ToB")
	,NatsWrapper( 0,                 200,   1024, 0, 0, 0, 0, 0, "MStats")
};

const std::size_t TEST_SectionCount  =
	sizeof(TEST_SectionList) / sizeof(TEST_SectionList[0]);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_NatsWrapper()
{
	using namespace MLB::NatsWrapper;

	NatsWrapperList section_list;

	for (std::size_t section_idx = 0; section_idx < TEST_SectionCount;
		++section_idx)
		NatsWrapper::AppendSection(TEST_SectionList[section_idx], section_list);

	NatsWrapper::FixupSectionList(section_list);

	NatsWrapper::ToStreamTabular(section_list);
	std::cout << '\n';
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		TEST_NatsWrapper();
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN
#endif // #if 0

