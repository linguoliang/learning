include_directories(./ include)
add_library(gtest STATIC src/gtest-all.cc)
target_link_libraries(gtest pthread)
