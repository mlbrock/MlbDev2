// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB NatsWrapper Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  NatsSubscription.hpp

   File Description  :  Include file for the NatsSubscription class.

   Revision History  :  2024-08-17 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__NatsWrapper__NatsSubscription_hpp__HH

#define HH__MLB__NatsWrapper__NatsSubscription_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file NatsSubscription.hpp

   \brief   Main include file for the NatsSubscription class.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

//#include <NatsWrapper/NatsConnection.hpp>
#include <NatsWrapper/NatsWrapper.hpp>

#include <memory>
#include <string>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace NatsWrapper {

// ////////////////////////////////////////////////////////////////////////////
class NatsConnection;
class NatsMsg;
// ////////////////////////////////////////////////////////////////////////////

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

	      natsSubscription *GetPtr();
	const natsSubscription *GetPtr() const;

	/// Returns a hollow NatMsg upon timeout.
	NatsMsg NextMessage(int64_t time_out);

	void Unsubscribe();
/*
	void Destroy();
*/
\
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
	std::shared_ptr<natsSubscription> nats_subscription_sptr_;
};
// ////////////////////////////////////////////////////////////////////////////

} // namespace NatsWrapper

} // namespace MLB

#endif // #ifndef HH__MLB__NatsWrapper__NatsSubscription_hpp__HH

