cmake_minimum_required(VERSION 3.14)
project(example_gtest)

message("TRY Installing gtest")

include(gtest_install.cmake)

enable_testing()

add_executable(
  hello_test
  test1.cpp
)

target_link_libraries(
  hello_test gtest_main
)

# target_include_directories(hello_test PUBLIC 
# ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

target_include_directories(
        hello_test 
        PUBLIC 
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
        hello_test
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../library
)
target_link_libraries(hello_test my_lib)

include(GoogleTest)
gtest_discover_tests(hello_test)