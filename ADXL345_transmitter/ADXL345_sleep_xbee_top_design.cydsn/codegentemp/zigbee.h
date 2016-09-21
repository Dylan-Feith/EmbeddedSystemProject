/*******************************************************************************
* File Name: zigbee.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_zigbee_H)
#define CY_UART_zigbee_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define zigbee_RX_ENABLED                     (0u)
#define zigbee_TX_ENABLED                     (1u)
#define zigbee_HD_ENABLED                     (0u)
#define zigbee_RX_INTERRUPT_ENABLED           (0u)
#define zigbee_TX_INTERRUPT_ENABLED           (0u)
#define zigbee_INTERNAL_CLOCK_USED            (1u)
#define zigbee_RXHW_ADDRESS_ENABLED           (0u)
#define zigbee_OVER_SAMPLE_COUNT              (8u)
#define zigbee_PARITY_TYPE                    (0u)
#define zigbee_PARITY_TYPE_SW                 (0u)
#define zigbee_BREAK_DETECT                   (0u)
#define zigbee_BREAK_BITS_TX                  (13u)
#define zigbee_BREAK_BITS_RX                  (13u)
#define zigbee_TXCLKGEN_DP                    (1u)
#define zigbee_USE23POLLING                   (1u)
#define zigbee_FLOW_CONTROL                   (0u)
#define zigbee_CLK_FREQ                       (0u)
#define zigbee_TX_BUFFER_SIZE                 (4u)
#define zigbee_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define zigbee_CONTROL_REG_REMOVED            (0u)
#else
    #define zigbee_CONTROL_REG_REMOVED            (1u)
#endif /* End zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct zigbee_backupStruct_
{
    uint8 enableState;

    #if(zigbee_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End zigbee_CONTROL_REG_REMOVED */

} zigbee_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void zigbee_Start(void) ;
void zigbee_Stop(void) ;
uint8 zigbee_ReadControlRegister(void) ;
void zigbee_WriteControlRegister(uint8 control) ;

void zigbee_Init(void) ;
void zigbee_Enable(void) ;
void zigbee_SaveConfig(void) ;
void zigbee_RestoreConfig(void) ;
void zigbee_Sleep(void) ;
void zigbee_Wakeup(void) ;

/* Only if RX is enabled */
#if( (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) )

    #if (zigbee_RX_INTERRUPT_ENABLED)
        #define zigbee_EnableRxInt()  CyIntEnable (zigbee_RX_VECT_NUM)
        #define zigbee_DisableRxInt() CyIntDisable(zigbee_RX_VECT_NUM)
        CY_ISR_PROTO(zigbee_RXISR);
    #endif /* zigbee_RX_INTERRUPT_ENABLED */

    void zigbee_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void zigbee_SetRxAddress1(uint8 address) ;
    void zigbee_SetRxAddress2(uint8 address) ;

    void  zigbee_SetRxInterruptMode(uint8 intSrc) ;
    uint8 zigbee_ReadRxData(void) ;
    uint8 zigbee_ReadRxStatus(void) ;
    uint8 zigbee_GetChar(void) ;
    uint16 zigbee_GetByte(void) ;
    uint8 zigbee_GetRxBufferSize(void)
                                                            ;
    void zigbee_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define zigbee_GetRxInterruptSource   zigbee_ReadRxStatus

#endif /* End (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) */

/* Only if TX is enabled */
#if(zigbee_TX_ENABLED || zigbee_HD_ENABLED)

    #if(zigbee_TX_INTERRUPT_ENABLED)
        #define zigbee_EnableTxInt()  CyIntEnable (zigbee_TX_VECT_NUM)
        #define zigbee_DisableTxInt() CyIntDisable(zigbee_TX_VECT_NUM)
        #define zigbee_SetPendingTxInt() CyIntSetPending(zigbee_TX_VECT_NUM)
        #define zigbee_ClearPendingTxInt() CyIntClearPending(zigbee_TX_VECT_NUM)
        CY_ISR_PROTO(zigbee_TXISR);
    #endif /* zigbee_TX_INTERRUPT_ENABLED */

    void zigbee_SetTxInterruptMode(uint8 intSrc) ;
    void zigbee_WriteTxData(uint8 txDataByte) ;
    uint8 zigbee_ReadTxStatus(void) ;
    void zigbee_PutChar(uint8 txDataByte) ;
    void zigbee_PutString(const char8 string[]) ;
    void zigbee_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void zigbee_PutCRLF(uint8 txDataByte) ;
    void zigbee_ClearTxBuffer(void) ;
    void zigbee_SetTxAddressMode(uint8 addressMode) ;
    void zigbee_SendBreak(uint8 retMode) ;
    uint8 zigbee_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define zigbee_PutStringConst         zigbee_PutString
    #define zigbee_PutArrayConst          zigbee_PutArray
    #define zigbee_GetTxInterruptSource   zigbee_ReadTxStatus

