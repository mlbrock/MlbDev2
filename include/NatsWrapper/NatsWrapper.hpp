// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB NatsWrapper Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  NatsWrapper.hpp

   File Description  :  Include file for the NatsWrapper library.

   Revision History  :  2024-08-17 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__NatsWrapper__NatsWrapper_hpp__HH

#define HH__MLB__NatsWrapper__NatsWrapper_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file NatsWrapper.hpp

   \brief   Main include file for the NatsWrapper library.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <nats.h>

#include <stdexcept>
#include <string>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace NatsWrapper {

// ////////////////////////////////////////////////////////////////////////////
/*
{
	natsStatus nats_code;

	if ((nats_code = nats_Open(1000)) == NATS_OK) {
		natsOptions *nats_opts = NULL;
		if ((nats_code = natsOptions_Create(&nats_opts)) == NATS_OK) {
			natsConnection *nats_conn = NULL;
			if ((nats_code = natsConnection_Connect(&nats_conn, nats_ops)) ==
				NATS_OK) {
				const char *subject_name = "foo";
				const char *message_data = "MLB Test Message";
				if ((nats_code = natsConnection_Publish(nats_conn, subject_name,
					static_cast<const void *>(message_data),
					static_cast<int>(::strlem(message_data)))) == NATS_OK) {
					if ((nats_code = natsConnection_FlushTimeout(nats_conn,
						1000)) == NATS_OK)
						std::cout << "Flushed message\n";
					else
						std::cerr << "ERROR: natsConnection_FlushTimeout()\n";
				}
				else
					std::cerr << "ERROR: natsConnection_Publish()\n";
				natsConnection_Close(nats_conn);
				natsConnection_Destroy(nats_conn);
			}
			else
				std::cerr << "ERROR: natsConnection_Connect()\n";
			natsOptions_Destroy(nats_opts);
		}
		else
			std::cerr << "ERROR: natsOptions_Create()\n";
		nats_Close();
	}
	else
		std::cerr << "ERROR: nats_Open()\n";
}
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class MB_LIB_EXCEPTION_CLASS(API_NATSWRAPPER) NatsExceptionStatus :
	public std::runtime_error
{
public:
	NatsExceptionStatus();
	NatsExceptionStatus(const std::string &error_text);
	NatsExceptionStatus(natsStatus nats_code, const char *func_name);

	virtual ~NatsExceptionStatus();

/*
	virtual const char *what() noexcept;
*/

	natsStatus GetNatsStatus() const;

private:
	natsStatus nats_code_;

	static std::string GetStatusString(natsStatus nats_code,
		const char *func_name);
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

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
	const char *func_name)
	:std::runtime_error(GetStatusString(nats_code, func_name))
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
	const char *func_name)
{
	func_name = (func_name && *func_name) ? func_name : "*UNKNOWN-FUNCTION*";

	std::string status_string("NATS error code " + std::to_string(nats_code) +
		" was encountered in function " + std::string(func_name) + "().");

	return(status_string);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
#define NatsWrapper_THROW_STRING_NAME(method_name)						\
	{																					\
		std::ostringstream INTERNAL_error_text;							\
		INTERNAL_error_text << "Invocation of '" << method_name <<	\
			"()' failed";															\
		throw NatsExceptionStatus(INTERNAL_error_text.str());			\
	}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
#define NatsWrapper_THROW_IF_NOT_OK(method_name, method_args)						\
	{																									\
		natsStatus INTERNAL_nats_error_code = method_name method_args ;			\
		if (INTERNAL_nats_error_code != NATS_OK) {										\
			throw NatsExceptionStatus(INTERNAL_nats_error_code, #method_name);	\
		}																								\
	}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
#define NatsWrapper_THROW_IF_NOT_OK_OR_TIMEOUT(method_name, method_args)		\
	{																									\
		natsStatus INTERNAL_nats_error_code = method_name method_args ;			\
		if ((INTERNAL_nats_error_code != NATS_OK) &&										\
			 (INTERNAL_nats_error_code != NATS_TIMEOUT)) {								\
			throw NatsExceptionStatus(INTERNAL_nats_error_code, #method_name);	\
		}																								\
	}
// ////////////////////////////////////////////////////////////////////////////

} // namespace NatsWrapper

} // namespace MLB

#endif // #ifndef HH__MLB__NatsWrapper__NatsWrapper_hpp__HH

