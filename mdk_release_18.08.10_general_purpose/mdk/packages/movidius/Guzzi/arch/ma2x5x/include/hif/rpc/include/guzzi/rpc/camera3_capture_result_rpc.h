/* =============================================================================
* Copyright (c) 2013-2014 MM Solutions AD
* All rights reserved. Property of MM Solutions AD.
*
* This source code may not be used against the terms and conditions stipulated
* in the licensing agreement under which it has been supplied, or without the
* written permission of MM Solutions. Rights to use, copy, modify, and
* distribute or disclose this source code and its documentation are granted only
* through signed licensing agreement, provided that this copyright notice
* appears in all copies, modifications, and distributions and subject to the
* following conditions:
* THIS SOURCE CODE AND ACCOMPANYING DOCUMENTATION, IS PROVIDED AS IS, WITHOUT
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED. MM SOLUTIONS SPECIFICALLY DISCLAIMS
* ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN
* NO EVENT SHALL MM SOLUTIONS BE LIABLE TO ANY PARTY FOR ANY CLAIM, DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
* PROFITS, OR OTHER LIABILITY, ARISING OUT OF THE USE OF OR IN CONNECTION WITH
* THIS SOURCE CODE AND ITS DOCUMENTATION.
* =========================================================================== */
/**
* @file
*
* @author ( MM Solutions AD )
*
*/
/* -----------------------------------------------------------------------------
*!
*! Revision History
*! ===================================
*! 05-Nov-2013 : Author ( MM Solutions AD )
*! Created
* =========================================================================== */

#ifndef _RPC_GUZZI_CAMERA3_CAPTURE_RESULT_H
#define _RPC_GUZZI_CAMERA3_CAPTURE_RESULT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <guzzi/rpc/rpc.h>

#define RPC_GUZZI_CAMERA3_CAPTURE_RESULT_FUNCTION_ID(N) \
    (rpc_guzzi_camera3_capture_result_function_id_base + (N))

#define RPC_GUZZI_CAMERA3_CAPTURE_RESULT RPC_GUZZI_CAMERA3_CAPTURE_RESULT_FUNCTION_ID(1)

extern const rpc_uint32_t rpc_guzzi_camera3_capture_result_function_id_base;

typedef struct {
    rpc_int32_t camera_id;
    rpc_uint32_t stream_id;
    rpc_uint32_t frame_number;
    rpc_uint32_t data_size;
    rpc_uint8_t data[0];
} rpc_guzzi_camera3_capture_result_t;

typedef struct {
} rpc_guzzi_camera3_capture_result_return_t;

#ifdef __cplusplus
}
#endif

#endif /* _RPC_GUZZI_CAMERA3_CAPTURE_RESULT_H */
