cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME
    clparser
)

project(${LIBRARY_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/Parser.cpp
)

add_library(ClParser ${SOURCES})

target_include_directories(ClParser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS ClParser
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    
install(FILES include/clparser/Parser.hpp DESTINATION include/clparser)
