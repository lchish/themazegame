project(themazegame)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${themazegame_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("Build instructions: 
mkdir build 
cd build
cmake ..
make
running instructions:
cp build/src/themazegame .
./themazegame")

INCLUDE_DIRECTORIES(external/SOIL)
ADD_DEFINITIONS(-Wall -g)#compiler options

find_package(OpenGL)
find_package(SDL)
find_package(OpenAL)
add_subdirectory(external)
add_subdirectory(src)
