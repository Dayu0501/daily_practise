cmake_minimum_required(VERSION 3.1.6)
project(programming_learn)

set(CMAKE_CXX_STANDARD 11)

#add_executable(programming_learn
#        friend_learn.cpp)

add_executable(friend_learn friend_learn.cpp)
add_executable(virtual_inherit virtual_inherit.cpp)
add_executable(testtest testtest.cpp)
add_executable(singleton singleton.cpp)
add_executable(singleton_magic_static singleton_magic_static.cpp)
add_executable(string_ref_count string_ref_count.cpp)