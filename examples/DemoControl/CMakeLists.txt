cmake_minimum_required (VERSION 3.10)
project (MYGAME)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC -march=native")

include_directories(./include)

SET(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
SET(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

FILE(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.hpp)
FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

add_executable(MyGame ${SOURCES} ${HEADERS})

target_include_directories(MyGame PUBLIC ../../include)
target_link_Libraries(MyGame GameEngine)
