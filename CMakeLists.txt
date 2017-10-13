cmake_minimum_required(VERSION 3.5)
project(thread)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES cv.cc)
add_executable(print ${SOURCE_FILES})
target_link_libraries(print pthread)
