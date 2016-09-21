/*******************************************************************************
* File Name: XBee_SPI_UART_PVT.h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_XBee_H)
#define CY_SCB_SPI_UART_PVT_XBee_H

#include "XBee_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (XBee_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  XBee_rxBufferHead;
    extern volatile uint32  XBee_rxBufferTail;
    extern volatile uint8   XBee_rxBufferOverflow;
#endif /* (XBee_INTERNAL_RX_SW_BUFFER_CONST) */

#if (XBee_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  XBee_txBufferHead;
    extern volatile uint32  XBee_txBufferTail;
#endif /* (XBee_INTERNAL_TX_SW_BUFFER_CONST) */

#if (XBee_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 XBee_rxBufferInternal[XBee_INTERNAL_RX_BUFFER_SIZE];
#endif /* (XBee_INTERNAL_RX_SW_BUFFER) */

#if (XBee_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 XBee_txBufferInternal[XBee_TX_BUFFER_SIZE];
#endif /* (XBee_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void XBee_SpiPostEnable(void);
void XBee_SpiStop(void);

#if (XBee_SCB_MODE_SPI_CONST_CFG)
    void XBee_SpiInit(void);
#endif /* (XBee_SCB_MODE_SPI_CONST_CFG) */

#if (XBee_SPI_WAKE_ENABLE_CONST)
    void XBee_SpiSaveConfig(void);
    void XBee_SpiRestoreConfig(void);
#endif /* (XBee_SPI_WAKE_ENABLE_CONST) */

void XBee_UartPostEnable(void);
void XBee_UartStop(void);

#if (XBee_SCB_MODE_UART_CONST_CFG)
    void XBee_UartInit(void);
#endif /* (XBee_SCB_MODE_UART_CONST_CFG) */

#if (XBee_UART_WAKE_ENABLE_CONST)
    void XBee_UartSaveConfig(void);
    void XBee_UartRestoreConfig(void);
#endif /* (XBee_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in XBee_SetPins() */
#define XBee_UART_RX_PIN_ENABLE    (XBee_UART_RX)
#define XBee_UART_TX_PIN_ENABLE    (XBee_UART_TX)

/* UART RTS and CTS position to be used in  XBee_SetPins() */
#define XBee_UART_RTS_PIN_ENABLE    (0x10u)
#define XBee_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define XBee_SpiUartEnableIntRx(intSourceMask)  XBee_SetRxInterruptMode(intSourceMask)
#define XBee_SpiUartEnableIntTx(intSourceMask)  XBee_SetTxInterruptMode(intSourceMask)
uint32  XBee_SpiUartDisableIntRx(void);
uint32  XBee_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_XBee_H) */


/* [] END OF FILE */
