# Minimal version of cmake required to run the script.
cmake_minimum_required(VERSION 3.24)

# Project definition.
project(mylib
  VERSION 1.0.0                         # Optional, but recommended
  LANGUAGES CXX                         # Optional
  DESCRIPTION "My library"              # Optional
  HOMEPAGE_URL "https://my_library.com" # Optional
)

# Testing utilities. They are only included if the project is at the top
# level, as it defines a BUILD_TESTING variable by default initialized
# to true.
if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif()

# An option to build tests. Requires ENABLE_TESTING option to be set as
# well.
option(mylib_BUILD_TESTS "Build mylib tests" ${PROJECT_IS_TOP_LEVEL})

# An option to build examples.
option(mylib_BUILD_EXAMPLES "Build mylib examples" ${PROJECT_IS_TOP_LEVEL})

# An option to optionally disable installation of the library targets.
option(mylib_INSTALL "Enable installation of mylib" ${PROJECT_IS_TOP_LEVEL})

# The library traget.
add_library(mylib)

# Its version and soversion, useful when built as a shared library.
set_target_properties(mylib
  PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Specify compile features, e.g. the standard.
target_compile_features(mylib
  PUBLIC
    cxx_std_23
)

# An alias to make usage through find_package and add_subdirectory
# act the same.
add_library(mylib::mylib ALIAS mylib)

# Sources of the library.
target_sources(mylib
  PRIVATE
    "src/hello_world.cpp"
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "include"
    FILES
      "include/mylib/hello_world.h"
)

if(mylib_BUILD_TESTS AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

if(mylib_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# If we enabled the installation of the library
if(mylib_INSTALL)
  # Standard paths to runtime/library/header directories.
  include(GNUInstallDirs)

  # Utilities for exporting cmake configuration files.
  include(CMakePackageConfigHelpers)

  # Install the library.
  install(
    TARGETS mylib
    EXPORT mylib-targets
    FILE_SET HEADERS
  )

  # Install the targets.
  install(
    EXPORT mylib-targets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    NAMESPACE mylib::
  )

  # Create the configuration file.
  configure_package_config_file(
    "cmake/${PROJECT_NAME}-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  )

  # Create the version file.
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake"
    COMPATIBILITY SameMajorVersion
  )

  # Install configuration and version file
  install(
    FILES
      "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake"
      "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  )
endif()
