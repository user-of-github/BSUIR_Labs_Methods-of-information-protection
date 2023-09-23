cmake_minimum_required(VERSION 3.19)
project(LR2)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        LR2
        ./main.cpp
        ./secret_parameters.hpp
        ./utils/utils.cpp ./utils/utils.hpp
        ./STB_34_101_31_2011/core/constants.hpp
        ./STB_34_101_31_2011/core/core.hpp STB_34_101_31_2011/core/core.cpp
        ./STB_34_101_31_2011/gamming_with_reversal_connection/gamming_with_reversal_connection.hpp ./STB_34_101_31_2011/gamming_with_reversal_connection/gamming_with_reversal_connection.cpp
        ./STB_34_101_31_2011/simple_exhange/simple_exchange.cpp ./STB_34_101_31_2011/simple_exhange/simple_exchange.hpp
)