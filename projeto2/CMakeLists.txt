cmake_minimum_required(VERSION 3.6)
project(lwnfs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES qotdfs.c)

add_custom_target(qotdfs COMMAND make -C ${projeto2_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})