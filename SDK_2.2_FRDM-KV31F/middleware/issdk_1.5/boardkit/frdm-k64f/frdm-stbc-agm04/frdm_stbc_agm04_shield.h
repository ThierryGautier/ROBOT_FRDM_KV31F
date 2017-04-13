/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
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

/** 
 * @file frdm_stbc_agm04_shield.h
 * @brief The frdm_stbc_agm04_shield.h file declares mapping of the Kinetis
         Device peripherals to the frmd-k64f and frmd-stbc-agm04 shield
 */

#ifndef _FRDM_STBC_AGM04_SHIELD_H_
#define _FRDM_STBC_AGM04_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBC-AGM04"

// MAG3110 Sensor Information
#define MAG3110_I2C_ADDR           0x0E
#define MAG3110_INT1               D5

// MMA8652 Sensor Information
#define MMA8652_I2C_ADDR           0x1D
#define MMA8652_INT1               D2
#define MMA8652_INT2               D8

// FXAS21002 Sensor Information
#define FXAS21002_I2C_ADDR         0x20
#define FXAS21002_INT1             D4
#define FXAS21002_INT2             D10

///@name Shield Parameters
/// Use this section to define the shield board: 3 bit code 0 to 7 inclusive
/// transmitted in bits 7-5 for display purposes only.
///@{
#define SHIELD_MULTIB 0
#define SHIELD_NONE 1
#define SHIELD_AGM01 2
#define SHIELD_AGM02 3
#define SHIELD_AGMP03 4
#define SHIELD_AGM04 5
#define THIS_SHIELD SHIELD_AGM04

///@}

#endif /* _FRDM_STBC_AGM04_SHIELD_H_ */
