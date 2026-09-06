#include "EventSystem.h"

#include "Papyrus/Event/EventListener.h"
#include "Papyrus/Core/Time.h"


namespace Papyrus
{
    void EventSystem::subscribe(const HashedString type, EventListener* listener)
    {
       s_Listeners[type].push_back(listener);
    }

    void EventSystem::subscribeAll(EventListener *listener)
    {
       s_GlobalListeners.push_back(listener);
    }

    void EventSystem::unsubscribeAll(EventListener* listener)
    {
       for (auto& [type, list] : s_Listeners)
       {
          std::erase(list,listener);
       }
       std::erase(s_GlobalListeners, listener);
    }

    void EventSystem::send(Event& e, EventListener& listener)
    {
       listener.onEvent(e);
    }

    void EventSystem::broadcast(Event& e)
    {
       auto it = s_Listeners.find(e.getType());
       if (it != s_Listeners.end())
       {
          for (EventListener* listener : it->second)
             listener->onEvent(e);
       }

       notifyGlobalListeners(e);
    }

    void EventSystem::queue(const Event& e, EventListener& listener, double delay, uint8_t priority)
    {
       Event* copy = s_EventPool.allocate(e);
       if (!copy)
          return;

       double deliveryTime = Time::totalTime() + delay;
       s_EventQueue.push({copy, &listener, deliveryTime, priority});
    }

    void EventSystem::queueBroadcast(Event& e, double delay, uint8_t priority)
    {
       Event* copy = s_EventPool.allocate(e);
       if (!copy)
          return;

       double deliveryTime = Time::totalTime() + delay;
       s_EventQueue.push({copy, nullptr, deliveryTime, priority});
    }

    void EventSystem::dispatchQueuedEvents(double currentTime)
    {
       while (!s_EventQueue.empty() and s_EventQueue.top().deliveryTime <= currentTime)
       {
          QueuedEventEntry entry = s_EventQueue.top();
          s_EventQueue.pop();

          if (entry.listener)
             entry.listener->onEvent(*entry.event);
          else
             broadcast(*entry.event);

          s_EventPool.free(entry.event);
       }
    }

    void EventSystem::notifyGlobalListeners(Event &e)
    {
       for (EventListener* listener : s_GlobalListeners)
          listener->onEvent(e);
    }
}
