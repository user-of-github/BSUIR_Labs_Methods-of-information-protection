cmake_minimum_required(VERSION 3.19)
project(LR2)

set(CMAKE_CXX_STANDARD 20)

add_executable(LR2 main.cpp STB_34_101_31_2011/stb_34_101_31_2011.cpp STB_34_101_31_2011/stb_34_101_31_2011.hpp ./utils/utils.cpp ./utils/utils.hpp STB_34_101_31_2011/constants.hpp)