#ifndef PAPYRUSENGINE_EVENT_LISTENER_H
#define PAPYRUSENGINE_EVENT_LISTENER_H
#include "Papyrus/Core/Core.h"
#include "Papyrus/Event/Event.h"

namespace Papyrus
{
	class PAPYRUS_API EventListener 
	{
	public: 
		virtual ~EventListener(); 
		virtual void onEvent(Event& e) = 0; 

	protected: 
		EventListener() = default; 

	};
}

#endif