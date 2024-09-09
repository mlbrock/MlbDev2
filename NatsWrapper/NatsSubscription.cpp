// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB NatsWrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  NatsSubscription.cpp

   File Description  :  Implementation of the NatsSubscription class.

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

#include <NatsWrapper/NatsSubscription.hpp>

#include <NatsWrapper/NatsConnection.hpp>
#include <NatsWrapper/NatsMsg.hpp>

#include <Utility/ArgCheck.hpp>

#include <cstring>

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

#if 0
// ////////////////////////////////////////////////////////////////////////////
class NatsSubscription
{
public:
	NatsSubscription(NatsConnection &nats_conn,
		const char *subject_name, std::size_t subject_name_length);
	NatsSubscription(NatsConnection &nats_conn, const std::string_view &subject_name);
	NatsSubscription(NatsConnection &nats_conn, const std::string &subject_name);
	NatsSubscription(NatsConnection &nats_conn, const char *subject_name);

	~NatsSubscription();

	/// Returns a hollow NatMsg upon timeout.
	NatsMsg NextMsg(int64_t time_out);

	void Unsubscribe();
/*
	void Destroy();
*/

/*
	void FlushTimeout(int64_t time_out);
	void Publish(const char *subject_name, std::size_t subject_name_length,
		const void *data_ptr, std::size_t data_length);
	void Publish(const std::string_view &subject_name, const void *data_ptr,
		data_length);
	void Publish(const std::string &subject_name, const void *data_ptr,
		data_length);
	void Publish(const char *subject_name, const void *data_ptr,
		data_length);
*/

private:
	std::shared_ptr<NatsSubscription> nats_subscription_sptr_;
};
// ////////////////////////////////////////////////////////////////////////////
#endif // #if 0

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
NatsSubscription::NatsSubscription(NatsConnection &nats_conn,
	const char *subject_name, std::size_t subject_name_length)
	:nats_subscription_sptr_()
{
	if (!subject_name)
		throw std::invalid_argument("The pointer to the subject name is NULL.");

	if (!subject_name_length)
		throw std::invalid_argument("The length of the subject name is 0.");

	natsSubscription *nats_sub = NULL;

	NatsWrapper_THROW_IF_NOT_OK(::natsConnection_SubscribeSync,
		(&nats_sub, nats_conn.GetPtr(), subject_name))

	nats_subscription_sptr_.reset(nats_sub, ::natsSubscription_Destroy);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsSubscription::NatsSubscription(NatsConnection &nats_conn,
	const std::string_view &subject_name)
	:NatsSubscription(nats_conn, subject_name.data(), subject_name.size())
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsSubscription::NatsSubscription(NatsConnection &nats_conn,
	const std::string &subject_name)
	:NatsSubscription(nats_conn, subject_name.c_str(), subject_name.size())
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsSubscription::NatsSubscription(NatsConnection &nats_conn,
	const char *subject_name)
	:NatsSubscription(nats_conn, MLB::Utility::ThrowIfNull(subject_name,
		"The subject name string"), ::strlen(subject_name))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsSubscription::~NatsSubscription()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
natsSubscription *NatsSubscription::GetPtr()
{
	return(nats_subscription_sptr_.get());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const natsSubscription *NatsSubscription::GetPtr() const
{
	return(nats_subscription_sptr_.get());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsMsg NatsSubscription::NextMsg(int64_t time_out)
{
	natsMsg *nats_msg = NULL;

	NatsWrapper_THROW_IF_NOT_OK_OR_TIMEOUT(::natsSubscription_NextMsg,
		(&nats_msg, GetPtr(), time_out))

	return(NatsMsg(nats_msg));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::Unsubscribe()
{
	if (nats_subscription_sptr_)
		::natsSubscription_Unsubscribe(GetPtr());
}
// ////////////////////////////////////////////////////////////////////////////

/*
// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::Destroy()
{
	if (nats_subscription_sptr_)
		nats_subscription_sptr_.release();
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::FlushTimeout(int64_t time_out)
{
	NatsWrapper_THROW_IF_NOT_OK(::natsConnection_FlushTimeout,
		(GetPtr(), time_out))
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::Publish(const char *subject_name,
	std::size_t subject_name_length, const void *data_ptr,
	std::size_t data_length)
{
	if (!subject_name)
		throw std::invalid_argument("The pointer to the subject name on which "
			"data is to be published is NULL.");

	if (!subject_name)
		throw std::invalid_argument("The length of the subject name on which "
			"data to be published is 0.");

	if (!data_ptr)
		throw std::invalid_argument("The pointer to data to be published "
			"is NULL.");

	if (!data_length)
		throw std::invalid_argument("The length of the data to be published "
			"is 0.");

	if (data_length >
		 static_cast<std::size>(std::numeric_limits<int>::max()))
		throw std::invalid_argument("Length of the data to be published is "
			"greater than the maximum permissible by the data type NATS uses to "
			"specify the length of published data (" +
			std::to_string(std::numeric_limits<int>::max()) + ").");

	NatsWrapper_THROW_IF_NOT_OK(::natsConnection_Publish,
		(GetPtr(), subject_name, data_ptr, data_length))
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::Publish(const std::string_view &subject_name,
	const void *data_ptr, std::size_t data_length)
{
	Publish(subject_name.data(), subject_name.size(), data_ptr, data_length);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::Publish(const std::string &subject_name,
	const void *data_ptr, std::size_t data_length)
{
	Publish(subject_name.c_str(), subject_name.size(), data_ptr, data_length);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::Publish(const char *subject_name, const void *data_ptr,
	std::size_t data_length)
{
	if (!subject_name)
		throw std::invalid_argument("Subject name on which to publish is NULL.");

	Publish(subject_name, ::strlen(subject_name), data_ptr, data_length);
}
// ////////////////////////////////////////////////////////////////////////////
*/

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::NatsMsgHandler(natsConnection * /* nats_conn_ptr */,
	natsSubscription * /* nats_subs_ptr */, natsMsg * /* nats_msg_ptr */)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsSubscription::NatsMsgHandler(natsConnection *nats_conn_ptr,
	natsSubscription *nats_subs_ptr, natsMsg *nats_msg_ptr, void *closure_ptr)
{
	if (!closure_ptr)
		MLB::Utility::ThrowIfNull("NatsSubscription::NatsMsgHandler() called "
			"with a NULL closure pointer.");

/*
	NatsSubscription *my_nats_sub;

	if ((my_nats_sub = dynamic_cast<NatsSubscription *>(closure_ptr)) == NULL)
		MLB::Utility::ThrowIfNull("NatsSubscription::NatsMsgHandler() called "
			"with a closure pointer which dynamic_cast<> reports can ot be "
			"converted to a NatsSubscription pointer.");
*/

	NatsSubscription *my_nats_sub = ((NatsSubscription *) closure_ptr);

	my_nats_sub->NatsMsgHandler(nats_conn_ptr, nats_subs_ptr, nats_msg_ptr);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace NatsWrapper

} // namespace MLB

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
void TEST_NatsSubscription(int argc, char **argv)
{
	using namespace MLB::NatsWrapper;

	NatsContext                   nats_context;
	NatsOptions                   nats_options;
	NatsConnection                nats_connection(nats_options);
	std::vector<NatsSubscription> subscription_list;

	for (int arg_idx = 1; arg_idx < argc; ++arg_idx) {
		NatsSubscription nats_subs(nats_comm, argv[arg_idx]);
		subscription_list.push_back(nats_subs);
	}
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int return_code = EXIT_SUCCESS;

	try {
		TEST_NatsSubscription(argc, argv);
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

