PROJECT(collision_check)

ADD_EXECUTABLE(collision_check_simple.out collision_check.c)

target_link_libraries(collision_check_simple.out simple table_generate)
target_compile_definitions(collision_check_simple.out PRIVATE SIMPLE)

ADD_EXECUTABLE(collision_check_twisted.out collision_check.c)

target_link_libraries(collision_check_twisted.out twisted table_generate)
target_compile_definitions(collision_check_twisted.out PRIVATE TWISTED)

ADD_EXECUTABLE(collision_check_double.out collision_check.c)

target_link_libraries(collision_check_double.out double table_generate)
target_compile_definitions(collision_check_double.out PRIVATE DOUBLE)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
