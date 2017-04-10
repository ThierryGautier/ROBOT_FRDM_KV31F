/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
PinsProfile:
- !!product 'Pins v2.0'
- !!processor 'MKV31F512xxx12'
- !!package 'MKV31F512VLL12'
- !!mcu_data 'ksdk2_0'
- !!processor_version '1.0.1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port */
#define PIN19_IDX                       19u   /*!< Pin number for pin 19 in a port */
#define SOPT5_UART0TXSRC_UART_TX      0x00u   /*!< UART 0 transmit data source select: UART0_TX pin */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '62', peripheral: UART0, signal: RX, pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN}
  - {pin_num: '63', peripheral: UART0, signal: TX, pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b}
  - {pin_num: '10', peripheral: SPI0, signal: PCS0_SS, pin_signal: ADC0_SE4a/PTE16/SPI0_PCS0/UART2_TX/FTM_CLKIN0/FTM0_FLT3}
  - {pin_num: '11', peripheral: SPI0, signal: SCK, pin_signal: ADC0_SE5a/PTE17/SPI0_SCK/UART2_RX/FTM_CLKIN1/LPTMR0_ALT3}
  - {pin_num: '12', peripheral: SPI0, signal: SOUT, pin_signal: ADC0_SE6a/PTE18/SPI0_SOUT/UART2_CTS_b/I2C0_SDA}
  - {pin_num: '13', peripheral: SPI0, signal: SIN, pin_signal: ADC0_SE7a/PTE19/SPI0_SIN/UART2_RTS_b/I2C0_SCL}
  - {pin_num: '58', peripheral: SPI1, signal: PCS0_SS, pin_signal: ADC1_SE14/PTB10/SPI1_PCS0/LPUART0_RX/FB_AD19/FTM0_FLT1}
  - {pin_num: '3', peripheral: SPI1, signal: SCK, pin_signal: ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b}
  - {pin_num: '4', peripheral: SPI1, signal: SIN, pin_signal: ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SPI1_SOUT}
  - {pin_num: '99', peripheral: SPI1, signal: SOUT, pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTB, PIN10_IDX, kPORT_MuxAlt2);           /* PORTB10 (pin 58) is configured as SPI1_PCS0 */
  PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3);           /* PORTB16 (pin 62) is configured as UART0_RX */
  PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3);           /* PORTB17 (pin 63) is configured as UART0_TX */
  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_MuxAlt7);            /* PORTD6 (pin 99) is configured as SPI1_SOUT */
  PORT_SetPinMux(PORTE, PIN16_IDX, kPORT_MuxAlt2);           /* PORTE16 (pin 10) is configured as SPI0_PCS0 */
  PORT_SetPinMux(PORTE, PIN17_IDX, kPORT_MuxAlt2);           /* PORTE17 (pin 11) is configured as SPI0_SCK */
  PORT_SetPinMux(PORTE, PIN18_IDX, kPORT_MuxAlt2);           /* PORTE18 (pin 12) is configured as SPI0_SOUT */
  PORT_SetPinMux(PORTE, PIN19_IDX, kPORT_MuxAlt2);           /* PORTE19 (pin 13) is configured as SPI0_SIN */
  PORT_SetPinMux(PORTE, PIN2_IDX, kPORT_MuxAlt2);            /* PORTE2 (pin 3) is configured as SPI1_SCK */
  PORT_SetPinMux(PORTE, PIN3_IDX, kPORT_MuxAlt2);            /* PORTE3 (pin 4) is configured as SPI1_SIN */
  SIM->SOPT5 = ((SIM->SOPT5 &
    (~(SIM_SOPT5_UART0TXSRC_MASK)))                          /* Mask bits to zero which are setting */
      | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)       /* UART 0 transmit data source select: UART0_TX pin */
    );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
