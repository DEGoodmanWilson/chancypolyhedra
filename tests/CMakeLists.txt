cmake_minimum_required(VERSION 3.5)

enable_testing()

add_executable(${PROJECT_NAME}_tests
        main.cpp
        chancypolyhedra_controller.cpp
        env.hpp assets.cpp
        ../chancypolyhedra/chancypolyhedra.cpp ../chancypolyhedra/chancypolyhedra.hpp
        ../chancypolyhedra/grammar.hpp
        ../chancypolyhedra/randutils.hpp
        ../chancypolyhedra/tokenizer.cpp ../chancypolyhedra/tokenizer.hpp
        webserver.cpp)

target_link_libraries(${PROJECT_NAME}_tests ${CONAN_LIBS})

add_test(${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_tests)