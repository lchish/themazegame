project(themazegame)

cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES(external/SOIL)
ADD_DEFINITIONS(-Wall)#compiler options

find_package(OpenGL)
find_package(GLU)
find_package(GLUT)
find_package(OpenAL)
add_subdirectory(external)
add_subdirectory(src)
