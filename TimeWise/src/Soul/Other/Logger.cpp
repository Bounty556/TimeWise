#include "Logger.h"

#include <iostream>
#include <stdarg.h>

namespace Soul
{
	Logger::LogLevel Logger::m_LogLevel = Logger::LogLevel::Info;

	void Logger::LogError(const char* message, ...)
	{
		if (m_LogLevel >= LogLevel::Error)
		{
			va_list arglist;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hConsole, 4);
			va_start(arglist, message);
			std::vprintf(message, arglist);
			va_end(arglist);
		}
	}

	void Logger::LogWarning(const char* message, ...)
	{
		if (m_LogLevel >= LogLevel::Warning)
		{
			va_list arglist;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hConsole, 14);
			va_start(arglist, message);
			std::vprintf(message, arglist);
			va_end(arglist);
		}
	}

	void Logger::LogInfo(const char* message, ...)
	{
		if (m_LogLevel >= LogLevel::Info)
		{
			va_list arglist;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hConsole, 15);
			va_start(arglist, message);
			std::vprintf(message, arglist);
			va_end(arglist);
		}
	}

	void Logger::SetLogLevel(Logger::LogLevel level)
	{
		m_LogLevel = level;
	}
}