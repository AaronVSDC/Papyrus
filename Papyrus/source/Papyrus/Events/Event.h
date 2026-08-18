#ifndef PAPYRUS_EVENT_H
#define PAPYRUS_EVENT_H
#include "Papyrus/Core/Core.h"

namespace Papyrus
{

	//events now are blocking, todo: maybe change to an event queue 
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0, 
		EventCategoryApplication = BIT(0), 
		EventCategoryInput       = BIT(1), 
		EventCategoryKeyboard    = BIT(2), 
		EventCategoryMouse       = BIT(3), 
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() {return EventType::type; }\
							   virtual EventType getEventType() const override {return getStaticType(); }\
							   virtual const char* getName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override {return category; }
	
	class PAPYRUS_API Event
	{
		friend class EventDispatcher; 
	public: 
		Event() = default; 
		Event(Event&) = delete; 
		Event(Event&&) = delete; 
		Event& operator=(Event&) = delete;
		Event& operator=(Event&&) = delete; 

		virtual ~Event() = default; 
		
		virtual EventType getEventType() const = 0; 
		virtual const char* getName() const = 0; 
		virtual int getCategoryFlags() const = 0; 

		virtual std::string toString() const { return getName();  }
		
		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category; 
		}

		bool m_Handled = false; 
	};

	class EventDispatcher
	{
	public: 
		EventDispatcher(EventDispatcher&) = delete; 
		EventDispatcher(EventDispatcher&&) = delete; 
		EventDispatcher& operator=(EventDispatcher&) = delete; 
		EventDispatcher& operator=(EventDispatcher&&) = delete; 

		EventDispatcher(Event& event)
			:m_Event(event)
		{
		}

		template<typename T, typename F>
		bool dispatch(const F& function)
		{
			if(m_Event.getEventType() == T::getStaticType())
			{
				m_Event.m_Handled = function(static_cast<T&>(m_Event)); 
				return true; 
			}
			return false; 
		}

	private: 
		Event& m_Event; 
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}

	//template <typename T>
	//struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<Papyrus::Event, T>, char>>
	//	: fmt::ostream_formatter
	//{
	//};
}



#endif
