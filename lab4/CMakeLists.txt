cmake_minimum_required(VERSION 3.15)
project(lab4)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/include)
add_executable(lab4 main.cpp src/Rsa.cpp)
