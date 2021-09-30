#include "stdtype.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"

#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"

#include "fsl_common.h"
#include "clock_config.h"

static lpuart_rtos_handle_t handle;
static struct _lpuart_handle t_handle;
static uint8_t lpuartbackground_buffer[256];

lpuart_rtos_config_t lpuart_config = {
//    .baudrate    = 115200,
//    .baudrate    = 230400,
	.baudrate    = 500000,
	.parity      = kLPUART_ParityDisabled,
    .stopbits    = kLPUART_OneStopBit,
    .buffer      = lpuartbackground_buffer,
    .buffer_size = sizeof(lpuartbackground_buffer),
};

BOOL LPUART_bOpenDevice (char pcDeviceName[])
{
    int error;

    CLOCK_SetLpuartClock(0x1U);

    NVIC_SetPriority(LPUART0_IRQn, 5);
    lpuart_config.srcclk = CLOCK_GetFreq(kCLOCK_PllFllSelClk);
    lpuart_config.base   = LPUART0;

    /* init device */
    error = LPUART_RTOS_Init(&handle, &t_handle, &lpuart_config);
    if (error != kStatus_Success )
    {
    	/** error */
    	return(FALSE);
    }
    else
    {
	    /** no error */
    	return(TRUE);
    }
}

BOOL LPUART_bGetRxChar(UI08 *pu8RxChar)
{
	BOOL bCharIsRecieved;
	size_t NbReceived;
    int error;

    /** read one byte */
	error = LPUART_RTOS_Receive(&handle, pu8RxChar, (uint32_t)1, &NbReceived);
    if((error == kStatus_Success ) &&
       (NbReceived == 1))
    {
    	/** no error */
    	bCharIsRecieved = TRUE;
    }
    else
    {
	    /** error */
    	bCharIsRecieved = FALSE;
    }
    return(bCharIsRecieved);
}

BOOL LPUART_bPutTxBuffer(UI08* u8TxBuffer, UI08 u8Size)
{
	BOOL bCharIsSent;
    int error;
	/** write one byte */
    error = LPUART_RTOS_Send(&handle, u8TxBuffer, (uint32_t)u8Size);
    if (error != kStatus_Success )
    {
    	/** error */
    	bCharIsSent = FALSE;
    }
    else
    {
	    /** no error */
    	bCharIsSent = TRUE;
    }
    return(bCharIsSent);
}

BOOL LPUART_bCloseDevice (void)
{
	/* close device and driver */
	LPUART_RTOS_Deinit(&handle);
	return TRUE;
}
