## -*- mode: CMake -*-
##
## Copyright (c) 2023, Tian Haoyu <tienhoayu@gmail.com>

###############################################################################

cmake_minimum_required(VERSION 3.14)
project(clangxloc)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CheckIncludeFile)

find_package(LLVM REQUIRED CONFIG NO_CMAKE_BUILDS_PATH)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in ${LLVM_DIR}")
if (${LLVM_PACKAGE_VERSION} VERSION_LESS "9.0")
  message(FATAL_ERROR "ClangXloc requires LLVM 9.0 or later")
endif()

find_package(Clang REQUIRED CONFIG NO_CMAKE_BUILDS_PATH)
message(STATUS "Using ClangConfig.cmake in ${Clang_DIR}")

###############################################################################
  
# Add flags for compiling against LLVM.
add_definitions(${LLVM_DEFINITIONS})
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
  $<$<CONFIG:Release>:NDEBUG>)
# include_directories(${PROJECT_BINARY_DIR}) --- if we generated .h files here
include_directories(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}) # needed for gen'ed .cpp files
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS}) # only works for LLVM post-4.0

link_directories(${LLVM_LIBRARY_DIRS})

if (${LLVM_LINK_LLVM_DYLIB})
  set(CLANG_LIBS
    clang-cpp
    LLVM
  )
else()
  set(CLANG_LIBS
    clangAST
    clangBasic
    clangFrontend
    clangParse
    clangLex
    clangRewrite
  )
endif()

add_executable(clang-xloc
  ClangXloc.cpp)

target_link_libraries(clang-xloc ${CLANG_LIBS})

###############################################################################

## End of file.
