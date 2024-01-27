include(CTest)

# test/CMakeLists.txt
add_executable(test test1.cpp
        test2.cpp)

# Link against the library
target_link_libraries(test ClParser)

add_test(NAME test
        COMMAND test)