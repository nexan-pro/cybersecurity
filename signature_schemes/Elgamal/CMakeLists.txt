cmake_minimum_required(VERSION 3.14)
project(Elgamal)

set(CMAKE_CXX_STANDARD 11)
set(SRC_FILES example/main.cpp Elgamal_cipher/Elgamal.cpp Elgamal_cipher/Elgamal.h Elgamal_sign.cpp Elgamal_sign.h)

add_executable(Elgamal_sign_scheme ${SRC_FILES})