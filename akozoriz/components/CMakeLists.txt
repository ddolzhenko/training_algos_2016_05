
include_directories(
    include
    )

set(SOURCES
    src/search.cc
    src/sort.cc
    )

add_library("components" ${SOURCES})
