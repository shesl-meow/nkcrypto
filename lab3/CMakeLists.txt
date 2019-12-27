cmake_minimum_required(VERSION 3.15)
project(Aes VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)


add_library(AesExport ./src/Aes.cpp src/Squre4Marix.cpp)
target_include_directories(AesExport
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
set_target_properties(AesExport
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_executable(lab3 main.cpp TestCase.h)
target_link_libraries(lab3 AesExport)
set_target_properties(lab3
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
