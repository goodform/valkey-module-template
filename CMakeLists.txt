cmake_minimum_required(VERSION 3.16)

project(valkeyexample)

set(CMAKE_CXX_STANDARD 14)
set(VALKEY_SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/valkey)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")

include_directories(${VALKEY_SOURCE_DIR}/src/)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

add_library(valkeyexample SHARED ${SOURCES})