include(CTest)

# test/CMakeLists.txt
add_executable(test test1.cpp)

# Link against the library
target_link_libraries(test vtkCommon)

add_test(NAME test
        COMMAND test)