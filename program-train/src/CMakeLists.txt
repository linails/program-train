# readme.txt
# Created Time: 2016-04-23 14:20:56
# Last modified: 2016-08-08 22:02:52
#
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/libs
    ${PROJECT_SOURCE_DIR}/src/libs/rapidjson
    ${PROJECT_SOURCE_DIR}/src/srcs
    ${PROJECT_SOURCE_DIR}/src/srcs/primer
    ${PROJECT_SOURCE_DIR}/src/srcs/stl
    ${PROJECT_SOURCE_DIR}/src/srcs/boost
    ${PROJECT_SOURCE_DIR}/src/srcs/ooc
    ${PROJECT_SOURCE_DIR}/src/srcs/tools
    ${PROJECT_SOURCE_DIR}/src/srcs/linux
    ${PROJECT_SOURCE_DIR}/src/srcs/db
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm
)

#aux_source_directory(. SRC_LIST)
#aux_source_directory(./libs/ SRC_LIST)
#aux_source_directory(./srcs/ SRC_LIST)
#aux_source_directory(./srcs/tools/ SRC_LIST)
#aux_source_directory(./srcs/primer/ SRC_LIST)
#aux_source_directory(./srcs/linux/ SRC_LIST)
#aux_source_directory(./srcs/stl/ SRC_LIST)
#aux_source_directory(./srcs/primer/ SRC_LIST)
#aux_source_directory(./srcs/ooc/ SRC_LIST)
#aux_source_directory(./srcs/sort/ SRC_LIST)

set(SRC_LIST
   main.cpp 
#   srcs/primer/regex_test.cpp
#   srcs/primer/regex_cpp11.cpp
#   srcs/primer/smart_pointer.cpp
   srcs/primer/other.cpp
#  srcs/primer/generic_test.cpp
   srcs/primer/thread_test.cpp
   srcs/primer/condition_variable.cpp
   srcs/primer/class_test.cpp
   srcs/stl/container_test.cpp
   srcs/primer/chrono_test.cpp
   srcs/primer/exception_test.cpp
#    srcs/primer/lambda.cpp
   srcs/db/db_test.cpp
   srcs/db/normal.cpp
)

add_executable(program-train ${SRC_LIST})

set(libs_path ${PROJECT_SOURCE_DIR}/src/libs)

set(link_lib
    ${libs_path}/libsqlite3.a
    pthread
    dl
)

target_link_libraries(program-train ${link_lib})

