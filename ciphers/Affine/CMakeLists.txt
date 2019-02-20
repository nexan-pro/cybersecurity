cmake_minimum_required(VERSION 3.12)
project(AffineCipher C)

set(CMAKE_C_STANDARD 11)

add_executable(AffineCipher main.c Affine.h Affine.c)