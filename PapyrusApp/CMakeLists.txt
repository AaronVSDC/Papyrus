add_executable(PapyrusApp
    source/PapyrusApp.cpp)

target_link_libraries(PapyrusApp PRIVATE Papyrus)

target_compile_definitions(PapyrusApp PRIVATE ENTRY_POINT)
target_precompile_headers(PapyrusApp PRIVATE ${CMAKE_SOURCE_DIR}/Papyrus/ppch.h)

papyrus_set_output_dirs(PapyrusApp)

#copy dll next to executable
add_custom_command(
        TARGET PapyrusApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:Papyrus>"
        "$<TARGET_FILE_DIR:PapyrusApp>"
        COMMENT "Copying Papyrus shared library to PapyrusApp output directory"
)