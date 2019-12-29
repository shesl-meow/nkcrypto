cmake_minimum_required(VERSION 3.15)
project(lab5)

set(CMAKE_CXX_STANDARD 11)

add_library(Md5Export src/Md5Hash.cpp)
target_include_directories(Md5Export
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
set_target_properties(Md5Export
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_executable(lab5 main.cpp)
set_target_properties(lab5
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
target_link_libraries(lab5 Md5Export)
