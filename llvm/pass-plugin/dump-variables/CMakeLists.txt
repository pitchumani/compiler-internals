#cmake_minimum_required(VERSION 4.0)
project(llvm-passes)

if(NOT DEFINED ENV{LLVM_HOME})
    message(FATAL_ERROR "Environment variable '$LLVM_HOME' is not defined")
else()
    set(ENV{LLVM_DIR} $ENV{LLVM_HOME}/lib/cmake/llvm)
    message("LLVM_HOME value: $ENV{LLVM_HOME}")
    message("LLVM_DIR value: $ENV{LLVM_DIR}")
endif()

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

#if(${LLVM_VERSION_MAJOR} VERSION_GREATER_EQUAL 10)
#    set(CMAKE_CXX_STANDARD 14)
#endif()

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard")

add_subdirectory(src)

