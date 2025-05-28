cmake_minimum_required(VERSION 3.10)
project(EmotiBitDataTester)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(EmotiBitDataTester
    src/EmotiBitDataTester.cpp
    src/EmotiBitPacket.cpp
)