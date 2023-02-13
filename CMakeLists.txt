cmake_minimum_required(VERSION 3.0.0)

project(asyncLog)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include/utils/)
include_directories(${PROJECT_SOURCE_DIR}/include/log/)
#include_directories(${PROJECT_SOURCE_DIR}/include/new/)

#add_subdirectory(src)
add_subdirectory(test)