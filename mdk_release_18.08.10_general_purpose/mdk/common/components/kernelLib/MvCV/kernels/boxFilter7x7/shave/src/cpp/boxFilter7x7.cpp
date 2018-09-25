#include "boxFilter7x7.h"

void mvcvBoxfilter7x7(u8** in, u8** out, u32 normalize, u32 width)
{
    unsigned int i;
	int x,y;
    u8* lines[7];
    unsigned int sum;
    unsigned short* aux;
    aux=(unsigned short *)(*out);

    //Initialize lines pointers
    lines[0] = *in;
    lines[1] = *(in+1);
    lines[2] = *(in+2);
    lines[3] = *(in+3);
    lines[4] = *(in+4);
    lines[5] = *(in+5);
    lines[6] = *(in+6);

    //Go on the whole line
    for (i = 0; i < width; i++)
    {
        sum = 0;
        for (y = 0; y < 7; y++)
        {
            for (x = -3; x <= 3; x++)
            {
                sum += (lines[y][x]);
            }
            lines[y]++;
        }

        if(normalize == 1)
        {
            *(*out+i)=(u8)(((half)(float)sum)*(half)(0.02040816326530612244897959183673));
        }
        else
        {
            *(aux+i)=(unsigned short)sum;
        }
    }
    return;
}

