#pragma once
#include <string>
#include <fstream>
#include <cassert>


#define INFO_LOG { neko::g_logger.log(neko::LogLevel::Info, __FILE__, __LINE__); }
#define WARNING_LOG { neko::g_logger.log(neko::LogLevel::Warning, __FILE__, __LINE__); }
#define ERROR_LOG { neko::g_logger.log(neko::LogLevel::Error, __FILE__, __LINE__); }
#define ASSERT_LOG { neko::g_logger.log(neko::LogLevel::Assert, __FILE__, __LINE__); }

namespace neko {
	enum class LogLevel {
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger {
	public:
		Logger(LogLevel logLevel, std::ostream* ostream) :
			m_logLevel{ logLevel },
			m_ostream{ ostream }
		{}

		bool log(LogLevel logLevel, const std::string filename, int line);

	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	extern Logger g_logger;

}
