#cmake_minimum_required(VERSION 4.0)
project(llvm-passes)

# Try to find a system-installed LLVM via CMake package config first. This allows
# building against packages like llvm-17-dev (or Homebrew's llvm@17) without
# setting an LLVM_HOME environment variable. If that fails, fall back to the
# existing LLVM_HOME behaviour so older workflows keep working.
find_package(LLVM QUIET CONFIG)

if(NOT LLVM_FOUND)
    if(DEFINED ENV{LLVM_HOME})
        set(ENV{LLVM_DIR} $ENV{LLVM_HOME}/lib/cmake/llvm)
        message(STATUS "Using LLVM_HOME: $ENV{LLVM_HOME}")
        message(STATUS "Setting LLVM_DIR to: $ENV{LLVM_DIR}")
        find_package(LLVM REQUIRED CONFIG)
    else()
        message(FATAL_ERROR "Could not find LLVM. Either install the LLVM development package (e.g. llvm-17-dev), or set the environment variable 'LLVM_HOME' to your LLVM installation root, or pass -DLLVM_DIR=/path/to/llvm/lib/cmake/llvm to CMake.")
    endif()
else()
    message(STATUS "Found LLVM via CMake package config")
endif()
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

#if(${LLVM_VERSION_MAJOR} VERSION_GREATER_EQUAL 10)
#    set(CMAKE_CXX_STANDARD 14)
#endif()

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard")

add_subdirectory(src)

