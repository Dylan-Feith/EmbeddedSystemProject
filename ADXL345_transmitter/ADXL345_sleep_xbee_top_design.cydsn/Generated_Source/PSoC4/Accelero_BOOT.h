/*******************************************************************************
* File Name: Accelero_BOOT.h
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

#if !defined(CY_SCB_BOOT_Accelero_H)
#define CY_SCB_BOOT_Accelero_H

#include "Accelero_PVT.h"

#if (Accelero_SCB_MODE_I2C_INC)
    #include "Accelero_I2C.h"
#endif /* (Accelero_SCB_MODE_I2C_INC) */

#if (Accelero_SCB_MODE_EZI2C_INC)
    #include "Accelero_EZI2C.h"
#endif /* (Accelero_SCB_MODE_EZI2C_INC) */

#if (Accelero_SCB_MODE_SPI_INC || Accelero_SCB_MODE_UART_INC)
    #include "Accelero_SPI_UART.h"
#endif /* (Accelero_SCB_MODE_SPI_INC || Accelero_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define Accelero_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Accelero) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (Accelero_SCB_MODE_I2C_INC)
    #define Accelero_I2C_BTLDR_COMM_ENABLED     (Accelero_BTLDR_COMM_ENABLED && \
                                                            (Accelero_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Accelero_I2C_SLAVE_CONST))
#else
     #define Accelero_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (Accelero_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (Accelero_SCB_MODE_EZI2C_INC)
    #define Accelero_EZI2C_BTLDR_COMM_ENABLED   (Accelero_BTLDR_COMM_ENABLED && \
                                                         Accelero_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define Accelero_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (Accelero_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (Accelero_SCB_MODE_SPI_INC)
    #define Accelero_SPI_BTLDR_COMM_ENABLED     (Accelero_BTLDR_COMM_ENABLED && \
                                                            (Accelero_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Accelero_SPI_SLAVE_CONST))
#else
        #define Accelero_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (Accelero_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (Accelero_SCB_MODE_UART_INC)
       #define Accelero_UART_BTLDR_COMM_ENABLED    (Accelero_BTLDR_COMM_ENABLED && \
                                                            (Accelero_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (Accelero_UART_RX_DIRECTION && \
                                                              Accelero_UART_TX_DIRECTION)))
#else
     #define Accelero_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (Accelero_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define Accelero_BTLDR_COMM_MODE_ENABLED    (Accelero_I2C_BTLDR_COMM_ENABLED   || \
                                                     Accelero_SPI_BTLDR_COMM_ENABLED   || \
                                                     Accelero_EZI2C_BTLDR_COMM_ENABLED || \
                                                     Accelero_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void Accelero_I2CCyBtldrCommStart(void);
    void Accelero_I2CCyBtldrCommStop (void);
    void Accelero_I2CCyBtldrCommReset(void);
    cystatus Accelero_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Accelero_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (Accelero_SCB_MODE_I2C_CONST_CFG)
        #define Accelero_CyBtldrCommStart   Accelero_I2CCyBtldrCommStart
        #define Accelero_CyBtldrCommStop    Accelero_I2CCyBtldrCommStop
        #define Accelero_CyBtldrCommReset   Accelero_I2CCyBtldrCommReset
        #define Accelero_CyBtldrCommRead    Accelero_I2CCyBtldrCommRead
        #define Accelero_CyBtldrCommWrite   Accelero_I2CCyBtldrCommWrite
    #endif /* (Accelero_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Accelero_EzI2CCyBtldrCommStart(void);
    void Accelero_EzI2CCyBtldrCommStop (void);
    void Accelero_EzI2CCyBtldrCommReset(void);
    cystatus Accelero_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Accelero_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (Accelero_SCB_MODE_EZI2C_CONST_CFG)
        #define Accelero_CyBtldrCommStart   Accelero_EzI2CCyBtldrCommStart
        #define Accelero_CyBtldrCommStop    Accelero_EzI2CCyBtldrCommStop
        #define Accelero_CyBtldrCommReset   Accelero_EzI2CCyBtldrCommReset
        #define Accelero_CyBtldrCommRead    Accelero_EzI2CCyBtldrCommRead
        #define Accelero_CyBtldrCommWrite   Accelero_EzI2CCyBtldrCommWrite
    #endif /* (Accelero_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void Accelero_SpiCyBtldrCommStart(void);
    void Accelero_SpiCyBtldrCommStop (void);
    void Accelero_SpiCyBtldrCommReset(void);
    cystatus Accelero_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Accelero_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (Accelero_SCB_MODE_SPI_CONST_CFG)
        #define Accelero_CyBtldrCommStart   Accelero_SpiCyBtldrCommStart
        #define Accelero_CyBtldrCommStop    Accelero_SpiCyBtldrCommStop
        #define Accelero_CyBtldrCommReset   Accelero_SpiCyBtldrCommReset
        #define Accelero_CyBtldrCommRead    Accelero_SpiCyBtldrCommRead
        #define Accelero_CyBtldrCommWrite   Accelero_SpiCyBtldrCommWrite
    #endif /* (Accelero_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void Accelero_UartCyBtldrCommStart(void);
    void Accelero_UartCyBtldrCommStop (void);
    void Accelero_UartCyBtldrCommReset(void);
    cystatus Accelero_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Accelero_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (Accelero_SCB_MODE_UART_CONST_CFG)
        #define Accelero_CyBtldrCommStart   Accelero_UartCyBtldrCommStart
        #define Accelero_CyBtldrCommStop    Accelero_UartCyBtldrCommStop
        #define Accelero_CyBtldrCommReset   Accelero_UartCyBtldrCommReset
        #define Accelero_CyBtldrCommRead    Accelero_UartCyBtldrCommRead
        #define Accelero_CyBtldrCommWrite   Accelero_UartCyBtldrCommWrite
    #endif /* (Accelero_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_BTLDR_COMM_ENABLED)
    #if (Accelero_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void Accelero_CyBtldrCommStart(void);
        void Accelero_CyBtldrCommStop (void);
        void Accelero_CyBtldrCommReset(void);
        cystatus Accelero_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus Accelero_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (Accelero_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Accelero)
        #define CyBtldrCommStart    Accelero_CyBtldrCommStart
        #define CyBtldrCommStop     Accelero_CyBtldrCommStop
        #define CyBtldrCommReset    Accelero_CyBtldrCommReset
        #define CyBtldrCommWrite    Accelero_CyBtldrCommWrite
        #define CyBtldrCommRead     Accelero_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Accelero) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define Accelero_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define Accelero_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define Accelero_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define Accelero_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef Accelero_SPI_BYTE_TO_BYTE
    #define Accelero_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef Accelero_UART_BYTE_TO_BYTE
    #define Accelero_UART_BYTE_TO_BYTE  (2500u)
#endif /* Accelero_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_Accelero_H) */


/* [] END OF FILE */
