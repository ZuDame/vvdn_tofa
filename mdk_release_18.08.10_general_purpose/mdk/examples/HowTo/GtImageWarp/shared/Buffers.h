///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief
///
// This header is left unguarded on purpose because it should be included only
// once in the entire project

#include <mv_types.h>
#include <Defines.h>

DDR_BSS u8   	       inputframe[IMG_WIDTH * IMG_HEIGHT];
DDR_BSS u8  	       outputframe[OUT_IMG_WIDTH * OUT_IMG_HEIGHT];