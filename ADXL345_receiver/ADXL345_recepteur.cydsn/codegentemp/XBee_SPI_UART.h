/*******************************************************************************
* File Name: XBee_SPI_UART.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_XBee_H)
#define CY_SCB_SPI_UART_XBee_H

#include "XBee.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define XBee_SPI_MODE                   (0u)
#define XBee_SPI_SUB_MODE               (0u)
#define XBee_SPI_CLOCK_MODE             (0u)
#define XBee_SPI_OVS_FACTOR             (16u)
#define XBee_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define XBee_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define XBee_SPI_RX_DATA_BITS_NUM       (8u)
#define XBee_SPI_TX_DATA_BITS_NUM       (8u)
#define XBee_SPI_WAKE_ENABLE            (0u)
#define XBee_SPI_BITS_ORDER             (1u)
#define XBee_SPI_TRANSFER_SEPARATION    (1u)
#define XBee_SPI_NUMBER_OF_SS_LINES     (1u)
#define XBee_SPI_RX_BUFFER_SIZE         (8u)
#define XBee_SPI_TX_BUFFER_SIZE         (8u)

#define XBee_SPI_INTERRUPT_MODE         (0u)

#define XBee_SPI_INTR_RX_MASK           (0u)
#define XBee_SPI_INTR_TX_MASK           (0u)

#define XBee_SPI_RX_TRIGGER_LEVEL       (7u)
#define XBee_SPI_TX_TRIGGER_LEVEL       (0u)

#define XBee_SPI_BYTE_MODE_ENABLE       (0u)
#define XBee_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define XBee_SPI_SS0_POLARITY           (0u)
#define XBee_SPI_SS1_POLARITY           (0u)
#define XBee_SPI_SS2_POLARITY           (0u)
#define XBee_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define XBee_UART_SUB_MODE              (0u)
#define XBee_UART_DIRECTION             (3u)
#define XBee_UART_DATA_BITS_NUM         (8u)
#define XBee_UART_PARITY_TYPE           (2u)
#define XBee_UART_STOP_BITS_NUM         (4u)
#define XBee_UART_OVS_FACTOR            (16u)
#define XBee_UART_IRDA_LOW_POWER        (0u)
#define XBee_UART_MEDIAN_FILTER_ENABLE  (1u)
#define XBee_UART_RETRY_ON_NACK         (0u)
#define XBee_UART_IRDA_POLARITY         (0u)
#define XBee_UART_DROP_ON_FRAME_ERR     (0u)
#define XBee_UART_DROP_ON_PARITY_ERR    (0u)
#define XBee_UART_WAKE_ENABLE           (0u)
#define XBee_UART_RX_BUFFER_SIZE        (8u)
#define XBee_UART_TX_BUFFER_SIZE        (8u)
#define XBee_UART_MP_MODE_ENABLE        (0u)
#define XBee_UART_MP_ACCEPT_ADDRESS     (0u)
#define XBee_UART_MP_RX_ADDRESS         (2u)
#define XBee_UART_MP_RX_ADDRESS_MASK    (255u)

#define XBee_UART_INTERRUPT_MODE        (0u)

#define XBee_UART_INTR_RX_MASK          (0u)
#define XBee_UART_INTR_TX_MASK          (0u)

#define XBee_UART_RX_TRIGGER_LEVEL      (7u)
#define XBee_UART_TX_TRIGGER_LEVEL      (0u)

#define XBee_UART_BYTE_MODE_ENABLE      (0u)
#define XBee_UART_CTS_ENABLE            (0u)
#define XBee_UART_CTS_POLARITY          (0u)
#define XBee_UART_RTS_ENABLE            (0u)
#define XBee_UART_RTS_POLARITY          (0u)
#define XBee_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define XBee_SPI_SLAVE  (0u)
#define XBee_SPI_MASTER (1u)

/* UART direction enum */
#define XBee_UART_RX    (1u)
#define XBee_UART_TX    (2u)
#define XBee_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define XBee_SPI_SLAVE_CONST        (1u)
    #define XBee_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define XBee_RX_DIRECTION           (1u)
    #define XBee_TX_DIRECTION           (1u)
    #define XBee_UART_RX_DIRECTION      (1u)
    #define XBee_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define XBee_INTERNAL_RX_SW_BUFFER   (0u)
    #define XBee_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define XBee_INTERNAL_RX_BUFFER_SIZE    (XBee_rxBufferSize + 1u)
    #define XBee_RX_BUFFER_SIZE             (XBee_rxBufferSize)
    #define XBee_TX_BUFFER_SIZE             (XBee_txBufferSize)

    /* Return true if buffer is provided */
    #define XBee_CHECK_RX_SW_BUFFER (NULL != XBee_rxBuffer)
    #define XBee_CHECK_TX_SW_BUFFER (NULL != XBee_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define XBee_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define XBee_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define XBee_SPI_WAKE_ENABLE_CONST  (1u)
    #define XBee_CHECK_SPI_WAKE_ENABLE  (0u != XBee_scbEnableWake)
    #define XBee_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
        #define XBee_SPI_UART_FIFO_SIZE             (XBee_FIFO_SIZE)
        #define XBee_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define XBee_SPI_UART_FIFO_SIZE (XBee_GET_FIFO_SIZE(XBee_CTRL_REG & \
                                                                                    XBee_CTRL_BYTE_MODE))

        #define XBee_CHECK_UART_RTS_CONTROL_FLOW \
                    ((XBee_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != XBee_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(XBee_UART_FLOW_CTRL_REG)))
    #endif /* (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (XBee_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define XBee_SPI_RX_DIRECTION (1u)
        #define XBee_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
            #define XBee_SPI_UART_FIFO_SIZE    (XBee_FIFO_SIZE)
        #else
            #define XBee_SPI_UART_FIFO_SIZE \
                                           XBee_GET_FIFO_SIZE(XBee_SPI_BYTE_MODE_ENABLE)

        #endif /* (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define XBee_INTERNAL_SPI_RX_SW_BUFFER  (XBee_SPI_RX_BUFFER_SIZE > \
                                                                XBee_SPI_UART_FIFO_SIZE)
        #define XBee_INTERNAL_SPI_TX_SW_BUFFER  (XBee_SPI_TX_BUFFER_SIZE > \
                                                                XBee_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define XBee_INTERNAL_RX_SW_BUFFER  (XBee_INTERNAL_SPI_RX_SW_BUFFER)
        #define XBee_INTERNAL_TX_SW_BUFFER  (XBee_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define XBee_INTERNAL_RX_BUFFER_SIZE    (XBee_SPI_RX_BUFFER_SIZE + 1u)
        #define XBee_RX_BUFFER_SIZE             (XBee_SPI_RX_BUFFER_SIZE)
        #define XBee_TX_BUFFER_SIZE             (XBee_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define XBee_SPI_WAKE_ENABLE_CONST  (0u != XBee_SPI_WAKE_ENABLE)
        #define XBee_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define XBee_UART_RX_DIRECTION (0u != (XBee_UART_DIRECTION & XBee_UART_RX))
        #define XBee_UART_TX_DIRECTION (0u != (XBee_UART_DIRECTION & XBee_UART_TX))

        /* Get FIFO size */
        #if (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
            #define XBee_SPI_UART_FIFO_SIZE    (XBee_FIFO_SIZE)
        #else
            #define XBee_SPI_UART_FIFO_SIZE \
                                           XBee_GET_FIFO_SIZE(XBee_UART_BYTE_MODE_ENABLE)
        #endif /* (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define XBee_INTERNAL_UART_RX_SW_BUFFER  (XBee_UART_RX_BUFFER_SIZE > \
                                                                XBee_SPI_UART_FIFO_SIZE)
        #define XBee_INTERNAL_UART_TX_SW_BUFFER  (XBee_UART_TX_BUFFER_SIZE > \
                                                                    XBee_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define XBee_INTERNAL_RX_SW_BUFFER  (XBee_INTERNAL_UART_RX_SW_BUFFER)
        #define XBee_INTERNAL_TX_SW_BUFFER  (XBee_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define XBee_INTERNAL_RX_BUFFER_SIZE    (XBee_UART_RX_BUFFER_SIZE + 1u)
        #define XBee_RX_BUFFER_SIZE             (XBee_UART_RX_BUFFER_SIZE)
        #define XBee_TX_BUFFER_SIZE             (XBee_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define XBee_SPI_WAKE_ENABLE_CONST  (0u)
        #define XBee_UART_WAKE_ENABLE_CONST (0u != XBee_UART_WAKE_ENABLE)

    #endif /* (XBee_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define XBee_SPI_SLAVE_CONST    (XBee_SPI_MODE == XBee_SPI_SLAVE)
    #define XBee_SPI_MASTER_CONST   (XBee_SPI_MODE == XBee_SPI_MASTER)

    /* Direction */
    #define XBee_RX_DIRECTION ((XBee_SCB_MODE_SPI_CONST_CFG) ? \
                                            (XBee_SPI_RX_DIRECTION) : (XBee_UART_RX_DIRECTION))

    #define XBee_TX_DIRECTION ((XBee_SCB_MODE_SPI_CONST_CFG) ? \
                                            (XBee_SPI_TX_DIRECTION) : (XBee_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define XBee_CHECK_RX_SW_BUFFER (XBee_INTERNAL_RX_SW_BUFFER)
    #define XBee_CHECK_TX_SW_BUFFER (XBee_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define XBee_INTERNAL_RX_SW_BUFFER_CONST    (XBee_INTERNAL_RX_SW_BUFFER)
    #define XBee_INTERNAL_TX_SW_BUFFER_CONST    (XBee_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define XBee_CHECK_SPI_WAKE_ENABLE  (XBee_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define XBee_CHECK_UART_RTS_CONTROL_FLOW    (XBee_SCB_MODE_UART_CONST_CFG && \
                                                             XBee_UART_RTS_ENABLE)

