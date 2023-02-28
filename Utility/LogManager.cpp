// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  LogManager.cpp

   File Description  :  Implementation of logging management.

   Revision History  :  1993-10-02 --- Creation of predecessor 'mlog' facility.
                           Michael L. Brock
                        2005-01-02 --- New ostream-based log model.
                           Michael L. Brock
                        2023-01-05 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1993 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////
 
// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/LogManager.hpp>

#include <Utility/ExceptionRethrow.hpp>

#include <fstream>
#include <iostream>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
LogLevelPair LogManager::GetLogLevelConsole() const
{
	return(LogLevelFlagsToLevels(log_level_screen_));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LogLevelPair LogManager::GetLogLevelFile() const
{
	return(LogLevelFlagsToLevels(log_level_persistent_));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LogLevelPair LogManager::SetLogLevelConsole(LogLevel min_log_level,
	LogLevel max_log_level)
{
	LogLockScoped my_lock(the_lock_);
	LogLevelPair  old_levels(GetLogLevelConsole());

	log_level_screen_ = GetLogLevelMask(min_log_level, max_log_level);

	return(old_levels);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LogLevelPair LogManager::SetLogLevelFile(LogLevel min_log_level,
	LogLevel max_log_level)
{
	LogLockScoped my_lock(the_lock_);
	LogLevelPair  old_levels(GetLogLevelFile());

	log_level_persistent_ = GetLogLevelMask(min_log_level, max_log_level);

	return(old_levels);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LogHandlerConsole::LogHandlerConsole()
	:LogHandler()
	,the_lock_()
	,iostreams_init_()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LogHandlerConsole::~LogHandlerConsole()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void LogHandlerConsole::InstallHandler()
{
	LogLockScoped my_lock(the_lock_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void LogHandlerConsole::RemoveHandler()
{
	LogLockScoped my_lock(the_lock_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void LogHandlerConsole::EmitLine(const LogEmitControl &emit_control)
{
	if (emit_control.ShouldLogScreen()) {
		LogLockScoped my_lock(the_lock_);
		emit_control.UpdateTime();
		std::cout.write(emit_control.GetLeaderPtr(),
			static_cast<std::streamsize>(emit_control.GetLeaderLength()));
		std::cout.write(emit_control.line_buffer_.c_str(),
			static_cast<std::streamsize>(emit_control.line_buffer_.size()));
		std::cout << std::endl;
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void LogHandlerConsole::EmitLiteral(unsigned int literal_length,
	const char *literal_string)
{
	LogLockScoped my_lock(the_lock_);

	std::cout.write(literal_string, static_cast<std::streamsize>(literal_length));
	std::cout << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void LogHandlerConsole::EmitLiteral(const LogEmitControl &emit_control,
	unsigned int literal_length, const char *literal_string)
{
	if (emit_control.ShouldLogScreen())
		EmitLiteral(literal_length, literal_string);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LogStream::~LogStream()
{
	try {
		LogLockScoped my_lock(the_lock_);
		thread_stream_map_.clear();
	}
	catch (const std::exception &) {
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void LogStream::LogSeparator(char sep_char, unsigned int text_length)
{
	GetThreadStream()->GetBufferPtrRef()->LogSeparator(sep_char, text_length);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LogStream::ThreadStreamPtr LogStream::GetThreadStream()
{
	LogLockScoped       my_lock(the_lock_);
	ThreadId            thread_id(CurrentThreadId());
	ThreadStreamMapIter iter_f(thread_stream_map_.find(thread_id));

	if (iter_f != thread_stream_map_.end())
		return(iter_f->second);

	ThreadStreamBufferPtr buffer_ptr(
									new ThreadStreamBuffer(manager_ref_, log_level_));
	ThreadStreamPtr       ostream_ptr(
									new ThreadStream(manager_ref_, log_level_,
									buffer_ptr));

	thread_stream_map_[thread_id] = ostream_ptr;

	return(ostream_ptr);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

// ////////////////////////////////////////////////////////////////////////////
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

#include <Utility/LogHandlerFile.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/LogTestSupport.hpp>

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	using namespace MLB::Utility;

	int return_code = EXIT_SUCCESS;

	try {
		//	Create a LogHandlerFile...
		LogHandlerPtr my_log_handler(
			new LogHandlerFile("TestLogFile.VERSION_OLD_001.log"));
		TEST_TestControl(my_log_handler, false);
	}
	catch (const std::exception &except) {
		std::cerr << std::endl << std::endl << "ERROR: " << except.what() <<
			std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN
