cmake_minimum_required(VERSION 3.10)
project(ArduinoStringTest)

add_executable(ArduinoStringTest
    src/main.cpp
)

target_include_directories(ArduinoStringTest PRIVATE ${CMAKE_SOURCE_DIR}/../../src)