#ifndef CORE_H
#define CORE_H

#ifdef PPR_PLATFORM_WINDOWS
	#ifdef PPR_BUILD_DLL
			#define PAPYRUS_API __declspec(dllexport)
		#else
			#define PAPYRUS_API __declspec(dllimport)
	#endif 
#elif defined(PPR_PLATFORM_LINUX)
	#ifdef PPR_BUILD_DLL
		#define PAPYRUS_API __attribute__((visibility("default")))
	#else
		#define PAPYRUS_API
	#endif
#else
	#error Papyrus only supports Windows and Linux.
#endif
#endif


#define BIT(x) (1 << x)