#ifdef MOVICOMPILE_OPTIMIZED
void mvcvBoxfilter7x7_opt(u8** in, u8** out, u32 normalize, u32 width)
{ 
 
  uchar8 *outputLine = *(uchar8**)out;
  ushort8 *outputLineNN = *(ushort8**)out;
   
  half8 mulVec = { 0.02040816326530612244897959183673, 0.02040816326530612244897959183673, 
                   0.02040816326530612244897959183673, 0.02040816326530612244897959183673,
                   0.02040816326530612244897959183673, 0.02040816326530612244897959183673, 
                   0.02040816326530612244897959183673, 0.02040816326530612244897959183673};                   
  half8 clampVec = { 255.0, 255.0, 255.0, 255.0,
                     255.0, 255.0, 255.0, 255.0};
  
  uchar8 *in0 = *(uchar8**)in++;
  uchar8 *in1 = *(uchar8**)in++;
  uchar8 *in2 = *(uchar8**)in++;
  uchar8 *in3 = *(uchar8**)in++;
  uchar8 *in4 = *(uchar8**)in++;
  uchar8 *in5 = *(uchar8**)in++;
  uchar8 *in6 = *(uchar8**)in;

  uchar8 line0, line1, line2, line3, line4, line5, line6;
  line0 = in0[-1];
  line1 = in1[-1];
  line2 = in2[-1];
  line3 = in3[-1];
  line4 = in4[-1];
  line5 = in5[-1];
  line6 = in6[-1];
  
  ushort8 line0_u16, line1_u16, line2_u16, line3_u16, line4_u16, line5_u16, line6_u16;
  
  line0_u16 = mvuConvert_ushort8(line0);
  line1_u16 = mvuConvert_ushort8(line1);
  line2_u16 = mvuConvert_ushort8(line2);
  line3_u16 = mvuConvert_ushort8(line3);
  line4_u16 = mvuConvert_ushort8(line4);
  line5_u16 = mvuConvert_ushort8(line5);
  line6_u16 = mvuConvert_ushort8(line6);

  ushort8 tmp, sum;
  ushort8 colSumBefore, colSumCurrent, colSumAfter;
  
  //load
  line0 = *in0++;
  line1 = *in1++;
  line2 = *in2++;
  line3 = *in3++;
  line4 = *in4++;  
  line5 = *in5++;  
  line6 = *in6++;  
  
  //column addition 
  colSumBefore = __builtin_shave_vau_add_i16_rr(line0_u16, line1_u16);
  colSumBefore = __builtin_shave_vau_add_i16_rr(colSumBefore, line2_u16);
  colSumBefore = __builtin_shave_vau_add_i16_rr(colSumBefore, line3_u16);
  colSumBefore = __builtin_shave_vau_add_i16_rr(colSumBefore, line4_u16);
  colSumBefore = __builtin_shave_vau_add_i16_rr(colSumBefore, line5_u16);
  colSumBefore = __builtin_shave_vau_add_i16_rr(colSumBefore, line6_u16);
  
  //convert
  line0_u16 = mvuConvert_ushort8(line0);
  line1_u16 = mvuConvert_ushort8(line1);
  line2_u16 = mvuConvert_ushort8(line2);
  line3_u16 = mvuConvert_ushort8(line3);
  line4_u16 = mvuConvert_ushort8(line4);
  line5_u16 = mvuConvert_ushort8(line5);
  line6_u16 = mvuConvert_ushort8(line6);
  
  //load
  line0 = *in0++;
  line1 = *in1++;
  line2 = *in2++;
  line3 = *in3++;
  line4 = *in4++; 
  line5 = *in5++; 
  line6 = *in6++; 
  
  //column addition 
  colSumCurrent = __builtin_shave_vau_add_i16_rr(line0_u16, line1_u16);
  colSumCurrent = __builtin_shave_vau_add_i16_rr(colSumCurrent, line2_u16);
  colSumCurrent = __builtin_shave_vau_add_i16_rr(colSumCurrent, line3_u16);
  colSumCurrent = __builtin_shave_vau_add_i16_rr(colSumCurrent, line4_u16);
  colSumCurrent = __builtin_shave_vau_add_i16_rr(colSumCurrent, line5_u16);
  colSumCurrent = __builtin_shave_vau_add_i16_rr(colSumCurrent, line6_u16);
  
  
  for(u32  i = 0; i < width; i+=8)
  {  
    //convert
    line0_u16 = mvuConvert_ushort8(line0);
    line1_u16 = mvuConvert_ushort8(line1);
    line2_u16 = mvuConvert_ushort8(line2);
    line3_u16 = mvuConvert_ushort8(line3);
    line4_u16 = mvuConvert_ushort8(line4);
    line5_u16 = mvuConvert_ushort8(line5);
    line6_u16 = mvuConvert_ushort8(line6);
    
    //column addition 
    colSumAfter = __builtin_shave_vau_add_i16_rr(line0_u16, line1_u16);
    colSumAfter = __builtin_shave_vau_add_i16_rr(colSumAfter, line2_u16);
    colSumAfter = __builtin_shave_vau_add_i16_rr(colSumAfter, line3_u16);
    colSumAfter = __builtin_shave_vau_add_i16_rr(colSumAfter, line4_u16);
    colSumAfter = __builtin_shave_vau_add_i16_rr(colSumAfter, line5_u16);
    colSumAfter = __builtin_shave_vau_add_i16_rr(colSumAfter, line6_u16);
    
    sum = __builtin_shave_cmu_alignvec_rri_short8(colSumBefore, colSumCurrent, 10);
    sum = __builtin_shave_vau_add_i16_rr(sum, colSumCurrent);
    tmp = __builtin_shave_cmu_alignvec_rri_short8(colSumBefore, colSumCurrent, 12);
    sum = __builtin_shave_vau_add_i16_rr(sum, tmp);
    tmp = __builtin_shave_cmu_alignvec_rri_short8(colSumBefore, colSumCurrent, 14);
    sum = __builtin_shave_vau_add_i16_rr(sum, tmp);
    tmp = __builtin_shave_cmu_alignvec_rri_short8(colSumCurrent, colSumAfter, 2);
    sum = __builtin_shave_vau_add_i16_rr(sum, tmp);
    tmp = __builtin_shave_cmu_alignvec_rri_short8(colSumCurrent, colSumAfter, 4);
    sum = __builtin_shave_vau_add_i16_rr(sum, tmp);
    tmp = __builtin_shave_cmu_alignvec_rri_short8(colSumCurrent, colSumAfter, 6);
    sum = __builtin_shave_vau_add_i16_rr(sum, tmp);
         
         
    colSumBefore = colSumCurrent;
    colSumCurrent = colSumAfter;
    
    line0 = *in0++;
    line1 = *in1++;
    line2 = *in2++;
    line3 = *in3++;
    line4 = *in4++; 
    line5 = *in5++; 
    line6 = *in6++; 
    
    if(normalize == 1)
    {
      half8 tmpFp16;
      tmpFp16 = mvuConvert_half8(sum);
      tmpFp16 = __builtin_shave_vau_mul_f16_rr(tmpFp16, mulVec);
      tmpFp16 = __builtin_shave_cmu_clamp_f16_rr_half8(tmpFp16, clampVec);
      
      uchar8 outputTemp;
      outputTemp = mvuConvert_uchar8(tmpFp16);
      *outputLine++ = outputTemp;
    }    
    
    else
    {      
      *outputLineNN++ = sum;    
    }
  }
  
  return;
}
#endif //MOVICOMPILE_OPTIMIZED