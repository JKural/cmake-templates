# Find a package necessary in the tests (if applicable)
find_package(GTest REQUIRED)

# Include gtest cmake utilities
include(GoogleTest)

# Add test executables
add_executable(hello_world_test)

# Specify their sources
target_sources(hello_world_test
  PRIVATE
    "hello_world_test.cpp"
)

# Link the tested library and GTest::gtest_main
target_link_libraries(hello_world_test
  PRIVATE
    mylib::mylib
    GTest::gtest_main
)

# Discover tests in the executable
gtest_discover_tests(hello_world_test)
