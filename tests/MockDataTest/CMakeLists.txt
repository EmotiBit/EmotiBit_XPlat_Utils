cmake_minimum_required(VERSION 3.10)
project(MockDataTest)

include_directories(${CMAKE_SOURCE_DIR}/../../src)

add_executable(MockDataTest
    src/main.cpp
    ../../src/EmotiBitPacket.cpp
)