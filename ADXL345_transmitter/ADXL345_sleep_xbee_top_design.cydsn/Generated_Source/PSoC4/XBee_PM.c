/*******************************************************************************
* File Name: XBee_PM.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "XBee.h"
#include "XBee_PVT.h"

#if(XBee_SCB_MODE_I2C_INC)
    #include "XBee_I2C_PVT.h"
#endif /* (XBee_SCB_MODE_I2C_INC) */

#if(XBee_SCB_MODE_EZI2C_INC)
    #include "XBee_EZI2C_PVT.h"
#endif /* (XBee_SCB_MODE_EZI2C_INC) */

#if(XBee_SCB_MODE_SPI_INC || XBee_SCB_MODE_UART_INC)
    #include "XBee_SPI_UART_PVT.h"
#endif /* (XBee_SCB_MODE_SPI_INC || XBee_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG || \
   (XBee_SCB_MODE_I2C_CONST_CFG   && (!XBee_I2C_WAKE_ENABLE_CONST))   || \
   (XBee_SCB_MODE_EZI2C_CONST_CFG && (!XBee_EZI2C_WAKE_ENABLE_CONST)) || \
   (XBee_SCB_MODE_SPI_CONST_CFG   && (!XBee_SPI_WAKE_ENABLE_CONST))   || \
   (XBee_SCB_MODE_UART_CONST_CFG  && (!XBee_UART_WAKE_ENABLE_CONST)))

    XBee_BACKUP_STRUCT XBee_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: XBee_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void XBee_Sleep(void)
{
#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)

    if(XBee_SCB_WAKE_ENABLE_CHECK)
    {
        if(XBee_SCB_MODE_I2C_RUNTM_CFG)
        {
            XBee_I2CSaveConfig();
        }
        else if(XBee_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            XBee_EzI2CSaveConfig();
        }
    #if(!XBee_CY_SCBIP_V1)
        else if(XBee_SCB_MODE_SPI_RUNTM_CFG)
        {
            XBee_SpiSaveConfig();
        }
        else if(XBee_SCB_MODE_UART_RUNTM_CFG)
        {
            XBee_UartSaveConfig();
        }
    #endif /* (!XBee_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        XBee_backup.enableState = (uint8) XBee_GET_CTRL_ENABLED;

        if(0u != XBee_backup.enableState)
        {
            XBee_Stop();
        }
    }

#else

    #if (XBee_SCB_MODE_I2C_CONST_CFG && XBee_I2C_WAKE_ENABLE_CONST)
        XBee_I2CSaveConfig();

    #elif (XBee_SCB_MODE_EZI2C_CONST_CFG && XBee_EZI2C_WAKE_ENABLE_CONST)
        XBee_EzI2CSaveConfig();

    #elif (XBee_SCB_MODE_SPI_CONST_CFG && XBee_SPI_WAKE_ENABLE_CONST)
        XBee_SpiSaveConfig();

    #elif (XBee_SCB_MODE_UART_CONST_CFG && XBee_UART_WAKE_ENABLE_CONST)
        XBee_UartSaveConfig();

    #else

        XBee_backup.enableState = (uint8) XBee_GET_CTRL_ENABLED;

        if(0u != XBee_backup.enableState)
        {
            XBee_Stop();
        }

    #endif /* defined (XBee_SCB_MODE_I2C_CONST_CFG) && (XBee_I2C_WAKE_ENABLE_CONST) */

#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: XBee_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void XBee_Wakeup(void)
{
#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)

    if(XBee_SCB_WAKE_ENABLE_CHECK)
    {
        if(XBee_SCB_MODE_I2C_RUNTM_CFG)
        {
            XBee_I2CRestoreConfig();
        }
        else if(XBee_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            XBee_EzI2CRestoreConfig();
        }
    #if(!XBee_CY_SCBIP_V1)
        else if(XBee_SCB_MODE_SPI_RUNTM_CFG)
        {
            XBee_SpiRestoreConfig();
        }
        else if(XBee_SCB_MODE_UART_RUNTM_CFG)
        {
            XBee_UartRestoreConfig();
        }
    #endif /* (!XBee_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != XBee_backup.enableState)
        {
            XBee_Enable();
        }
    }

#else

    #if (XBee_SCB_MODE_I2C_CONST_CFG  && XBee_I2C_WAKE_ENABLE_CONST)
        XBee_I2CRestoreConfig();

    #elif (XBee_SCB_MODE_EZI2C_CONST_CFG && XBee_EZI2C_WAKE_ENABLE_CONST)
        XBee_EzI2CRestoreConfig();

    #elif (XBee_SCB_MODE_SPI_CONST_CFG && XBee_SPI_WAKE_ENABLE_CONST)
        XBee_SpiRestoreConfig();

    #elif (XBee_SCB_MODE_UART_CONST_CFG && XBee_UART_WAKE_ENABLE_CONST)
        XBee_UartRestoreConfig();

    #else

        if(0u != XBee_backup.enableState)
        {
            XBee_Enable();
        }

    #endif /* (XBee_I2C_WAKE_ENABLE_CONST) */

#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
