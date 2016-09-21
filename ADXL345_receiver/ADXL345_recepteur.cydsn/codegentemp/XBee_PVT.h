/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_XBee_H)
#define CY_SCB_PVT_XBee_H

#include "XBee.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define XBee_SetI2CExtClkInterruptMode(interruptMask) XBee_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define XBee_ClearI2CExtClkInterruptSource(interruptMask) XBee_CLEAR_INTR_I2C_EC(interruptMask)
#define XBee_GetI2CExtClkInterruptSource()                (XBee_INTR_I2C_EC_REG)
#define XBee_GetI2CExtClkInterruptMode()                  (XBee_INTR_I2C_EC_MASK_REG)
#define XBee_GetI2CExtClkInterruptSourceMasked()          (XBee_INTR_I2C_EC_MASKED_REG)

#if (!XBee_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define XBee_SetSpiExtClkInterruptMode(interruptMask) \
                                                                XBee_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define XBee_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                XBee_CLEAR_INTR_SPI_EC(interruptMask)
    #define XBee_GetExtSpiClkInterruptSource()                 (XBee_INTR_SPI_EC_REG)
    #define XBee_GetExtSpiClkInterruptMode()                   (XBee_INTR_SPI_EC_MASK_REG)
    #define XBee_GetExtSpiClkInterruptSourceMasked()           (XBee_INTR_SPI_EC_MASKED_REG)
#endif /* (!XBee_CY_SCBIP_V1) */

#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void XBee_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (XBee_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_XBee_CUSTOM_INTR_HANDLER)
    extern cyisraddress XBee_customIntrHandler;
#endif /* !defined (CY_REMOVE_XBee_CUSTOM_INTR_HANDLER) */
#endif /* (XBee_SCB_IRQ_INTERNAL) */

extern XBee_BACKUP_STRUCT XBee_backup;

#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 XBee_scbMode;
    extern uint8 XBee_scbEnableWake;
    extern uint8 XBee_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 XBee_mode;
    extern uint8 XBee_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * XBee_rxBuffer;
    extern uint8   XBee_rxDataBits;
    extern uint32  XBee_rxBufferSize;

    extern volatile uint8 * XBee_txBuffer;
    extern uint8   XBee_txDataBits;
    extern uint32  XBee_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 XBee_numberOfAddr;
    extern uint8 XBee_subAddrSize;
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define XBee_SCB_MODE_I2C_RUNTM_CFG     (XBee_SCB_MODE_I2C      == XBee_scbMode)
    #define XBee_SCB_MODE_SPI_RUNTM_CFG     (XBee_SCB_MODE_SPI      == XBee_scbMode)
    #define XBee_SCB_MODE_UART_RUNTM_CFG    (XBee_SCB_MODE_UART     == XBee_scbMode)
    #define XBee_SCB_MODE_EZI2C_RUNTM_CFG   (XBee_SCB_MODE_EZI2C    == XBee_scbMode)
    #define XBee_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (XBee_SCB_MODE_UNCONFIG == XBee_scbMode)

    /* Defines wakeup enable */
    #define XBee_SCB_WAKE_ENABLE_CHECK       (0u != XBee_scbEnableWake)
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!XBee_CY_SCBIP_V1)
    #define XBee_SCB_PINS_NUMBER    (7u)
#else
    #define XBee_SCB_PINS_NUMBER    (2u)
#endif /* (!XBee_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_XBee_H) */


/* [] END OF FILE */
