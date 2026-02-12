# Add example executable
add_executable(hello_world_example)

# Add sources of the example executable
target_sources(hello_world_example
  PRIVATE
    "hello_world_example.cpp"
)

# Link the library
target_link_libraries(hello_world_example
  PRIVATE
    mylib::mylib
)
