cmake_minimum_required(VERSION 3.10)
SET(CMAKE_C_COMPLIER gcc)
SET(CMAKE_C_STANDARD 11)
project(Book-Management-System)
file(GLOB SRC_FILES 
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c")
add_executable(BookManageSystem ${SRC_FILES})
