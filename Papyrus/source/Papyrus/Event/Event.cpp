#include "Event.h"


namespace Papyrus
{
	void Event::setArgFloat(HashedString name, float value, DebugName debugName)
	{
		PPR_ASSERT(m_NumArgs < MAX_EVENT_ARGS, "Event exceeded MAX_EVENT_ARGS."); 

		if (m_NumArgs >= MAX_EVENT_ARGS)
			return; 

		EventArg& arg = m_Args[m_NumArgs++]; 
		arg.name = name;
		arg.type = ArgType::Float; 
		arg.debugName = debugName;
		arg.f = value; 

	}

	void Event::setArgInt(HashedString name, uint32_t value, DebugName debugName)
	{
		PPR_ASSERT(m_NumArgs < MAX_EVENT_ARGS, "Event exceeded MAX_EVENT_ARGS."); 

		if (m_NumArgs >= MAX_EVENT_ARGS)
			return; 

		EventArg& arg = m_Args[m_NumArgs++]; 
		arg.name = name;
		arg.type = ArgType::Int32; 
		arg.debugName = debugName;
		arg.i = value; 
	}

	void Event::setArgBool(HashedString name, bool value, DebugName debugName)
	{
		PPR_ASSERT(m_NumArgs < MAX_EVENT_ARGS, "Event exceeded MAX_EVENT_ARGS.");

		if (m_NumArgs >= MAX_EVENT_ARGS)
			return;

		EventArg& arg = m_Args[m_NumArgs++];
		arg.name = name;
		arg.type = ArgType::Bool;
		arg.debugName = debugName;
		arg.i = value;
	}

	float Event::getArgFloat(HashedString name) const
	{
		for (uint8_t index = 0; index < m_NumArgs; ++index)
		{
			if (m_Args[index].name == name)
			{
				PPR_ASSERT(m_Args[index].type == ArgType::Float, "Arg type mismatch."); 
				return m_Args[index].f; 
			}
		}
		PPR_ASSERT(false, "Arg key not found."); 
		return 0.f; 
	}

	uint32_t Event::getArgInt(HashedString name) const
	{
		for (uint8_t index = 0; index < m_NumArgs; ++index)
		{
			if (m_Args[index].name == name)
			{
				PPR_ASSERT(m_Args[index].type == ArgType::Int32, "Arg type mismatch.");
				return m_Args[index].i;
			}
		}
		PPR_ASSERT(false, "Arg key not found.");
		return 0; 
	}

	bool Event::getArgBool(HashedString name) const
	{
		for (uint8_t index = 0; index < m_NumArgs; ++index)
		{
			if (m_Args[index].name == name)
			{
				PPR_ASSERT(m_Args[index].type == ArgType::Bool, "Arg type mismatch.");
				return m_Args[index].b;
			}
		}
		PPR_ASSERT(false, "Arg key not found.");
		return false;
	}

	std::string Event::toDebugString() const
	{
		std::string result = m_DebugName.name ? m_DebugName.name : "UnknownEvent";

		for (uint8_t i = 0; i < m_NumArgs; ++i)
		{
			const EventArg& arg = m_Args[i];
			std::string keyName = arg.debugName.name ? arg.debugName.name : "?";

			result += " " + keyName + "=";
			switch (arg.type)
			{
				case ArgType::Float:
					result += std::to_string(arg.f);
					break;
				case ArgType::Int32:
					result += std::to_string(arg.i);
					break;
				case ArgType::Bool:
					result += arg.b ? "true" : "false";
					break;
			}
		}

		return result;
	}


}


