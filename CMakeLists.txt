cmake_minimum_required(VERSION 3.20)
project(libclang_test)

set(CMAKE_CXX_STANDARD 14)
set(LIB_DIR "/usr/lib/llvm-10/lib")
set(INC_DIR "/usr/lib/llvm-10/include")

add_subdirectory(project)
add_subdirectory(test)


