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
typedef unsigned __int128 uint128_t

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
uint64_t * SimpleTab32(uint32_t x, uint32_t H[4][256]) {
  
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
uint32_t DoubleTab32(uint32_t x, uint32_t H[4][256]) {
  /* Simple tabulation function with 6 times more output than input characters */

  /* Simple tabulation function */
}