#endif /* End (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* XBee_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} XBee_SPI_INIT_STRUCT;

/* XBee_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} XBee_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    void XBee_SpiInit(const XBee_SPI_INIT_STRUCT *config);
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(XBee_SCB_MODE_SPI_INC)
    #define XBee_SpiIsBusBusy() ((uint32) (0u != (XBee_SPI_STATUS_REG & \
                                                              XBee_SPI_STATUS_BUS_BUSY)))

    #if (XBee_SPI_MASTER_CONST)
        void XBee_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(XBee_SPI_MASTER_CONST) */

    #if !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
        void XBee_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */
#endif /* (XBee_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    void XBee_UartInit(const XBee_UART_INIT_STRUCT *config);
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(XBee_SCB_MODE_UART_INC)
    void XBee_UartSetRxAddress(uint32 address);
    void XBee_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(XBee_UART_RX_DIRECTION)
        uint32 XBee_UartGetChar(void);
        uint32 XBee_UartGetByte(void);

        #if !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void XBee_UartSetRtsPolarity(uint32 polarity);
            void XBee_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */
    #endif /* (XBee_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(XBee_UART_TX_DIRECTION)
        #define XBee_UartPutChar(ch)    XBee_SpiUartWriteTxData((uint32)(ch))
        void XBee_UartPutString(const char8 string[]);
        void XBee_UartPutCRLF(uint32 txDataByte);

        #if !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void XBee_UartEnableCts(void);
            void XBee_UartDisableCts(void);
            void XBee_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */
    #endif /* (XBee_UART_TX_DIRECTION) */
