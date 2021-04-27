//
// Created by Yuhang Chen on 30/3/21.
//
#include "table_generate.h"

/**
 * @brief Hash Table Generating
 *    Generate the Hash Table for Tabulation
 * @param size
 *    The size of the table(in bytes)
 * @return
 *    The generated Hash Table
 */
char* table_generate(unsigned long long size){
    int* table = (int*)calloc(size, sizeof(char));
    srand(time(NULL));
    for(unsigned long long i = 0; i < size/sizeof(int); i++){
        table[i] = rand();
    }
    return table;
}
