cmake_minimum_required(VERSION 3.5)

project(Library VERSION 0.0.2)

message("INSTALL LIB")

configure_file(
        config.h.in 
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_library(my_lib STATIC lib.cpp lib.h)
set_target_properties(
        my_lib PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_include_directories(
        my_lib 
        PRIVATE 
        ${CMAKE_CURRENT_BINARY_DIR}
)