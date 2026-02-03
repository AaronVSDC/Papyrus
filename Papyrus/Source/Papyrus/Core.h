#ifndef CORE_H
#define CORE_H

#ifdef PPR_PLATFORM_WINDOWS
	#ifdef PPR_BUILD_DLL
			#define PAPYRUS_API __declspec(dllexport)
		#else
			#define PAPYRUS_API __declspec(dllimport)
	#endif 
#else
	#error Papyrus only supports Windows.
#endif







#endif