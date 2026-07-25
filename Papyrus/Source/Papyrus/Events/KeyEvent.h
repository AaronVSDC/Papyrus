#ifndef KEY_EVENT_H
#define KEY_EVENT_H
#include "Event.h"

namespace Papyrus
{

	class Keyevent : public Event
	{
	public: 
		KeyCode getKeyCode() const { return m_KeyCode;  }



	};



}

#endif