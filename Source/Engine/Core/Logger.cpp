#include "Logger.h"
#include <iostream>
#include "FileIO.h"

namespace neko {
	
	Logger g_logger(LogLevel::Info, &std::cout, "log.txt");

	bool Logger::log(LogLevel logLevel, const std::string filename, int line) {
		if (logLevel < m_logLevel) return false;

		switch (m_logLevel)
		{
		case LogLevel::Info:
			*this << "INFO: ";
			break;

		case LogLevel::Warning:
			*this << "WARNING: ";
			break;

		case LogLevel::Error:
			*this << "ERROR: ";
			break;

		case LogLevel::Assert:
			*this << "ASSERT: ";
			break;

		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";

		return true;
	}
}