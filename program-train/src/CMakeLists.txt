# readme.txt
# Created Time: 2016-04-23 14:20:56
# Last modified: 2016-04-23 14:24:57
#
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
)

aux_source_directory(. SRC_LIST)

add_executable(program-train ${SRC_LIST})

set(link_lib
    pthread
    dl
)

target_link_libraries(program-train ${link_lib})

