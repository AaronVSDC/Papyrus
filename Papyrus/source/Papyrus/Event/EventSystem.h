#ifndef PAPYRUSENGINE_EVENT_SYSTEM_H
#define PAPYRUSENGINE_EVENT_SYSTEM_H
#include "Papyrus/Core/Core.h"
#include "Papyrus/Event/Event.h"
#include "Papyrus/Event/EventPool.h"

namespace Papyrus
{
	class EventListener;
	class PAPYRUS_API EventSystem final
	{
		friend class Application;
	public:
		EventSystem() = delete;
		EventSystem(const EventSystem&) = delete;
		EventSystem(EventSystem&&) = delete;
		EventSystem& operator=(const EventSystem&) = delete;
		EventSystem& operator=(EventSystem&&) = delete;

		static void subscribe(HashedString type, EventListener* listener);

		//subscribes to all events that are ever made, best only use this for debugging purposes
		//when you want to see all events that were ever created.
		static void subscribeAll(EventListener* listener);

		static void unsubscribeAll(EventListener* listener);
		static inline void send(Event&, EventListener& listener);
		static void broadcast(Event& e);

		//convention: high priority will be prioritised over low priority
		static void queue(const Event& e, EventListener& listener, double delay = 0.0, uint8_t priority = 0);
		//convention: high priority will be prioritised over low priority
		static void queueBroadcast(Event& e, double delay = 0.0, uint8_t priority = 0);

	private:
		static void dispatchQueuedEvents(double currentTime);
		static void notifyGlobalListeners(Event& e);

		struct QueuedEventEntry
		{
			Event* event;
			EventListener* listener;
			double deliveryTime;
			uint8_t priority;
		};

		struct QueuedEventCompare
		{
			bool operator()(const QueuedEventEntry& a, const QueuedEventEntry& b) const
			{
				if (a.deliveryTime != b.deliveryTime)
					return a.deliveryTime > b.deliveryTime;
				return a.priority < b.priority;
			}
		};

	private:
		static inline std::unordered_map<HashedString, std::vector<EventListener*>> s_Listeners;
		static inline std::vector<EventListener*> s_GlobalListeners;
		static inline EventPool s_EventPool;
		static inline std::priority_queue<QueuedEventEntry, std::vector<QueuedEventEntry>, QueuedEventCompare> s_EventQueue;

	};
}

#endif