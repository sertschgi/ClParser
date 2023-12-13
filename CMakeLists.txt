cmake_minimum_required(VERSION 3.10)

project(clparser)

set(PROJECT_VERSION 1)
set(CMAKE_CXX_STANDARD 17)

add_library(ClParser
        src/Parser.cpp
        src/modules/ClParser.cpp
        include/modules/ClParser.hpp
        src/modules/ClPosArg.cpp
        include/modules/ClPosArg.hpp
        src/modules/ClOption.cpp
        include/modules/ClOption.hpp
        src/modules/ClCommand.cpp
        include/modules/ClCommand.hpp
        src/modules/parent/commandFunctionality.cpp
        include/modules/parent/commandFunctionality.hpp
        src/modules/parent/optionHandleFunctionality.cpp
        include/modules/parent/optionHandleFunctionality.hpp
        src/modules/parent/posArgHandleFunctionality.cpp
        include/modules/parent/posArgHandleFunctionality.hpp
        src/modules/parent/generalFunctionality.cpp
        include/modules/parent/generalFunctionality.hpp
        include/modules/ClLists.hpp
        src/modules/utility/helperFunctions.cpp
        include/modules/ClErrors.hpp
        include/modules/utility/helperFunctions.hpp
        include/modules/utility/ClCommandPreDef.hpp
)

target_include_directories(ClParser PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)

install(TARGETS ClParser
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES include/clparser/Parser.hpp DESTINATION include/clparser)