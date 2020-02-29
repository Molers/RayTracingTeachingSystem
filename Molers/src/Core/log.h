#pragma once

//#include <memory>

#include "Core.h"
#include <spdlog/spdlog.h>

#include "spdlog/fmt/ostr.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Molers {
	class MOLERS_API log
	{
	public :
	
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_Corelogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_Clientlogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Corelogger;
		static std::shared_ptr<spdlog::logger> s_Clientlogger;
	};
	
}
//日志函数宏定义 简写

//Core log macros
#define MOLERS_CORE_ERROR(...)	::Molers::log::GetCoreLogger()->error(__VA_ARGS__)
#define MOLERS_CORE_WARN(...)	::Molers::log::GetCoreLogger()->warn(__VA_ARGS__)
#define MOLERS_CORE_INFO(...)	::Molers::log::GetCoreLogger()->info(__VA_ARGS__)
#define MOLERS_CORE_TRACE(...)	::Molers::log::GetCoreLogger()->trace(__VA_ARGS__)
#define MOLERS_CORE_FATAL(...)	::Molers::log::GetCoreLogger()->fatal(__VA_ARGS__)


//Client log macros
#define MOLERS_ERROR(...)	::Molers::log::GetClientLogger()->error(__VA_ARGS__)
#define MOLERS_WARN(...)	::Molers::log::GetClientLogger()->warn(__VA_ARGS__)
#define MOLERS_INFO(...)	::Molers::log::GetClientLogger()->info(__VA_ARGS__)
#define MOLERS_TRACE(...)	::Molers::log::GetClientLogger()->trace(__VA_ARGS__)
#define MOLERS_FATAL(...)	::Molers::log::GetClientLogger()->fatal(__VA_ARGS__)