cmake_minimum_required(VERSION 3.16)
project(stable_version)

set(CMAKE_CXX_STANDARD 14)

add_executable(stable_version
        file_operation/write_operation.cpp
        file_operation/direct_io.c
        file_operation/write_test.c)
