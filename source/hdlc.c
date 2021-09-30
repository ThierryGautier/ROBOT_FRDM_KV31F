#include "stdtype.h"
#include "hdlc.h"

/** list of specific HDLC characters */
#define U8_DLE         (UI08)0x10U /**<@brief escape character */
#define U8_STX         (UI08)0x02U /**<@brief start frame character */
#define U8_ETX         (UI08)0x03U /**<@brief end frame character */

/** list of state of the finite state machine in charge to decode HDLC */
#define U8_STATE_WAIT_FIRST_DLE  (UI08)0U
#define U8_STATE_WAIT_STX        (UI08)1U
#define U8_STATE_WAIT_FRAME      (UI08)2U
#define U8_STATE_ALGO_DLE        (UI08)3U
#define U8_STATE_WAIT_CHECKSUM   (UI08)4U
#define U8_NUMBER_OF_STATE       (UI08)5U

/** @brief context of HDLC */
typedef struct
{
    UI08 u8RxState;
    UI08 u8Size;
    UI08 au8Data[HDLC_U8_MAX_NB_BYTE_IN_FRAME];
    BOOL bReceivedFrame;
    UI08 u8ChecksumOfFrame;
    UI16 gu16DLLRxFrameErrorCounter;
    UI16 gu16DLLRxFrameOKCounter;

    /* @list of function pointers used to control hardware device */
    BOOL (*bOpenDevice) (char pcDeviceName[]);
    BOOL (*bGetRxChar) (UI08 *pu8RxChar);
    BOOL (*bPutTxBuffer) (UI08* u8TxBuffer, UI08 u8Size);
    BOOL (*bClosDevice) (void);
}HDLC_stContext;

static HDLC_stContext HDLC_gstContext;


static void UpdateDLLRxFrameErrorCounter(void)
{
    if(HDLC_gstContext.gu16DLLRxFrameErrorCounter < 0xFFFF)
    {
    	HDLC_gstContext.gu16DLLRxFrameErrorCounter++;
    }
}

static void UpdateDLLRxFrameOKCounter(void)
{
    if(HDLC_gstContext.gu16DLLRxFrameOKCounter < 0xFFFF)
    {
    	HDLC_gstContext.gu16DLLRxFrameOKCounter++;
    }
}

static void HDLC_StateWaitFirstDLE(UI08 pu8Char)
{
    if (pu8Char == U8_DLE)
    {
        HDLC_gstContext.u8RxState = U8_STATE_WAIT_STX;
    }
    else
    {
        UpdateDLLRxFrameErrorCounter();
    }
}

static void HDLC_StateWaitSTX(UI08 pu8Char)
{
    if (pu8Char == U8_STX)
    {
        HDLC_gstContext.u8Size = 0;
        HDLC_gstContext.u8ChecksumOfFrame = 0;
        HDLC_gstContext.u8RxState = U8_STATE_WAIT_FRAME;
    }
    else
    {
		HDLC_gstContext.u8RxState = U8_STATE_WAIT_FIRST_DLE;
		UpdateDLLRxFrameErrorCounter();
    }
}

static void HDLC_StateWaitFrame(UI08 pu8Char)
{
    if (pu8Char == U8_DLE)
    {
        HDLC_gstContext.u8RxState = U8_STATE_ALGO_DLE;
    }
    else
    {
        if ( HDLC_gstContext.u8Size < HDLC_U8_MAX_NB_BYTE_IN_FRAME )
        {
            HDLC_gstContext.au8Data[HDLC_gstContext.u8Size] = pu8Char;
            HDLC_gstContext.u8ChecksumOfFrame ^= pu8Char;
            HDLC_gstContext.u8Size = HDLC_gstContext.u8Size + 1;
        }
        else
        {
            UpdateDLLRxFrameErrorCounter();
            HDLC_gstContext.u8RxState = U8_STATE_WAIT_FIRST_DLE;
        }
    }
}

static void HDLC_StateAlgoDLE(UI08 pu8Char)
{
    switch(pu8Char)
    {
        case U8_DLE:
            if ( HDLC_gstContext.u8Size < HDLC_U8_MAX_NB_BYTE_IN_FRAME )
            {
                HDLC_gstContext.au8Data[HDLC_gstContext.u8Size] = pu8Char;
                HDLC_gstContext.u8ChecksumOfFrame ^= pu8Char;
                HDLC_gstContext.u8Size =  HDLC_gstContext.u8Size + 1;
                HDLC_gstContext.u8RxState = U8_STATE_WAIT_FRAME;
            }
            else
            {
                UpdateDLLRxFrameErrorCounter();
                HDLC_gstContext.u8RxState = U8_STATE_WAIT_FIRST_DLE;
            }
            break;

        case U8_ETX:
            HDLC_gstContext.u8RxState = U8_STATE_WAIT_CHECKSUM;
            break;

        case U8_STX:
            HDLC_gstContext.u8Size = 0;
            HDLC_gstContext.u8ChecksumOfFrame = 0;
            HDLC_gstContext.u8RxState = U8_STATE_WAIT_FRAME;
            break;
        default:
            UpdateDLLRxFrameErrorCounter();
            HDLC_gstContext.u8RxState = U8_STATE_WAIT_FIRST_DLE;
            break;
    }
}

