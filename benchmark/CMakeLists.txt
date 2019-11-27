cmake_minimum_required(VERSION 3.0)
project(PlaceboBenchmark)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_library(GBENCH benchmark REQUIRED)
find_library(GBENCHMAIN benchmark_main REQUIRED)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/placebo)

add_executable( ${PROJECT_NAME} ${SRC}/details/arithmetic_[fill_from_unsigned_builtin]_bench.cpp)

target_link_libraries(${PROJECT_NAME} ${GBENCH} ${GBENCHMAIN} pthread)
target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Werror
        )
