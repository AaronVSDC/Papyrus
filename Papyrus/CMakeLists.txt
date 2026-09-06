#DOWNLOAD DEPENDENCIES
#-----------------------------------------------------------------
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
vendor_add( spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.14.1
)
vendor_add(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.5.1
)
#----------------------------------------------------------------

add_library(Papyrus SHARED
        source/Papyrus.h
        source/Papyrus/Log.cpp
        source/Papyrus/Core/Application.cpp
        source/Papyrus/Core/Core.h
        source/Papyrus/Core/EntryPoint.h 
        source/Papyrus/Core/KeyCodes.h 
        source/Papyrus/Event/Event.cpp
        source/Papyrus/Event/EventSystem.cpp
        source/Papyrus/Event/EventListener.cpp
        source/Papyrus/Core/Time.cpp
        source/Papyrus/Core/Window.cpp
        source/Papyrus/Platform/Windows/WindowsWindow.cpp
        source/Papyrus/Platform/Linux/LinuxWindow.cpp
        source/Papyrus/Debug/DebugName.h
        source/Papyrus/Event/EventPool.h
        source/Papyrus/Debug/EventFormatter.h)

target_include_directories(Papyrus
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)


target_link_libraries(Papyrus PUBLIC spdlog::spdlog)
target_link_libraries(Papyrus PRIVATE glfw)

target_precompile_headers(Papyrus PRIVATE ppch.h)

target_compile_definitions(Papyrus PRIVATE PPR_BUILD_DLL)

if(UNIX)
    set_target_properties(Papyrus PROPERTIES
            CXX_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN ON
    )
endif()
