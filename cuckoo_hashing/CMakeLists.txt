PROJECT(cuckoo_hashing)

ADD_EXECUTABLE(cuckoo_hashing_simple.out cuckoo_hashing.c)

target_link_libraries(cuckoo_hashing_simple.out simple table_generate)
target_compile_definitions(cuckoo_hashing_simple.out PRIVATE SIMPLE)

ADD_EXECUTABLE(cuckoo_hashing_twisted.out cuckoo_hashing.c)

target_link_libraries(cuckoo_hashing_twisted.out twisted table_generate)
target_compile_definitions(cuckoo_hashing_twisted.out PRIVATE TWISTED)

ADD_EXECUTABLE(cuckoo_hashing_double.out cuckoo_hashing.c)

target_link_libraries(cuckoo_hashing_double.out double table_generate)
target_compile_definitions(cuckoo_hashing_double.out PRIVATE DOUBLE)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
