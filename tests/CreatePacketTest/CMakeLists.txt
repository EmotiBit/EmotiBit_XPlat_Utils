cmake_minimum_required(VERSION 3.10)
project(CreatePacketTest)

include_directories(${CMAKE_SOURCE_DIR}/../../src)

add_executable(CreatePacketTest
    src/main.cpp
    ../../src/EmotiBitPacket.cpp
)