#ifndef _CONVOLUTION11x11S1HHHH_ASM_TEST_H_
#define _CONVOLUTION11x11S1HHHH_ASM_TEST_H_

#include "half.h"

extern unsigned int convolution11x11s1hhhhCycleCount;
void Convolution11x11s1hhhh_asm_test(half** in, half** out, half conv[121], unsigned int width);

#endif //_CONVOLUTION11x11S1HHHH_ASM_TEST_H_