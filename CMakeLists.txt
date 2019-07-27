cmake_minimum_required(VERSION 3.8)

project(delta_raytracing)

find_package(OpenMP REQUIRED)
include_directories("include")
add_subdirectory(src)