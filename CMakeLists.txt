cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(game ${SOURCES})

target_sources(game PRIVATE
    src/network/src/utils.cc
    src/network/src/baseLayer.cc
    src/network/src/layers/activation.cc
    src/network/src/layers/conv1d.cc
    src/network/src/layers/conv2d.cc
    src/network/src/layers/dense.cc
    src/network/src/layers/elu.cc
    src/network/src/layers/embedding.cc
    src/network/src/layers/flatten.cc
    src/network/src/layers/lstm.cc
    src/network/src/layers/locally1d.cc
    src/network/src/layers/locally2d.cc
    src/network/src/layers/maxPooling2d.cc
    src/network/src/layers/batchNormalization.cc
    src/network/src/model.cc
    src/network/src/tensor.cc
)
