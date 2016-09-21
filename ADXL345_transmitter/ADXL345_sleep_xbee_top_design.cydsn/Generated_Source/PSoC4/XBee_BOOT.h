/*******************************************************************************
* File Name: XBee_BOOT.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_XBee_H)
#define CY_SCB_BOOT_XBee_H

#include "XBee_PVT.h"

#if (XBee_SCB_MODE_I2C_INC)
    #include "XBee_I2C.h"
#endif /* (XBee_SCB_MODE_I2C_INC) */

#if (XBee_SCB_MODE_EZI2C_INC)
    #include "XBee_EZI2C.h"
#endif /* (XBee_SCB_MODE_EZI2C_INC) */

#if (XBee_SCB_MODE_SPI_INC || XBee_SCB_MODE_UART_INC)
    #include "XBee_SPI_UART.h"
#endif /* (XBee_SCB_MODE_SPI_INC || XBee_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define XBee_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_XBee) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (XBee_SCB_MODE_I2C_INC)
    #define XBee_I2C_BTLDR_COMM_ENABLED     (XBee_BTLDR_COMM_ENABLED && \
                                                            (XBee_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             XBee_I2C_SLAVE_CONST))
#else
     #define XBee_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (XBee_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (XBee_SCB_MODE_EZI2C_INC)
    #define XBee_EZI2C_BTLDR_COMM_ENABLED   (XBee_BTLDR_COMM_ENABLED && \
                                                         XBee_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define XBee_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (XBee_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (XBee_SCB_MODE_SPI_INC)
    #define XBee_SPI_BTLDR_COMM_ENABLED     (XBee_BTLDR_COMM_ENABLED && \
                                                            (XBee_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             XBee_SPI_SLAVE_CONST))
#else
        #define XBee_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (XBee_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (XBee_SCB_MODE_UART_INC)
       #define XBee_UART_BTLDR_COMM_ENABLED    (XBee_BTLDR_COMM_ENABLED && \
                                                            (XBee_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (XBee_UART_RX_DIRECTION && \
                                                              XBee_UART_TX_DIRECTION)))
#else
     #define XBee_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (XBee_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define XBee_BTLDR_COMM_MODE_ENABLED    (XBee_I2C_BTLDR_COMM_ENABLED   || \
                                                     XBee_SPI_BTLDR_COMM_ENABLED   || \
                                                     XBee_EZI2C_BTLDR_COMM_ENABLED || \
                                                     XBee_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void XBee_I2CCyBtldrCommStart(void);
    void XBee_I2CCyBtldrCommStop (void);
    void XBee_I2CCyBtldrCommReset(void);
    cystatus XBee_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus XBee_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (XBee_SCB_MODE_I2C_CONST_CFG)
        #define XBee_CyBtldrCommStart   XBee_I2CCyBtldrCommStart
        #define XBee_CyBtldrCommStop    XBee_I2CCyBtldrCommStop
        #define XBee_CyBtldrCommReset   XBee_I2CCyBtldrCommReset
        #define XBee_CyBtldrCommRead    XBee_I2CCyBtldrCommRead
        #define XBee_CyBtldrCommWrite   XBee_I2CCyBtldrCommWrite
    #endif /* (XBee_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void XBee_EzI2CCyBtldrCommStart(void);
    void XBee_EzI2CCyBtldrCommStop (void);
    void XBee_EzI2CCyBtldrCommReset(void);
    cystatus XBee_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus XBee_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (XBee_SCB_MODE_EZI2C_CONST_CFG)
        #define XBee_CyBtldrCommStart   XBee_EzI2CCyBtldrCommStart
        #define XBee_CyBtldrCommStop    XBee_EzI2CCyBtldrCommStop
        #define XBee_CyBtldrCommReset   XBee_EzI2CCyBtldrCommReset
        #define XBee_CyBtldrCommRead    XBee_EzI2CCyBtldrCommRead
        #define XBee_CyBtldrCommWrite   XBee_EzI2CCyBtldrCommWrite
    #endif /* (XBee_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void XBee_SpiCyBtldrCommStart(void);
    void XBee_SpiCyBtldrCommStop (void);
    void XBee_SpiCyBtldrCommReset(void);
    cystatus XBee_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus XBee_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (XBee_SCB_MODE_SPI_CONST_CFG)
        #define XBee_CyBtldrCommStart   XBee_SpiCyBtldrCommStart
        #define XBee_CyBtldrCommStop    XBee_SpiCyBtldrCommStop
        #define XBee_CyBtldrCommReset   XBee_SpiCyBtldrCommReset
        #define XBee_CyBtldrCommRead    XBee_SpiCyBtldrCommRead
        #define XBee_CyBtldrCommWrite   XBee_SpiCyBtldrCommWrite
    #endif /* (XBee_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void XBee_UartCyBtldrCommStart(void);
    void XBee_UartCyBtldrCommStop (void);
    void XBee_UartCyBtldrCommReset(void);
    cystatus XBee_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus XBee_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (XBee_SCB_MODE_UART_CONST_CFG)
        #define XBee_CyBtldrCommStart   XBee_UartCyBtldrCommStart
        #define XBee_CyBtldrCommStop    XBee_UartCyBtldrCommStop
        #define XBee_CyBtldrCommReset   XBee_UartCyBtldrCommReset
        #define XBee_CyBtldrCommRead    XBee_UartCyBtldrCommRead
        #define XBee_CyBtldrCommWrite   XBee_UartCyBtldrCommWrite
    #endif /* (XBee_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_BTLDR_COMM_ENABLED)
    #if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void XBee_CyBtldrCommStart(void);
        void XBee_CyBtldrCommStop (void);
        void XBee_CyBtldrCommReset(void);
        cystatus XBee_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus XBee_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_XBee)
        #define CyBtldrCommStart    XBee_CyBtldrCommStart
        #define CyBtldrCommStop     XBee_CyBtldrCommStop
        #define CyBtldrCommReset    XBee_CyBtldrCommReset
        #define CyBtldrCommWrite    XBee_CyBtldrCommWrite
        #define CyBtldrCommRead     XBee_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_XBee) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (XBee_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define XBee_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define XBee_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define XBee_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define XBee_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef XBee_SPI_BYTE_TO_BYTE
    #define XBee_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef XBee_UART_BYTE_TO_BYTE
    #define XBee_UART_BYTE_TO_BYTE  (2100u)
#endif /* XBee_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_XBee_H) */


/* [] END OF FILE */
