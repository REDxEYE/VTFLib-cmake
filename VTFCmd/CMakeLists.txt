cmake_minimum_required(VERSION 3.15)
project(VTFCmd)
set(CMAKE_C_STANDARD 11)

if (MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif (MINGW)

file(GLOB_RECURSE VTFCMD_SRC_G ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

set(VTFCMD_SRC
        ${VTFCMD_SRC_G}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/VTFCmd.rc.out
        )
configure_file(
        resources/VTFCmd.rc
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/VTFCmd.rc.out
)

set_source_files_properties(VTFLib/resources/Resource.rc.out PROPERTIES LANGUAGE RC)

add_library(VTFCmd SHARED
        ${VTFCMD_SRC}
        )
set_target_properties(VTFCmd PROPERTIES PREFIX "")
#add_definitions(-DVTFLIB_EXPORTS)
target_include_directories(VTFCmd PUBLIC include)