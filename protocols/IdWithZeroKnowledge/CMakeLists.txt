cmake_minimum_required(VERSION 3.14)
project(IdWithZeroKnowledge)

set(CMAKE_CXX_STANDARD 14)
set(SRC_FILES main.cpp Generator.cpp Generator.h Alice.cpp Alice.h Bob.cpp Bob.h)

add_executable(IdWithZeroKnowledge ${SRC_FILES})