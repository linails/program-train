# readme.txt
# Created Time: 2016-04-23 14:20:56
# Last modified: 2016-04-28 17:21:25
#
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/libs
    ${PROJECT_SOURCE_DIR}/src/srcs
    ${PROJECT_SOURCE_DIR}/src/srcs/c_src
    ${PROJECT_SOURCE_DIR}/src/srcs/ooc
    ${PROJECT_SOURCE_DIR}/src/srcs/sort
)

aux_source_directory(. SRC_LIST)
aux_source_directory(./libs/ SRC_LIST)
aux_source_directory(./srcs/ SRC_LIST)
aux_source_directory(./srcs/c_src/ SRC_LIST)
aux_source_directory(./srcs/ooc/ SRC_LIST)
aux_source_directory(./srcs/sort/ SRC_LIST)

add_executable(program-train ${SRC_LIST})

set(libs_path ${PROJECT_SOURCE_DIR}/src/libs)

set(link_lib
    ${libs_path}/libsqlite3.a
    pthread
    dl
)

target_link_libraries(program-train ${link_lib})

