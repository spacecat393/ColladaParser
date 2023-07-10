cmake_minimum_required(VERSION 3.0.0)
project(ColladaParser VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

add_executable(ColladaParser
    src/Core.cpp
    src/FileReader/FileReader.cpp
    src/FileWriter/FileWriter.cpp
    src/FolderWriter/FolderWriter.cpp
    src/GraphicReader/GraphicReader.cpp
    src/stdafx.cpp)

target_include_directories(ColladaParser
    PUBLIC
    ../SE-Library/CPP/Math
    src)

target_precompile_headers(ColladaParser PUBLIC "src/stdafx.h")
