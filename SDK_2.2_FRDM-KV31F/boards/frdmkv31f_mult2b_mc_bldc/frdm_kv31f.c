/*
* Copyright (c) 2016, Freescale Semiconductor, Inc.
* All rights reserved.
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
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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

/*! \file frdm_kv31f.h
    \brief The \b frdm_kv31f.h file defines GPIO pins for FRDM-KV31F board
*/

#ifndef FRDM_KV31F_H_
#define FRDM_KV31F_H_
#include "Driver_GPIO.h"
#include "gpio_driver.h"
#include "frdm_kv31f.h"

// I2C0 Handle
// PTD2 = I2C0_SCL
// PTD3 = I2C0_SDA
gpioHandleKSDK_t I2C0_SCL = {.base = GPIOD,
                             .portBase = PORTD,
                             .pinNumber = 2,
							 .mask = 1 << (2),
							 .irq = PORTD_IRQn,
							 .clockName = kCLOCK_PortD,
							 .portNumber = PORTD_NUM};
gpioHandleKSDK_t I2C0_SDA = {.base = GPIOD,
                       	     .portBase = PORTD,
						     .pinNumber = 3,
							 .mask = 1 << (3),
							 .irq = PORTD_IRQn,
							 .clockName = kCLOCK_PortD,
							 .portNumber = PORTD_NUM};

// I2C1 Handle
// PTC10 = I2C1_SCL
// PTC11 = I2C1_SDA
gpioHandleKSDK_t I2C1_SCL = {.base = GPIOC,
                             .portBase = PORTC,
                             .pinNumber = 10,
							 .mask = 1 << (10),
							 .irq = PORTC_IRQn,
							 .clockName = kCLOCK_PortC,
							 .portNumber = PORTC_NUM};
gpioHandleKSDK_t I2C1_SDA = {.base = GPIOC,
                       	     .portBase = PORTC,
						     .pinNumber = 11,
							 .mask = 1 << (11),
							 .irq = PORTC_IRQn,
							 .clockName = kCLOCK_PortC,
							 .portNumber = PORTC_NUM};

// SPI0 Handle
// PTE17 = SPI0_SCK
// PTE18 = SPI0_SOUT
// PTE19 = SPI0_SIN
gpioHandleKSDK_t SPI0_SCK = {.base = GPIOE,
                        	 .portBase = PORTE,
							 .pinNumber = 17,
							 .mask = 1 << (17),
							 .irq = PORTE_IRQn,
							 .clockName = kCLOCK_PortE,
							 .portNumber = PORTE_NUM};
gpioHandleKSDK_t SPI0_SOUT = {.base = GPIOE,
                              .portBase = PORTE,
							  .pinNumber = 18,
							  .mask = 1 << (18),
							  .irq = PORTE_IRQn,
							  .clockName = kCLOCK_PortE,
							  .portNumber = PORTE_NUM};
gpioHandleKSDK_t SPI0_SIN = {.base = GPIOE,
                             .portBase = PORTE,
							 .pinNumber = 19,
							 .mask = 1 << (19),
							 .irq = PORTE_IRQn,
							 .clockName = kCLOCK_PortE,
							 .portNumber = PORTE_NUM};

// UART0 Handle
// PTB17 = UART0_TX
// PTB16 = UART0_RX
gpioHandleKSDK_t UART0_TX = {.base = GPIOB,
                             .portBase = PORTB,
                             .pinNumber = 17,
							 .mask = 1 << (17),
							 .irq = PORTB_IRQn,
							 .clockName = kCLOCK_PortB,
							 .portNumber = PORTB_NUM};
gpioHandleKSDK_t UART0_RX = {.base = GPIOB,
                         	 .portBase = PORTB,
							 .pinNumber = 16,
							 .mask = 1 << (16),
							 .irq = PORTB_IRQn,
							 .clockName = kCLOCK_PortB,
							 .portNumber = PORTB_NUM};

// UART1 Handle
// PTE0 = UART1_TX
// PTE1 = UART1_RX
gpioHandleKSDK_t UART1_TX = {.base = GPIOE,
                             .portBase = PORTE,
                             .pinNumber = 0,
							 .mask = 1 << (0),
							 .irq = PORTE_IRQn,
							 .clockName = kCLOCK_PortE,
							 .portNumber = PORTE_NUM};
