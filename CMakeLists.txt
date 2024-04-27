cmake_minimum_required(VERSION 3.23)
project(NitroCppTest_SeanMcGoff)

# Ensures C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Package Lists
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# src directory
add_subdirectory(src)

# testing directory
enable_testing()
add_subdirectory(test)

