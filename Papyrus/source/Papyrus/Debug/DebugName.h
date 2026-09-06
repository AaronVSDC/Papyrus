#ifndef PAPYRUSENGINE_DEBUG_NAME_H
#define PAPYRUSENGINE_DEBUG_NAME_H

namespace Papyrus
{
#ifdef PPR_DEBUG
	//name you can give something that will dissapear in release builds
	//make sure to add [[no_unique_address]] to enforce this 
    struct DebugName
    {
        const char* name = nullptr;   
        constexpr DebugName() noexcept = default;
        constexpr DebugName(const char* _name) noexcept : name(_name) {}
    };
#else
    struct DebugName
    {
        constexpr DebugName() noexcept = default;
        constexpr DebugName(const char*) noexcept {}
    };
#endif
}


#endif