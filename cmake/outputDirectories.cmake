if(WIN32)
    set(PLATFORM_NAME "windows")
elseif(UNIX)
    set(PLATFORM_NAME "linux")
else()
    message(FATAL_ERROR "Unsupported platform. Only Windows and Linux are currently supported.")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm64|aarch64|ARM64)$")
    set(ARCHITECTURE_NAME "arm64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE_NAME "x64")
else() 
    message(FATAL_ERROR "Unsupported architecture: Papyrus currently doesn't support 32bit builds.")
endif()

set(OUTPUT_SUBDIR "$<CONFIG>-${PLATFORM_NAME}-${ARCHITECTURE_NAME}")

function(papyrus_set_output_dirs target)
    set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_SUBDIR}/${target}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUPUT_SUBDIR}/${target}"
            #ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_SUBDIR}/${target}"
    )
endfunction()
