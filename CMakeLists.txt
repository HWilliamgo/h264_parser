cmake_minimum_required(VERSION 3.17)
project(h264_parser)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)
add_executable(h264_parser h264parser.c main.cpp)