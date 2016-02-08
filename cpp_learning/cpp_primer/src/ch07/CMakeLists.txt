set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Weverything -Wno-c++11-extensions \
-Wno-c++98-compat -Wno-c++98-compat-pedantic")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(ch07 chpater7.cc)

