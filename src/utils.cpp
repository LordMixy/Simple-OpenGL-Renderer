#include "../include/utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#define WHITE_COLOR  "\033[37m"
#define GREEN_COLOR  "\033[92m"
#define CYAN_COLOR   "\033[36m"
#define YELLOW_COLOR "\033[33m"
#define RED_COLOR    "\033[31m"
#define BRED_COLOR   "\e[1;91m"
#define COLOR_RESET  "\e[0m"

void Utils::log(const std::string& msg, const LogLevel& level)
{
	std::string logLevel;
	switch (level) {
		case LogLevel::TRACE: 
			logLevel = WHITE_COLOR "[TRACE]" COLOR_RESET;
			break;
		case LogLevel::DEBUG: 
			logLevel = GREEN_COLOR "[DEBUG]" COLOR_RESET;
			break;
		case LogLevel::INFO: 
			logLevel = CYAN_COLOR "[INFO]" COLOR_RESET;
			break;
		case LogLevel::WARN: 
			logLevel = YELLOW_COLOR "[WARN]" COLOR_RESET; 
			break;
		case LogLevel::ERROR: 
			logLevel = RED_COLOR "[ERROR]" COLOR_RESET; 
			break;
		case LogLevel::FATAL: 
			logLevel = BRED_COLOR "[FATAL]" COLOR_RESET; 
			break;
	}		
	std::cout << logLevel << " " << msg << std::endl;
}

std::string Utils::readFileContent(const std::string& filePath)
{
	std::ifstream fileStream(filePath);

	std::stringstream buffer;
	buffer << fileStream.rdbuf();

	fileStream.close();
	return buffer.str();
}
