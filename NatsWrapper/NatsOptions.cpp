// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB NatsWrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  NatsOptions.cpp

   File Description  :  Implementation of the NatsOptions class.

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

#include <NatsWrapper/NatsOptions.hpp>

/*
#include <Utility/EmitterSep.hpp>
#include <Utility/GranularRound.hpp>
#include <Utility/ThrowErrno.hpp>

#include <cstring>
#include <stdexcept>

#include <boost/io/ios_state.hpp>
*/

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace NatsWrapper {

/*
// ////////////////////////////////////////////////////////////////////////////
class NatsOptions
{
public:
	NatsOptions();

	~NatsOptions();

	void Destroy();

	      natsOptions *GetPtr();
	const natsOptions *GetPtr() const;

private:
	std::shared_ptr<natsOptions> nats_options_sptr_;
};
// ////////////////////////////////////////////////////////////////////////////
*/

} // namespace NatsWrapper

} // namespace MLB

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace NatsWrapper {

// ////////////////////////////////////////////////////////////////////////////
NatsOptions::NatsOptions()
	:nats_options_sptr_()
{
	natsOptions *nats_opts = NULL;

	NatsWrapper_THROW_IF_NOT_OK(::natsOptions_Create, (&nats_opts))

/*
	nats_options_sptr_ =
		std::make_shared<natsOptions>(nats_opts, natsOptions_Destroy);
*/
	nats_options_sptr_.reset(nats_opts, natsOptions_Destroy);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsOptions::~NatsOptions()
{
	try {
		Destroy();
	}
	catch (const std::exception &except) {
		;	// SwallowException(except);
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsOptions::Destroy()
{
	if (GetPtr()) {
//		::natsOptions_Destroy(GetPtr());
		nats_options_sptr_.reset();
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
natsOptions *NatsOptions::GetPtr()
{
	return(nats_options_sptr_.get());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const natsOptions *NatsOptions::GetPtr() const
{
	return(nats_options_sptr_.get());
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

