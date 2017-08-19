# readme.txt
# Created Time: 2016-04-23 14:15:51
# Last modified: 2017-08-19 20:10:14
#
cmake_minimum_required(VERSION 2.8)

project(program-train)

set(CMAKE_C_FLAGS "$ENV{CMAKE_C_FLAGS} -std=gnu99 -g -Wall")
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

add_subdirectory(src bin)

#
# [Note]
#
#set(CMAKE_C_FLAGS "$ENV{CMAKE_C_FLAGS} -std=c99 -g -Wall")
#
# Setting -std=c99 is to provide support for struct sigaction 
#
