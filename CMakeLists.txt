cmake_minimum_required(VERSION 2.8)
project(chancypolyhedra)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

##### Options

macro(chancypolyhedra_option OPTION_NAME OPTION_TEXT OPTION_DEFAULT)
    option(${OPTION_NAME} ${OPTION_TEXT} ${OPTION_DEFAULT})
    if(DEFINED ENV{${OPTION_NAME}})
        # Allow setting the option through an environment variable
        set(${OPTION_NAME} $ENV{${OPTION_NAME}})
    endif()
    if(${OPTION_NAME})
        add_definitions(-D${OPTION_NAME})
    endif()
    message(STATUS "  ${OPTION_NAME}: ${${OPTION_NAME}}")
endmacro()

message(STATUS "ChancyPolyhedra CMake Options")
message(STATUS "=======================================================")
chancypolyhedra_option(BUILD_SHARED_LIBS   "Build the library as a dynamic object"     OFF)
chancypolyhedra_option(BUILD_CHANCYPOLYHEDRA_TESTS    "Build the test suite"                  ON)
chancypolyhedra_option(BUILD_CHANCYPOLYHEDRA_COVERAGE "Generate test coverage information"    OFF)
chancypolyhedra_option(BUILD_CHANCYPOLYHEDRA_API "Build the API server"              OFF)
message(STATUS "=======================================================")

set(SOURCE_FILES chancypolyhedra/grammar.hpp chancypolyhedra/chancypolyhedra.cpp chancypolyhedra/chancypolyhedra.h)
add_library(chancypolyhedra ${SOURCE_FILES})
set(CHANCYPOLYHEDRA_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
include_directories(SYSTEM ${CHANCYPOLYHEDRA_INCLUDE_DIRS})
include_directories(SYSTEM PRIVATE chancypolyhedra)
target_link_libraries(chancypolyhedra ${CONAN_LIBS})

if(BUILD_CHANCYPOLYHEDRA_TESTS)
    message(STATUS "Building Chancy Polyhedra tests")
    add_subdirectory(tests)
endif()

if(BUILD_CHANCYPOLYHEDRA_API)
    message(STATUS "Building Chancy Polyhedra API server")
    add_subdirectory(API)
endif()
