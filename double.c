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
#include <limits.h>

/**
 * @brief Simple Tabulation to obtain (a) in Theorem 1
 * 
 * @param x 
 *    Key from Φ^c, c = 4
 * @param H 
 *    Tabulation from Φ = {0, ... , 2^8 - 1} -> Ψ = {0, ... , 2^32 - 1}, d = 32
 * @return  
 *    Hash value of key x
 */
uint32_t * SimpleTab_f(uint32_t x, uint32_t * H[4][256]) {
  uint32_t * h = (uint32_t *)malloc(32 * sizeof(uint32_t));
  uint8_t c;
  for (int i = 0; i < 4; i++) {
    c = x;
    for (int j = 0; j < 32; j++) {
      h[j] ^= H[i][c][j];
    }
    x = x >> 8;
  }
  return h;
}

/**
 * @brief Simple Tabulation
 * 
 * @param x 
 *    Key from Ψ^d, d = 32
 * @param H 
 *    Tabulation from Ψ = {0, ... , 2^32 - 1}, d = 32 -> R = {0, ... , 2^32 - 1}
 * @return  
 *    Hash value of key x
 */
uint32_t SimpleTab_r(uint32_t * x, uint32_t H[32][UINT_MAX]) {
  uint32_t h = 0;
  uint8_t c;
  for (int i = 0; i < 32; i++) {
    c = x[i];
    h ^= H[i][c];
  }
  return h;
}

/**
 * @brief Double Tabulation
 *    Simple tabulation is 3-independent, so we need a 3-unique function
 * @param x 
 *    
 * @param H 
 *    
 * @return  
 *    
 */
uint128_t DoubleTab32(uint32_t x, uint32_t * H1[4][256], uint32_t H2[32][UINT_MAX]) {
  /* Simple tabulation function with 6 times more output than input characters */
  /* h1: 32 x 32bytes */
  uint32_t * h1 = SimpleTab_f(x, H1);
  
  /* Simple tabulation function */
  uint32_t h2 = SimpleTab_r(h1, H2);

  return h2;
}