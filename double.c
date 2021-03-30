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

/**
 * @brief Simple Tabulation
 * 
 * @param x 
 *    Key from Φ^c, c = 4
 * @param H 
 *    Tabulation from Φ = {0, ... , 2^8 - 1} -> Ψ = {0,1}, r = 32
 * @return  
 *    Hash value of key x
 */
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

/**
 * @brief Double Tabulation
 * 
 * @param x 
 *    
 * @param H 
 *    
 * @return  
 *    
 */
uint32_t DoubleTab32(uint32_t x, uint32_t H[4][256]) {
  /* k-unique function */
  
  /* k-independent function */
}