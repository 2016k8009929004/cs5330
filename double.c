/**
 * @file double.c
 * @author Yang Yihan (yangyihan@comp.nus.edu.sg)
 * @brief 
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 *
 */

#include <stdint.h>

/* Simple Tabulation algoritm */
uint32_t SimpleTab32(uint32_t x, uint32_t H[4][256]) {
  /* H is pointing to randomly filled 4KB storage */
  uint32_t i;
  uint32_t h = 0;
  uint8_t c;
  for (i=0; i<4; i++) {
    c = x;
    h ^= H[i][c];
    x = x >> 8;
  }
  return h;
}

/* Double Tabulation algoritm */
uint32_t DoubleTab32(uint32_t x, uint32_t H[4][256]) {
  
}