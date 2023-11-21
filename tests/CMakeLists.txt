# test/CMakeLists.txt
add_executable(test test1.cpp)

# Link against the library
target_link_libraries(test PRIVATE ClParser)