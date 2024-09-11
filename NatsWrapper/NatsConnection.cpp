// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB NatsWrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  NatsConnection.cpp

   File Description  :  Implementation of the NatsConnection class.

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

#include <NatsWrapper/NatsConnection.hpp>

#include <NatsWrapper/NatsSubscription.hpp>

#include <Utility/ArgCheck.hpp>

#include <cstring>
#include <limits>

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

// ////////////////////////////////////////////////////////////////////////////
class NatsSubscription;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
/*
class NatsConnection
{
public:
	NatsConnection(NatsOptions &nats_options);
	NatsConnection(const char *urls, std::size_t urls_length);
	NatsConnection(const std::string_view &urls);
	NatsConnection(const std::string &urls);
	NatsConnection(const char *urls);

	~NatsConnection();

	      natsConnection *GetPtr();
	const natsConnection *GetPtr() const;

	void Close();
	void Destroy();
	void FlushTimeout(int64_t time_out);
	void Publish(const char *subject_name, std::size_t subject_name_length,
		const void *data_ptr, std::size_t data_length);
	void Publish(const std::string_view &subject_name, const void *data_ptr,
		std::size_t data_length);
	void Publish(const std::string &subject_name, const void *data_ptr,
		std::size_t data_length);
	void Publish(const char *subject_name, const void *data_ptr,
		std::size_t data_length);

	NatsSubscription SubscribeSync(const char *subject_name,
		std::size_t subject_name_length);
	NatsSubscription SubscribeSync(const std::string &subject_name);
	NatsSubscription SubscribeSync(const char *subject_name);

	static NatsConnection Connect(NatsOptions &nats_options);
	static NatsConnection ConnectTo(const char *urls, std::size_t urls_length);
	static NatsConnection ConnectTo(const std::string_view &urls);
	static NatsConnection ConnectTo(const std::string &urls);
	static NatsConnection ConnectTo(const char *urls);

private:
	std::shared_ptr<natsConnection> nats_connection_sptr_;
};
*/
// ////////////////////////////////////////////////////////////////////////////

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
NatsConnection::NatsConnection(NatsOptions &nats_options)
	:nats_connection_sptr_()
{
	natsConnection *nats_conn = NULL;

	NatsWrapper_THROW_IF_NOT_OK(::natsConnection_Connect,
		(&nats_conn, nats_options.GetPtr()))

	nats_connection_sptr_.reset(nats_conn, ::natsConnection_Destroy);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection::NatsConnection(const char *urls, std::size_t urls_length)
	:nats_connection_sptr_()
{
	if (!urls)
		throw std::invalid_argument("The pointer to the URLs string is NULL.");

	if (!urls_length)
		throw std::invalid_argument("The length of the URLs string is 0.");

	natsConnection *nats_conn = NULL;

	NatsWrapper_THROW_IF_NOT_OK(::natsConnection_ConnectTo, (&nats_conn, urls))

	nats_connection_sptr_.reset(nats_conn, ::natsConnection_Destroy);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection::NatsConnection(const std::string_view &urls)
	:NatsConnection(urls.data(), urls.size())
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection::NatsConnection(const std::string &urls)
	:NatsConnection(urls.c_str(), urls.size())
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection::NatsConnection(const char *urls)
	:NatsConnection(MLB::Utility::ThrowIfNull(urls, "The URLs string"),
		::strlen(urls))
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection::~NatsConnection()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
natsConnection *NatsConnection::GetPtr()
{
	return(nats_connection_sptr_.get());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const natsConnection *NatsConnection::GetPtr() const
{
	return(nats_connection_sptr_.get());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsConnection::Close()
{
	if (nats_connection_sptr_)
		natsConnection_Close(nats_connection_sptr_.get());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
/*
void NatsConnection::Destroy()
{
	nats_connection_sptr_.reset();
}
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsConnection::FlushTimeout(int64_t time_out)
{
	NatsWrapper_THROW_IF_NOT_OK(::natsConnection_FlushTimeout,
		(GetPtr(), time_out))
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsConnection::Publish(const char *subject_name,
	std::size_t subject_name_length, const void *data_ptr,
	std::size_t data_length)
{
	if (!subject_name)
		throw std::invalid_argument("The pointer to the subject name on which "
			"data is to be published is NULL.");

	if (!subject_name_length)
		throw std::invalid_argument("The length of the subject name on which "
			"data to be published is 0.");

	if (!data_ptr)
		throw std::invalid_argument("The pointer to data to be published "
			"is NULL.");

	if (!data_length)
		throw std::invalid_argument("The length of the data to be published "
			"is 0.");

	if (data_length >
		 static_cast<std::size_t>(std::numeric_limits<int>::max()))
		throw std::invalid_argument("Length of the data to be published is "
			"greater than the maximum permissible by the data type NATS uses to "
			"specify the length of published data (" +
			std::to_string(std::numeric_limits<int>::max()) + ").");

	NatsWrapper_THROW_IF_NOT_OK(::natsConnection_Publish,
		(GetPtr(), subject_name, data_ptr, data_length))
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsConnection::Publish(const std::string_view &subject_name,
	const void *data_ptr, std::size_t data_length)
{
	Publish(subject_name.data(), subject_name.size(), data_ptr, data_length);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsConnection::Publish(const std::string &subject_name,
	const void *data_ptr, std::size_t data_length)
{
	Publish(subject_name.c_str(), subject_name.size(), data_ptr, data_length);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void NatsConnection::Publish(const char *subject_name, const void *data_ptr,
	std::size_t data_length)
{
	if (!subject_name)
		throw std::invalid_argument("Subject name on which to publish is NULL.");

	Publish(subject_name, ::strlen(subject_name), data_ptr, data_length);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsSubscription NatsConnection::SubscribeSync(const char *subject_name,
	std::size_t subject_name_length)
{
	return(NatsSubscription(*this, subject_name, subject_name_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsSubscription NatsConnection::SubscribeSync(const std::string &subject_name)
{
	return(SubscribeSync(subject_name.c_str(), subject_name.size()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsSubscription NatsConnection::SubscribeSync(const char *subject_name)
{
	if (!subject_name)
		throw std::invalid_argument("The pointer to the subject name to which "
			"the subscription is to be made is NULL.");

	return(SubscribeSync(subject_name, ::strlen(subject_name)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection NatsConnection::ConnectTo(const char *urls,
	std::size_t urls_length)
{
	return(NatsConnection(urls, urls_length));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection NatsConnection::ConnectTo(const std::string_view &urls)
{
	return(NatsConnection(urls));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection NatsConnection::ConnectTo(const std::string &urls)
{
	return(NatsConnection(urls));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsConnection NatsConnection::ConnectTo(const char *urls)
{
	return(NatsConnection(urls));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace NatsWrapper

} // namespace MLB

