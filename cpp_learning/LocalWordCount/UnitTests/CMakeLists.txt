set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/Deps/gtest/include)
include_directories(${PROJECT_SOURCE_DIR}/Deps)
include_directories(${PROJECT_SOURCE_DIR}/LocalWordCount/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Weverything -Wno-c++11-extensions -Wno-c++98-compat -Wno-c++98-compat-pedantic")

add_library(conf_obj STATIC ${PROJECT_SOURCE_DIR}/LocalWordCount/src/Conf.cc)
add_library(util_obj STATIC ${PROJECT_SOURCE_DIR}/LocalWordCount/src/Util.cc)

aux_source_directory(${PROJECT_SOURCE_DIR}/UnitTests/src UNITTEST_SOURCE_FILES)
add_executable(unit_test ${UNITTEST_SOURCE_FILES})

target_link_libraries(unit_test gtest conf_obj util_obj)
