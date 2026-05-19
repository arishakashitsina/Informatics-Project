cmake_minimum_required(VERSION 3.10)
project(FlappyBird)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

add_executable(flappy
    src/main.cpp
    src/Game.cpp
    src/Bird.cpp
    src/PipeManager.cpp
    src/AssetManager.cpp
)

target_link_libraries(flappy sfml-graphics sfml-window sfml-system sfml-audio)
target_include_directories(flappy PRIVATE ${SFML_INCLUDE_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
