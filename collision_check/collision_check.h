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
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#include "table_generate.h"

typedef uint32_t (*HASH)(uint32_t, uint32_t*);

double two_collision_check(HASH h, uint32_t* table);
double three_collision_check(HASH h, uint32_t* table);

double get_time()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}

#endif //CS5330_INDEPENDENT_CHECK_H
