cmake_minimum_required(VERSION 3.25.1)
project(fulgur-pinger VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nlohmann_json 3.12.0 REQUIRED)

add_executable(fulgur-pinger
    src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

target_include_directories(fulgur-pinger PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

link_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(fulgur-pinger PRIVATE 
    nlohmann_json::nlohmann_json
    fulgur-messaging
    fulgur-logger
)


target_compile_options(fulgur-pinger PRIVATE -Wall -Wextra -pedantic)