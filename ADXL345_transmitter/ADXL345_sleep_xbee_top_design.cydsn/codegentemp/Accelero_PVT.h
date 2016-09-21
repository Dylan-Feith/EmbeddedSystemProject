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

#if !defined(CY_SCB_PVT_Accelero_H)
#define CY_SCB_PVT_Accelero_H

#include "Accelero.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define Accelero_SetI2CExtClkInterruptMode(interruptMask) Accelero_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define Accelero_ClearI2CExtClkInterruptSource(interruptMask) Accelero_CLEAR_INTR_I2C_EC(interruptMask)
#define Accelero_GetI2CExtClkInterruptSource()                (Accelero_INTR_I2C_EC_REG)
#define Accelero_GetI2CExtClkInterruptMode()                  (Accelero_INTR_I2C_EC_MASK_REG)
#define Accelero_GetI2CExtClkInterruptSourceMasked()          (Accelero_INTR_I2C_EC_MASKED_REG)

#if (!Accelero_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define Accelero_SetSpiExtClkInterruptMode(interruptMask) \
                                                                Accelero_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define Accelero_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                Accelero_CLEAR_INTR_SPI_EC(interruptMask)
    #define Accelero_GetExtSpiClkInterruptSource()                 (Accelero_INTR_SPI_EC_REG)
    #define Accelero_GetExtSpiClkInterruptMode()                   (Accelero_INTR_SPI_EC_MASK_REG)
    #define Accelero_GetExtSpiClkInterruptSourceMasked()           (Accelero_INTR_SPI_EC_MASKED_REG)
#endif /* (!Accelero_CY_SCBIP_V1) */

#if(Accelero_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void Accelero_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (Accelero_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (Accelero_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_Accelero_CUSTOM_INTR_HANDLER)
    extern cyisraddress Accelero_customIntrHandler;
#endif /* !defined (CY_REMOVE_Accelero_CUSTOM_INTR_HANDLER) */
#endif /* (Accelero_SCB_IRQ_INTERNAL) */

extern Accelero_BACKUP_STRUCT Accelero_backup;

#if(Accelero_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 Accelero_scbMode;
    extern uint8 Accelero_scbEnableWake;
    extern uint8 Accelero_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 Accelero_mode;
    extern uint8 Accelero_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * Accelero_rxBuffer;
    extern uint8   Accelero_rxDataBits;
    extern uint32  Accelero_rxBufferSize;

    extern volatile uint8 * Accelero_txBuffer;
    extern uint8   Accelero_txDataBits;
    extern uint32  Accelero_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 Accelero_numberOfAddr;
    extern uint8 Accelero_subAddrSize;
#endif /* (Accelero_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(Accelero_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define Accelero_SCB_MODE_I2C_RUNTM_CFG     (Accelero_SCB_MODE_I2C      == Accelero_scbMode)
    #define Accelero_SCB_MODE_SPI_RUNTM_CFG     (Accelero_SCB_MODE_SPI      == Accelero_scbMode)
    #define Accelero_SCB_MODE_UART_RUNTM_CFG    (Accelero_SCB_MODE_UART     == Accelero_scbMode)
    #define Accelero_SCB_MODE_EZI2C_RUNTM_CFG   (Accelero_SCB_MODE_EZI2C    == Accelero_scbMode)
    #define Accelero_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (Accelero_SCB_MODE_UNCONFIG == Accelero_scbMode)

    /* Defines wakeup enable */
    #define Accelero_SCB_WAKE_ENABLE_CHECK       (0u != Accelero_scbEnableWake)
#endif /* (Accelero_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!Accelero_CY_SCBIP_V1)
    #define Accelero_SCB_PINS_NUMBER    (7u)
#else
    #define Accelero_SCB_PINS_NUMBER    (2u)
#endif /* (!Accelero_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_Accelero_H) */


/* [] END OF FILE */
