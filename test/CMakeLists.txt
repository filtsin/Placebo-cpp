cmake_minimum_required(VERSION 3.0)
project(PlaceboTest)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

find_library(GTEST gtest REQUIRED)
find_library(GTESTMAIN gtest_main REQUIRED)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable( ${PROJECT_NAME} ${SRC}/nothing/empty.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST} ${GTESTMAIN} pthread)
target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Werror
        )