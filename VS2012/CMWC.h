#ifndef __CMWC_H__
#define __CMWC_H__

#include <stdint.h>
 
// random generator state
static uint32_t Q[4096];
static uint32_t c = 123;   /* 0 <= c < 18782 */
static uint32_t i = 4095;
 
// generates a new random number 0 to 2^32-1
uint32_t CMWC();

// initializes the random generator.
void CMWC_init(uint32_t seed = 0);

#endif