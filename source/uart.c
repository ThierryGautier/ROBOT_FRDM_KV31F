#include "stdtype.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"

#include "fsl_uart_freertos.h"
#include "fsl_uart.h"

#include "fsl_common.h"
//#include "pin_mux.h"
#include "clock_config.h"

static uart_rtos_handle_t handle;
static struct _uart_handle t_handle;
static uint8_t background_buffer[256];

BOOL UART_bOpenDevice (char pcDeviceName[])
{
    int error;
    uart_rtos_config_t uart_config;

	/* Init board hardware. */
    NVIC_SetPriority(UART1_RX_TX_IRQn, 5);

    uart_config.baudrate = 115200;
    uart_config.parity = kUART_ParityDisabled;
    uart_config.stopbits = kUART_OneStopBit;
    uart_config.buffer = background_buffer;
    uart_config.buffer_size = sizeof(background_buffer);
    uart_config.srcclk = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    uart_config.base = UART1;

    /* init device */
    error = UART_RTOS_Init(&handle, &t_handle, &uart_config);
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

BOOL UART_bGetRxChar(UI08 *pu8RxChar)
{
	BOOL bCharIsRecieved;
	size_t NbReceived;
    int error;
	/** read one byte */
	error = UART_RTOS_Receive(&handle, pu8RxChar, (uint32_t)1, &NbReceived);
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

BOOL UART_bPutTxBuffer(UI08* u8TxBuffer, UI08 u8Size)
{
	BOOL bCharIsSent;
    int error;
	/** write one byte */
    error = UART_RTOS_Send(&handle, u8TxBuffer, (uint32_t)u8Size);
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

// initialize BlueRadios BR-LE4.0-D2A Bluetooth module
// This is required for NXP FRDM-FXS-MULT2-B boards.
void UART_BlueRadiosInit(void)
{
	{
		// transmit "ATSRM,2,1\r" to minimize traffic from the module
		UI08 sUARTOutputBuffer[] = "ATSRM,2,1\r";
		UART_bPutTxBuffer(sUARTOutputBuffer, sizeof(sUARTOutputBuffer));
		//wait response
	}

	{
		// transmit "ATSRM,2,1\r" to minimize traffic from the module
		UI08 sUARTOutputBuffer[] = "ATSRM,2,1\r";
		UART_bPutTxBuffer(sUARTOutputBuffer, sizeof(sUARTOutputBuffer)-1);
		//wait response
	}
	{
		// transmit "ATSRM,2,1\r" to minimize traffic from the module
		UI08 sUARTOutputBuffer[] = "ATSRM,2,1\r";
		UART_bPutTxBuffer(sUARTOutputBuffer, sizeof(sUARTOutputBuffer)-1);
		//wait response
	}

	{
		// command "ATSRM": sets the module response mode which configures how verbose the module will be
		// 2: response mode at to minimal
		// 1: Ignore Mode – SM Only. No AT commands are accepted and UART data is flushed
		// \r: carriage return escape sequence
		UI08 sUARTOutputBuffer[] = "ATSSP,0,0\r";
		UART_bPutTxBuffer(sUARTOutputBuffer, sizeof(sUARTOutputBuffer)-1);
		//wait response
	}

	{
	//
		UI08 sUARTOutputBuffer[] = "ATCFG?\r";
		UART_bPutTxBuffer(sUARTOutputBuffer, sizeof(sUARTOutputBuffer)-1);
		//wait response
	}
	return;
}

BOOL UART_bCloseDevice (void)
{
	/* close device and driver */
	UART_RTOS_Deinit(&handle);
	return TRUE;
}
