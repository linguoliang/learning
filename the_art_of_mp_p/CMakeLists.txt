cmake_minimum_required(VERSION 3.2)
project(the_art_of_mp_p)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Weverything -Wno-c++11-extensions -Wno-c++98-compat")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" THE_ART_OF_MP_P_SOURCE_FILES)

add_executable(the_art_of_mp_p ${THE_ART_OF_MP_P_SOURCE_FILES})
target_link_libraries(the_art_of_mp_p ch1)
