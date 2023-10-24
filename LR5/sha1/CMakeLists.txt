cmake_minimum_required(VERSION 3.19)
project(sha1)

set(CMAKE_CXX_STANDARD 20)

add_executable(sha1 main.cpp ./sha/include/sha1.hpp ./sha/src/sha1.cpp ./sha/include/sha_utils.hpp ./sha/src/sha_utils.cpp)