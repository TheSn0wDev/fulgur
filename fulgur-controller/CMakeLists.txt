cmake_minimum_required(VERSION 3.25.1)
project(fulgur-controller VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(nlohmann_json 3.12.0 REQUIRED)

include_directories(${SDL3_INCLUDE_DIRS})

add_executable(fulgur-controller
    src/main.cpp
    src/controller/PS5Controller.cpp
    src/utils/welcome.cpp
)

add_compile_definitions(SDL_DISABLE_OLD_NAMES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

target_include_directories(fulgur-controller PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

link_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(fulgur-controller PRIVATE 
    SDL3::SDL3
    nlohmann_json::nlohmann_json
    fulgur-messaging
    fulgur-logger
)


target_compile_options(fulgur-controller PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(fulgur-controller PRIVATE SDL_DISABLE_OLD_NAMES)