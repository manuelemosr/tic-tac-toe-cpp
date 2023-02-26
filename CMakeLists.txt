cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(game ${SOURCES})
