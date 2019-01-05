cmake_minimum_required (VERSION 3.10)
project (GameEngine)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC")

# spdlog is header only library
include_directories(./deps/spdlog/include)

# glfw
include_directories(./deps/glfw/include/)
link_directories(./deps/glfw/build/src)

# reactphysics
include_directories(./deps/reactphysics3d/src/)
link_directories(./deps/reactphysics3d/build/lib/)

# assimp
include_directories(./deps/assimp/include/)
include_directories(./deps/assimp/build/include/)
link_directories(./deps/assimp/build/code/)

# njson is header only
include_directories(.deps/json/single_include/nlohmann/)

# nanogui
link_directories(./deps/nanogui/build/)
include_directories(./deps/nanogui/include/)

include_directories(./deps/nanogui/ext/eigen)
include_directories(./deps/nanogui/ext/nanovg/src)


# stb_image is header only
include_directories(./deps/stb_image/)

#glad
include_directories(./deps/glad/include/)

SET(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
SET(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

FILE(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.hpp)
FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

find_package(Threads REQUIRED)

include_directories(./include/)

# main game that uses engine
add_subdirectory(./examples)

# for glad we need only to add single glad.c file
add_library(GameEngine ./deps/glad/src/glad.c ${PROJECT_HEADERS_DIR} ${PROJECT_SOURCES_DIR})

target_link_libraries(GameEngine dl)
target_link_libraries(GameEngine nanogui)
target_link_libraries(GameEngine glfw3)
target_link_libraries(GameEngine reactphysics3d)
target_link_libraries(GameEngine assimp)

set_target_properties(GameEngine PROPERTIES LINKER_LANGUAGE CXX)