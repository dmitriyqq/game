cmake_minimum_required (VERSION 3.10)
project (GameEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC -march=native")
set(CMAKE_PREFIX_PATH "./cget/lib/cmake")

find_package(Curses REQUIRED)
include_directories(./cget/include)
include_directories(./include)
include_directories(./deps/include)
link_directories(./cget/lib)

SET(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
SET(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)
set(ASSETS ${PROJECT_SOURCE_DIR}/sharedAssets)

FILE(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.hpp)
FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

find_package(Threads REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Assimp REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

add_subdirectory(./examples)

add_library(GameEngine ./deps/include/stb_image.hpp ./deps/src/glad.c ./deps/include/PerlinNoise.h ${HEADERS} ${SOURCES})
target_include_directories(GameEngine PUBLIC ./deps/include/glad)

message(${ASSIMP_LIBRARIES})
target_link_libraries(GameEngine glfw)
target_link_libraries(GameEngine ${ASSIMP_LIBRARIES})
target_link_libraries(GameEngine dl)
link_libraries(GameEngine PRIVATE nlohmann_json::nlohmann_json)
set_target_properties(GameEngine PROPERTIES LINKER_LANGUAGE CXX)