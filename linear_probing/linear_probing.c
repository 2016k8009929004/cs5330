//
// Created by Yuhang Chen on 5/4/21.
//
#include "linear_probing.h"
#include "table_generate.h"

#include <limits.h>

/**
 * @brief Init Probing Array
 *
 * @param f
 *    Input hash function(e.g, simple tabulation, double tabulation...)
 * @return
 *    Pointer to the initialed probing array
 */
PROBING_ARRAY* Init(HASH f){
    PROBING_ARRAY* probing_array = (PROBING_ARRAY*)malloc(sizeof(PROBING_ARRAY));
    probing_array->arr = (int*)malloc(sizeof(int) * SIZE);
    probing_array->count = 0;
    probing_array->hash_function = f;

    for(int i = 0; i < SIZE; i++){
        probing_array->arr[i] = -1;
    }
    return probing_array;
}

/**
 * @brief Search element in the probing array a
 *
 * @param a
 *    Probing array
 * @param table
 *    Hash table
 * @param element
 *    The element we want to find in the probing array a
 * @return
 *    Location of element, -1 if not found
 */
int Search(PROBING_ARRAY* a, uint32_t* table, int element){
    if(a->count == 0){
        printf("Search error!\nArray is empty\n");
        return -1;
    }

    int probe = a->hash_function(element, table) % SIZE;
    int count = 0;
    while(count != SIZE)
    {
        if(a->arr[probe] == element)
            return probe;
        probe = (probe+1) % SIZE;
        count++;
    }
    return -1;
}

/**
 * @brief Insert element into the probing array a
 *
 * @param a
 *    Probing array
 * @param table
 *    Hash table
 * @param element
 *    The element we want to insert into the probing array a
 */
void Insert(PROBING_ARRAY* a, uint32_t* table, int element){
    if(a->count == SIZE){
        printf("Insert error.\nArray is full!\n");
        return;
    }
    int probe = a->hash_function(element, table) % SIZE;
    while(a->arr[probe] != -1)
    {
        probe = (probe+1) % SIZE;
    }
    a->arr[probe] = element;
    a->count++;
}

/**
 * @brief Delete element from the probing array a
 *
 * @param a
 *    Probing array
 * @param table
 *    Hash table
 * @param element
 *    The element we want to delete from the probing array a
 */
void Delete(PROBING_ARRAY* a, uint32_t* table, int element){
    if(a->count == 0){
        printf("Delete error!\nArray is empty!\n");
        return;
    }
    int loc = Search(a, table, element);
    if(loc != -1)
    {
        a->arr[loc] = -1;
        a->count--;
    }
}

/**
 * @brief Print all the element in array a
 *
 * @param a
 *    Probing array
 */
void PrintArray(PROBING_ARRAY *a){
    for(int i = 0; i < SIZE; i++)
        printf("%d%c", a->arr[i], ' ');
    printf("\n");
}

int main(){
#ifdef DOUBLE
    uint32_t* table = (uint32_t *)table_generate((4*256*32 + 32*(unsigned long long)UINT_MAX)*sizeof(uint32_t));
#else
    uint32_t* table = (uint32_t *)table_generate(4*256*sizeof(uint32_t));
#endif

#ifdef SIMPLE
    PROBING_ARRAY * probing_array = Init((HASH)SimpleTab32);
#elif TWISTED
    PROBING_ARRAY * probing_array = Init((HASH)TwistedTab32);
#elif DOUBLE
    PROBING_ARRAY * probing_array = Init((HASH)DoubleTab32);
#else
    PROBING_ARRAY * probing_array = NULL;
    printf("ERROR\n");
#endif

    double start = get_time();
    for(int i = 0; i < 100; i++){
        probing_array->hash_function(i, table);
    }
    printf("Avg hash time is %f ns.\n", (get_time() - start)*10e9/100);

    start = get_time();
    for(int i = 0; i < 100; i++){
        Insert(probing_array, table, i);
    }
    assert(probing_array->count == 100);
    printf("Avg insert time is %f ns.\n", (get_time() - start)*10e9/100);

//    PrintArray(probing_array);

    start = get_time();
    for(int i = 0; i < 100; i++){
        Delete(probing_array, table, i);
    }
    assert(probing_array->count == 0);
    printf("Avg delete time is %f ns.\n", (get_time() - start)*10e9/100);

    free(table);
    free(probing_array->arr);
    free(probing_array);
    return 0;
}

