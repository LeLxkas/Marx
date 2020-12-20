#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Marx
{

	class MARX_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }
	private:
		DISABLE_DLL_INTERFACE_WARN;
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
		REENABLE_DLL_INTERFACE_WARN;
	};

}


// Core log macros
#define MX_CORE_TRACE(...)    ::Marx::Log::getCoreLogger()->trace(__VA_ARGS__)
#define MX_CORE_INFO(...)     ::Marx::Log::getCoreLogger()->info(__VA_ARGS__)
#define MX_CORE_WARN(...)     ::Marx::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MX_CORE_ERROR(...)    ::Marx::Log::getCoreLogger()->error(__VA_ARGS__)
#define MX_CORE_CRITICAL(...)    ::Marx::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MX_TRACE(...)    ::Marx::Log::getClientLogger()->trace(__VA_ARGS__)
#define MX_INFO(...)     ::Marx::Log::getClientLogger()->info(__VA_ARGS__)
#define MX_WARN(...)     ::Marx::Log::getClientLogger()->warn(__VA_ARGS__)
#define MX_ERROR(...)    ::Marx::Log::getClientLogger()->error(__VA_ARGS__)
#define MX_CRITICAL(...)    ::Marx::Log::getClientLogger()->critical(__VA_ARGS__)