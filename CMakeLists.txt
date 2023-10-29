cmake_minimum_required(VERSION 3.26)
project(MacMahon)

set(CMAKE_CXX_STANDARD 17)

add_executable(MacMahon main.cpp
        fichier/fichier.cpp
        plateau/tuile/tuile.cpp
        plateau/plateau.h
        plateau/plateau.cpp)