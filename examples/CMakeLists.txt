cmake_minimum_required (VERSION 3.10)
project (GameEngineExamples)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wdangling-else -Wno-unused-parameter -fPIC -march=native")

add_subdirectory(SnakeOpenGL)
add_subdirectory(MyGame)