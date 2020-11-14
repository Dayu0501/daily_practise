cmake_minimum_required(VERSION 3.16)
project(c__11_learn)

set(CMAKE_CXX_STANDARD 14)

add_executable(test smart_ptr.cpp standard_shared_ptr.cpp move_semantic.cpp container.cpp)
add_executable(smart_ptr smart_ptr.cpp)
add_executable(standard_shared_ptr standard_shared_ptr.cpp)
add_executable(move_semantic move_semantic.cpp)
add_executable(container container.cpp)