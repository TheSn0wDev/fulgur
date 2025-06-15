cmake_minimum_required(VERSION 3.25.1)
project(fulgur-messaging VERSION 1.0 LANGUAGES CXX)

add_library(fulgur-messaging STATIC
    src/NatsMessagingBus.cpp
)

find_library(NATS_LIBRARY nats PATHS /usr/local/lib)

include_directories(/usr/local/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

target_include_directories(fulgur-messaging PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(fulgur-messaging PUBLIC ${NATS_LIBRARY})