#ifndef UART_H_
#define UART_H_

typedef unsigned char  UI08;

BOOL UART_bOpenDevice (char pcDeviceName[]);
BOOL UART_bGetRxChar(UI08 *pu8RxChar);
BOOL UART_bPutTxBuffer(UI08* u8TxBuffer, UI08 u8Size);
void UART_BlueRadiosInit(void);
BOOL UART_bCloseDevice (void);

#endif
