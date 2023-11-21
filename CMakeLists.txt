cmake_minimum_required(VERSION 3.10)

project(clparser)

set(CMAKE_CXX_STANDARD 17)

add_library(ClParser
        src/Parser.cpp
)

target_include_directories(ClParser PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)

install(TARGETS ClParser
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES include/clparser/Parser.hpp DESTINATION include/clparser)