#endif /* End zigbee_TX_ENABLED || zigbee_HD_ENABLED */

#if(zigbee_HD_ENABLED)
    void zigbee_LoadRxConfig(void) ;
    void zigbee_LoadTxConfig(void) ;
#endif /* End zigbee_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_zigbee) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    zigbee_CyBtldrCommStart(void) CYSMALL ;
    void    zigbee_CyBtldrCommStop(void) CYSMALL ;
    void    zigbee_CyBtldrCommReset(void) CYSMALL ;
    cystatus zigbee_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus zigbee_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_zigbee)
        #define CyBtldrCommStart    zigbee_CyBtldrCommStart
        #define CyBtldrCommStop     zigbee_CyBtldrCommStop
        #define CyBtldrCommReset    zigbee_CyBtldrCommReset
        #define CyBtldrCommWrite    zigbee_CyBtldrCommWrite
        #define CyBtldrCommRead     zigbee_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_zigbee) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define zigbee_BYTE2BYTE_TIME_OUT (25u)
    #define zigbee_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define zigbee_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define zigbee_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define zigbee_SET_SPACE      (0x00u)
#define zigbee_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (zigbee_TX_ENABLED) || (zigbee_HD_ENABLED) )
    #if(zigbee_TX_INTERRUPT_ENABLED)
        #define zigbee_TX_VECT_NUM            (uint8)zigbee_TXInternalInterrupt__INTC_NUMBER
        #define zigbee_TX_PRIOR_NUM           (uint8)zigbee_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* zigbee_TX_INTERRUPT_ENABLED */

    #define zigbee_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define zigbee_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define zigbee_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(zigbee_TX_ENABLED)
        #define zigbee_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (zigbee_HD_ENABLED) */
        #define zigbee_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (zigbee_TX_ENABLED) */

    #define zigbee_TX_STS_COMPLETE            (uint8)(0x01u << zigbee_TX_STS_COMPLETE_SHIFT)
    #define zigbee_TX_STS_FIFO_EMPTY          (uint8)(0x01u << zigbee_TX_STS_FIFO_EMPTY_SHIFT)
    #define zigbee_TX_STS_FIFO_FULL           (uint8)(0x01u << zigbee_TX_STS_FIFO_FULL_SHIFT)
    #define zigbee_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << zigbee_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (zigbee_TX_ENABLED) || (zigbee_HD_ENABLED)*/

#if( (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) )
    #if(zigbee_RX_INTERRUPT_ENABLED)
        #define zigbee_RX_VECT_NUM            (uint8)zigbee_RXInternalInterrupt__INTC_NUMBER
        #define zigbee_RX_PRIOR_NUM           (uint8)zigbee_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* zigbee_RX_INTERRUPT_ENABLED */
    #define zigbee_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define zigbee_RX_STS_BREAK_SHIFT             (0x01u)
    #define zigbee_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define zigbee_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define zigbee_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define zigbee_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define zigbee_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define zigbee_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define zigbee_RX_STS_MRKSPC           (uint8)(0x01u << zigbee_RX_STS_MRKSPC_SHIFT)
    #define zigbee_RX_STS_BREAK            (uint8)(0x01u << zigbee_RX_STS_BREAK_SHIFT)
    #define zigbee_RX_STS_PAR_ERROR        (uint8)(0x01u << zigbee_RX_STS_PAR_ERROR_SHIFT)
    #define zigbee_RX_STS_STOP_ERROR       (uint8)(0x01u << zigbee_RX_STS_STOP_ERROR_SHIFT)
    #define zigbee_RX_STS_OVERRUN          (uint8)(0x01u << zigbee_RX_STS_OVERRUN_SHIFT)
    #define zigbee_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << zigbee_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define zigbee_RX_STS_ADDR_MATCH       (uint8)(0x01u << zigbee_RX_STS_ADDR_MATCH_SHIFT)
    #define zigbee_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << zigbee_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define zigbee_RX_HW_MASK                     (0x7Fu)
