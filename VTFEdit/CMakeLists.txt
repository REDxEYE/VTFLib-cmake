cmake_minimum_required(VERSION 3.15)
project(VTFEdit)
set(CMAKE_CXX_STANDARD 17)

if (MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif (MINGW)

file(GLOB_RECURSE VTFEDIT_SRC_G ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE VTFEDIT_SRC_RESX ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.resx)

set(VTFEDIT_SRC
        ${VTFEDIT_SRC_G}
        ${VTFEDIT_SRC_RESX}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/VTFEdit.rc.out
        )
configure_file(
        resources/VTFEdit.rc
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/VTFEdit.rc.out
)

set_source_files_properties(VTFLib/resources/VTFEdit.rc.out PROPERTIES LANGUAGE RC)

add_library(VTFEdit SHARED
        ${VTFEDIT_SRC}
        )
set_target_properties(VTFEdit PROPERTIES PREFIX "")
#add_definitions(-DVTFLIB_EXPORTS)
target_include_directories(VTFEdit PUBLIC include)