///
/// @file
/// @copyright All code copyright Movidius Ltd 2017, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Inter-Leon : passing PoPtr<>
///

#include <Flic.h>
#include <FlicRmt.h>
#include <RmtBarr.h>
#include <MemAllocator.h>
#include <DrvLeon.h>
#include <DrvCpr.h>
#include "../shared/PlgEcho.h"

// LOS
       Pool<ImgFrame> pool [N] SECTION(".cmx_direct.bss");
       PlgA<MyMsg>    plugA[N]; //sends
       RmtO<MyMsg>    stubA[N]; //local stub
extern RmtI<MyMsg>    skelB[N]; //remote skeleton on LRT
       Pipeline       p;

extern RmtBarr        bLRT;
       RmtBarr        bLOS SECTION(".cmx_direct.bss");

//########################################################
extern "C" void* POSIX_Init(void *args)
{
   UNUSED(args);
   DrvCprInit();
   printf("Sys freq = %ld KHz\n", DrvCprGetSysClockKhz());
   printf("Estimated duration : %s\n", SZ_ETC);

   RgnAlloc.Create(RgnBuff, DEF_POOL_SZ);
   FlicRmt::Init();

   for(int i=0; i<N; i++)
   {
     pool [i].Create(&RgnAlloc, N_POOL_FRMS, FRM_SZ, true);
     stubA[i].Create(&skelB[i]);
     plugA[i].Create(N_MSG, SEED(i));
     p.Add(&pool [i]);
     p.Add(&plugA[i]);
     p.Add(&stubA[i]);
     pool [i].out.Link(&plugA[i].in);
     plugA[i].out.Link(&stubA[i].in);
   }
   bLOS.Create(&bLRT);

  //Start LRT
   DrvLeonRTStartupStart();
   DrvLeonRTWaitForBoot ();

   p.Start();

  //Skel/stub never stop so can't just do "p.Wait()" in this test
  //waiting instead after relevant/active plugins.
  //In a practical app a p.Stop() would be invoked some user-interface block
   for(int i=0; i<N; i++)
    plugA[i].Join();
   bLOS.Wait(); //wait for LRT to hit the barrier

   FlicRmt::Destroy();
   exit(0);
}