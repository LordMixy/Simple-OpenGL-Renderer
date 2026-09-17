#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string_view>

namespace Utils 
{
	enum class LogLevel 
	{
		TRACE, 
		DEBUG, 
		INFO,
		WARN, 
		ERROR,
		FATAL	
	};
	
	void log(const std::string& msg, const LogLevel& level);
	std::string readFileContent(const std::string& filePath);
}

#endif // UTILS_HPP
