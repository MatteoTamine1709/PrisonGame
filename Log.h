#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "HUD.h"
enum LogLevel_e {
	All = 4,
	Info = 3,
	Warning = 2,
	Error = 1,
	None = 0
};

class Log
{
private:
	int m_logLevel = LogLevel_e::Info;
public:
	void setLogLevel(LogLevel_e level);
	void setLogLevel(int level);
	void All(const std::string& str);
	void Info(const std::string& str);
	void Warn(const std::string& str);
	void Error(const std::string& str);
	bool LogIf(LogLevel_e level);
};
extern Log LOG;