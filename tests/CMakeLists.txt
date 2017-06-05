cmake_minimum_required(VERSION 2.8)

enable_testing()

add_executable(chancypolyhedra_tests
        main.cpp
        basic.cpp distributions.cpp)

message(STATUS "CONAN_LIBS: ${CONAN_LIBS}")

target_link_libraries(chancypolyhedra_tests chancypolyhedra ${CONAN_LIBS})

add_test(chancypolyhedra ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/chancypolyhedra_tests)