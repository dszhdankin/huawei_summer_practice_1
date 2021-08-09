set(GTEST_ROOT_DIR googletest)
set(GTEST_SOURCE_DIR googletest/googletest)

add_subdirectory(${GTEST_ROOT_DIR})
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

add_executable(test test1.cpp)
target_link_libraries(test gtest gtest_main)
