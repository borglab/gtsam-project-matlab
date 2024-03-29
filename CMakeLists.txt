# This file should be used as a template for creating new projects using the
# CMake tools This project has the following features - GTSAM linking - Unit
# tests via CppUnitLite - Scripts - Automatic MATLAB wrapper generation

# ##############################################################################
# To create your own project, replace "example" with the actual name of your
# project
cmake_minimum_required(VERSION 3.0)
project(example_matlab CXX C)

# Enforce c++17 standards
add_compile_options(-std=c++17) # CMake 3.1 and earlier
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include GTSAM CMake tools
find_package(GTSAMCMakeTools)
include(GtsamBuildTypes) # Load build type flags and default to Debug mode
include(GtsamTesting) # Easy functions for creating unit tests and scripts

# Import the gtwrap package.
find_package(gtwrap)

set(WRAP_PYTHON_VERSION
    "Default"
    CACHE STRING "The Python version to use for wrapping")

gtwrap_get_python_version(${WRAP_PYTHON_VERSION})

# Set up cache options
option(WRAP_MEX_BUILD_STATIC_MODULE
       "Build MATLAB wrapper statically (increases build time)" OFF)
set(WRAP_BUILD_MEX_BINARY_FLAGS
    ""
    CACHE STRING "Extra flags for running Matlab MEX compilation")
set(WRAP_TOOLBOX_INSTALL_PATH
    "${CMAKE_INSTALL_PREFIX}/gtsam_toolbox"
    CACHE
      PATH
      "Matlab toolbox destination, blank defaults to CMAKE_INSTALL_PREFIX/gtsam_toolbox"
)

option(
  WRAP_BUILD_TYPE_POSTFIXES
  "Enable/Disable appending the build type to the name of compiled libraries"
  ON)

# Copy matlab.h to the correct folder.
configure_file(${PROJECT_SOURCE_DIR}/matlab/matlab.h
  ${PROJECT_BINARY_DIR}/wrap/matlab.h COPYONLY)

# Include the Matlab related code.
include(MatlabWrap)

# Ensure that local folder is searched before library folders
include_directories(BEFORE "${PROJECT_SOURCE_DIR}")

# ##############################################################################
# Find GTSAM components
find_package(GTSAM REQUIRED) # Uses installed package
# Note: Since Jan-2019, GTSAMConfig.cmake defines exported CMake targets that
# automatically do include the include_directories() without the need to call
# include_directories(), just target_link_libraries(NAME gtsam)
# include_directories(${GTSAM_INCLUDE_DIR})

# ##############################################################################
# Build static library from common sources
add_library(${PROJECT_NAME} SHARED example/PrintExamples.h
                                           example/PrintExamples.cpp)
target_link_libraries(${PROJECT_NAME} gtsam)

# Install library
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)

# ##############################################################################
# Build tests (CMake tracks the dependecy to link with GTSAM through our
# project's static library)
gtsamaddtestsglob("example" "tests/test*.cpp" "" "${PROJECT_NAME}")

# ##############################################################################
# Build scripts (CMake tracks the dependecy to link with GTSAM through our
# project's static library)
gtsamaddexamplesglob("*.cpp" "" "${PROJECT_NAME}" ON)

# Variable for Matlab wrapper CMake command
set(GTSAM_ENABLE_BOOST_SERIALIZATION ON)
set(MexFlags "")
set(FilesToIgnore "")
# ##############################################################################
# Build MATLAB wrapper (CMake tracks the dependecy to link with GTSAM through
# our project's static library)
matlab_wrap("example.i" "${PROJECT_NAME}" "" "" "${mexFlags}" "${FilesToIgnore}" ON)

# We print out our configuration for an easy visual check
message("========== Configuration Options ==========")
message(STATUS "Project:                  ${PROJECT_NAME}")
message(STATUS "MATLAB Root:              ${MATLAB_ROOT}")
message(STATUS "Mex Compiler:             ${Matlab_MEX_COMPILER}")
message("===========================================")
