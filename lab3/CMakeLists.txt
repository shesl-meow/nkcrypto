cmake_minimum_required(VERSION 3.15)
project(Aes)

set(CMAKE_CXX_STANDARD 11)

set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_library(AesExport ./src/Aes.cpp)
target_include_directories(AesExport
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 AesExport)