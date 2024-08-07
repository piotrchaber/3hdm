cmake_minimum_required(VERSION 3.5)

project(3hdm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(3HDM_SOURCE
    src/combination.cpp
    src/group_list.cpp
    src/group.cpp
    src/invariance_equation_solver.cpp
    src/matrix_form.cpp
    src/unique_solutions_seeker.cpp
    src/utilities.cpp
)

set(EXAMPLES_DIR
    ${CMAKE_SOURCE_DIR}/doc/examples/
)

set(EIGEN_DIR
    ${CMAKE_SOURCE_DIR}/extern/eigen/
)

set(NLOHMANN_DIR
    ${CMAKE_SOURCE_DIR}/extern/json/
)

set(INPUT_DIR
    ${CMAKE_SOURCE_DIR}/input/
)

set(INPUT_FILES
    tutorial_group.json tutorial_mymatrix.txt tutorial_representation.txt
)

if(NOT EXISTS ${EIGEN_DIR})
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    )
endif()

if(NOT EXISTS ${NLOHMANN_DIR})
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    )
endif()

add_library(${PROJECT_NAME}_lib STATIC
    ${3HDM_SOURCE}
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
    ${EIGEN_DIR}
    ${NLOHMANN_DIR}/include/
)

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
)

add_custom_command(TARGET ${PROJECT_NAME}_lib PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${INPUT_DIR} ${PROJECT_BINARY_DIR}/input
)

foreach(input_file IN LISTS INPUT_FILES)
    configure_file(${EXAMPLES_DIR}/${input_file}
        ${PROJECT_BINARY_DIR}/
    )
endforeach()

set(TUTORIAL_SOURCE
    ${EXAMPLES_DIR}/include/tutorial.cpp
    ${EXAMPLES_DIR}/include/tutorial.h
)

add_library(tutorial_lib STATIC
    ${TUTORIAL_SOURCE}
)

target_include_directories(tutorial_lib PUBLIC
    ${EXAMPLES_DIR}/include/
)

target_link_libraries(tutorial_lib
    ${PROJECT_NAME}_lib
)

function(add_example file_name app_name)
    add_executable(${PROJECT_NAME}_${app_name}
        ${EXAMPLES_DIR}/${file_name}
    )

    target_link_libraries(${PROJECT_NAME}_${app_name}
        ${PROJECT_NAME}_lib
        tutorial_lib
    )

    set_target_properties(${PROJECT_NAME}_${app_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
    )
endfunction()

add_example(tutorial_group_list.cpp group_list)
add_example(tutorial_group.cpp group)
add_example(tutorial_invariance_equation_solver.cpp invariance_equation_solver)
add_example(tutorial_mymatrix.cpp mymatrix)
add_example(tutorial_representation.cpp representation)
add_example(tutorial_unique_solutions_seeker.cpp unique_solutions_seeker)
add_example(tutorial_combination.cpp combination)
add_example(tutorial_matrix_form.cpp matrix_form)
add_example(tutorial_real_life_example.cpp real_life_example)
