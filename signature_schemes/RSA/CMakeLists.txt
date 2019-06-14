cmake_minimum_required(VERSION 3.9)
project(rsa_sign_scheme)

set(CMAKE_CXX_STANDARD 11)
set(SRC_RSA_SIGN_SCHEME example/main.cpp rsa_cipher/rsa.cpp rsa_cipher/rsa.h rsa_cipher/rsa_sign.cpp rsa_cipher/rsa_sign.h)

add_executable(rsa_sign_scheme ${SRC_RSA_SIGN_SCHEME})
