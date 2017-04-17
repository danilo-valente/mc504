cmake_minimum_required(VERSION 3.0)
project(projeto1)
include(FindPkgConfig)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(projeto1 ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} pthread)
