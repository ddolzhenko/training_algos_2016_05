set (${CMAKE_SOURCE_DIR}/test TEST_DIR)
set (${CMAKE_SOURCE_DIR}/components COMPONENTS_DIR)

#FLAGS

set (CMAKE_CXX_FLAGS -std=c++11)

# SUBDIRECTOIES

add_subdirectory(test)
add_subdirectory(components)

# MAIN()

include_directories(
    ${TEST_DIR}/include
    ${COMPONENTS_DIR}/include
    )

set(LIBRARIES
test_lib
components
)

set(SOURCES
main.cc
)

add_executable("search" ${SOURCES})
target_link_libraries("search" ${LIBRARIES})

