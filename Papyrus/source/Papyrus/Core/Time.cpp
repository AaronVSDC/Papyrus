#include "Time.h"

namespace Papyrus
{
	void Time::update(double deltaTime)
	{
		s_DeltaTime = deltaTime; 
		s_TotalTime += deltaTime; 
	}
}