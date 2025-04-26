cmake_minimum_required(VERSION 3.31)
project(fulgur-logger VERSION 1.0 LANGUAGES CXX)

add_library(fulgur-logger INTERFACE)

target_include_directories(fulgur-logger INTERFACE src)