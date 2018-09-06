cmake_minimum_required (VERSION 3.10)
project (GameEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC -march=native")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(./include)

SET(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
SET(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

FILE(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.hpp)
FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

add_executable(GameEngine ./src/main.cpp ${PROJECT_HEADERS_DIR} ${PROJECT_SOURCES_DIR})
target_link_libraries(GameEngine ${CURSES_LIBRARIES})
set_target_properties(GameEngine PROPERTIES LINKER_LANGUAGE CXX)