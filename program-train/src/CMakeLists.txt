# readme.txt
# Created Time: 2016-04-23 14:20:56
# Last modified: 2017-02-14 13:39:38
#
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/libs
    ${PROJECT_SOURCE_DIR}/src/libs/rapidjson
    ${PROJECT_SOURCE_DIR}/src/libs/cppjieba
    ${PROJECT_SOURCE_DIR}/src/libs/jsoncpp/src
    ${PROJECT_SOURCE_DIR}/src/libs/cppjieba/limonp
    ${PROJECT_SOURCE_DIR}/src/libs/x86_64/include
    ${PROJECT_SOURCE_DIR}/src/srcs
    ${PROJECT_SOURCE_DIR}/src/srcs/primer
    ${PROJECT_SOURCE_DIR}/src/srcs/advanced
    ${PROJECT_SOURCE_DIR}/src/srcs/advanced/design-pattern
    ${PROJECT_SOURCE_DIR}/src/srcs/complex
    ${PROJECT_SOURCE_DIR}/src/srcs/stl
    ${PROJECT_SOURCE_DIR}/src/srcs/boost
    ${PROJECT_SOURCE_DIR}/src/srcs/ooc
    ${PROJECT_SOURCE_DIR}/src/srcs/tools
    ${PROJECT_SOURCE_DIR}/src/srcs/linux
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/network
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/os
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/process
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/threads
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/io
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/server
    ${PROJECT_SOURCE_DIR}/src/srcs/sep/
    ${PROJECT_SOURCE_DIR}/src/srcs/db
    ${PROJECT_SOURCE_DIR}/src/srcs/db/sqlite
    ${PROJECT_SOURCE_DIR}/src/srcs/db/postgresql
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm/stl
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm/ds
    ${PROJECT_SOURCE_DIR}/src/srcs/cases
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/case001/src
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/case001/test
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/case002
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/case003
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases/case-json
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases/case-openssl
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
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/primer/primer.cpp
#   srcs/primer/regex_test.cpp
#   srcs/primer/regex_cpp11.cpp
#   srcs/primer/smart_pointer.cpp
#   srcs/primer/other.cpp
   srcs/primer/c-primer.c
#   srcs/primer/ctest.c
   srcs/primer/jump.c
#   srcs/primer/thread_test.cpp
#   srcs/primer/condition_variable.cpp
#   srcs/primer/class_test.cpp
#   srcs/primer/class-enhenced.cpp
#   srcs/primer/chrono_test.cpp
#   srcs/primer/exception_test.cpp
#   srcs/primer/lambda.cpp
#   srcs/primer/template.cpp
#   srcs/primer/overload.cpp
#   srcs/primer/operator-overload.cpp
#   srcs/primer/type-traits.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/advanced/advanced.cpp
#   srcs/advanced/design-pattern/design-pattern.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/complex/
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/linux/mlinux.cpp
#   srcs/linux/network/server-udp.c
#   srcs/linux/network/server-tcp.c
#   srcs/linux/network/fd-test.c
#   srcs/linux/network/endian-conv.c
#   srcs/linux/sys_cmd.cpp
   srcs/linux/os/mos.cpp
#   srcs/linux/io/io.cpp
#   srcs/linux/process/process.cpp
#   srcs/linux/process/ipc_msgq.c
#   srcs/linux/threads/cthread.cpp
   srcs/linux/server/server.cpp
   srcs/linux/server/log.c
   srcs/linux/server/user.c
   srcs/linux/server/process-rela.c
   srcs/linux/server/model.c
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/stl/container.cpp
#   srcs/stl/container-test.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/db/db-caller.cpp
   srcs/db/sqlite/normal.cpp
#   srcs/db/postgresql/normal-pg.cpp
#   srcs/db/sqlite/advanced.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/algorithm/malgorithm.cpp
   srcs/algorithm/stl/non-mutating-algo.cpp
#   srcs/algorithm/stl/mutating-algo.cpp
#   srcs/algorithm/stl/sorting-algo.cpp
#   srcs/algorithm/ds/data-structure.cpp
#   srcs/algorithm/ds/data-structure.c
#   srcs/algorithm/ds/linear-list.cpp
#   srcs/algorithm/ds/seq-list.cpp
#   srcs/algorithm/ds/mstack.cpp
#   srcs/algorithm/ds/mqueue.cpp
#   srcs/algorithm/ds/tree.cpp
#   srcs/algorithm/ds/graph.cpp
#   srcs/algorithm/ds/search.cpp
#   srcs/algorithm/ds/sort.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/sep/sep.cpp
#####################################################################
   srcs/tools/timer.cpp
   srcs/tools/timing.c
   srcs/tools/format.c
   srcs/cases/cases.cpp
   srcs/cases/exlib-cases/exlibCases.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/case001/src/infinite_loops_v2.cpp
#   srcs/cases/case001/src/infinite_loops_v3.cpp
#   srcs/cases/case001/test/test_main.cpp
#   srcs/cases/case001/test/v3_test.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/case002/dic-parser.cpp
#   srcs/cases/case002/formatParsing.cpp
#   srcs/cases/case002/format-parser.cpp
#   srcs/cases/case002/regex_common.cpp
#   srcs/cases/case002/rfileoprt.cpp
#   srcs/cases/case002/rwfileoprt.cpp
#   srcs/cases/case002/stringTools.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/cases/case003/key-bind-main.cpp
   srcs/cases/case003/disk.cpp
   srcs/cases/case003/msg.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/cases/exlib-cases/case-json/mjson.cpp
#   srcs/cases/exlib-cases/case-openssl/sha-test.cpp
#   srcs/cases/exlib-cases/case-openssl/openssl-test.cpp
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
    ${libs_path}/libjson.a
    ${libs_path}/lib/libssl.a
    ${libs_path}/lib/libcrypto.a
    ${libs_path}/lib/libpqxx.a
    pthread
    dl
    pq
)

target_link_libraries(program-train ${link_lib})