#endif /* End (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) */

/* Control Register definitions */
#define zigbee_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define zigbee_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define zigbee_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define zigbee_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define zigbee_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define zigbee_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define zigbee_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define zigbee_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define zigbee_CTRL_HD_SEND               (uint8)(0x01u << zigbee_CTRL_HD_SEND_SHIFT)
#define zigbee_CTRL_HD_SEND_BREAK         (uint8)(0x01u << zigbee_CTRL_HD_SEND_BREAK_SHIFT)
#define zigbee_CTRL_MARK                  (uint8)(0x01u << zigbee_CTRL_MARK_SHIFT)
#define zigbee_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << zigbee_CTRL_PARITY_TYPE0_SHIFT)
#define zigbee_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << zigbee_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define zigbee_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define zigbee_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define zigbee_SEND_BREAK                         (0x00u)
#define zigbee_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define zigbee_REINIT                             (0x02u)
#define zigbee_SEND_WAIT_REINIT                   (0x03u)

#define zigbee_OVER_SAMPLE_8                      (8u)
#define zigbee_OVER_SAMPLE_16                     (16u)

#define zigbee_BIT_CENTER                         (zigbee_OVER_SAMPLE_COUNT - 2u)

#define zigbee_FIFO_LENGTH                        (4u)
#define zigbee_NUMBER_OF_START_BIT                (1u)
#define zigbee_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define zigbee_TXBITCTR_BREAKBITS8X   ((zigbee_BREAK_BITS_TX * zigbee_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define zigbee_TXBITCTR_BREAKBITS ((zigbee_BREAK_BITS_TX * zigbee_OVER_SAMPLE_COUNT) - 1u)

#define zigbee_HALF_BIT_COUNT   \
                            (((zigbee_OVER_SAMPLE_COUNT / 2u) + (zigbee_USE23POLLING * 1u)) - 2u)
#if (zigbee_OVER_SAMPLE_COUNT == zigbee_OVER_SAMPLE_8)
    #define zigbee_HD_TXBITCTR_INIT   (((zigbee_BREAK_BITS_TX + \
                            zigbee_NUMBER_OF_START_BIT) * zigbee_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define zigbee_RXBITCTR_INIT  ((((zigbee_BREAK_BITS_RX + zigbee_NUMBER_OF_START_BIT) \
                            * zigbee_OVER_SAMPLE_COUNT) + zigbee_HALF_BIT_COUNT) - 1u)

#else /* zigbee_OVER_SAMPLE_COUNT == zigbee_OVER_SAMPLE_16 */
    #define zigbee_HD_TXBITCTR_INIT   ((8u * zigbee_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define zigbee_RXBITCTR_INIT      (((7u * zigbee_OVER_SAMPLE_COUNT) - 1u) + \
                                                      zigbee_HALF_BIT_COUNT)
#endif /* End zigbee_OVER_SAMPLE_COUNT */

#define zigbee_HD_RXBITCTR_INIT                   zigbee_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 zigbee_initVar;
#if (zigbee_TX_INTERRUPT_ENABLED && zigbee_TX_ENABLED)
    extern volatile uint8 zigbee_txBuffer[zigbee_TX_BUFFER_SIZE];
    extern volatile uint8 zigbee_txBufferRead;
    extern uint8 zigbee_txBufferWrite;
#endif /* (zigbee_TX_INTERRUPT_ENABLED && zigbee_TX_ENABLED) */
#if (zigbee_RX_INTERRUPT_ENABLED && (zigbee_RX_ENABLED || zigbee_HD_ENABLED))
    extern uint8 zigbee_errorStatus;
    extern volatile uint8 zigbee_rxBuffer[zigbee_RX_BUFFER_SIZE];
    extern volatile uint8 zigbee_rxBufferRead;
    extern volatile uint8 zigbee_rxBufferWrite;
    extern volatile uint8 zigbee_rxBufferLoopDetect;
    extern volatile uint8 zigbee_rxBufferOverflow;
    #if (zigbee_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 zigbee_rxAddressMode;
        extern volatile uint8 zigbee_rxAddressDetected;
    #endif /* (zigbee_RXHW_ADDRESS_ENABLED) */
