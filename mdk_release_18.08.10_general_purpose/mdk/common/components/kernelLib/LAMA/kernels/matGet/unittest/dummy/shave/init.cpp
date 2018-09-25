///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief  /// matrix get block


#include "matGet.h"
#include <stdio.h>
#include "svuCommonShave.h"
#include "mv_types.h"
#include <moviVectorTypes.h>

#define TEST_MATRIX_HEIGHT 64
#define TEST_MATRIX_WIDTH 64
#define EDGE 16

float input1[TEST_MATRIX_HEIGHT * TEST_MATRIX_WIDTH] __attribute__ ((aligned (16)));

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
float __attribute__((section(".kept.data"))) output[TEST_MATRIX_HEIGHT * TEST_MATRIX_WIDTH + EDGE]  __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));

unsigned int width __attribute__ ((aligned (16)));
unsigned int height;

unsigned int width_out __attribute__ ((aligned (16)));
unsigned int height_out;

int start_row __attribute__ ((aligned (16)));
int start_col;

MAT *A;
MAT *C;
MAT *out;

float matA[30]; ;//28 is size of mat structure
float matC[30]; ;//28 is size of mat structure
float matOut[30]; ;//28 is size of mat structure

int main(void)
{
	A   = (MAT *)(&matA[0]); 
	C   = (MAT *)(&matC[0]); 
	out = (MAT *)(&matOut[0]); 

	
	A->m    = height;           out->m    = height_out;
	A->n    = width;            out->n    = width_out;

	A->base = (float*)input1;   out->base = (float*)output;
	

#ifdef UNIT_TEST_USE_C_VERSION
    C = mvcvMatGet(A, out, start_row, start_col);
#else                 
    C = mvcvMatGet_asm(A, out, start_row, start_col);
#endif

    SHAVE_HALT;
    return 0;
}