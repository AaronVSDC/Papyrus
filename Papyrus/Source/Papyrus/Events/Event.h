#ifndef EVENT_H
#define EVENT_H
#include "Papyrus/Core.h"

namespace Papyrus
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory
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
							   virtual const char* getName() const override {return #type}

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override {return category; }
	
	class PAPYRUS_API Event
	{
		friend class EventDispatcher; 
	public: 
		Event(Event&) = delete; 
		Event(Event&&) = delete; 
		Event& operator=(Event&) = delete;
		Event& operator=(Event&&) = delete; 

		virtual EventType getEventType() const = 0; 
		virtual const char* getName() const = 0; 

	private: 
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
}



#endif
