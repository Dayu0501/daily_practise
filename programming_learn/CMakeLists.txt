cmake_minimum_required(VERSION 3.1.6)
project(programming_learn)

set(CMAKE_CXX_STANDARD 14)

#add_executable(programming_learn
#        friend_learn.cpp)

add_executable(friend_learn friend_learn.cpp)
add_executable(virtual_inherit virtual_inherit.cpp)
add_executable(testtest testtest.cpp)
add_executable(singleton singleton.cpp)
add_executable(singleton_magic_static singleton_magic_static.cpp)
add_executable(string_ref_count string_ref_count.cpp)
add_executable(cpp_mem_management cpp_mem_management.cpp MString.cpp initializer_list_learn.cpp share_file_write.cpp dailyTest.cpp test_macro_and_noLock.cpp noMutexQueue.cpp public_private.cpp)
add_executable(renameFile renameFile.cpp)
add_executable(linkByArry listByArry.cpp)
add_executable(MString MString.cpp)
add_executable(initializer_list_learn initializer_list_learn.cpp)
add_executable(share_file_write share_file_write.cpp)
add_executable(dailyTest dailyTest.cpp)
#add_executable(fileOperation1 fileOperation.cpp)
add_executable(test_macro test_macro_and_noLock.cpp)
add_executable(public_private public_private.cpp)