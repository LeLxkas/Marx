#include "mxpch.h"

#include "Log.h"

namespace Marx
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::init()
	{
		// Pattern: "[currentTime] [shortLogLevel] loggerName: textToLog"
		spdlog::set_pattern("%^[%T] [%L] %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("MARX");
		s_coreLogger->set_level(spdlog::level::trace);
		s_clientLogger = spdlog::stdout_color_mt("App");
		s_clientLogger->set_level(spdlog::level::trace);
	}
}