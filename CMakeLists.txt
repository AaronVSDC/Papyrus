cmake_minimum_required(VERSION 3.20)
project(PapyrusEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #turned on for clion implicitly ignored by vs, without it and its metadata it has more trouble with autocomplete, goto definitions etc...

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(outputDirectories) 
include(vendor)

#compile definitions
if(WIN32)
    add_compile_definitions(PPR_PLATFORM_WINDOWS)
    add_compile_definitions(UNICODE _UNICODE)
elseif(UNIX)
    add_compile_definitions(PPR_PLATFORM_LINUX)
endif()
add_compile_definitions($<$<CONFIG:Debug>:PPR_DEBUG>)
add_compile_definitions($<$<CONFIG:Release>:PPR_RELEASE>) 



add_subdirectory(Papyrus)
add_subdirectory(PapyrusApp)