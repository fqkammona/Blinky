cmake_minimum_required(VERSION 3.24)
project(Blinky)

set(CMAKE_CXX_STANDARD 17)

add_executable(Blinky main.cpp Master.cpp Master.h Slave.cpp Slave.h)