gpioHandleKSDK_t UART1_RX = {.base = GPIOE,
                         	 .portBase = PORTE,
							 .pinNumber = 1,
							 .mask = 1 << (1),
							 .irq = PORTE_IRQn,
							 .clockName = kCLOCK_PortE,
							 .portNumber = PORTE_NUM};

// FRDM-KV31F Arduino Connector Pin Defintion
gpioHandleKSDK_t A0 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 8,
                       .mask = 1 << (8),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t A1 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 9,
                       .mask = 1 << (9),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t A2 = {.base = GPIOB,
                       .portBase = PORTB,
                       .pinNumber = 11,
                       .mask = 1 << (11),
                       .irq = PORTB_IRQn,
                       .clockName = kCLOCK_PortB,
                       .portNumber = PORTB_NUM};
gpioHandleKSDK_t A3 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 0,
                       .mask = 1 << (0),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D0 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 1,
                       .mask = 1 << (1),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTD_NUM};
gpioHandleKSDK_t D1 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 0,
                       .mask = 1 << (0),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D2 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 5,
                       .mask = 1 << (5),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D3 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 6,
                       .mask = 1 << (6),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D4 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 13,
                       .mask = 1 << (13),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D5 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 12,
                       .mask = 1 << (12),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D6 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 3,
                       .mask = 1 << (3),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D7 = {.base = GPIOC,
                       .portBase = PORTC,
                       .pinNumber = 6,
                       .mask = 1 << (6),
                       .irq = PORTC_IRQn,
                       .clockName = kCLOCK_PortC,
                       .portNumber = PORTC_NUM};
gpioHandleKSDK_t D8 = {.base = GPIOE,
                       .portBase = PORTE,
                       .pinNumber = 24,
                       .mask = 1 << (24),
                       .irq = PORTE_IRQn,
                       .clockName = kCLOCK_PortE,
                       .portNumber = PORTE_NUM};
gpioHandleKSDK_t D9 = {.base = GPIOA,
                       .portBase = PORTA,
                       .pinNumber = 5,
                       .mask = 1 << (5),
                       .irq = PORTA_IRQn,
                       .clockName = kCLOCK_PortA,
                       .portNumber = PORTA_NUM};
gpioHandleKSDK_t D10 = {.base = GPIOD,
                        .portBase = PORTD,
                        .pinNumber = 6,
                        .mask = 1 << (6),
                        .irq = PORTD_IRQn,
                        .clockName = kCLOCK_PortD,
                        .portNumber = PORTD_NUM};

// FRDM-KV31F RGB LED Pin Definitions
// PTD1  = RED LED
// PTD7  = GREEN LED
// PTE25 = BLUE LED
gpioHandleKSDK_t RED_LED = {.base = GPIOD,
                            .portBase = PORTD,
                            .pinNumber = 1,
                            .mask = 1 << (1),
                            .irq = PORTD_IRQn,
                            .clockName = kCLOCK_PortD,
                            .portNumber = PORTD_NUM};
gpioHandleKSDK_t GREEN_LED = {.base = GPIOD,
                              .portBase = PORTD,
                              .pinNumber = 7,
                              .mask = 1 << (7),
                              .irq = PORTD_IRQn,
                              .clockName = kCLOCK_PortD,
                              .portNumber = PORTD_NUM};
gpioHandleKSDK_t BLUE_LED = {.base = GPIOE,
                             .portBase = PORTE,
                             .pinNumber = 25,
                             .mask = 1 << (25),
                             .irq = PORTE_IRQn,
                             .clockName = kCLOCK_PortE,
                             .portNumber = PORTE_NUM};

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART0_GetFreq(void)
{
    return CLOCK_GetFreq(UART0_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t UART1_GetFreq(void)
{
    return CLOCK_GetFreq(UART1_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t I2C0_GetFreq(void)
{
    return CLOCK_GetFreq(I2C0_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t I2C1_GetFreq(void)
{
    return CLOCK_GetFreq(I2C1_CLK_SRC);
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t DSPI0_GetFreq(void)
{
    return CLOCK_GetBusClkFreq();
}

#endif /* FRDM_KV31F_H_ */
