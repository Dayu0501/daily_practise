cmake_minimum_required(VERSION 3.16)
project(STL_alg)

aux_source_directory(*.cpp SRC_DIR)

set(CMAKE_CXX_STANDARD 14)

add_executable(STL_alg
        ${SRC_DIR} unity_head.h)
