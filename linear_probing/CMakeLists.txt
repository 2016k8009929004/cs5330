PROJECT(Linear_probing)

ADD_EXECUTABLE(linear_probing_simple.out linear_probing.c)

target_link_libraries(linear_probing_simple.out simple table_generate)
target_compile_definitions(linear_probing_simple.out PRIVATE SIMPLE)

ADD_EXECUTABLE(linear_probing_twisted.out linear_probing.c)

target_link_libraries(linear_probing_twisted.out twisted table_generate)
target_compile_definitions(linear_probing_twisted.out PRIVATE TWISTED)

ADD_EXECUTABLE(linear_probing_double.out linear_probing.c)

target_link_libraries(linear_probing_double.out double table_generate)
target_compile_definitions(linear_probing_double.out PRIVATE DOUBLE)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
