#include "EventListener.h"
#include "EventSystem.h"

namespace Papyrus
{
	EventListener::~EventListener()
	{
		EventSystem::unsubscribeAll(this); 
	}

}


