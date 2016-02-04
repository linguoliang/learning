set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Weverything -Wno-c++11-extensions \
    -Wno-c++98-compat -Wno-c++98-compat-pedantic")
include_directories(${PROJECT_SOURCE_DIR}/Deps)
aux_source_directory(${PROJECT_SOURCE_DIR}/LocalWordCount/src LOCALWORDCOUNT_SOURCE_FILES)

add_executable(local_word_count ${LOCALWORDCOUNT_SOURCE_FILES})
