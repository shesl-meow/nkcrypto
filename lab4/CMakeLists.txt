cmake_minimum_required(VERSION 3.15)
project(lab4)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(lab4 main.cpp src/Rsa.cpp)
target_link_libraries(lab4 gmp)