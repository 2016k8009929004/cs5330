//
// Created by Yuhang Chen on 5/4/21.
//

#ifndef CS5330_LINEAR_PROBING_H
#define CS5330_LINEAR_PROBING_H

#ifdef SIMPLE
#include "simple.h"
#endif

#ifdef TWISTED
#include "twisted.h"
#endif

#ifdef DOUBLE
#include "double.h"
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#include "table_generate.h"


typedef uint32_t (*HASH)(uint32_t, uint32_t*);

typedef struct probing_array {
    int* arr;
    int count;
    HASH hash_function;
} PROBING_ARRAY;


PROBING_ARRAY* Init(HASH f);

int Search(PROBING_ARRAY* a, uint32_t* table, int element);

void Insert(PROBING_ARRAY* a, uint32_t* table, int element);

void Delete(PROBING_ARRAY* a, uint32_t* table, int element);

void PrintArray(PROBING_ARRAY *a);

double get_time()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}

#endif //CS5330_LINEAR_PROBING_H
