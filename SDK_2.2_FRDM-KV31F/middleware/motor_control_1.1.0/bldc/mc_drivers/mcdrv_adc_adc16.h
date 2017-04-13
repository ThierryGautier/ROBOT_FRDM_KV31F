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
#ifndef _MCDRV_ADC_ADC16_H_
#define _MCDRV_ADC_ADC16_H_

#include "gdflib.h"
#include "gmclib_types.h"
#include "fsl_device_registers.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define MCDRV_CHAN_OFF (0x1F)
#define MCDRV_TEMP (0x1A)

#define MCDRV_ADC0_BEMFA (0)
#define MCDRV_ADC1_BEMFA (1)
#define MCDRV_ADC0_BEMFB (2)
#define MCDRV_ADC1_BEMFB (3)
#define MCDRV_ADC0_BEMFC (4)
#define MCDRV_ADC1_BEMFC (5)
#define MCDRV_ADC0_UDCB (6)
#define MCDRV_ADC1_UDCB (7)
#define MCDRV_ADC0_IDCB (8)
#define MCDRV_ADC1_IDCB (9)
#define MCDRV_ADC0_AUX (10)
#define MCDRV_ADC1_AUX (11)

/* init sensors/actuators pointers */
#define M1_SET_PTR_U_DC_BUS(par1) (g_sM1AdcSensor.pf16UDcBus = &(par1))
#define M1_SET_PTR_I_DC_BUS(par1) (g_sM1AdcSensor.pf16IDcBus = &(par1))
#define M1_SET_PTR_BEMF_VOLT(par1) (g_sM1AdcSensor.pf16BemfVoltage = &(par1))
#define M1_SET_PTR_AUX_CHAN(par1) (g_sM1AdcSensor.pui16AuxChan = &(par1))

typedef struct _mcdrv_adc16
{
    GDFLIB_FILTER_MA_T_A32 ui16FiltDcCurr; /* Dc-bus current offset filter */
    ADC_Type *pui32UdcbAdcBase;            /* pointer to ADC where DC-bus voltage channel is assigned */
    ADC_Type *pui32IdcbAdcBase;            /* pointer to ADC where DC-bus current channel is assigned */
    ADC_Type *pui32BemfAAdcBase;           /* pointer to ADC where BEMF phase A channel is assigned */
    ADC_Type *pui32BemfBAdcBase;           /* pointer to ADC where BEMF phase B channel is assigned */
    ADC_Type *pui32BemfCAdcBase;           /* pointer to ADC where BEMF phase C channel is assigned */
    ADC_Type *pui32AuxAdcBase;             /* pointer to ADC where AUX channel is assigned  */
    uint16_t ui16IndexAux;                 /* auxiliary ADC channel index  */
    uint16_t ui16IndexUdcb;                /* DC-bus voltage ADC channel index  */
    uint16_t ui16IndexIdcb;                /* DC-bus current ADC channel index  */
    uint16_t ui16IndexBemf;                /* BEMF ADC channel index  */
    uint16_t ui16OffsetFiltWindow;         /* ADC offset filter window */
    uint16_t ui16OffsetDcCurr;             /* Dc-bus current offset */
    uint16_t ui16CalibDcCurr;              /* Dc-bus current offset calibration */
    frac16_t *pf16IDcBus;                  /* pointer to DC-bus  current variable */
    frac16_t *pf16UDcBus;                  /* pointer to DC-bus  voltage variable */
    frac16_t *pf16BemfVoltage;             /* pointer to actual BEMF voltage     */
    uint16_t *pui16AuxChan;                /* pointer to actual auxiliary variable   */
    uint16_t ui16Sector;                   /* commutation sector */
    uint16_t bldcAdc0SectorCfg[6];         /* array with BEMF channels assigned to ADC0 according commutation table */
    uint16_t bldcAdc1SectorCfg[6];         /* array with BEMF channels assigned to ADC1 according commutation table */
    uint16_t *pui16AdcArray;               /* pointer to ADC Array with channels numbers */
    ADC_Type *bldcAdcSelCfg[6]; 		   /* array with ADC base addresses for BEMF sensing according commutation table*/
} mcdrv_adc16_t;

typedef struct _mcdrv_adc16_init
{
    uint16_t *ui16AdcArray;  /* pointer to ADC Array */
    ADC_Type *pui32Adc0Base; /* pointer to ADC0 base address */
    ADC_Type *pui32Adc1Base; /* pointer to ADC1 base address */
} mcdrv_adc16_init_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initializes ADC driver to measure DC-bus current, DC-bus voltage
 *        and BEMF voltage for BLDC sensorless algorithm
 *
 * @param this   Pointer to the current object
 * @param init   Pointer to initialization structure
 *
 * @return boot_t true on success
 */
bool_t MCDRV_Adc16Init(mcdrv_adc16_t *this, mcdrv_adc16_init_t *init);

/*!
 * @brief Function set new channel assignment for next BEMF voltage sensing
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_AssignBemfChannel(mcdrv_adc16_t *this);

/*!
 * @brief Function reads ADC result register containing actual BEMF voltage
 *
 * Result register value is shifted three times to the right and stored
 * to BEMF voltage pointer
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_BemfVoltageGet(mcdrv_adc16_t *this);

/*!
 * @brief Function reads ADC result register containing actual DC-bus voltage sample
 *
 * Result register value is shifted three times to the right and stored
 * to DC-bus voltage pointer
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_VoltDcBusGet(mcdrv_adc16_t *this);

/*!
 * @brief Function reads ADC result register containing actual DC-bus current sample
 *
 * Result register value is shifted three times to the right and stored
 * to DC-bus current pointer
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_CurrDcBusGet(mcdrv_adc16_t *this);

/*!
 * @brief Function reads ADC result register containing actual auxiliary sample
 *
 * Result register value is shifted 3 times right and stored to
 * auxiliary pointer
 *
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_AuxValGet(mcdrv_adc16_t *this);

/*!
 * @brief Function initializes phase current channel offset measurement
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_CurrOffsetCalibInit(mcdrv_adc16_t *this);

/*!
 * @brief Function reads current samples and filter them
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_CurrOffsetCalib(mcdrv_adc16_t *this);

/*!
 * @brief Function passes measured offset values to main structure
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_CurrOffsetCalibSet(mcdrv_adc16_t *this);

#ifdef __cplusplus
}
#endif

#endif /* _MCDRV_ADC_ADC16_H_ */
