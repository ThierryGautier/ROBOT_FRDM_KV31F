/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file issdk_hal.h
 * @brief Wrapper for Hardware Abstraction Layer (HAL)

    This file simply provides one level of indirection for the developer
    to select the particular Hardware Abstraction Layer they would like to use.
*/

#ifndef __ISSDK_HAL_H__
#define __ISSDK_HAL_H__

#include "fsl_i2c_cmsis.h"
#include "fsl_dspi_cmsis.h"
#include "fsl_uart_cmsis.h"

#include "frdm_kv31f.h"              //Include appropriate MCU board header file
#include "frdm_fxs_mult2b_shield.h" //Include appropriate sensor shield board header file

// Pin mapping and driver information for default I2C brought to mother board of FRDM_KV31
// Also, we use I2C_S0 defined in the FRDM_KV31F.h file to control device on the based board (BB).
// S0 is on D2:3.
#define I2C_B_SCL_PIN I2C_BB_SCL_PIN
#define I2C_B_SDA_PIN I2C_BB_SDA_PIN
#define I2C_B_DRIVER I2C_BB_DRIVER
#define I2C_B_SIGNAL_EVENT I2C_BB_SIGNAL_EVENT
#define I2C_B_DEVICE_INDEX I2C_BB_DEVICE_INDEX


// Pin mapping and driver information for default I2C brought to shield
// By default, we use I2C_S1 defined in the FRDM_KV31F.h file.
// Other options: I2C_S2.
// S1 is on A5:4.  S2 is on D15:14.
#define I2C_S_SCL_PIN I2C_S1_SCL_PIN
#define I2C_S_SDA_PIN I2C_S1_SDA_PIN
#define I2C_S_DRIVER I2C_S1_DRIVER
#define I2C_S_SIGNAL_EVENT I2C_S1_SIGNAL_EVENT
#define I2C_S_DEVICE_INDEX I2C_S1_DEVICE_INDEX

#endif // __ISSDK_HAL_H__
