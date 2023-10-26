cmake_minimum_required(VERSION 3.26)
project(LR6)

set(CMAKE_CXX_STANDARD 23)

add_executable(LR6 main.cpp ECPoint.hpp
        gost.hpp
        base.hpp)
