#ifndef __MVCV_H__
#define __MVCV_H__

#include "mat.h"
#include "mvcv_types.h"
#include "point.h"

// MvCV kernels
#include "../kernels/absoluteDiff/shave/include/absoluteDiff.h"
#include "../kernels/accumulateSquare/shave/include/accumulateSquare.h"
#include "../kernels/accumulateWeighted/shave/include/accumulateWeighted.h"
#include "../kernels/arithmeticAdd/shave/include/arithmeticAdd.h"
#include "../kernels/arithmeticAddmask/shave/include/arithmeticAddmask.h"
#include "../kernels/arithmeticSub/shave/include/arithmeticSub.h"
#include "../kernels/arithmeticSubFp16ToFp16/shave/include/arithmeticSubFp16ToFp16.h"
#include "../kernels/arithmeticSubmask/shave/include/arithmeticSubmask.h"
#include "../kernels/bilateral5x5/shave/include/bilateral5x5.h"
#include "../kernels/bitwiseAnd/shave/include/bitwiseAnd.h"
#include "../kernels/bitwiseAndMask/shave/include/bitwiseAndMask.h"
#include "../kernels/bitwiseNot/shave/include/bitwiseNot.h"
#include "../kernels/bitwiseOr/shave/include/bitwiseOr.h"
#include "../kernels/bitwiseOrMask/shave/include/bitwiseOrMask.h"
#include "../kernels/bitwiseXor/shave/include/bitwiseXor.h"
#include "../kernels/bitwiseXorMask/shave/include/bitwiseXorMask.h"
#include "../kernels/boxFilter/shave/include/boxFilter.h"
#include "../kernels/boxFilter11x11/shave/include/boxFilter11x11.h"
#include "../kernels/boxFilter13x13/shave/include/boxFilter13x13.h"
#include "../kernels/boxFilter15x15/shave/include/boxFilter15x15.h"
#include "../kernels/boxFilter3x3/shave/include/boxFilter3x3.h"
#include "../kernels/boxFilter5x5/shave/include/boxFilter5x5.h"
#include "../kernels/boxFilter7x7/shave/include/boxFilter7x7.h"
#include "../kernels/boxFilter9x9/shave/include/boxFilter9x9.h"
#include "../kernels/canny/shave/include/canny.h"
#include "../kernels/censusTransform5x5/shave/include/censusTransform5x5.h"
#include "../kernels/censusMatching16/shave/include/censusMatching16.h"
#include "../kernels/censusMatching32/shave/include/censusMatching32.h"
#include "../kernels/censusMatching64/shave/include/censusMatching64.h"
#include "../kernels/censusMatching65/shave/include/censusMatching65.h"
#include "../kernels/censusMin65/shave/include/censusMin65.h"
#include "../kernels/censusMin7/shave/include/censusMin7.h"
#include "../kernels/censusMin16/shave/include/censusMin16.h"
#include "../kernels/censusMatchingPyr/shave/include/censusMatchingPyr.h"
#include "../kernels/channelExtract/shave/include/channelExtract.h"
#include "../kernels/convertFrom12BppTo8Bpp/shave/include/convertFrom12BppTo8Bpp.h"
#include "../kernels/convolution11x11/shave/include/convolution11x11.h"
#include "../kernels/convolution15x1/shave/include/convolution15x1.h"
#include "../kernels/convolution1x15/shave/include/convolution1x15.h"
#include "../kernels/convolution1x5/shave/include/convolution1x5.h"
#include "../kernels/convolution1x5Fp16ToFp16/shave/include/convolution1x5Fp16ToFp16.h"
#include "../kernels/convolution1x7/shave/include/convolution1x7.h"
#include "../kernels/convolution1x7Fp16ToFp16/shave/include/convolution1x7Fp16ToFp16.h"
#include "../kernels/convolution1x9/shave/include/convolution1x9.h"
#include "../kernels/convolution3x3/shave/include/convolution3x3.h"
#include "../kernels/convolution3x3Fp16ToFp16/shave/include/convolution3x3Fp16ToFp16.h"
#include "../kernels/convolution5x1/shave/include/convolution5x1.h"
#include "../kernels/convolution5x1Fp16ToFp16/shave/include/convolution5x1Fp16ToFp16.h"
#include "../kernels/convolution5x5/shave/include/convolution5x5.h"
#include "../kernels/convolution5x5Fp16ToFp16/shave/include/convolution5x5Fp16ToFp16.h"
#include "../kernels/convolution7x1/shave/include/convolution7x1.h"
#include "../kernels/convolution7x1Fp16ToFp16/shave/include/convolution7x1Fp16ToFp16.h"
#include "../kernels/convolution7x7/shave/include/convolution7x7.h"
#include "../kernels/convolution7x7Fp16ToFp16/shave/include/convolution7x7Fp16ToFp16.h"
#include "../kernels/convolution7x7Fp16ToU8/shave/include/convolution7x7Fp16ToU8.h"
#include "../kernels/convolution9x1/shave/include/convolution9x1.h"
#include "../kernels/convolution9x9/shave/include/convolution9x9.h"
#include "../kernels/convolution9x9Fp16ToFp16/shave/include/convolution9x9Fp16ToFp16.h"
#include "../kernels/convSeparable11x11/shave/include/convSeparable11x11.h"
#include "../kernels/convSeparable11x11Fp16ToFp16/shave/include/convSeparable11x11Fp16ToFp16.h"
#include "../kernels/convSeparable3x3/shave/include/convSeparable3x3.h"
#include "../kernels/convSeparable3x3Fp16ToFp16/shave/include/convSeparable3x3Fp16ToFp16.h"
#include "../kernels/convSeparable5x5/shave/include/convSeparable5x5.h"
#include "../kernels/convSeparable5x5Fp16ToFp16/shave/include/convSeparable5x5Fp16ToFp16.h"
#include "../kernels/convSeparable7x7/shave/include/convSeparable7x7.h"
#include "../kernels/convSeparable7x7Fp16ToFp16/shave/include/convSeparable7x7Fp16ToFp16.h"
#include "../kernels/convSeparable9x9/shave/include/convSeparable9x9.h"
#include "../kernels/convSeparable9x9Fp16ToFp16/shave/include/convSeparable9x9Fp16ToFp16.h"
#include "../kernels/cornerMinEigenVal/shave/include/cornerMinEigenVal.h"
#include "../kernels/cornerMinEigenVal_patched/shave/include/cornerMinEigenVal_patched.h"
#include "../kernels/cvtColorKernelRGBToYUV/shave/include/cvtColorKernelRGBToYUV.h"
#include "../kernels/cvtColorKernelRGBToYUV422/shave/include/cvtColorKernelRGBToYUV422.h"
#include "../kernels/cvtColorKernelYUV422ToRGB/shave/include/cvtColorKernelYUV422ToRGB.h"
#include "../kernels/cvtColorKernelYUVToRGB/shave/include/cvtColorKernelYUVToRGB.h"
#include "../kernels/cvtColorNV21toRGB/shave/include/cvtColorNV21toRGB.h"
#include "../kernels/cvtColorRGBfp16ToLumaU8/shave/include/cvtColorRGBfp16ToLumaU8.h"
#include "../kernels/cvtColorRGBfp16ToUV420U8/shave/include/cvtColorRGBfp16ToUV420U8.h"
#include "../kernels/cvtColorRGBtoChromaNV12/shave/include/cvtColorRGBtoChromaNV12.h"
#include "../kernels/cvtColorRGBtoLuma/shave/include/cvtColorRGBtoLuma.h"
#include "../kernels/cvtColorRGBtoLumaNV12/shave/include/cvtColorRGBtoLumaNV12.h"
#include "../kernels/cvtColorRGBtoNV21/shave/include/cvtColorRGBtoNV21.h"
#include "../kernels/cvtColorRGBtoUV/shave/include/cvtColorRGBtoUV.h"
#include "../kernels/cvtColorRGBtoUV420/shave/include/cvtColorRGBtoUV420.h"
#include "../kernels/dilate/shave/include/dilate.h"
#include "../kernels/dilate3x3/shave/include/dilate3x3.h"
#include "../kernels/dilate5x5/shave/include/dilate5x5.h"
#include "../kernels/dilate7x7/shave/include/dilate7x7.h"
#include "../kernels/equalizeHist/shave/include/equalizeHist.h"
#include "../kernels/erode3x3/shave/include/erode3x3.h"
#include "../kernels/erode5x5/shave/include/erode5x5.h"
#include "../kernels/erode7x7/shave/include/erode7x7.h"
#include "../kernels/f32UnitTestSample/shave/include/f32UnitTestSample.h"
#include "../kernels/fast9M2/shave/include/fast9M2.h"
#include "../kernels/fastAtan2Positive/shave/include/fastAtan2Positive.h"
#include "../kernels/gauss/shave/include/gauss.h"
#include "../kernels/gaussHx2_fp16/shave/include/gaussHx2_fp16.h"
#include "../kernels/gaussVx2_fp16/shave/include/gaussVx2_fp16.h"
#include "../kernels/hammingDistance/shave/include/hammingDistance.h"
#include "../kernels/harrisResponse/shave/include/harrisResponse.h"
#include "../kernels/histogram/shave/include/histogram.h"
#include "../kernels/integralImageSquareSumFloatM2/shave/include/integralImageSquareSumFloatM2.h"
#include "../kernels/integralImageSquareSumM2/shave/include/integralImageSquareSumM2.h"
#include "../kernels/integralImageSumFloatM2/shave/include/integralImageSumFloatM2.h"
#include "../kernels/integralImageSumM2/shave/include/integralImageSumM2.h"
#include "../kernels/integralImageSumU16U32/shave/include/integralImageSumU16U32.h"
#include "../kernels/interpolatePixelBilinear/shave/include/interpolatePixelBilinear.h"
#include "../kernels/kernelUnitTestSample/shave/include/kernelUnitTestSample.h"
#include "../kernels/lookupTable10to16/shave/include/lookupTable10to16.h"
#include "../kernels/lookupTable10to8/shave/include/lookupTable10to8.h"
#include "../kernels/lookupTable12to16/shave/include/lookupTable12to16.h"
#include "../kernels/lookupTable12to8/shave/include/lookupTable12to8.h"
#include "../kernels/lookupTable8to8/shave/include/lookupTable8to8.h"
#include "../kernels/maxTest3x3_fp16/shave/include/maxTest3x3_fp16.h"
#include "../kernels/meanStdDev/shave/include/meanStdDev.h"
#include "../kernels/minMaxKernel/shave/include/minMaxKernel.h"
#include "../kernels/minMaxPos/shave/include/minMaxPos.h"
#include "../kernels/minTest3x3_fp16/shave/include/minTest3x3_fp16.h"
#include "../kernels/nonMax3x3_fp32/shave/include/nonMax3x3_fp32.h"
#include "../kernels/opticalFlowPyrLK/shave/include/opticalFlowPyrLK.h"
#include "../kernels/pixelPos/shave/include/pixelPos.h"
#include "../kernels/pyrdown/shave/include/pyrdown.h"
//#include "../kernels/RANSAC/shave/include/dummy/shared/RANSAC.h"
#include "../kernels/sLaplacian3x3/shave/include/sLaplacian3x3.h"
#include "../kernels/sLaplacian3x3Fp16ToFp16/shave/include/sLaplacian3x3Fp16ToFp16.h"
#include "../kernels/sLaplacian5x5/shave/include/sLaplacian5x5.h"
#include "../kernels/sLaplacian5x5Fp16ToFp16/shave/include/sLaplacian5x5Fp16ToFp16.h"
#include "../kernels/sLaplacian7x7/shave/include/sLaplacian7x7.h"
#include "../kernels/sLaplacian7x7Fp16ToFp16/shave/include/sLaplacian7x7Fp16ToFp16.h"
#include "../kernels/sobel/shave/include/sobel.h"
#include "../kernels/ssdPointLine7x7U8U32/shave/include/ssdPointLine7x7U8U32.h"
#include "../kernels/sumOfAbsDiff11x11/shave/include/sumOfAbsDiff11x11.h"
#include "../kernels/sumOfAbsDiff5x5/shave/include/sumOfAbsDiff5x5.h"
#include "../kernels/sumOfSquaredDiff11x11/shave/include/sumOfSquaredDiff11x11.h"
#include "../kernels/sumOfSquaredDiff5x5/shave/include/sumOfSquaredDiff5x5.h"
#include "../kernels/sumOfSquaredDiff7x7U8ToU32/shave/include/sumOfSquaredDiff7x7U8ToU32.h"
#include "../kernels/thresholdBinaryRange/shave/include/thresholdBinaryRange.h"
#include "../kernels/thresholdBinaryU8/shave/include/thresholdBinaryU8.h"
#include "../kernels/thresholdKernel/shave/include/thresholdKernel.h"
#include "../kernels/whiteBalanceBayerGBRG/shave/include/whiteBalanceBayerGBRG.h"
#include "../kernels/whiteBalanceRGB/shave/include/whiteBalanceRGB.h"

#endif //MVCV_H