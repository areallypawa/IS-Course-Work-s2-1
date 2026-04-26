cmake_minimum_required(VERSION 3.10)

project(TreeProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(TreeProject
    src/main.cpp
    src/menu.cpp
    src/bst.cpp
    src/avl.cpp
    src/red_black.cpp
)