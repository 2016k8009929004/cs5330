add_library(simple SHARED simple.c)

target_include_directories(simple
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(twisted SHARED twisted.c)

target_include_directories(twisted
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(double SHARED double.c)

target_include_directories(double
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(table_generate SHARED table_generate.c)

target_include_directories(table_generate
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