#endif /* (XBee_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(XBee_RX_DIRECTION)
    uint32 XBee_SpiUartReadRxData(void);
    uint32 XBee_SpiUartGetRxBufferSize(void);
    void   XBee_SpiUartClearRxBuffer(void);
#endif /* (XBee_RX_DIRECTION) */

/* Common APIs TX direction */
#if(XBee_TX_DIRECTION)
    void   XBee_SpiUartWriteTxData(uint32 txData);
    void   XBee_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 XBee_SpiUartGetTxBufferSize(void);
    void   XBee_SpiUartClearTxBuffer(void);
#endif /* (XBee_TX_DIRECTION) */

CY_ISR_PROTO(XBee_SPI_UART_ISR);

#if(XBee_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(XBee_UART_WAKEUP_ISR);
#endif /* (XBee_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   XBee_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 XBee_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   XBee_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 XBee_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(XBee_INTERNAL_RX_SW_BUFFER_CONST)
        #define XBee_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    XBee_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define XBee_GetWordFromRxBuffer(idx) XBee_rxBufferInternal[(idx)]

    #endif /* (XBee_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(XBee_INTERNAL_TX_SW_BUFFER_CONST)
        #define XBee_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        XBee_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define XBee_GetWordFromTxBuffer(idx) XBee_txBufferInternal[(idx)]

    #endif /* (XBee_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (XBee_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define XBee_SPI_MODE_MOTOROLA      (0x00u)
