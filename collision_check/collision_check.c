//
// Created by Yuhang Chen on 24/4/21.
//

#include "collision_check.h"
long long int SIZE = 1000000;

int main(int argc, char* argv[]){
    if(argc >= 2){
        SIZE = atoll(argv[1]);
    }

#ifdef SIMPLE
    uint32_t* table = (uint32_t *)table_generate(4*256*sizeof(uint32_t));
    HASH h = (HASH)SimpleTab32;
#elif TWISTED
    HASH h = (HASH)TwistedTab32;
    uint32_t* table = (uint32_t *)table_generate(4*256*sizeof(uint64_t));
#elif DOUBLE
    HASH h = (HASH)DoubleTab32;
    uint32_t* table = (uint32_t *)table_generate((4*256*32 + 32*(unsigned long long)(1<<28))*sizeof(uint32_t));
#else
    uint32_t* table = NULL;
    HASH h = NULL;
    printf("ERROR\n");
#endif

    printf("Check Array Size = %d\n", SIZE);

    bool* count_table1 = (bool*)malloc(UINT_MAX * sizeof(bool));
    bool* count_table2 = (bool*)malloc(UINT_MAX * sizeof(bool));
    double two_collision_count = 0;
    double three_collision_count = 0;
    for(uint32_t i = 0; i < UINT_MAX; i++){
        count_table1[i] = 0;
        count_table2[i] = 0;
    }
    printf("Finish Initialization.\n");
    uint32_t pos;
    for(long long int i = 0; i < SIZE; i++){
        pos = h(i, table);
        if(count_table1[pos] == 0){
            count_table1[pos] = 1;
        }
        else{
            two_collision_count++;
            if(count_table2[pos] == 0){
                count_table2[pos] = 1;
            }
            else{
                three_collision_count++;
            }
        }
    }

    printf("Two collision rate=%f\n", two_collision_count/(SIZE));
    printf("Three collision rate=%f\n", three_collision_count/(SIZE*SIZE));
    free(count_table1);
    free(count_table2);
}
