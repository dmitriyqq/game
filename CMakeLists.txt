cmake_minimum_required (VERSION 3.10)
project (GameEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC -march=native")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${GLFW3_INCLUDE_DIR})

include_directories(./include)
include_directories(./deps/include)

SET(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
SET(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

FILE(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.hpp)
FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

find_package(Threads REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Assimp REQUIRED)

add_subdirectory(./examples)

add_library(GameEngine ./deps/src/glad.c ./deps/include/PerlinNoise.h ${HEADERS} ${SOURCES})
target_include_directories(GameEngine PUBLIC ./deps/include/glad)
target_link_libraries(GameEngine glfw dl)
target_link_libraries(GameEngine assimp)
set_target_properties(GameEngine PROPERTIES LINKER_LANGUAGE CXX)