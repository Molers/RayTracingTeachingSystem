#include "Precompile.h"
#include "log.h"


namespace Molers
{
	std::shared_ptr<spdlog::logger> log::s_Corelogger;
	std::shared_ptr<spdlog::logger> log::s_Clientlogger;

	
	void log::Init()
	{
		spdlog::set_pattern("%^[%T] %n :%v%$");
		s_Corelogger = spdlog::stdout_color_mt("Molers");
		s_Corelogger->set_level(spdlog::level::trace);

		s_Clientlogger = spdlog::stdout_color_mt("APP");
		s_Clientlogger->set_level(spdlog::level::trace);

	}

}

