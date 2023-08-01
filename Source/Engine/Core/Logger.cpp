#include "Logger.h"
#include <iostream>
#include "FileIO.h"

namespace neko {
	
	Logger g_logger(LogLevel::Info, &std::cout);

	bool Logger::log(LogLevel logLevel, const std::string filename, int line) {
		if (logLevel < m_logLevel) return false;

		switch (m_logLevel)
		{
		case LogLevel::Info:
			*m_ostream << "INFO: ";
			break;

		case LogLevel::Warning:
			*m_ostream << "WARNING: ";
			break;

		case LogLevel::Error:
			*m_ostream << "ERROR: ";
			break;

		case LogLevel::Assert:
			*m_ostream << "ASSERT: ";
			break;

		default:
			break;
		}

		*m_ostream << filename << "(" << line << ")\n";

		return false;
	}
}