
#ifndef HDLC_H_
#define HDLC_H_

#define HDLC_U8_MAX_NB_BYTE_IN_FRAME        (UI08)32U

BOOL HDLC_bInitialize(char pcDeviceName[],
		BOOL (*bOpenDevice)(char pcDeviceName[]),
		BOOL (*bGetRxChar) (UI08 *pu8RxChar),
		BOOL (*bPutTxChar) (UI08 u8TxChar),
		BOOL (*bCloseDevice)(void)
		);
BOOL HDLC_bGetFrame(UI08 *pu8RxFrame, UI08 *pu8RxSize);
BOOL HDLC_bPutFrame(UI08 *pu8TxFrame, UI08 *pu8TxSize);

#endif /* HDLC_H_ */
