# readme.txt
# Created Time: 2016-04-23 14:20:56
# Last modified: 2017-04-14 17:15:39
#
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/libs
    ${PROJECT_SOURCE_DIR}/src/libs/rapidjson
    ${PROJECT_SOURCE_DIR}/src/srcs
    ${PROJECT_SOURCE_DIR}/src/srcs/primer
    ${PROJECT_SOURCE_DIR}/src/srcs/complex
    ${PROJECT_SOURCE_DIR}/src/srcs/stl
    ${PROJECT_SOURCE_DIR}/src/srcs/boost
    ${PROJECT_SOURCE_DIR}/src/srcs/ooc
    ${PROJECT_SOURCE_DIR}/src/srcs/tools
    ${PROJECT_SOURCE_DIR}/src/srcs/linux
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/network
    ${PROJECT_SOURCE_DIR}/src/srcs/db
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm/stl
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm/ds
    ${PROJECT_SOURCE_DIR}/src/srcs/cases
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/case001/src
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/case001/test
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
#   srcs/primer/other.cpp
#   srcs/primer/ctest.c
#   srcs/primer/thread_test.cpp
#   srcs/primer/condition_variable.cpp
#   srcs/primer/class_test.cpp
#   srcs/primer/chrono_test.cpp
#   srcs/primer/exception_test.cpp
#   srcs/primer/lambda.cpp
#   srcs/primer/generic_test.cpp
#   srcs/primer/template_test.cpp
#   srcs/primer/overload.cpp
#   srcs/complex/
   srcs/linux/linux_main.cpp
   srcs/linux/network/server-udp.c
   srcs/linux/network/server-tcp.c
   srcs/linux/network/fd-test.c
   srcs/linux/network/endian-conv.c
   srcs/linux/network/socket-opt.c
   srcs/linux/network/p2p-server.c
   srcs/linux/network/server-tcp.cpp
#   srcs/linux/sys_cmd.cpp
#   srcs/stl/container_test.cpp
#   srcs/db/db_test.cpp
#   srcs/db/normal.cpp
#   srcs/algorithm/algorithm_main.cpp
#   srcs/algorithm/stl/non-mutating-algo.cpp
#   srcs/algorithm/stl/mutating-algo.cpp
#   srcs/algorithm/stl/sorting-algo.cpp
#   srcs/algorithm/ds/data_structure.cpp
#   srcs/algorithm/ds/seq_list.cpp
#####################################################################
   srcs/tools/timer.cpp
   srcs/tools/timing.c
   srcs/tools/format.c
#   srcs/cases/cases_main.cpp
#   srcs/cases/case001/src/infinite_loops_v2.cpp
#   srcs/cases/case001/test/test_main.cpp
)

add_executable(program-train ${SRC_LIST})

if ("${SYSTEM_TYPE}" STREQUAL "i686")
set(libs_path ${PROJECT_SOURCE_DIR}/src/libs/i686)
endif()

if ("${SYSTEM_TYPE}" STREQUAL "x86_64")
set(libs_path ${PROJECT_SOURCE_DIR}/src/libs/x86_64)
endif()

set(link_lib
    ${libs_path}/libsqlite3.a
    pthread
    dl
)

target_link_libraries(program-train ${link_lib})

