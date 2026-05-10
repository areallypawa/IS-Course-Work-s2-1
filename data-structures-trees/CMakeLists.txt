cmake_minimum_required(VERSION 3.10)

project(App)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(App
    trees/src/main.cpp
    trees/src/binary_tree.cpp
    trees/src/bst.cpp
    trees/src/avl.cpp
    trees/src/red_black.cpp
    trees/src/menu.cpp
)

target_include_directories(App PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/trees/include
)


