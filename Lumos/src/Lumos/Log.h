#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include<spdlog/fmt/ostr.h>


namespace Lumos {
	class LUMOS_API Log
	{
	public: 
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


//Core logging macros
#define LOG_CORE_TRACE(...) Lumos::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...) Lumos::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...) Lumos::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) Lumos::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) Lumos::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client logging macros
#define LOG_TRACE(...) Lumos::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) Lumos::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Lumos::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Lumos::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Lumos::Log::GetClientLogger()->critical(__VA_ARGS__)