#endif /* (zigbee_RX_INTERRUPT_ENABLED && (zigbee_RX_ENABLED || zigbee_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define zigbee__B_UART__AM_SW_BYTE_BYTE 1
#define zigbee__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define zigbee__B_UART__AM_HW_BYTE_BY_BYTE 3
#define zigbee__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define zigbee__B_UART__AM_NONE 0

#define zigbee__B_UART__NONE_REVB 0
#define zigbee__B_UART__EVEN_REVB 1
#define zigbee__B_UART__ODD_REVB 2
#define zigbee__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define zigbee_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define zigbee_NUMBER_OF_STOP_BITS    (1u)

#if (zigbee_RXHW_ADDRESS_ENABLED)
    #define zigbee_RX_ADDRESS_MODE    (0u)
    #define zigbee_RX_HW_ADDRESS1     (0u)
    #define zigbee_RX_HW_ADDRESS2     (0u)
#endif /* (zigbee_RXHW_ADDRESS_ENABLED) */

#define zigbee_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << zigbee_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << zigbee_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << zigbee_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << zigbee_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << zigbee_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << zigbee_RX_STS_BREAK_SHIFT) \
                                        | (0 << zigbee_RX_STS_OVERRUN_SHIFT))

#define zigbee_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << zigbee_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << zigbee_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << zigbee_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << zigbee_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define zigbee_CONTROL_REG \
                            (* (reg8 *) zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define zigbee_CONTROL_PTR \
                            (  (reg8 *) zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(zigbee_TX_ENABLED)
    #define zigbee_TXDATA_REG          (* (reg8 *) zigbee_BUART_sTX_TxShifter_u0__F0_REG)
    #define zigbee_TXDATA_PTR          (  (reg8 *) zigbee_BUART_sTX_TxShifter_u0__F0_REG)
    #define zigbee_TXDATA_AUX_CTL_REG  (* (reg8 *) zigbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define zigbee_TXDATA_AUX_CTL_PTR  (  (reg8 *) zigbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define zigbee_TXSTATUS_REG        (* (reg8 *) zigbee_BUART_sTX_TxSts__STATUS_REG)
    #define zigbee_TXSTATUS_PTR        (  (reg8 *) zigbee_BUART_sTX_TxSts__STATUS_REG)
    #define zigbee_TXSTATUS_MASK_REG   (* (reg8 *) zigbee_BUART_sTX_TxSts__MASK_REG)
    #define zigbee_TXSTATUS_MASK_PTR   (  (reg8 *) zigbee_BUART_sTX_TxSts__MASK_REG)
    #define zigbee_TXSTATUS_ACTL_REG   (* (reg8 *) zigbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define zigbee_TXSTATUS_ACTL_PTR   (  (reg8 *) zigbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(zigbee_TXCLKGEN_DP)
        #define zigbee_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define zigbee_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define zigbee_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define zigbee_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define zigbee_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define zigbee_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define zigbee_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define zigbee_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define zigbee_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define zigbee_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) zigbee_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* zigbee_TXCLKGEN_DP */

#endif /* End zigbee_TX_ENABLED */

#if(zigbee_HD_ENABLED)

    #define zigbee_TXDATA_REG             (* (reg8 *) zigbee_BUART_sRX_RxShifter_u0__F1_REG )
    #define zigbee_TXDATA_PTR             (  (reg8 *) zigbee_BUART_sRX_RxShifter_u0__F1_REG )
    #define zigbee_TXDATA_AUX_CTL_REG     (* (reg8 *) zigbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define zigbee_TXDATA_AUX_CTL_PTR     (  (reg8 *) zigbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define zigbee_TXSTATUS_REG           (* (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_REG )
    #define zigbee_TXSTATUS_PTR           (  (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_REG )
    #define zigbee_TXSTATUS_MASK_REG      (* (reg8 *) zigbee_BUART_sRX_RxSts__MASK_REG )
    #define zigbee_TXSTATUS_MASK_PTR      (  (reg8 *) zigbee_BUART_sRX_RxSts__MASK_REG )
    #define zigbee_TXSTATUS_ACTL_REG      (* (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define zigbee_TXSTATUS_ACTL_PTR      (  (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End zigbee_HD_ENABLED */

#if( (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) )
    #define zigbee_RXDATA_REG             (* (reg8 *) zigbee_BUART_sRX_RxShifter_u0__F0_REG )
    #define zigbee_RXDATA_PTR             (  (reg8 *) zigbee_BUART_sRX_RxShifter_u0__F0_REG )
    #define zigbee_RXADDRESS1_REG         (* (reg8 *) zigbee_BUART_sRX_RxShifter_u0__D0_REG )
    #define zigbee_RXADDRESS1_PTR         (  (reg8 *) zigbee_BUART_sRX_RxShifter_u0__D0_REG )
    #define zigbee_RXADDRESS2_REG         (* (reg8 *) zigbee_BUART_sRX_RxShifter_u0__D1_REG )
    #define zigbee_RXADDRESS2_PTR         (  (reg8 *) zigbee_BUART_sRX_RxShifter_u0__D1_REG )
    #define zigbee_RXDATA_AUX_CTL_REG     (* (reg8 *) zigbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define zigbee_RXBITCTR_PERIOD_REG    (* (reg8 *) zigbee_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define zigbee_RXBITCTR_PERIOD_PTR    (  (reg8 *) zigbee_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define zigbee_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) zigbee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define zigbee_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) zigbee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define zigbee_RXBITCTR_COUNTER_REG   (* (reg8 *) zigbee_BUART_sRX_RxBitCounter__COUNT_REG )
    #define zigbee_RXBITCTR_COUNTER_PTR   (  (reg8 *) zigbee_BUART_sRX_RxBitCounter__COUNT_REG )

    #define zigbee_RXSTATUS_REG           (* (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_REG )
    #define zigbee_RXSTATUS_PTR           (  (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_REG )
    #define zigbee_RXSTATUS_MASK_REG      (* (reg8 *) zigbee_BUART_sRX_RxSts__MASK_REG )
    #define zigbee_RXSTATUS_MASK_PTR      (  (reg8 *) zigbee_BUART_sRX_RxSts__MASK_REG )
    #define zigbee_RXSTATUS_ACTL_REG      (* (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define zigbee_RXSTATUS_ACTL_PTR      (  (reg8 *) zigbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) */

#if(zigbee_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define zigbee_INTCLOCK_CLKEN_REG     (* (reg8 *) zigbee_IntClock__PM_ACT_CFG)
    #define zigbee_INTCLOCK_CLKEN_PTR     (  (reg8 *) zigbee_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define zigbee_INTCLOCK_CLKEN_MASK    zigbee_IntClock__PM_ACT_MSK
#endif /* End zigbee_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(zigbee_TX_ENABLED)
    #define zigbee_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End zigbee_TX_ENABLED */

#if(zigbee_HD_ENABLED)
    #define zigbee_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End zigbee_HD_ENABLED */

#if( (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) )
    #define zigbee_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define zigbee_WAIT_1_MS      zigbee_BL_CHK_DELAY_MS   

#define zigbee_TXBUFFERSIZE   zigbee_TX_BUFFER_SIZE
#define zigbee_RXBUFFERSIZE   zigbee_RX_BUFFER_SIZE

#if (zigbee_RXHW_ADDRESS_ENABLED)
    #define zigbee_RXADDRESSMODE  zigbee_RX_ADDRESS_MODE
    #define zigbee_RXHWADDRESS1   zigbee_RX_HW_ADDRESS1
    #define zigbee_RXHWADDRESS2   zigbee_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define zigbee_RXAddressMode  zigbee_RXADDRESSMODE
#endif /* (zigbee_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define zigbee_initvar                    zigbee_initVar

#define zigbee_RX_Enabled                 zigbee_RX_ENABLED
#define zigbee_TX_Enabled                 zigbee_TX_ENABLED
#define zigbee_HD_Enabled                 zigbee_HD_ENABLED
#define zigbee_RX_IntInterruptEnabled     zigbee_RX_INTERRUPT_ENABLED
#define zigbee_TX_IntInterruptEnabled     zigbee_TX_INTERRUPT_ENABLED
#define zigbee_InternalClockUsed          zigbee_INTERNAL_CLOCK_USED
#define zigbee_RXHW_Address_Enabled       zigbee_RXHW_ADDRESS_ENABLED
#define zigbee_OverSampleCount            zigbee_OVER_SAMPLE_COUNT
#define zigbee_ParityType                 zigbee_PARITY_TYPE

#if( zigbee_TX_ENABLED && (zigbee_TXBUFFERSIZE > zigbee_FIFO_LENGTH))
    #define zigbee_TXBUFFER               zigbee_txBuffer
    #define zigbee_TXBUFFERREAD           zigbee_txBufferRead
    #define zigbee_TXBUFFERWRITE          zigbee_txBufferWrite
#endif /* End zigbee_TX_ENABLED */
#if( ( zigbee_RX_ENABLED || zigbee_HD_ENABLED ) && \
     (zigbee_RXBUFFERSIZE > zigbee_FIFO_LENGTH) )
    #define zigbee_RXBUFFER               zigbee_rxBuffer
    #define zigbee_RXBUFFERREAD           zigbee_rxBufferRead
    #define zigbee_RXBUFFERWRITE          zigbee_rxBufferWrite
    #define zigbee_RXBUFFERLOOPDETECT     zigbee_rxBufferLoopDetect
    #define zigbee_RXBUFFER_OVERFLOW      zigbee_rxBufferOverflow
#endif /* End zigbee_RX_ENABLED */

#ifdef zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define zigbee_CONTROL                zigbee_CONTROL_REG
#endif /* End zigbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(zigbee_TX_ENABLED)
    #define zigbee_TXDATA                 zigbee_TXDATA_REG
    #define zigbee_TXSTATUS               zigbee_TXSTATUS_REG
    #define zigbee_TXSTATUS_MASK          zigbee_TXSTATUS_MASK_REG
    #define zigbee_TXSTATUS_ACTL          zigbee_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(zigbee_TXCLKGEN_DP)
        #define zigbee_TXBITCLKGEN_CTR        zigbee_TXBITCLKGEN_CTR_REG
        #define zigbee_TXBITCLKTX_COMPLETE    zigbee_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define zigbee_TXBITCTR_PERIOD        zigbee_TXBITCTR_PERIOD_REG
        #define zigbee_TXBITCTR_CONTROL       zigbee_TXBITCTR_CONTROL_REG
        #define zigbee_TXBITCTR_COUNTER       zigbee_TXBITCTR_COUNTER_REG
    #endif /* zigbee_TXCLKGEN_DP */
#endif /* End zigbee_TX_ENABLED */

#if(zigbee_HD_ENABLED)
    #define zigbee_TXDATA                 zigbee_TXDATA_REG
    #define zigbee_TXSTATUS               zigbee_TXSTATUS_REG
    #define zigbee_TXSTATUS_MASK          zigbee_TXSTATUS_MASK_REG
    #define zigbee_TXSTATUS_ACTL          zigbee_TXSTATUS_ACTL_REG
#endif /* End zigbee_HD_ENABLED */

#if( (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) )
    #define zigbee_RXDATA                 zigbee_RXDATA_REG
    #define zigbee_RXADDRESS1             zigbee_RXADDRESS1_REG
    #define zigbee_RXADDRESS2             zigbee_RXADDRESS2_REG
    #define zigbee_RXBITCTR_PERIOD        zigbee_RXBITCTR_PERIOD_REG
    #define zigbee_RXBITCTR_CONTROL       zigbee_RXBITCTR_CONTROL_REG
    #define zigbee_RXBITCTR_COUNTER       zigbee_RXBITCTR_COUNTER_REG
    #define zigbee_RXSTATUS               zigbee_RXSTATUS_REG
    #define zigbee_RXSTATUS_MASK          zigbee_RXSTATUS_MASK_REG
    #define zigbee_RXSTATUS_ACTL          zigbee_RXSTATUS_ACTL_REG
#endif /* End  (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) */

#if(zigbee_INTERNAL_CLOCK_USED)
    #define zigbee_INTCLOCK_CLKEN         zigbee_INTCLOCK_CLKEN_REG
#endif /* End zigbee_INTERNAL_CLOCK_USED */

#define zigbee_WAIT_FOR_COMLETE_REINIT    zigbee_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_zigbee_H */


/* [] END OF FILE */
