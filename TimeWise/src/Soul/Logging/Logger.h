#pragma once

#include <Windows.h>

namespace Soul
{
	/*
	The Logger is used to print color-coded debug information out to
	the console. There are three log levels: Error, Warning, and
	Info. Setting a lighter log level (Warning, Info) will show the
	heavier log levels (Error, Warning).

	By default the log level is set to Info, so all logs are shown.
	You can change the log level with SetLogLevel().

	The LogError(), LogWarning(), and LogInfo() functions should
	not be used. Rather, the SoulLogError, SoulLogWarning and
	SoulLogInfo macros should be used to log.
	*/
	class Logger
	{
	public:
		/*
		Determines which messages the logger prints and which
		messages it ignores.
		*/
		enum LogLevel
		{
			Error = 1,
			Warning = 2,
			Info = 4
		};

	public:
		Logger() = delete;

		/*
		Logs an error to the console, with red text for 
		distinguishability.
		*/
		static void LogError(const char* message, ...);

		/*
		Logs a warning to the console, with yellow text for
		distinguishability.
		*/
		static void LogWarning(const char* message, ...);

		/*
		Logs info to the console, with white text for
		distinguishability.
		*/
		static void LogInfo(const char* message, ...);

		/*
		Sets which messages the log will output to the console, and
		which messages will be ignored.
		*/
		static void SetLogLevel(LogLevel level);

	private:
		static LogLevel m_LogLevel;
	};
}

#define SoulLogError(message, ...) (Logger::LogError("[Error]: " message "\n", ##__VA_ARGS__))
#define SoulLogWarning(message, ...) (Logger::LogWarning("[Warning]: " message "\n", ##__VA_ARGS__))
#define SoulLogInfo(message, ...) (Logger::LogInfo("[Info]: " message "\n", ##__VA_ARGS__))