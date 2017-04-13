#ifndef UART_H_
#define UART_H_

typedef unsigned char  UI08;

BOOL UART_bOpenDevice (char pcDeviceName[]);
BOOL UART_bGetRxChar(UI08 *pu8RxChar);
BOOL UART_bPutTxChar(UI08 u8TxChar);
BOOL UART_bCloseDevice (void);

#endif
