# readme.txt
# Created Time: 2016-04-23 14:20:56
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
    ${PROJECT_SOURCE_DIR}/src/srcs/linux/shell
    ${PROJECT_SOURCE_DIR}/src/srcs/sep/
    ${PROJECT_SOURCE_DIR}/src/srcs/db
    ${PROJECT_SOURCE_DIR}/src/srcs/db/sqlite
    ${PROJECT_SOURCE_DIR}/src/srcs/db/postgresql
    ${PROJECT_SOURCE_DIR}/src/srcs/db/redis
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm/stl
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm/ds
    ${PROJECT_SOURCE_DIR}/src/srcs/algorithm/others
    ${PROJECT_SOURCE_DIR}/src/srcs/cases
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/infinite-loops/src
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/infinite-loops/test
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/dic-parser
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/key-bind
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/binditem-tetris
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/binditem-tetris/src
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/binditem-tetris/test
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/ts-parser
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/ts-parser/parser
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/ts-parser/parser/pmt
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/ts-parser/parser/pmt/descriptors
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/ts-parser/c-parser
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/code-formater
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/code-formater/test
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/case-other
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases/case-json
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases/case-openssl
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases/case-gtest
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases/case-xml
    ${PROJECT_SOURCE_DIR}/src/srcs/cases/exlib-cases/case-sigslot
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
   srcs/manager.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/primer/primer.cpp
#   srcs/primer/regex_test.cpp
#   srcs/primer/regex_cpp11.cpp
#   srcs/primer/smart_pointer.cpp
   srcs/primer/other.cpp
   srcs/primer/c-primer.c
   srcs/primer/clib-eg.c
   srcs/primer/clib-eg-linux.c
#   srcs/primer/ctest.c
   srcs/primer/jump.c
   srcs/primer/jump.cpp
#   srcs/primer/thread_test.cpp
#   srcs/primer/condition_variable.cpp
   srcs/primer/class_test.cpp
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
   srcs/linux/sys_cmd.cpp
   srcs/linux/os/mos.cpp
   srcs/linux/os/backtrace.cpp
   srcs/linux/os/file-manager.cpp
#   srcs/linux/io/io.cpp
   srcs/linux/process/process.cpp
   srcs/linux/process/ipc_msgq.c
   srcs/linux/process/ipc-shm.c
   srcs/linux/threads/cthread.cpp
   srcs/linux/server/server.cpp
   srcs/linux/server/log.c
   srcs/linux/server/user.c
   srcs/linux/server/process-rela.c
   srcs/linux/server/model.c
#   srcs/linux/server/daemon.cpp
   srcs/linux/shell/shell-server.cpp
   srcs/linux/shell/shell-client.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/stl/container.cpp
#   srcs/stl/container-test.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/db/db-caller.cpp
   srcs/db/sqlite/normal.cpp
   srcs/db/redis/normal-redis.cpp
#   srcs/db/postgresql/normal-pg.cpp
#   srcs/db/sqlite/advanced.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/algorithm/malgorithm.cpp
   srcs/algorithm/others/other-string.cpp
#   srcs/algorithm/others/finder.cpp
#   srcs/algorithm/others/finder-en.cpp
   srcs/algorithm/others/hsb2hsl.c
   srcs/algorithm/others/hue_driver.c
   srcs/algorithm/stl/non-mutating-algo.cpp
#   srcs/algorithm/stl/mutating-algo.cpp
#   srcs/algorithm/stl/sorting-algo.cpp
   srcs/algorithm/ds/data-structure.cpp
   srcs/algorithm/ds/data-structure.c
   srcs/algorithm/ds/linear-list.cpp
   srcs/algorithm/ds/seq-list.cpp
   srcs/algorithm/ds/mstack.cpp
   srcs/algorithm/ds/mqueue.cpp
   srcs/algorithm/ds/tree.cpp
   srcs/algorithm/ds/graph.cpp
   srcs/algorithm/ds/search.cpp
   srcs/algorithm/ds/sort.cpp
   srcs/algorithm/ds/sort.c
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/sep/sep.cpp
#####################################################################
   srcs/tools/timer.cpp
   srcs/tools/timing.c
   srcs/tools/stopwatch.c
   srcs/tools/cfg-loader.cpp
   srcs/tools/mbacktrace.c
   srcs/cases/cases.cpp
   srcs/cases/exlib-cases/exlibCases.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/infinite-loops/src/infinite_loops_v2.cpp
