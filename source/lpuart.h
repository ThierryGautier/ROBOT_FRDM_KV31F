#ifndef LPUART_H_
#define LPUART_H_

typedef unsigned char  UI08;

BOOL LPUART_bOpenDevice (char pcDeviceName[]);
BOOL LPUART_bGetRxChar(UI08 *pu8RxChar);
BOOL LPUART_bPutTxBuffer(UI08* u8TxBuffer, UI08 u8Size);
void LPUART_BlueRadiosInit(void);
BOOL LPUART_bCloseDevice (void);

#endif
