#ifndef PAPYRUSENGINE_STRING_ID_H
#define PAPYRUSENGINE_STRING_ID_H


namespace Papyrus
{
	using HashedString = uint32_t;

	consteval HashedString FNV1aHash(const char* string, HashedString hash = 2166136261u)
	{
		return (*string == '\0') ? hash : FNV1aHash(string + 1, (hash ^ static_cast<HashedString>(*string)) * 16777619u);
	}
	consteval HashedString HashID(const char* string)
	{
		return FNV1aHash(string); 
	}
}

#define PPR_SID(name) Papyrus::HashID(name)

#endif