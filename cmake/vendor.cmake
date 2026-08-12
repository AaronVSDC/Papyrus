include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

function(vendor_add name)
    cmake_parse_arguments(ARG "" "GIT_REPOSITORY;GIT_TAG" "" ${ARGN})

    set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps)

    FetchContent_Declare(
            ${name}
            GIT_REPOSITORY ${ARG_GIT_REPOSITORY}
            GIT_TAG        ${ARG_GIT_TAG}
            SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/vendor/${name}
    )
    FetchContent_MakeAvailable(${name})
endfunction()