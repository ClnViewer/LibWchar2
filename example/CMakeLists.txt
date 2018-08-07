cmake_minimum_required(VERSION 3.3)
project(wreaddir_cb)
enable_language(C)
enable_testing()

set( CMAKE_COLOR_MAKEFILE ON )
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE )
set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib CACHE PATH "Cmake prefix" FORCE )
set( CMAKE_SUPPRESS_REGENERATION true )
set( CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true )
set( CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY true )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set( PREDEFINED_TARGETS_FOLDER "CmakeDepends" )

include_directories( "${CMAKE_SOURCE_DIR}/../include" )

if(UNIX)
    link_directories( "${CMAKE_SOURCE_DIR}/../src/.libs" )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -fshort-wchar")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wstrict-prototypes")

elseif(MINGW)
    link_directories( "${CMAKE_SOURCE_DIR}/../winext/mingw" )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -fshort-wchar")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wstrict-prototypes")

elseif(MSVC)
    link_directories( "${CMAKE_SOURCE_DIR}/../winext/msvs/Debug" )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /Zc:wchar_t")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t")

endif()

set( app_target "wreaddir_cb_test" )
add_executable( ${app_target} "wreaddir_cb-cross-platform.c" )

if(UNIX)
    target_link_libraries( ${app_target} "wchar2" )
    add_compile_options( "-Wl,-rpath=${CMAKE_SOURCE_DIR}/../src/.libs" )
elseif(MINGW)
    target_link_libraries( ${app_target} "wchar2ext" )
    add_compile_options( "-Wl,-rpath=${CMAKE_SOURCE_DIR}/../winext/mingw" )
elseif(MSVC)
    target_link_libraries( ${app_target} "libwchar2ext" )
endif()


set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${app_target} )

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_test( NAME test COMMAND ${app_target} )
