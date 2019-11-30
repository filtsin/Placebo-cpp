cmake_minimum_required(VERSION 3.0)
project(PlaceboTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "--coverage")


enable_testing()

find_library(GTEST gtest REQUIRED)
find_library(GTESTMAIN gtest_main REQUIRED)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/placebo)

add_executable( ${PROJECT_NAME} ${SRC}/details/arithmetic_[fill_from_unsigned_builtin]_test.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST} ${GTESTMAIN} pthread)
target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Werror
        )
