cmake_minimum_required(VERSION 3.10)
project(FlappyBird)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(flappy
    src/main.cpp
    src/game.cpp
    src/physics.cpp
    src/obstacles.cpp
    src/render.cpp
)
