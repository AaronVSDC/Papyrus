#ifndef PAPYRUSENGINE_EVENTPOOL_H
#define PAPYRUSENGINE_EVENTPOOL_H
#include "Papyrus/Core/Core.h"
#include "Papyrus/Event/Event.h"
#include "Papyrus/Log.h"
#include <new>

namespace Papyrus
{
    //note for future me if this looks a little cryptic: this event pool is just allocating some raw memory (aligning it as Event types)
    //and then creating a chain where each free slot "points to" the next free slot just by writing an incrementing integer in each slot.
    //When an event is allocated we actually put a copy of that event in the raw event sized memory slot if there is space.
    //This way of making a memory pool was in the game engine architecture book and is fast and cache friendly
    class PAPYRUS_API EventPool final
    {
    public:
        EventPool() noexcept
        {
            for (uint16_t index = 0; index < m_POOL_SIZE - 1; ++index)
                *reinterpret_cast<uint16_t*>(&m_Slots[index]) = index + 1;

            *reinterpret_cast<uint16_t*>(&m_Slots[m_POOL_SIZE - 1]) = m_INVALID_INDEX;
            m_FreeListHead = 0;
        }

        Event* allocate(const Event& source)
        {
            PPR_ASSERT(m_FreeListHead != m_INVALID_INDEX, "EventPool exhausted.");
            if (m_FreeListHead == m_INVALID_INDEX)
                return nullptr;

            uint16_t index = m_FreeListHead;
            m_FreeListHead = *reinterpret_cast<uint16_t*>(&m_Slots[index]);

            return new (&m_Slots[index]) Event(source);

        }

        void free(Event* e)
        {
            uint16_t index = static_cast<uint16_t>(reinterpret_cast<unsigned char(*)[sizeof(Event)]>(e) - m_Slots);

            e->~Event(); 

            *reinterpret_cast<uint16_t*>(&m_Slots[index]) = m_FreeListHead;
            m_FreeListHead = index;
        }

    private:
        static constexpr uint16_t m_POOL_SIZE = 16;
        static constexpr uint16_t m_INVALID_INDEX = 0xFFFF;

        alignas(Event) unsigned char m_Slots[m_POOL_SIZE][sizeof(Event)];
        uint16_t m_FreeListHead;
    };
}
#endif //PAPYRUSENGINE_EVENTPOOL_H
