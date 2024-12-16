cmake_minimum_required(VERSION 3.28)
project(task_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(${CMAKE_PROJECT_NAME}_run main.cpp)
# set this flag when running coverage tests in Clion
set(CMAKE_CXX_FLAGS "--coverage")

# generate debug information
#set(CMAKE_CXX_FLAGS "-g")

include_directories(src)
add_subdirectory(src)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)

