cmake_minimum_required(VERSION 2.5)
project(projeto1)
include(FindPkgConfig)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        constants.h
        main.cpp
        Street.cpp Street.h
        BusStatus.h
        RiderStatus.h
        Worker.cpp Worker.h
        Bus.cpp Bus.h
        Rider.cpp Rider.h
        Shape.h
        BusShape.cpp BusShape.h
        RiderShape.cpp RiderShape.h
)
add_executable(projeto1 ${SOURCE_FILES})

# SDL2
pkg_search_module(SDL2 REQUIRED sdl2)

# GLEW
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIR}
        ${OpenGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES} SDL2
        ${SDL2IMAGE_LIBRARY} SDL2_image
        ${GLEW_LIBRARIES} glut GL GLU GLEW
)
