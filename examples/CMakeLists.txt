cmake_minimum_required (VERSION 3.10)
project (GameEngineExamples)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC -march=native")

add_subdirectory(SnakeOpenGL)


#include_directories(./include)
#include_directories(./deps/include)
#
#SET(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
#SET(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)
#
#FILE(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.hpp)
#FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)
#
#find_package(Threads REQUIRED)
#find_package(glfw3 REQUIRED)
#find_package(glm REQUIRED)
#
## add_subdirectory(./examples)
#
#add_library(GameEngine ./deps/include/PerlinNoise.h src/glad.c ${HEADERS} ${SOURCES})
#
#target_link_libraries(GameEngine glfw3)
#target_link_libraries(GameEngine ${CURSES_LIBRARIES})
#target_link_libraries(GameEngine spdlog::spdlog Threads::Threads)
#set_target_properties(GameEngine PROPERTIES LINKER_LANGUAGE CXX)