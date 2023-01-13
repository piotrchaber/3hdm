cmake_minimum_required(VERSION 3.5)

project(3hdm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(3HDM_SOURCE
    src/group.cpp
    src/invariance_equation_solver.cpp
    src/unique_solutions_seeker.cpp
)
set(EXAMPLES_DIR
    ${CMAKE_SOURCE_DIR}/doc/examples/
)
set(EIGEN_DIR
    ${CMAKE_SOURCE_DIR}/extern/eigen/
)

if(NOT EXISTS ${EIGEN_DIR})
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    )
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/include/
    ${EIGEN_DIR}
)

add_library(${PROJECT_NAME}_lib SHARED
    ${3HDM_SOURCE}
)

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
)

function(add_example file_name app_name input_file)
    add_executable(${PROJECT_NAME}_${app_name}
        ${EXAMPLES_DIR}/${file_name}
    )

    target_link_libraries(${PROJECT_NAME}_${app_name}
        ${PROJECT_NAME}_lib
    )

    set_target_properties(${PROJECT_NAME}_${app_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
    )

    if(input_file)
        configure_file(${EXAMPLES_DIR}/${input_file}
            ${PROJECT_BINARY_DIR}/)
    endif()
endfunction()

add_example(tutorial_group.cpp group tutorial_group)
add_example(tutorial_invariance_equation_solver.cpp invariance_equation_solver tutorial_group)
add_example(tutorial_mymatrix.cpp mymatrix tutorial_mymatrix.txt)
add_example(tutorial_representation.cpp representation tutorial_representation.txt)
add_example(tutorial_unique_solutions_seeker.cpp unique_solutions_seeker tutorial_group)
