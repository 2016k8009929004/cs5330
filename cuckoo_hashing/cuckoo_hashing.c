//
// Created by Yuhang Chen on 24/4/21.
//

#include "cuckoo_hashing.h"
int SIZE = 1000000;
double EPSILON = 0.1;


/**
 * @brief Init Cuckoo Table
 *
 * @param f
 *    Input hash function(e.g, simple tabulation, double tabulation...)
 * @return
 *    Pointer to the initialed cuckoo table
 */
CUCKOO_TABLE* Init(HASH f){ CUCKOO_TABLE * cuckoo_table = (CUCKOO_TABLE *)malloc(sizeof(CUCKOO_TABLE));
    cuckoo_table->arr1 = (int*)malloc(sizeof(int) * SIZE);
    cuckoo_table->arr2 = (int*)malloc(sizeof(int) * SIZE);
    cuckoo_table->hash_function = f;

    for(int i = 0; i < SIZE; i++){
        cuckoo_table->arr1[i] = -1;
        cuckoo_table->arr2[i] = -1;
    }
    return cuckoo_table;
}

/**
 * @brief Insert element into the cuckoo table a
 *
 * @param T
 *   Cuckoo Table
 * @param table
 *    Hash table
 * @param element
 *    The element we want to insert into the cuckoo table T
 */
int Insert(CUCKOO_TABLE * T, uint32_t* table1, uint32_t* table2, int element){
    int probe1 = T->hash_function(element, table1) % SIZE;
    int probe2 = T->hash_function(element, table2) % SIZE;
    if(T->arr1[probe1] == -1){
        T->arr1[probe1] = element;
        return probe1;
    }

    if(T->arr2[probe2] == -1){
        T->arr2[probe2] = element;
        return probe2;
    }
    return -1;
}


int main(int argc, char* argv[]){
    if(argc >= 2){
        SIZE = atoi(argv[1]);
    }
    if(argc >= 3){
        EPSILON = atof(argv[2]);
    }
    else{
        EPSILON = 0.05;
    }
#ifdef SIMPLE
    CUCKOO_TABLE * cuckoo_table = Init((HASH)SimpleTab32);
    uint32_t* table1 = (uint32_t *)table_generate(4*256*sizeof(uint32_t));
    uint32_t* table2 = (uint32_t *)table_generate(4*256*sizeof(uint32_t));
#elif TWISTED
    CUCKOO_TABLE * cuckoo_table = Init((HASH)TwistedTab32);
    uint32_t* table1 = (uint32_t *)table_generate(4*256*sizeof(uint64_t));
    uint32_t* table2 = (uint32_t *)table_generate(4*256*sizeof(uint64_t));
#elif DOUBLE
    CUCKOO_TABLE * cuckoo_table = Init((HASH)DoubleTab32);
    uint32_t* table1 = (uint32_t *)table_generate((4*256*32 + 32*(unsigned long long)(1<<16))*sizeof(uint32_t));
    uint32_t* table2 = (uint32_t *)table_generate((4*256*32 + 32*(unsigned long long)(1<<16))*sizeof(uint32_t));
#else
    CUCKOO_TABLE * cuckoo_table = NULL;
    printf("ERROR\n");
#endif

    double count = 0;
    int pos = 0;
    const int array_size = SIZE*(1 + EPSILON);

    printf("Table Size = %d, Insert Array Size = %d\n", SIZE, array_size);

    double start = get_time();
    for(int i = 0; i < array_size; i++){
        pos = Insert(cuckoo_table, table1, table2, i);
        count += (pos == -1);
    }
    printf("Avg insert time is %f ns, error rate is %f.\n", (get_time() - start)*10e9/array_size, count/array_size);


    free(table1);
    free(table2);
    free(cuckoo_table->arr1);
    free(cuckoo_table->arr2);
    free(cuckoo_table);
    return 0;
}

