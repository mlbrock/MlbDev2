// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB NatsWrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  NatsExceptionStatus.cpp

   File Description  :  Implementation of the NatsExceptionStatus class.

   Revision History  :  2024-09-10 --- Creation.
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

#include <NatsWrapper/NatsExceptionStatus.hpp>

#include <set>									// CODE NOTE: for NatsStatusSet ONLY.

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace NatsWrapper {

// ////////////////////////////////////////////////////////////////////////////
NatsExceptionStatus::NatsExceptionStatus()
	:std::runtime_error("")
	,nats_code_(NATS_OK)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsExceptionStatus::NatsExceptionStatus(const std::string &error_text)
	:std::runtime_error(error_text)
	,nats_code_(NATS_OK)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsExceptionStatus::NatsExceptionStatus(natsStatus nats_code,
	const char *func_name, const char *params)
	:std::runtime_error(GetStatusString(nats_code, func_name, params))
	,nats_code_(nats_code)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsExceptionStatus::NatsExceptionStatus(const std::string &src_text,
	natsStatus nats_code)
	:std::runtime_error(GetStatusString(src_text, nats_code))
	,nats_code_(nats_code)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
NatsExceptionStatus::~NatsExceptionStatus()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
natsStatus NatsExceptionStatus::GetNatsStatus() const
{
	return(nats_code_);
}
// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
std::string NatsExceptionStatus::GetStatusString(natsStatus nats_code,
	const char *func_name, const char *params)
{
/*
	func_name = (func_name && *func_name) ? func_name : "*UNKNOWN-FUNCTION*";

	const char *nats_text = ::natsStatus_GetText(nats_code);

	nats_text = (nats_text && *nats_text) ? nats_text : "*UNKNOWN-NATS-TEXT*";

	std::string status_string("NATS error code " + std::to_string(nats_code) +
		" (\"" + std::string(nats_text) + "\") was encountered in function " +
		std::string(func_name) + "().");

	return(status_string);
*/
	std::string tmp_string("Error was encountered in function " +
		std::string(func_name) + ((params && *params) ? params : "()"));

	return(GetStatusString(tmp_string, nats_code));
}
// ////////////////////////////////////////////////////////////////////////////

namespace {

// ////////////////////////////////////////////////////////////////////////////
std::pair<natsStatus, natsStatus> GetNatsStatusRange()
{
	static std::set<natsStatus> NatsStatusSet =
	{
    NATS_OK         , //= 0,                ///< Success

    NATS_ERR,                           ///< Generic error
    NATS_PROTOCOL_ERROR,                ///< Error when parsing a protocol message,
                                        ///  or not getting the expected message.
    NATS_IO_ERROR,                      ///< IO Error (network communication).
    NATS_LINE_TOO_LONG,                 ///< The protocol message read from the socket
                                        ///  does not fit in the read buffer.

    NATS_CONNECTION_CLOSED,             ///< Operation on this connection failed because
                                        ///  the connection is closed.
    NATS_NO_SERVER,                     ///< Unable to connect, the server could not be
                                        ///  reached or is not running.
    NATS_STALE_CONNECTION,              ///< The server closed our connection because it
                                        ///  did not receive PINGs at the expected interval.
    NATS_SECURE_CONNECTION_WANTED,      ///< The client is configured to use TLS, but the
                                        ///  server is not.
    NATS_SECURE_CONNECTION_REQUIRED,    ///< The server expects a TLS connection.
    NATS_CONNECTION_DISCONNECTED,       ///< The connection was disconnected. Depending on
                                        ///  the configuration, the connection may reconnect.

    NATS_CONNECTION_AUTH_FAILED,        ///< The connection failed due to authentication error.
    NATS_NOT_PERMITTED,                 ///< The action is not permitted.
    NATS_NOT_FOUND,                     ///< An action could not complete because something
                                        ///  was not found. So far, this is an internal error.

    NATS_ADDRESS_MISSING,               ///< Incorrect URL. For instance no host specified in
                                        ///  the URL.

    NATS_INVALID_SUBJECT,               ///< Invalid subject, for instance NULL or empty string.
    NATS_INVALID_ARG,                   ///< An invalid argument is passed to a function. For
                                        ///  instance passing NULL to an API that does not
                                        ///  accept this value.
    NATS_INVALID_SUBSCRIPTION,          ///< The call to a subscription function fails because
                                        ///  the subscription has previously been closed.
    NATS_INVALID_TIMEOUT,               ///< Timeout must be positive numbers.

    NATS_ILLEGAL_STATE,                 ///< An unexpected state, for instance calling
                                        ///  #natsSubscription_NextMsg() on an asynchronous
                                        ///  subscriber.

    NATS_SLOW_CONSUMER,                 ///< The maximum number of messages waiting to be
                                        ///  delivered has been reached. Messages are dropped.

    NATS_MAX_PAYLOAD,                   ///< Attempt to send a payload larger than the maximum
                                        ///  allowed by the NATS Server.
    NATS_MAX_DELIVERED_MSGS,            ///< Attempt to receive more messages than allowed, for
                                        ///  instance because of #natsSubscription_AutoUnsubscribe().

    NATS_INSUFFICIENT_BUFFER,           ///< A buffer is not large enough to accommodate the data.

    NATS_NO_MEMORY,                     ///< An operation could not complete because of insufficient
                                        ///  memory.

    NATS_SYS_ERROR,                     ///< Some system function returned an error.

    NATS_TIMEOUT,                       ///< An operation timed-out. For instance
                                        ///  #natsSubscription_NextMsg().

    NATS_FAILED_TO_INITIALIZE,          ///< The library failed to initialize.
    NATS_NOT_INITIALIZED,               ///< The library is not yet initialized.

    NATS_SSL_ERROR,                     ///< An SSL error occurred when trying to establish a
                                        ///  connection.

    NATS_NO_SERVER_SUPPORT,             ///< The server does not support this action.

    NATS_NOT_YET_CONNECTED,             ///< A connection could not be immediately established and
                                        ///  #natsOptions_SetRetryOnFailedConnect() specified
                                        ///  a connected callback. The connect is retried asynchronously.

    NATS_DRAINING,                      ///< A connection and/or subscription entered the draining mode.
                                        ///  Some operations will fail when in that mode.

    NATS_INVALID_QUEUE_NAME,            ///< An invalid queue name was passed when creating a queue subscription.

    NATS_NO_RESPONDERS,                 ///< No responders were running when the server received the request.

    NATS_MISMATCH,                      ///< For JetStream subscriptions, it means that a consumer sequence mismatch was discovered.

    NATS_MISSED_HEARTBEAT,              ///< For JetStream subscriptions, it means that the library detected that server heartbeats have been missed.
	};

	return(std::pair<natsStatus, natsStatus>(
		*NatsStatusSet.begin(), *NatsStatusSet.rbegin()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
natsStatus GetNatsStatusMin()
{
	return(GetNatsStatusRange().first);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
natsStatus GetNatsStatusMax()
{
	return(GetNatsStatusRange().second);
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
std::string NatsExceptionStatus::GetStatusString(const std::string &src_text,
	natsStatus nats_code)
{
	const char *nats_text =
		((nats_code >= GetNatsStatusMin()) && (nats_code <= GetNatsStatusMax()))?
		::natsStatus_GetText(nats_code) : nullptr;

	nats_text = (nats_text && *nats_text) ? nats_text : "*UNKNOWN-NATS-TEXT*";

	std::string status_string(((!src_text.empty()) ? src_text :
		std::string("Unspecified error occurred")) + ": NATS error code " +
		std::to_string(nats_code) + " (\"" + std::string(nats_text) +"\").");

	return(status_string);
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

#include <iomanip>
#include <iostream>

namespace {

// ////////////////////////////////////////////////////////////////////////////
void TEST_NatsExceptionStatus()
{
	using namespace MLB::NatsWrapper;

	for (int nats_code = -1; nats_code < 100; ++nats_code) {
		try {
			throw NatsExceptionStatus(
				std::string("Test natsStatus = ") + std::to_string(nats_code),
				static_cast<natsStatus>(nats_code));
		}
		catch (const std::exception &except) {
			std::cout << "RESULTS FOR NATS CODE = " << std::setw(3) <<
				nats_code << ": " << except.what() << '\n';
		}
	}

	std::cout << "*** MIN=" << GetNatsStatusMin()
		<< "MAX=" << GetNatsStatusMax() << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		TEST_NatsExceptionStatus();
	}
	catch (const std::exception &except) {
		return_code = EXIT_FAILURE;
		std::cerr << "\n\nERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

