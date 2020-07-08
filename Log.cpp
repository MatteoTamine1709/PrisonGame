#include "Log.h"
#include <iostream>

void Log::setLogLevel(LogLevel_e level)
{
	m_logLevel = level;
}

void Log::setLogLevel(int level)
{
	m_logLevel = static_cast<LogLevel_e>(level);
}

void Log::All(const std::string& str)
{
	if (m_logLevel >= LogLevel_e::All)
		std::cout << "[ALL] : " << str << "\n";
}

void Log::Info(const std::string& str)
{
	if (m_logLevel >= LogLevel_e::Info)
		std::cout << "[INFO] : " << str << "\n";
}

void Log::Warn(const std::string& str)
{
	if (m_logLevel >= LogLevel_e::Warning)
		std::cout << "[WARNING] : " << str << "\n";
}
void Log::Error(const std::string& str)
{
	if (m_logLevel >= LogLevel_e::Error)
		std::cout << "[ERROR] : " << str << "\n";
}

bool Log::LogIf(LogLevel_e level)
{
	return (level <= m_logLevel);
}
