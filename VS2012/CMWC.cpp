#include "CMWC.h"

// CMWC random number generator.
uint32_t CMWC() {

  uint64_t t;
  uint32_t x;
 
  i = (i + 1) & 4095;
  t = (18782ULL * Q[i]) + c;
  c = t >> 32;
  x = t + c;
 
  if (x < c) { ++x; ++c; }
 
  Q[i] = 0xfffffffe - x;
 
  return Q[i];
}

// initialize cmwc random generator.
void CMWC_init(uint32_t x)
{
	static const uint32_t PHI = 0x9e3779b9;
	Q[0] = x;
	Q[1] = x + PHI;
	Q[2] = x + PHI + PHI;

	for(uint32_t j = 3; j < 4096; j++)
		Q[j] = Q[j - 3] ^ Q[j - 2] ^ PHI ^ j;

	c = 18781;
	i = 4095;

	for(int i=0;i<4096;i++)
	{
		CMWC();
	}
}