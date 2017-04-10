/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
*
* @brief  Conversion functions
* 
*******************************************************************************/
#ifndef _MLIB_CONVSC_FLT_H_
#define _MLIB_CONVSC_FLT_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Includes
*******************************************************************************/
#include "mlib_types.h"  
#include "MLIB_Div_FLT.h"
#include "MLIB_Mul_FLT.h"

/*******************************************************************************
* Macros 
*******************************************************************************/  
#define MLIB_ConvSc_A32ff_Ci(fltVal, fltSc) MLIB_ConvSc_A32ff_FCi(fltVal, fltSc)
#define MLIB_ConvSc_FLTaf_Ci(a32Val, fltSc) MLIB_ConvSc_FLTaf_FCi(a32Val, fltSc) 

/***************************************************************************//*!
*  float to 32-bit accumulator convert function  
*    
* @param  in:  fltVal   Input value in single precision floating point format 
*                       to be converted.
*              fltSc    Scale factor in single precision floating point format.                         
*                
* @return This function returns - 32-bit accumulator value (-65536.0, 65536.0]
*       
* @remarks This inline function returns converted input value. The input value
* is considered as single precision floating point data type and output value 
* is considered as 32-bit accumulator data type. The second value represents the
* scale factor and is considered as single precision floating point data type.
* The output value represents the values in unity model. The output saturation 
* is implemented in this function, thus in case the input value is outside
* the (-65536.0, 65536.0] interval, the output value is limited to the boundary value.
*           
*******************************************************************************/
static inline acc32_t MLIB_ConvSc_A32ff_FCi(register float_t fltVal, register float_t fltSc)
{      
    register float_t fltInScaled;
    
    fltInScaled = MLIB_Div_FLT_FCi(fltVal, fltSc);
    
    return((fltInScaled>=(float_t)65535.999969482421875F) ? (acc32_t)INT32_MAX :
    ((fltInScaled<(float_t)-65536.0F) ? (acc32_t)INT32_MIN :
    (acc32_t)MLIB_Mul_FLT_FCi(fltInScaled,((float_t)INT16_MAX) + (float_t)1.0F)));
}
 
/***************************************************************************//*!
*  32-bit accumulator to float convert function   
*    
* @param  in:   float_t f32Acc - Argument in acc32_t (-65536.0, 65536.0]
*               float_t fltSc  - Argument in float_t                          
*
* @return This function returns - float_t value 
*       
* @remarks This inline function returns converted input value. The input value 
* is considered as 32-bit accumulator and float data types and output value is  
* considered as single precision floating point data type. The input value  
* represents the values in unity model. The second value represents the scale  
* factor and is considered as single precision float data type and determine the
* scale conversion.    
*           
*******************************************************************************/
static inline float_t MLIB_ConvSc_FLTaf_FCi(register acc32_t a32Val, register float_t fltSc)
{        
    return ((float_t)(MLIB_Mul_FLT_FCi(MLIB_Div_FLT_FCi((float_t)a32Val,
                                                       ((float_t)INT16_MAX+(float_t)1.0F)),
                                      (float_t)fltSc)));
}
 
#if defined(__cplusplus)
}
#endif

#endif  /* _MLIB_CONVSC_FLT_H_ */
