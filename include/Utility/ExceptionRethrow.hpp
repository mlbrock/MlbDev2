// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	ExceptionRethrow.hpp

	File Description	:	Include file for utility library.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock
                        2023-01-04 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

		Copyright Michael L. Brock 1998 - 2023.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


#ifndef HH__MLB__Utility__ExceptionRethrow_hpp__HH

#define HH__MLB__Utility__ExceptionRethrow_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file ExceptionRethrow.hpp

	\brief	The MLB Utility exception rethrow header file.

   Contains logic for rethrowing exceptions with altered what() strings.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility.hpp>

#include <exception>
#include <stdexcept>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
template <typename ExceptType> void Rethrow(const ExceptType &,
	const char *except_string)
{
	// Way of disambiguating std::exception without a dynamic_cast<>.
	try {
		throw;
	}
/*
	catch (const ExceptionGeneral &tmp_except) {
		RethrowExceptionGeneral(tmp_except, except_string);
	}
*/
	catch (const std::domain_error &) {
		throw std::domain_error(except_string);
	}
	catch (const std::invalid_argument &) {
		throw std::invalid_argument(except_string);
	}
	catch (const std::length_error &) {
		throw std::length_error(except_string);
	}
	catch (const std::out_of_range &) {
		throw std::out_of_range(except_string);
	}
	catch (const std::logic_error &) {
		throw std::logic_error(except_string);
	}
	catch (const std::overflow_error &) {
		throw std::overflow_error(except_string);
	}
	catch (const std::underflow_error &) {
		throw std::underflow_error(except_string);
	}
	catch (const std::range_error &) {
		throw std::range_error(except_string);
	}
	catch (const std::runtime_error &) {
		throw std::runtime_error(except_string);
	}
	catch (const std::bad_alloc &) {
#if defined(_MSC_VER) && !defined(__MINGW32__) && (_MSC_VER < 1700)
		// Because P. J. and Pete provided a ctor taking a const char *...
		throw std::bad_alloc(except_string);
#else
		throw;
#endif // #if defined(_MSC_VER) && !defined(__MINGW32__) && (_MSC_VER < 1700)
	}
	catch (const std::bad_exception &) {
#if defined(_MSC_VER) && !defined(__MINGW32__) && (_MSC_VER < 1900)
		// Because P. J. and Pete provided a ctor taking a const char *...
		throw std::bad_exception(except_string);
#else
		throw;
#endif // #if defined(_MSC_VER) && !defined(__MINGW32__) && (_MSC_VER < 1900)
	}
	catch (const std::exception &) {
#if defined(_MSC_VER) && !defined(__MINGW32__)
		// Because P. J. and Pete provided a ctor taking a const char *...
		throw std::exception(except_string);
#else
		throw;
#endif // #if defined(_MSC_VER) && !defined(__MINGW32__)
	}
#if defined(_MSC_VER) && (_MSC_VER >= 1500)
# pragma warning(push)
# pragma warning(disable: 4571)
#endif // #if defined(_MSC_VER) && (_MSC_VER >= 1500)
	catch (...) {
		throw;
	}
#if defined(_MSC_VER) && (_MSC_VER >= 1500)
# pragma warning(pop)
#endif // #if defined(_MSC_VER) && (_MSC_VER >= 1500)
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename ExceptType> void Rethrow(const ExceptType &except,
	const std::string &except_string)
{
	Rethrow(except, except_string.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__ExceptionRethrow_hpp__HH

