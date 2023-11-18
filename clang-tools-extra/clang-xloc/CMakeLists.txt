include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_clang_tool(clang-xloc
  ClangXloc.cpp
  )

clang_target_link_libraries(clang-xloc
  PRIVATE
  clangAST
  clangBasic
  clangTooling
  )

