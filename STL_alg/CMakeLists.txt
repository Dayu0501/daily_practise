cmake_minimum_required(VERSION 3.16)
project(STL_alg)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. CPP_DIR)

include_directories(.)

add_executable(STL_alg
        algorithmUnity.h
        ${CPP_DIR})
