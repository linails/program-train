# readme.txt
# Created Time: 2016-04-23 14:15:51
# Last modified: 2016-04-23 14:18:49
#
cmake_minimum_required(VERSION 2.8)

project(program-train)

set(CMAKE_C_FLAGS "$ENV{CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

add_subdirectory(src bin)

