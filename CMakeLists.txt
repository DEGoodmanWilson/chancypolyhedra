cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME chancypolyhedra)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

set(SOURCE_FILES main.cpp logger.cpp logger.hpp
        chancypolyhedra/chancypolyhedra.cpp chancypolyhedra/chancypolyhedra.hpp
        chancypolyhedra/grammar.hpp
        chancypolyhedra/randutils.hpp
        chancypolyhedra/tokenizer.cpp chancypolyhedra/tokenizer.hpp
        )

set(CONTROLLERS
        controllers/controller.hpp
        controllers/chancypolyhedra_controller.hpp
        )

add_executable(${PROJECT_NAME} ${CONTROLLERS} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

# Tests
add_subdirectory(tests)