#   srcs/cases/infinite-loops/src/infinite_loops_v3.cpp
#   srcs/cases/infinite-loops/src/dev-child-sibling-tree.cpp
#   srcs/cases/infinite-loops/src/dev-avl-tree.cpp
#   srcs/cases/infinite-loops/src/conflict-check.cpp
#   srcs/cases/infinite-loops/src/illegal-check.cpp
#   srcs/cases/infinite-loops/test/tester-case001.cpp
#   srcs/cases/infinite-loops/test/test_main.cpp
#   srcs/cases/infinite-loops/test/v3_test.cpp
#   srcs/cases/infinite-loops/test/test-avl-tree.cpp
#   srcs/cases/infinite-loops/test/test-child-sibling-tree.cpp
#   srcs/cases/infinite-loops/test/test-conflict-check.cpp
#   srcs/cases/infinite-loops/test/test-illegal-check.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/dic-parser/dic-parser.cpp
#   srcs/cases/dic-parser/formatParsing.cpp
#   srcs/cases/dic-parser/format-parser.cpp
#   srcs/cases/dic-parser/regex_common.cpp
   srcs/cases/dic-parser/rfileoprt.cpp
#   srcs/cases/dic-parser/rwfileoprt.cpp
#   srcs/cases/dic-parser/stringTools.cpp
#   srcs/cases/dic-parser/disk-dic.cpp
#   srcs/cases/dic-parser/segmentation.cpp
#   srcs/cases/dic-parser/alpha-bet.cpp
#   srcs/cases/dic-parser/statistics.cpp
#   srcs/cases/dic-parser/denoise.cpp
#   srcs/cases/dic-parser/format-later-stage.cpp
#   srcs/cases/dic-parser/python-module.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/key-bind/key-bind-main.cpp
#   srcs/cases/key-bind/disk.cpp
#   srcs/cases/key-bind/msg.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/binditem-tetris/bit.cpp
#   srcs/cases/binditem-tetris/src/worker-thread.cpp
#   srcs/cases/binditem-tetris/src/binditem-tetris.cpp
#   srcs/cases/binditem-tetris/test/queue-tetris.cpp
#   srcs/cases/binditem-tetris/test/bt-test.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/ts-parser/ts-parser-main.cpp
#   srcs/cases/ts-parser/parser/ts-parser.cpp
#   srcs/cases/ts-parser/parser/ts-buffer.cpp
#   srcs/cases/ts-parser/parser/ts-unit.cpp
#   srcs/cases/ts-parser/parser/ts-pat.cpp
#   srcs/cases/ts-parser/parser/ts-pmt.cpp
#   srcs/cases/ts-parser/parser/ts-pes.cpp
#   srcs/cases/ts-parser/c-parser/ts-parser.c
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/cases/code-formater/code-formatter.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   srcs/cases/case-other/case-other.cpp
   srcs/cases/case-other/callstack-log.cpp
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   srcs/cases/exlib-cases/case-json/mjson.cpp
#   srcs/cases/exlib-cases/case-gtest/case-gtest.cpp
#   srcs/cases/exlib-cases/case-gtest/event-mecha.cpp
#   srcs/cases/exlib-cases/case-xml/xml-main.cpp
#   srcs/cases/exlib-cases/case-xml/xml-parser.cpp
#   srcs/cases/exlib-cases/case-openssl/sha-test.cpp
#   srcs/cases/exlib-cases/case-openssl/openssl-test.cpp
   srcs/cases/exlib-cases/case-sigslot/msigslot.cpp
)

add_executable(program-train ${SRC_LIST})

if ("${SYSTEM_TYPE}" STREQUAL "i686")
set(libs_path ${PROJECT_SOURCE_DIR}/src/libs/i686)
endif()

if ("${SYSTEM_TYPE}" STREQUAL "x86_64")
set(libs_path ${PROJECT_SOURCE_DIR}/src/libs/x86_64)
endif()

set(link_lib
    ${libs_path}/lib/libsqlite3.a
    ${libs_path}/lib/libjson.a
    ${libs_path}/lib/libssl.a
    ${libs_path}/lib/libcrypto.a
    ${libs_path}/lib/libpqxx.a
    ${libs_path}/lib/libgtest.a
    ${libs_path}/lib/libgtest_main.a
    ${libs_path}/lib/libtinyxml.a
    ${libs_path}/lib/libhiredis.a
    pthread
    dl
    pq
)

target_link_libraries(program-train ${link_lib})

