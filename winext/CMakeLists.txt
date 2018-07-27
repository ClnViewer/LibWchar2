cmake_minimum_required (VERSION 2.6)
# ----------------------------------------------------------------------------
#  CMake file for libwchar2ext. See CMakeINSTALL.md
#  this required to compile the libwchar2 extension library for MSVC/MSVS
# ----------------------------------------------------------------------------

project(libwchar2ext)
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

include(CheckCCompilerFlag)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

set(inst_hdrs
	${CMAKE_CURRENT_SOURCE_DIR}/../include/wchar2ext.h
)

set(lib_hdrs
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/wchar2ext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/libbuild.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/libwcharext.h
)

set(lib_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/libwcharext.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/waccess.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wbasename.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wchar_utf8.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wcprint.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wfopen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wmkdir.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wpathnormalize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wremove.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wrename.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wstat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/wstring_util.c
)

set( lib_target "libwchar2ext" )
set( app_target "TestWchar2ext" )

add_library( ${lib_target} STATIC ${lib_srcs} ${lib_hdrs} )
add_executable( ${app_target} "../test/check_wchar2_MSVC.c" ) 
target_link_libraries( ${app_target} ${lib_target} )
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${app_target} )
set_target_properties(${lib_target} PROPERTIES PUBLIC_HEADER ${inst_hdrs})

add_test( NAME test COMMAND ${app_target} )

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(UNIX OR MINGW OR MSYS)

     CHECK_C_COMPILER_FLAG("-std=c11" COMPILER_SUPPORTS_C11)
     if(COMPILER_SUPPORTS_C11)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
     endif()

     CHECK_C_COMPILER_FLAG("-Wstrict-prototypes" COMPILER_SUPPORTS_CWSP)
     if(COMPILER_SUPPORTS_CWSP)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-prototypes")
     endif()

     CHECK_C_COMPILER_FLAG("-Wall" COMPILER_SUPPORTS_CWALL)
     if(COMPILER_SUPPORTS_CWALL)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
     endif()

     CHECK_C_COMPILER_FLAG("-Wextra" COMPILER_SUPPORTS_CWETRA)
     if(COMPILER_SUPPORTS_CWETRA)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
     endif()

     CHECK_C_COMPILER_FLAG("-pedantic" COMPILER_SUPPORTS_CPEDANT)
     if(COMPILER_SUPPORTS_CPEDANT)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
     endif()

endif()

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /Zc:wchar_t")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t")
    if(OS_WIN_EXCEPTION_CONSOLE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /DOS_WIN_EXCEPTION_CONSOLE=1")
    endif()
    if(OS_WIN_FOPEN_MIXED_CHAR)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /DOS_WIN_FOPEN_MIXED_CHAR=1")
    endif()
endif()

if(UNIX)
     if(CMAKE_COMPILER_IS_GNUCC OR CV_ICC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
     endif()
endif()

if(WIN32)
# Postfix of DLLs:
    set(LIB_DEBUG_POSTFIX d)
    if(OS_WIN_FOPEN_MIXED_CHAR AND NOT MSVC)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DOS_WIN_FOPEN_MIXED_CHAR")
    endif()
else()
# Postfix of so's:
    set(LIB_DEBUG_POSTFIX)
endif()

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties( ${lib_target} PROPERTIES FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/lib/docs" )
endif()

install ( TARGETS ${lib_target}
  ARCHIVE DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  PUBLIC_HEADER DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/include"
)

install ( TARGETS ${app_target}
  RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/test"
)

