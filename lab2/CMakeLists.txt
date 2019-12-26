cmake_minimum_required(VERSION 3.15)
project(Des VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(DesExport src/Des.cpp)
target_include_directories(DesExport
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
set_target_properties(DesExport
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_executable(lab2 main.cpp src/Des.cpp)
set_target_properties(lab2
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
target_link_libraries(lab2 DesExport)
