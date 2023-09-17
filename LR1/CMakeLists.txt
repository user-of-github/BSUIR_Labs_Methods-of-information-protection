cmake_minimum_required(VERSION 3.19)
project(LR1)

set(CMAKE_CXX_STANDARD 20)

add_executable(LR1 main.cpp utils.cpp gost28147_89.cpp gost28147_89.hpp)