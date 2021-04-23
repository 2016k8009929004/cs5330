/**
 * @file twisted.c
 * @author Yang Yihan (yangyihan@comp.nus.edu.sg)
 * @brief
 * @version 0.1
 * @date 2021-03-30
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "twisted.h"

/* Twisted Tabulation algoritm */
uint32_t TwistedTab32(uint32_t x, uint64_t H[4 * 256]) {
    /* H is pointing to randomly filled 8KB storage */
    uint32_t i;
    uint64_t h = 0;
    uint8_t c;
    for (i=0; i<3; i++) {
        c = x;
        h ^= H[i*256 + c];
        x = x >> 8;
    }
    c = x^h;  // extra xor compared with simple
    h ^= H[i*256 + c];
    h >>= 32;
    return ( (uint32_t) h);
}
