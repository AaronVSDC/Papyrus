#ifndef PAPYRUSENGINE_TIME_H
#define PAPYRUSENGINE_TIME_H

#include "Papyrus/Core/Core.h"


namespace Papyrus
{
	class PAPYRUS_API Time final
	{
	public:
		Time() = delete;
		Time(const Time&) = delete;
		Time& operator=(const Time&) = delete;
		Time(Time&&) = delete;
		Time& operator=(Time&&) = delete;


		static float deltaTime() noexcept { return static_cast<float>(s_DeltaTime);  }
		static double deltaTimeD() noexcept { return s_DeltaTime;  }

		static double totalTime() noexcept { return s_TotalTime; }

	private: 
		static inline double s_DeltaTime;
		static inline double s_TotalTime;

		static void update(double deltaTime);

		friend class Application; 

	};
}



#endif