project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_task1_run
        BitArrayTests.cpp
        main.cpp)

target_link_libraries(Google_Tests_task1_run ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(Google_Tests_task1_run gtest gtest_main)