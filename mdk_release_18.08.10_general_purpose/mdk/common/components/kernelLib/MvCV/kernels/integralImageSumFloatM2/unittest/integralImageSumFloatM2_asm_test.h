#ifndef _INTEGRALIMAGESUMF_ASM_TEST_H_
#define _INTEGRALIMAGESUMF_ASM_TEST_H_

extern unsigned int integralImageSumFCycleCount;
void integralImageSumF_asm_test(float* out, unsigned char* in, unsigned int runNr,  float** sum, unsigned int width);

#endif //_INTEGRALIMAGESUMF_ASM_TEST_H_