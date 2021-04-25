//
// Created by Yuhang Chen on 24/4/21.
//

#ifndef CS5330_INDEPENDENT_CHECK_H
#define CS5330_INDEPENDENT_CHECK_H
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
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#include "table_generate.h"

typedef uint32_t (*HASH)(uint32_t, uint32_t*);

//double collision_check(int i, int* count_table);

double get_time()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}

#endif //CS5330_INDEPENDENT_CHECK_H
