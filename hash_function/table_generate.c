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
    char* table = (char*)calloc(size, sizeof(char));
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        table[i] = rand() % (1<<8);
    }
    return table;
}
