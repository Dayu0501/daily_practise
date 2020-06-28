# 指定cmake最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

#支持c++11
add_definitions(-std=c++11)

#支持gdb -g
add_definitions("-Wall -g")

# 指定工程的名称
PROJECT(mysqlDemo)

# 查找当前目录下的所有源文件,并将名称保存到 DIR_SRCS 变量
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)

# 添加 math 子目录
#add_subdirectory(json)

#指定头文件目录位置
#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/json)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/mysql)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/uuid)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/test)

#添加共享库搜索路径
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/mysql)
#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/json)

#生成可执行文件
ADD_EXECUTABLE(mysqlDemo ${DIR_SRCS} "src/DB_tools.h" "src/DB_tools.cpp" test/left_right_value_test.cpp test/time_interval.h test/time_interval_test.cpp test/move_constructor_test.cpp test/initialization_test.cpp)

#为mysqlDemo添加共享库链接
TARGET_LINK_LIBRARIES(mysqlDemo libmysqlclient.so)
TARGET_LINK_LIBRARIES(mysqlDemo libuuid.so)
#TARGET_LINK_LIBRARIES(mysqlDemo libjson.so)