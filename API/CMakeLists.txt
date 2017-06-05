cmake_minimum_required(VERSION 2.8)

enable_testing()

add_executable(chancypolyhedrad
        main.cpp
        logger.cpp logger.h)

target_link_libraries(chancypolyhedrad chancypolyhedra ${CONAN_LIBS})