#define XBee_SPI_MODE_TI_COINCIDES  (0x01u)
#define XBee_SPI_MODE_TI_PRECEDES   (0x11u)
#define XBee_SPI_MODE_NATIONAL      (0x02u)
#define XBee_SPI_MODE_MASK          (0x03u)
#define XBee_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define XBee_SPI_MODE_NS_MICROWIRE  (XBee_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define XBee_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define XBee_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define XBee_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define XBee_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define XBee_BITS_ORDER_LSB_FIRST   (0u)
#define XBee_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define XBee_SPI_TRANSFER_SEPARATED     (0u)
#define XBee_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define XBee_SPI_SLAVE_SELECT0    (XBee_SCB__SS0_POSISTION)
#define XBee_SPI_SLAVE_SELECT1    (XBee_SCB__SS1_POSISTION)
#define XBee_SPI_SLAVE_SELECT2    (XBee_SCB__SS2_POSISTION)
#define XBee_SPI_SLAVE_SELECT3    (XBee_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define XBee_SPI_SS_ACTIVE_LOW  (0u)
#define XBee_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define XBee_UART_MODE_STD          (0u)
#define XBee_UART_MODE_SMARTCARD    (1u)
#define XBee_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define XBee_UART_RX    (1u)
#define XBee_UART_TX    (2u)
#define XBee_UART_TX_RX (3u)

/* UART parity enum */
#define XBee_UART_PARITY_EVEN   (0u)
#define XBee_UART_PARITY_ODD    (1u)
#define XBee_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define XBee_UART_STOP_BITS_1   (2u)
#define XBee_UART_STOP_BITS_1_5 (3u)
#define XBee_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define XBee_UART_IRDA_LP_OVS16     (16u)
#define XBee_UART_IRDA_LP_OVS32     (32u)
#define XBee_UART_IRDA_LP_OVS48     (48u)
#define XBee_UART_IRDA_LP_OVS96     (96u)
#define XBee_UART_IRDA_LP_OVS192    (192u)
#define XBee_UART_IRDA_LP_OVS768    (768u)
#define XBee_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define XBee_UART_MP_MARK       (0x100u)
#define XBee_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define XBee_UART_CTS_ACTIVE_LOW    (0u)
#define XBee_UART_CTS_ACTIVE_HIGH   (1u)
#define XBee_UART_RTS_ACTIVE_LOW    (0u)
#define XBee_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define XBee_INTR_RX_ERR        (XBee_INTR_RX_OVERFLOW    | \
                                             XBee_INTR_RX_UNDERFLOW   | \
                                             XBee_INTR_RX_FRAME_ERROR | \
                                             XBee_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for XBee_UartGetByte() */
#define XBee_UART_RX_OVERFLOW       (XBee_INTR_RX_OVERFLOW << 8u)
#define XBee_UART_RX_UNDERFLOW      (XBee_INTR_RX_UNDERFLOW << 8u)
#define XBee_UART_RX_FRAME_ERROR    (XBee_INTR_RX_FRAME_ERROR << 8u)
#define XBee_UART_RX_PARITY_ERROR   (XBee_INTR_RX_PARITY_ERROR << 8u)
#define XBee_UART_RX_ERROR_MASK     (XBee_UART_RX_OVERFLOW    | \
                                                 XBee_UART_RX_UNDERFLOW   | \
                                                 XBee_UART_RX_FRAME_ERROR | \
                                                 XBee_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const XBee_SPI_INIT_STRUCT  XBee_configSpi;
    extern const XBee_UART_INIT_STRUCT XBee_configUart;
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define XBee_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & XBee_INTR_SLAVE_SPI_BUS_ERROR)
#define XBee_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & XBee_INTR_MASTER_SPI_DONE)
#define XBee_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~XBee_INTR_SLAVE_SPI_BUS_ERROR)

