CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(myLib)

AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)

ADD_LIBRARY(mylib SHARED ${DIR_LIB_SRCS})