static void HDLC_StateWaitChecksum(UI08 pu8Char)
{
    if( HDLC_gstContext.u8Size & 0x01 )
    {
        HDLC_gstContext.u8ChecksumOfFrame ^= 0x4A;
    }
    else
    {
    }

    if (pu8Char == HDLC_gstContext.u8ChecksumOfFrame )
    {
        HDLC_gstContext.bReceivedFrame = TRUE;
        UpdateDLLRxFrameOKCounter();
    }
    else
    {
        UpdateDLLRxFrameErrorCounter();
    }
    HDLC_gstContext.u8RxState = U8_STATE_WAIT_FIRST_DLE;
}

static void HDLC_ControlRxCharacter(void)
{
   UI08 u8Char = '\0';

   while((HDLC_gstContext.bReceivedFrame==FALSE) &&
          (HDLC_gstContext.bGetRxChar(&u8Char)==TRUE))
    {
        switch(HDLC_gstContext.u8RxState)
        {
            case U8_STATE_WAIT_FIRST_DLE:
                HDLC_StateWaitFirstDLE(u8Char);
                break;
            case U8_STATE_WAIT_STX:
                HDLC_StateWaitSTX(u8Char);
                break;

            case U8_STATE_WAIT_FRAME:
                HDLC_StateWaitFrame(u8Char);
                break;

            case U8_STATE_ALGO_DLE:
                HDLC_StateAlgoDLE(u8Char);
                break;

            case U8_STATE_WAIT_CHECKSUM:
                HDLC_StateWaitChecksum(u8Char);
                break;

            default:
                break;
        }
    }
}

BOOL HDLC_bInitialize(char pcDeviceName[],
		BOOL (*bOpenDevice)(char pcDeviceName[]),
		BOOL (*bGetRxChar) (UI08 *pu8RxChar),
		BOOL (*bPutTxBuffer) (UI08* u8TxBuffer, UI08 u8Size),
		BOOL (*bCloseDevice)(void)
		)
{
	if(bOpenDevice!=0)
		HDLC_gstContext.bOpenDevice = bOpenDevice;

	if(bGetRxChar!=0)
		HDLC_gstContext.bGetRxChar = bGetRxChar;

	if(bPutTxBuffer!=0)
		HDLC_gstContext.bPutTxBuffer = bPutTxBuffer;

	if(bCloseDevice!=0)
		HDLC_gstContext.bClosDevice = bCloseDevice;

	return(HDLC_gstContext.bOpenDevice(pcDeviceName));
}

BOOL HDLC_bGetFrame(UI08 *pu8RxFrame, UI08 *pu8RxSize)
{
    UI08 i;
    UI08 bReturnValue = FALSE;

    HDLC_ControlRxCharacter();

    if((HDLC_gstContext.bReceivedFrame == TRUE) &&
       (HDLC_gstContext.u8Size <= HDLC_U8_MAX_NB_BYTE_IN_FRAME)
      )
    {
        HDLC_gstContext.bReceivedFrame = FALSE;

        for(i=0;i<HDLC_gstContext.u8Size;i++)
        {
            *(pu8RxFrame+i) = HDLC_gstContext.au8Data[i];
        }

        *pu8RxSize = HDLC_gstContext.u8Size;

        bReturnValue = TRUE;
    }
    else
    {
        *pu8RxSize = 0;
        bReturnValue = FALSE;
    }
    return(bReturnValue);
}

UI08 au8HDLCFrame[128];

BOOL HDLC_bPutFrame(UI08 *pu8TxFrame, UI08 *pu8TxSize)
{
    UI08 u8Checksum = 0;
    UI08 u8Size = *pu8TxSize;
    UI08 u8index = 0;
    if(*pu8TxSize>HDLC_U8_MAX_NB_BYTE_IN_FRAME) return(FALSE);

    au8HDLCFrame[u8index++]=(U8_DLE);
    au8HDLCFrame[u8index++]=(U8_STX);
    while( u8Size > 0 )
    {
        if ( *pu8TxFrame == U8_DLE )
        {
        	au8HDLCFrame[u8index++]=(U8_DLE);
        }
        au8HDLCFrame[u8index++]=(*pu8TxFrame);

        u8Checksum ^= *pu8TxFrame;
        pu8TxFrame = pu8TxFrame + 1U;

        u8Size = u8Size - 1U;
    }
    if( (*pu8TxSize & 0x01) == 0x01)
    {
        u8Checksum ^= 0x4A;
    }
    au8HDLCFrame[u8index++]=(U8_DLE);
    au8HDLCFrame[u8index++]=(U8_ETX);
    au8HDLCFrame[u8index++]=(u8Checksum);
    HDLC_gstContext.bPutTxBuffer(au8HDLCFrame,u8index);

    return( TRUE );
}

