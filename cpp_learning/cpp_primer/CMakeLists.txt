cmake_minimum_required(VERSION 3.2)
project(cpp_primer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Weverything -Wno-c++11-extensions \
-Wno-c++98-compat -Wno-c++98-compat-pedantic")

add_subdirectory(${PROJECT_SOURCE_DIR}/src/ch02)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ch03)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ch07)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ch08)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ch09)
