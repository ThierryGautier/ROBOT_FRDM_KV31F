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
* @brief  Multiply with rounding
* 
*******************************************************************************/
#ifndef _MLIB_MULRND_F32_ASM_H_
#define _MLIB_MULRND_F32_ASM_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Includes
*******************************************************************************/
#include "mlib_types.h"

/*******************************************************************************
* Macros
*******************************************************************************/  
#define MLIB_MulRndSat_F32_Asmi(f32Mult1, f32Mult2) MLIB_MulRndSat_F32_FAsmi(f32Mult1, f32Mult2)
#define MLIB_MulRndSat_F32ls_Asmi(f32Mult1, f16Mult2) MLIB_MulRndSat_F32ls_FAsmi(f32Mult1, f16Mult2)

/***************************************************************************//*!
*
* f32Out = f32Mult1 * f32Mult2
* With saturation
*******************************************************************************/  
/* inline function without any optimization (compilation issue) */
#if defined(__IAR_SYSTEMS_ICC__) /* set no optimization for IAR compiler   */
    #pragma language=save        /* Save existing optimization level */
    #pragma optimize=none        /* Optimization none level now */        
#elif defined(__CC_ARM)          /* set no optimization for ARM(KEIL) compiler */
    #pragma O0                   /* Optimization level now O0 */                    
#else                            /* set no optimization for GCC(KDS) compiler */
    __attribute__((optimize("O0")))  
#endif
static inline frac32_t MLIB_MulRndSat_F32_FAsmi(register frac32_t f32Mult1, register frac32_t f32Mult2)
{
    #if defined(__CC_ARM)                                            /* For ARM Compiler */
        __asm volatile{ smull f32Mult2, f32Mult1, f32Mult1, f32Mult2 /* f32Mult1 * f32Mult2 */
                        lsrs f32Mult2, f32Mult2, #31                 /* f32Mult2 >> 31 */
                        adc f32Mult2, f32Mult2, #0                   /* Rounding */
                        qdadd f32Mult1, f32Mult2, f32Mult1 };        /* 2 * f32Mult1 + f32Mult2 with saturation */
    #else
        __asm volatile( "smull %1, %0, %0, %1 \n"                    /* f32Mult1:f32Mult2 = f32Mult1 * f32Mult2 */
                        "lsrs %1, %1, #31 \n"                        /* f32Mult2 >> 31 */
                        "adc %1, %1, #0 \n"                          /* Rounding */
                        "qdadd %0, %1, %0 \n"                        /* 2 * f32Mult1 + f32Mult2 with saturation */
                        : "+l"(f32Mult1), "+l"(f32Mult2):);
    #endif

    return f32Mult1;
}
#if defined(__IAR_SYSTEMS_ICC__) /* set no optimization for IAR compiler   */
    #pragma language=restore     /* Restore original optimization level */         
#elif defined(__CC_ARM)          /* set no optimization for ARM(KEIL) compiler */  
#else                            /* set no optimization for GCC(KDS) compiler */                
#endif 

/***************************************************************************//*!
*
* f32Out = f32Mult1 * f16Mult2
* With saturation
*******************************************************************************/
/* inline function without any optimization (compilation issue) */
#if defined(__IAR_SYSTEMS_ICC__) /* set no optimization for IAR compiler   */
    #pragma language=save        /* Save existing optimization level */
    #pragma optimize=none        /* Optimization none level now */        
#elif defined(__CC_ARM)          /* set no optimization for ARM(KEIL) compiler */
    #pragma O0                   /* Optimization level now O0 */                    
#else                            /* set no optimization for GCC(KDS) compiler */
    __attribute__((optimize("O0")))  
#endif
static inline frac32_t MLIB_MulRndSat_F32ls_FAsmi(register frac32_t f32Mult1, register frac16_t f16Mult2)
{
    #if defined(__CC_ARM)                                            /* For ARM Compiler */
        __asm volatile{ lsl f16Mult2, f16Mult2, #16                  /* f16Mult2 << 16 */
                        smull f16Mult2, f32Mult1, f32Mult1, f16Mult2 /* f32Mult1 * f16Mult2 */
                        lsrs f16Mult2, f16Mult2, #31                 /* f16Mult2 >> 31 */
                        adc f16Mult2, f16Mult2, #0                   /* Rounding */
                        qdadd f32Mult1, f16Mult2, f32Mult1 };        /* 2 * f32Mult1 + f16Mult2 with saturation */
    #else
        __asm volatile( "lsl %1, %1, #16 \n"                         /* f16Mult2 << 16 */
                        "smull %1, %0, %0, %1 \n"                    /* f32Mult1:f16Mult2 = f32Mult1 * f16Mult2 */
                        "lsrs %1, %1, #31 \n"                        /* f16Mult2 >> 31 */
                        "adc %1, %1, #0 \n"                          /* Rounding */
                        "qdadd %0, %1, %0 \n"                        /* 2 * f32Mult1 + f16Mult2 with saturation */
                        : "+l"(f32Mult1), "+l"(f16Mult2):);
    #endif

    return f32Mult1;
}
#if defined(__IAR_SYSTEMS_ICC__) /* set no optimization for IAR compiler   */
    #pragma language=restore     /* Restore original optimization level */         
#elif defined(__CC_ARM)          /* set no optimization for ARM(KEIL) compiler */  
#else                            /* set no optimization for GCC(KDS) compiler */                
#endif 

#if defined(__cplusplus)
}
#endif

#endif /* _MLIB_MULRND_F32_ASM_H_ */
