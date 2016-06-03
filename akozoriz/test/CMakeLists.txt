
include_directories(
    include
    )

set(SOUCES_TEST
    src/helpers.cc
    src/macro.cc
    )

add_library("test_lib" ${SOUCES_TEST})
