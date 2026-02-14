#ifndef LOG_H
#define LOG_H

//std
#include <memory>

#include "Core.h"
#include "spdlog\spdlog.h" 

namespace Papyrus
{
	class PAPYRUS_API Log 
	{
	public:  
		static void init(); 

		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger;  }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger;  }

	private: 

		static std::shared_ptr<spdlog::logger> s_CoreLogger; 
		static std::shared_ptr<spdlog::logger> s_ClientLogger; 

	};
}

//todo: redefine these for release builds so that logging gets removed in release.

#define PPR_CORE_CRITICAL(...) ::Papyrus::Log::getCoreLogger()->critical(__VA_ARGS__)  
#define PPR_CORE_ERROR(...)    ::Papyrus::Log::getCoreLogger()->error(__VA_ARGS__)
#define PPR_CORE_WARN(...)     ::Papyrus::Log::getCoreLogger()->warn(__VA_ARGS__) 
#define PPR_CORE_TRACE(...)    ::Papyrus::Log::getCoreLogger()->trace(__VA_ARGS__)  
#define PPR_CORE_INFO(...)     ::Papyrus::Log::getCoreLogger()->info(__VA_ARGS__) 
									   
#define PPR_CRITICAL(...)	   ::Papyrus::Log::getClientLogger()->critical(__VA_ARGS__)
#define PPR_ERROR(...)	       ::Papyrus::Log::getClientLogger()->error(__VA_ARGS__)
#define PPR_WARN(...)	       ::Papyrus::Log::getClientLogger()->warn(__VA_ARGS__) 
#define PPR_TRACE(...)	       ::Papyrus::Log::getClientLogger()->trace(__VA_ARGS__) 
#define PPR_INFO(...)	       ::Papyrus::Log::getClientLogger()->info(__VA_ARGS__)



#endif

