cmake_minimum_required(VERSION 3.15)
project(exe1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(shift_crypto src/shift_crypto.cpp)
add_executable(single_table_crypto src/single_table_crypto.cpp)
add_executable(freq_analysis src/freq_analysis.cpp)