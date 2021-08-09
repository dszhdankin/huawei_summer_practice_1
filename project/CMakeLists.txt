include_directories(${INC_DIR})
add_library(libclang SHARED IMPORTED project/code_examples/example.cpp project/code_examples/includes_closed.cpp ../test/test1.cpp)
set_property(TARGET libclang PROPERTY IMPORTED_LOCATION "${LIB_DIR}/libclang.so")

add_executable(project main.cpp)

target_link_libraries(project libclang)