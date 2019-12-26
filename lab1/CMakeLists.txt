cmake_minimum_required(VERSION 3.15)
project(exe1)

set(CMAKE_CXX_STANDARD 11)

add_executable(shift_crypto shift_crypto.cpp)
add_executable(single_table_crypto single_table_crypto.cpp)
add_executable(freq_analysis freq_analysis.cpp)