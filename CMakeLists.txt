cmake_minimum_required(VERSION 3.25)
project(cryptoh)

set(CMAKE_CXX_STANDARD 23)

add_library(cryptoh SHARED hash/sha/sha256.h hash/sha/sha256.cpp)
