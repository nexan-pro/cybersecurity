cmake_minimum_required(VERSION 3.9)
project(RSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(RSA main.cpp rsa/rsa.cpp rsa/rsa.h)