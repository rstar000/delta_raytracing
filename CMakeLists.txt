cmake_minimum_required(VERSION 3.8)

project(delta_raytracing)
set(CMAKE_CXXFLAGS, "-g")
find_package(OpenMP REQUIRED)
include_directories("include")
add_subdirectory(src)