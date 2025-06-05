cmake_minimum_required(VERSION 3.10)
project(ArduinoStringTest)

include_directories(${CMAKE_SOURCE_DIR}/../../src)

add_executable(ArduinoStringTest
    src/main.cpp
    ../../src/ArduinoString.h
)