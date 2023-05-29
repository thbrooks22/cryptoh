cmake_minimum_required(VERSION 3.25)
project(cryptoh_project)

set(CMAKE_CXX_STANDARD 23)

include_directories(cryptoh_lib)
add_subdirectory(cryptoh_lib)
add_subdirectory(cryptoh_test)