cmake_minimum_required(VERSION 3.25.1)
project(Fulgur VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) 

add_subdirectory(fulgur-controller)
add_subdirectory(fulgur-messaging)
add_subdirectory(fulgur-logger)
add_subdirectory(fulgur-pinger)
# add_subdirectory(fulgur-fpv-webrtc)