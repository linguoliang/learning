cmake_minimum_required(VERSION 3.4)
project(LocalWordCount)

add_subdirectory(Deps)
add_subdirectory(LocalWordCount)
add_subdirectory(UnitTests)

enable_testing()
add_test(NAME ./unit_test COMMAND ./unit_test)
