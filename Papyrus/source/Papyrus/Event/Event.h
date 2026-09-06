#ifndef PAPYRUSENGINE_EVENT_H
#define PAPYRUSENGINE_EVENT_H
#include "Papyrus/Core/Core.h"
#include "Papyrus/Utils/StringID.h"
#include "Papyrus/Debug/DebugName.h"
#include "Papyrus/Log.h"

namespace Papyrus
{
	//todo: expand according to our needs. very simple at the moment
	enum class ArgType : uint8_t
	{
		Float, 
		Int32, 
		Bool, 
		//EntityID? 
		//Vec3?
	};

	struct PAPYRUS_API EventArg
	{
		HashedString name;
		ArgType	  type; 

		[[no_unique_address]] DebugName debugName;

		union
		{
			float   f; 
			int32_t i; 
			bool    b; 

		 };
	};


	constexpr uint8_t MAX_EVENT_ARGS = 4; 

	class PAPYRUS_API Event final
	{
	public:
		Event(HashedString name, DebugName debugName) noexcept
			: m_Name(name), m_DebugName(debugName), m_NumArgs(0) {}

		[[nodiscard]] HashedString getType() const noexcept { return m_Name;  }

		void setArgFloat(HashedString name, float value, DebugName debugName);
		void setArgInt(HashedString name, uint32_t value, DebugName debugName);
		void setArgBool(HashedString name, bool value, DebugName debugName);

		[[nodiscard]] float    getArgFloat(HashedString name) const;
		[[nodiscard]] uint32_t getArgInt(HashedString name) const;
		[[nodiscard]] bool     getArgBool(HashedString name) const;

		std::string toDebugString() const;
	private: 
		HashedString m_Name;
		[[no_unique_address]] DebugName m_DebugName; 
		uint8_t m_NumArgs; 
		EventArg m_Args[MAX_EVENT_ARGS]; 

	};




#define PPR_MAKE_EVENT(name)                       Papyrus::Event(Papyrus::HashID(name), name)
#define PPR_SET_EVENT_ARG_FLOAT(event, name, value) (event).setArgFloat(Papyrus::HashID(name), value, name)
#define PPR_SET_EVENT_ARG_INT(event, name, value)   (event).setArgInt(Papyrus::HashID(name), value, name)
#define PPR_SET_EVENT_ARG_BOOL(event, name, value)  (event).setArgBool(Papyrus::HashID(name), value, name)

#define PPR_GET_EVENT_ARG_FLOAT(event, name)        (event).getArgFloat(Papyrus::HashID(name))
#define PPR_GET_EVENT_ARG_INT(event, name)          (event).getArgInt(Papyrus::HashID(name))
#define PPR_GET_EVENT_ARG_BOOL(event, name)         (event).getArgBool(Papyrus::HashID(name))







}

#endif
