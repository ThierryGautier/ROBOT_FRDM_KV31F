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

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/* PORTB17 (number 63), U10[1]/UART0_TX_TGTMCU */
#define BOARD_INITPINS_DEBUG_UART_TX_PERIPHERAL                            UART0   /*!< Device name: UART0 */
#define BOARD_INITPINS_DEBUG_UART_TX_SIGNAL                                   TX   /*!< UART0 signal: TX */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN_NAME                           UART0_TX   /*!< Pin name */
#define BOARD_INITPINS_DEBUG_UART_TX_LABEL              "U10[1]/UART0_TX_TGTMCU"   /*!< Label */
#define BOARD_INITPINS_DEBUG_UART_TX_NAME                        "DEBUG_UART_TX"   /*!< Identifier name */

/* PORTB16 (number 62), U7[4]/UART0_RX_TGTMCU */
#define BOARD_INITPINS_DEBUG_UART_RX_PERIPHERAL                            UART0   /*!< Device name: UART0 */
#define BOARD_INITPINS_DEBUG_UART_RX_SIGNAL                                   RX   /*!< UART0 signal: RX */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN_NAME                           UART0_RX   /*!< Pin name */
#define BOARD_INITPINS_DEBUG_UART_RX_LABEL               "U7[4]/UART0_RX_TGTMCU"   /*!< Label */
#define BOARD_INITPINS_DEBUG_UART_RX_NAME                        "DEBUG_UART_RX"   /*!< Identifier name */

/* PORTD2 (number 95), U8[4]/I2C0_SCL */
#define BOARD_INITPINS_ACCEL_SCL_PERIPHERAL                                 I2C0   /*!< Device name: I2C0 */
#define BOARD_INITPINS_ACCEL_SCL_SIGNAL                                      SCL   /*!< I2C0 signal: SCL */
#define BOARD_INITPINS_ACCEL_SCL_PIN_NAME                               I2C0_SCL   /*!< Pin name */
#define BOARD_INITPINS_ACCEL_SCL_LABEL                          "U8[4]/I2C0_SCL"   /*!< Label */
#define BOARD_INITPINS_ACCEL_SCL_NAME                                "ACCEL_SCL"   /*!< Identifier name */

/* PORTD3 (number 96), U8[6]/I2C0_SDA */
#define BOARD_INITPINS_ACCEL_SDA_PERIPHERAL                                 I2C0   /*!< Device name: I2C0 */
#define BOARD_INITPINS_ACCEL_SDA_SIGNAL                                      SDA   /*!< I2C0 signal: SDA */
#define BOARD_INITPINS_ACCEL_SDA_PIN_NAME                               I2C0_SDA   /*!< Pin name */
#define BOARD_INITPINS_ACCEL_SDA_LABEL                          "U8[6]/I2C0_SDA"   /*!< Label */
#define BOARD_INITPINS_ACCEL_SDA_NAME                                "ACCEL_SDA"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/* PORTD2 (number 95), U8[4]/I2C0_SCL */
#define I2C0_INITPINS_ACCEL_SCL_PERIPHERAL                                  I2C0   /*!< Device name: I2C0 */
#define I2C0_INITPINS_ACCEL_SCL_SIGNAL                                       SCL   /*!< I2C0 signal: SCL */
#define I2C0_INITPINS_ACCEL_SCL_PIN_NAME                                I2C0_SCL   /*!< Pin name */
#define I2C0_INITPINS_ACCEL_SCL_LABEL                           "U8[4]/I2C0_SCL"   /*!< Label */
#define I2C0_INITPINS_ACCEL_SCL_NAME                                 "ACCEL_SCL"   /*!< Identifier name */

/* PORTD3 (number 96), U8[6]/I2C0_SDA */
#define I2C0_INITPINS_ACCEL_SDA_PERIPHERAL                                  I2C0   /*!< Device name: I2C0 */
#define I2C0_INITPINS_ACCEL_SDA_SIGNAL                                       SDA   /*!< I2C0 signal: SDA */
#define I2C0_INITPINS_ACCEL_SDA_PIN_NAME                                I2C0_SDA   /*!< Pin name */
#define I2C0_INITPINS_ACCEL_SDA_LABEL                           "U8[6]/I2C0_SDA"   /*!< Label */
#define I2C0_INITPINS_ACCEL_SDA_NAME                                 "ACCEL_SDA"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C0_InitPins(void);

/* PORTD2 (number 95), U8[4]/I2C0_SCL */
#define I2C0_DEINITPINS_ACCEL_SCL_PERIPHERAL                                 n/a   /*!< Device name: n/a */
#define I2C0_DEINITPINS_ACCEL_SCL_SIGNAL                                disabled   /*!< n/a signal: disabled */
#define I2C0_DEINITPINS_ACCEL_SCL_PIN_NAME PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/LPUART0_RX/I2C0_SCL /*!< Pin name */
#define I2C0_DEINITPINS_ACCEL_SCL_LABEL                         "U8[4]/I2C0_SCL"   /*!< Label */
#define I2C0_DEINITPINS_ACCEL_SCL_NAME                               "ACCEL_SCL"   /*!< Identifier name */

/* PORTD3 (number 96), U8[6]/I2C0_SDA */
#define I2C0_DEINITPINS_ACCEL_SDA_PERIPHERAL                                 n/a   /*!< Device name: n/a */
#define I2C0_DEINITPINS_ACCEL_SDA_SIGNAL                                disabled   /*!< n/a signal: disabled */
#define I2C0_DEINITPINS_ACCEL_SDA_PIN_NAME PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/LPUART0_TX/I2C0_SDA /*!< Pin name */
#define I2C0_DEINITPINS_ACCEL_SDA_LABEL                         "U8[6]/I2C0_SDA"   /*!< Label */
#define I2C0_DEINITPINS_ACCEL_SDA_NAME                               "ACCEL_SDA"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C0_DeinitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
