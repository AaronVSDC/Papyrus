#DOWNLOAD DEPENDENCIES
#-----------------------------------------------------------------
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
vendor_add( spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.14.1
)
#----------------------------------------------------------------

add_library(Papyrus SHARED
        source/Papyrus.h
        source/Papyrus/Log.cpp
        source/Papyrus/Core/Application.cpp
        source/Papyrus/Core/Core.h
        source/Papyrus/Core/EntryPoint.h
        source/Papyrus/Core/KeyCodes.h
        source/Papyrus/Events/Event.h
        source/Papyrus/Events/KeyEvent.h
)

target_include_directories(Papyrus
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include)

target_link_libraries(Papyrus PUBLIC spdlog::spdlog)

target_precompile_headers(Papyrus PRIVATE source/Papyrus.h)

target_compile_definitions(Papyrus PRIVATE PPR_BUILD_DLL)

if(UNIX)
    set_target_properties(Papyrus PROPERTIES
            CXX_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN ON
    )
endif()
