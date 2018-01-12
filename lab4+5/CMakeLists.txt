cmake_minimum_required(VERSION 3.8)
project(lab4)

set(CMAKE_CXX_STANDARD 11)
find_package (Threads)
set(SOURCE_FILES main.cpp Reader.h Exception.h Factorisator.h)
add_executable(lab4 ${SOURCE_FILES})