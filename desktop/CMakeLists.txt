cmake_minimum_required(VERSION 3.20)

project(MiniLogicAnalyzer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MiniLogicAnalyzer
        src/main.cpp
        src/SerialPort.cpp
        src/SerialPort.h
        src/Capture.cpp
        src/Capture.h
)