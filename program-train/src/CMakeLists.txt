# readme.txt
# Created Time: 2016-04-23 14:20:56
# Last modified: 2016-07-30 09:42:35
#
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/libs
    ${PROJECT_SOURCE_DIR}/src/srcs
    ${PROJECT_SOURCE_DIR}/src/srcs/c_src
    ${PROJECT_SOURCE_DIR}/src/srcs/ooc
    ${PROJECT_SOURCE_DIR}/src/srcs/sort
    ${PROJECT_SOURCE_DIR}/src/srcs/tools
)

#aux_source_directory(. SRC_LIST)
#aux_source_directory(./libs/ SRC_LIST)
#aux_source_directory(./srcs/ SRC_LIST)
#aux_source_directory(./srcs/tools/ SRC_LIST)
#aux_source_directory(./srcs/c_src/ SRC_LIST)
#aux_source_directory(./srcs/ooc/ SRC_LIST)
#aux_source_directory(./srcs/sort/ SRC_LIST)

set(SRC_LIST
   main.cpp 
#   srcs/c_src/regex_test.cpp
#   srcs/c_src/regex_cpp11.cpp
#   srcs/c_src/smart_pointer.cpp
#  srcs/c_src/other.cpp
#  srcs/c_src/generic_test.cpp
   srcs/c_src/thread_test.cpp
   srcs/c_src/condition_variable.cpp
#  srcs/c_src/container_test.cpp
#    srcs/c_src/lambda.cpp
#    srcs/sort/insertion_sort.c
)

add_executable(program-train ${SRC_LIST})

set(libs_path ${PROJECT_SOURCE_DIR}/src/libs)

set(link_lib
    ${libs_path}/libsqlite3.a
    pthread
    dl
)

target_link_libraries(program-train ${link_lib})

