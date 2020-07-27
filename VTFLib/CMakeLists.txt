cmake_minimum_required(VERSION 3.15)
project(VTFLib)
set(CMAKE_CXX_STANDARD 17)

if (MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif (MINGW)

file(GLOB_RECURSE VTFLIB_SRC_G ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(VTFLIB_SRC
        ${VTFLIB_SRC_G}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/Resource.rc.out
        )
configure_file(
        resources/Resource.rc
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/Resource.rc.out
)

set_source_files_properties(VTFLib/resources/Resource.rc.out PROPERTIES LANGUAGE RC)

add_library(VTFLib SHARED
        ${VTFLIB_SRC}
        )
set_target_properties(VTFLib PROPERTIES PREFIX "")
add_definitions(-DVTFLIB_EXPORTS)
target_include_directories(VTFLib PUBLIC include)