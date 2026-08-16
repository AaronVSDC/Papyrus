#ifndef LOG_H
#define LOG_H

//std
#include <memory>

#include "Core/Core.h"
#include "spdlog/spdlog.h"

namespace Papyrus
{
	class PAPYRUS_API Log 
	{
	public:  

		Log(Log&) = delete; 
		Log(Log&&) = delete; 
		Log& operator=(Log&) = delete; 
		Log& operator=(Log&&) = delete;

		static void init(); 

		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger;  }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger;  }

	private: 

		static std::shared_ptr<spdlog::logger> s_CoreLogger; 
		static std::shared_ptr<spdlog::logger> s_ClientLogger; 

	};
}



#if defined PPR_DEBUG
	
	#define PPR_LOG_INIT ::Papyrus::Log::init()

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

	// do while(0) is a little trick to avoid logical collisions with the client when the macro expands, 
	// ex the client does something like this:
	// if(x) 
	//    PPR_CORE_CRITICAL_COND(y, "error"); 
	// else
	//    doSomething(); 

	#define PPR_CORE_CRITICAL_COND(condition,...) do {if((condition)) ::Papyrus::Log::getCoreLogger()->critical(__VA_ARGS__);} while(0)
	#define PPR_CORE_ERROR_COND(condition, ...)   do {if((condition)) ::Papyrus::Log::getCoreLogger()->error(__VA_ARGS__);}    while(0)
	#define PPR_CORE_WARN_COND(condition, ...)    do {if((condition)) ::Papyrus::Log::getCoreLogger()->warn(__VA_ARGS__);}     while(0)
	#define PPR_CORE_TRACE_COND(condition, ...)   do {if((condition)) ::Papyrus::Log::getCoreLogger()->trace(__VA_ARGS__);}    while(0)
	#define PPR_CORE_INFO_COND(condition, ...)    do {if((condition)) ::Papyrus::Log::getCoreLogger()->info(__VA_ARGS__);}     while(0)

	#define PPR_CRITICAL_COND(condition,...)      do {if((condition)) ::Papyrus::Log::getClientLogger()->critical(__VA_ARGS__);} while(0)
	#define PPR_ERROR_COND(condition, ...)        do {if((condition)) ::Papyrus::Log::getClientLogger()->error(__VA_ARGS__);}    while(0)
	#define PPR_WARN_COND(condition, ...)         do {if((condition)) ::Papyrus::Log::getClientLogger()->warn(__VA_ARGS__);}     while(0)
	#define PPR_TRACE_COND(condition, ...)        do {if((condition)) ::Papyrus::Log::getClientLogger()->trace(__VA_ARGS__);}    while(0)
	#define PPR_INFO_COND(condition, ...)         do {if((condition)) ::Papyrus::Log::getClientLogger()->info(__VA_ARGS__);}     while(0)

#endif

#if defined PPR_RELEASE

	#define PPR_LOG_INIT 
	#define PPR_CORE_CRITICAL 
	#define PPR_CORE_ERROR    
	#define PPR_CORE_WARN     
	#define PPR_CORE_TRACE
	#define PPR_CORE_INFO

	#define PPR_CRITICAL
	#define PPR_ERROR    
	#define PPR_WARN	       
	#define PPR_TRACE	       
	#define PPR_INFO	     

	#define PPR_CORE_CRITICAL_COND
	#define PPR_CORE_ERROR_COND  
	#define PPR_CORE_WARN_COND    
	#define PPR_CORE_TRACE_COND
	#define PPR_CORE_INFO_COND

	#define PPR_CRITICAL_COND
	#define PPR_ERROR_COND   
	#define PPR_WARN_COND	       
	#define PPR_TRACE_COND       
	#define PPR_INFO_COND	     


#endif



#endif

