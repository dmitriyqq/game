cmake_minimum_required (VERSION 3.10)
project (SnakeOpenGL)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC -march=native")

include_directories(./include)

add_executable(TST main.cpp Mesh.hpp)

target_include_directories(TST PUBLIC ../../include)
target_link_libraries(TST GameEngine)
