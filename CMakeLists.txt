cmake_minimum_required(VERSION 3.26)
project(MacMahon)

set(CMAKE_CXX_STANDARD 17)

add_executable(MacMahon main.cpp
        file/file.cpp
        board/tile/tile.cpp
        board/board.h
        board/board.cpp)