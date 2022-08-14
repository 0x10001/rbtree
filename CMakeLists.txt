cmake_minimum_required(VERSION 3.0)
project(rbtree C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(src SRC)
aux_source_directory(test TEST)

add_executable(rbtree ${SRC} ${TEST})
