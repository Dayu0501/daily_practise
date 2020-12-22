cmake_minimum_required(VERSION 3.16)
project(Ring_Log_NoLoseData)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Ring_Log_NoLoseData
        example/multi-thread-example.cc
        example/single-thread-example.cc
        src/rlog.cc
        src/rlog.h
        "test/echo server QPS/echo_cli.cc"
        "test/echo server QPS/echo_serv.cc"
        "test/multi thread/mtest.cc"
        "test/single thread/test.cc"
        tool/flusher.cc)
