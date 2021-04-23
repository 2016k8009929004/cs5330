//
// Created by Yuhang Chen on 5/4/21.
//

#ifndef CS5330_TABLE_GENERATE_H
#define CS5330_TABLE_GENERATE_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef CS5330_SIMPLE_H
#include "simple.h"
#endif

char* table_generate(unsigned long long size);

#endif //CS5330_TABLE_GENERATE_H