#define XBee_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~XBee_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define XBee_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((XBee_UART_IRDA_LP_OVS16   == (oversample)) ? XBee_CTRL_OVS_IRDA_LP_OVS16 : \
         ((XBee_UART_IRDA_LP_OVS32   == (oversample)) ? XBee_CTRL_OVS_IRDA_LP_OVS32 : \
          ((XBee_UART_IRDA_LP_OVS48   == (oversample)) ? XBee_CTRL_OVS_IRDA_LP_OVS48 : \
           ((XBee_UART_IRDA_LP_OVS96   == (oversample)) ? XBee_CTRL_OVS_IRDA_LP_OVS96 : \
            ((XBee_UART_IRDA_LP_OVS192  == (oversample)) ? XBee_CTRL_OVS_IRDA_LP_OVS192 : \
             ((XBee_UART_IRDA_LP_OVS768  == (oversample)) ? XBee_CTRL_OVS_IRDA_LP_OVS768 : \
              ((XBee_UART_IRDA_LP_OVS1536 == (oversample)) ? XBee_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          XBee_CTRL_OVS_IRDA_LP_OVS16)))))))

#define XBee_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (XBee_UART_RX & (direction))) ? \
                                                                     (XBee_RX_CTRL_ENABLED) : (0u))

#define XBee_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (XBee_UART_TX & (direction))) ? \
                                                                     (XBee_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define XBee_CTRL_SPI      (XBee_CTRL_MODE_SPI)
#define XBee_SPI_RX_CTRL   (XBee_RX_CTRL_ENABLED)
#define XBee_SPI_TX_CTRL   (XBee_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define XBee_SPI_SS_POLARITY \
             (((uint32) XBee_SPI_SS0_POLARITY << XBee_SPI_SLAVE_SELECT0) | \
              ((uint32) XBee_SPI_SS1_POLARITY << XBee_SPI_SLAVE_SELECT1) | \
              ((uint32) XBee_SPI_SS2_POLARITY << XBee_SPI_SLAVE_SELECT2) | \
              ((uint32) XBee_SPI_SS3_POLARITY << XBee_SPI_SLAVE_SELECT3))

#if(XBee_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define XBee_SPI_DEFAULT_CTRL \
                    (XBee_GET_CTRL_OVS(XBee_SPI_OVS_FACTOR) | \
                     XBee_GET_CTRL_BYTE_MODE (XBee_SPI_BYTE_MODE_ENABLE) | \
                     XBee_GET_CTRL_EC_AM_MODE(XBee_SPI_WAKE_ENABLE)      | \
                     XBee_CTRL_SPI)

    #define XBee_SPI_DEFAULT_SPI_CTRL \
                    (XBee_GET_SPI_CTRL_CONTINUOUS    (XBee_SPI_TRANSFER_SEPARATION)       | \
                     XBee_GET_SPI_CTRL_SELECT_PRECEDE(XBee_SPI_SUB_MODE &                   \
                                                                  XBee_SPI_MODE_TI_PRECEDES_MASK)     | \
                     XBee_GET_SPI_CTRL_SCLK_MODE     (XBee_SPI_CLOCK_MODE)                | \
                     XBee_GET_SPI_CTRL_LATE_MISO_SAMPLE(XBee_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     XBee_GET_SPI_CTRL_SCLK_CONTINUOUS(XBee_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     XBee_GET_SPI_CTRL_SSEL_POLARITY (XBee_SPI_SS_POLARITY)               | \
                     XBee_GET_SPI_CTRL_SUB_MODE      (XBee_SPI_SUB_MODE)                  | \
                     XBee_GET_SPI_CTRL_MASTER_MODE   (XBee_SPI_MODE))

    /* RX direction */
    #define XBee_SPI_DEFAULT_RX_CTRL \
                    (XBee_GET_RX_CTRL_DATA_WIDTH(XBee_SPI_RX_DATA_BITS_NUM)     | \
                     XBee_GET_RX_CTRL_BIT_ORDER (XBee_SPI_BITS_ORDER)           | \
                     XBee_GET_RX_CTRL_MEDIAN    (XBee_SPI_MEDIAN_FILTER_ENABLE) | \
                     XBee_SPI_RX_CTRL)

    #define XBee_SPI_DEFAULT_RX_FIFO_CTRL \
                    XBee_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(XBee_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define XBee_SPI_DEFAULT_TX_CTRL \
                    (XBee_GET_TX_CTRL_DATA_WIDTH(XBee_SPI_TX_DATA_BITS_NUM) | \
                     XBee_GET_TX_CTRL_BIT_ORDER (XBee_SPI_BITS_ORDER)       | \
                     XBee_SPI_TX_CTRL)

    #define XBee_SPI_DEFAULT_TX_FIFO_CTRL \
                    XBee_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(XBee_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define XBee_SPI_DEFAULT_INTR_SPI_EC_MASK   (XBee_NO_INTR_SOURCES)

    #define XBee_SPI_DEFAULT_INTR_I2C_EC_MASK   (XBee_NO_INTR_SOURCES)
    #define XBee_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (XBee_SPI_INTR_RX_MASK & XBee_INTR_SLAVE_SPI_BUS_ERROR)

    #define XBee_SPI_DEFAULT_INTR_MASTER_MASK \
                    (XBee_SPI_INTR_TX_MASK & XBee_INTR_MASTER_SPI_DONE)

    #define XBee_SPI_DEFAULT_INTR_RX_MASK \
                    (XBee_SPI_INTR_RX_MASK & (uint32) ~XBee_INTR_SLAVE_SPI_BUS_ERROR)

    #define XBee_SPI_DEFAULT_INTR_TX_MASK \
                    (XBee_SPI_INTR_TX_MASK & (uint32) ~XBee_INTR_MASTER_SPI_DONE)

#endif /* (XBee_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define XBee_CTRL_UART      (XBee_CTRL_MODE_UART)
#define XBee_UART_RX_CTRL   (XBee_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define XBee_UART_TX_CTRL   (XBee_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(XBee_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(XBee_UART_MODE_IRDA == XBee_UART_SUB_MODE)

        #define XBee_DEFAULT_CTRL_OVS   ((0u != XBee_UART_IRDA_LOW_POWER) ?              \
                                (XBee_UART_GET_CTRL_OVS_IRDA_LP(XBee_UART_OVS_FACTOR)) : \
                                (XBee_CTRL_OVS_IRDA_OVS16))

    #else

        #define XBee_DEFAULT_CTRL_OVS   XBee_GET_CTRL_OVS(XBee_UART_OVS_FACTOR)

    #endif /* (XBee_UART_MODE_IRDA == XBee_UART_SUB_MODE) */

    #define XBee_UART_DEFAULT_CTRL \
                                (XBee_GET_CTRL_BYTE_MODE  (XBee_UART_BYTE_MODE_ENABLE)  | \
                                 XBee_GET_CTRL_ADDR_ACCEPT(XBee_UART_MP_ACCEPT_ADDRESS) | \
                                 XBee_DEFAULT_CTRL_OVS                                              | \
                                 XBee_CTRL_UART)

    #define XBee_UART_DEFAULT_UART_CTRL \
                                    (XBee_GET_UART_CTRL_MODE(XBee_UART_SUB_MODE))

    /* RX direction */
    #define XBee_UART_DEFAULT_RX_CTRL_PARITY \
                                ((XBee_UART_PARITY_NONE != XBee_UART_PARITY_TYPE) ?      \
                                  (XBee_GET_UART_RX_CTRL_PARITY(XBee_UART_PARITY_TYPE) | \
                                   XBee_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define XBee_UART_DEFAULT_UART_RX_CTRL \
                    (XBee_GET_UART_RX_CTRL_MODE(XBee_UART_STOP_BITS_NUM)                    | \
                     XBee_GET_UART_RX_CTRL_POLARITY(XBee_UART_IRDA_POLARITY)                | \
                     XBee_GET_UART_RX_CTRL_MP_MODE(XBee_UART_MP_MODE_ENABLE)                | \
                     XBee_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(XBee_UART_DROP_ON_PARITY_ERR) | \
                     XBee_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(XBee_UART_DROP_ON_FRAME_ERR)   | \
                     XBee_UART_DEFAULT_RX_CTRL_PARITY)

    #define XBee_UART_DEFAULT_RX_CTRL \
                                (XBee_GET_RX_CTRL_DATA_WIDTH(XBee_UART_DATA_BITS_NUM)        | \
                                 XBee_GET_RX_CTRL_MEDIAN    (XBee_UART_MEDIAN_FILTER_ENABLE) | \
                                 XBee_GET_UART_RX_CTRL_ENABLED(XBee_UART_DIRECTION))

    #define XBee_UART_DEFAULT_RX_FIFO_CTRL \
                                XBee_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(XBee_UART_RX_TRIGGER_LEVEL)

    #define XBee_UART_DEFAULT_RX_MATCH_REG  ((0u != XBee_UART_MP_MODE_ENABLE) ?          \
                                (XBee_GET_RX_MATCH_ADDR(XBee_UART_MP_RX_ADDRESS) | \
                                 XBee_GET_RX_MATCH_MASK(XBee_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define XBee_UART_DEFAULT_TX_CTRL_PARITY (XBee_UART_DEFAULT_RX_CTRL_PARITY)

    #define XBee_UART_DEFAULT_UART_TX_CTRL \
                                (XBee_GET_UART_TX_CTRL_MODE(XBee_UART_STOP_BITS_NUM)       | \
                                 XBee_GET_UART_TX_CTRL_RETRY_NACK(XBee_UART_RETRY_ON_NACK) | \
                                 XBee_UART_DEFAULT_TX_CTRL_PARITY)

    #define XBee_UART_DEFAULT_TX_CTRL \
                                (XBee_GET_TX_CTRL_DATA_WIDTH(XBee_UART_DATA_BITS_NUM) | \
                                 XBee_GET_UART_TX_CTRL_ENABLED(XBee_UART_DIRECTION))

    #define XBee_UART_DEFAULT_TX_FIFO_CTRL \
                                XBee_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(XBee_UART_TX_TRIGGER_LEVEL)

    #define XBee_UART_DEFAULT_FLOW_CTRL \
                        (XBee_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(XBee_UART_RTS_FIFO_LEVEL) | \
                         XBee_GET_UART_FLOW_CTRL_RTS_POLARITY (XBee_UART_RTS_POLARITY)   | \
                         XBee_GET_UART_FLOW_CTRL_CTS_POLARITY (XBee_UART_CTS_POLARITY)   | \
                         XBee_GET_UART_FLOW_CTRL_CTS_ENABLE   (XBee_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define XBee_UART_DEFAULT_INTR_I2C_EC_MASK  (XBee_NO_INTR_SOURCES)
    #define XBee_UART_DEFAULT_INTR_SPI_EC_MASK  (XBee_NO_INTR_SOURCES)
    #define XBee_UART_DEFAULT_INTR_SLAVE_MASK   (XBee_NO_INTR_SOURCES)
    #define XBee_UART_DEFAULT_INTR_MASTER_MASK  (XBee_NO_INTR_SOURCES)
    #define XBee_UART_DEFAULT_INTR_RX_MASK      (XBee_UART_INTR_RX_MASK)
    #define XBee_UART_DEFAULT_INTR_TX_MASK      (XBee_UART_INTR_TX_MASK)

#endif /* (XBee_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define XBee_SPIM_ACTIVE_SS0    (XBee_SPI_SLAVE_SELECT0)
#define XBee_SPIM_ACTIVE_SS1    (XBee_SPI_SLAVE_SELECT1)
#define XBee_SPIM_ACTIVE_SS2    (XBee_SPI_SLAVE_SELECT2)
#define XBee_SPIM_ACTIVE_SS3    (XBee_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_XBee_H */


/* [] END OF FILE */
