cmake_minimum_required(VERSION 3.16)
project(ed)

set(CMAKE_CXX_STANDARD 20)
file(GLOB SOURCES *.cpp)#Reload all .cpp files into variable SOURCES
#add_executable(ed main.cpp)
add_executable(ed ${SOURCES})