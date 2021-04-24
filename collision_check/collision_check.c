//
// Created by Yuhang Chen on 24/4/21.
//

#include "collision_check.h"
int SIZE = 1000000;

double two_collision_check(HASH h, uint32_t* table){
    double count = 0;
    double total_pair = (double)SIZE*(SIZE-1)/2;
    for(int i = 0; i < SIZE; i++){
        for(int j = i+1; j < SIZE; j++){
            if(h(i, table) == h(j, table)){
                count++;
            }
        }
    }
    return count/total_pair;
}

double three_collision_check(HASH h, uint32_t* table){
    double count = 0;
    double total_pair = (double)SIZE*(SIZE-1)*(SIZE-2)/6;
    for(int i = 0; i < SIZE; i++){
        for(int j = i+1; j < SIZE; j++){
            for(int k = j+1; k < SIZE; k++){
                if((h(i, table) == h(j, table)) && (h(i, table) == h(k, table))) {
                    count++;
                }
            }
        }
    }
    return count/total_pair;
}

int main(int argc, char* argv[]){
    if(argc >= 2){
        SIZE = atoi(argv[1]);
    }

#ifdef SIMPLE
    uint32_t* table = (uint32_t *)table_generate(4*256*sizeof(uint32_t));
    HASH h = (HASH)SimpleTab32;
#elif TWISTED
    HASH h = (HASH)TwistedTab32;
    uint32_t* table = (uint32_t *)table_generate(4*256*sizeof(uint64_t));
#elif DOUBLE
    HASH h = (HASH)DoubleTab32;
    uint32_t* table = (uint32_t *)table_generate((4*256*32 + 32*(unsigned long long)UINT_MAX)*sizeof(uint32_t));
#else
    uint32_t* table = NULL;
    HASH h = NULL;
    printf("ERROR\n");
#endif

    printf("Check Array Size = %d\n", SIZE);

    double collision_rate = 0;
    collision_rate = two_collision_check(h, table);
    printf("Two collision rate=%f\n", collision_rate);
    collision_rate = three_collision_check(h, table);
    printf("Three collision rate=%f\n", collision_rate);
}
