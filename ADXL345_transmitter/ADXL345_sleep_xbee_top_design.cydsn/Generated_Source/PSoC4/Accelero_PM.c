/*******************************************************************************
* File Name: Accelero_PM.c
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

#include "Accelero.h"
#include "Accelero_PVT.h"

#if(Accelero_SCB_MODE_I2C_INC)
    #include "Accelero_I2C_PVT.h"
#endif /* (Accelero_SCB_MODE_I2C_INC) */

#if(Accelero_SCB_MODE_EZI2C_INC)
    #include "Accelero_EZI2C_PVT.h"
#endif /* (Accelero_SCB_MODE_EZI2C_INC) */

#if(Accelero_SCB_MODE_SPI_INC || Accelero_SCB_MODE_UART_INC)
    #include "Accelero_SPI_UART_PVT.h"
#endif /* (Accelero_SCB_MODE_SPI_INC || Accelero_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Accelero_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Accelero_SCB_MODE_I2C_CONST_CFG   && (!Accelero_I2C_WAKE_ENABLE_CONST))   || \
   (Accelero_SCB_MODE_EZI2C_CONST_CFG && (!Accelero_EZI2C_WAKE_ENABLE_CONST)) || \
   (Accelero_SCB_MODE_SPI_CONST_CFG   && (!Accelero_SPI_WAKE_ENABLE_CONST))   || \
   (Accelero_SCB_MODE_UART_CONST_CFG  && (!Accelero_UART_WAKE_ENABLE_CONST)))

    Accelero_BACKUP_STRUCT Accelero_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Accelero_Sleep
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
void Accelero_Sleep(void)
{
#if(Accelero_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Accelero_SCB_WAKE_ENABLE_CHECK)
    {
        if(Accelero_SCB_MODE_I2C_RUNTM_CFG)
        {
            Accelero_I2CSaveConfig();
        }
        else if(Accelero_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Accelero_EzI2CSaveConfig();
        }
    #if(!Accelero_CY_SCBIP_V1)
        else if(Accelero_SCB_MODE_SPI_RUNTM_CFG)
        {
            Accelero_SpiSaveConfig();
        }
        else if(Accelero_SCB_MODE_UART_RUNTM_CFG)
        {
            Accelero_UartSaveConfig();
        }
    #endif /* (!Accelero_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Accelero_backup.enableState = (uint8) Accelero_GET_CTRL_ENABLED;

        if(0u != Accelero_backup.enableState)
        {
            Accelero_Stop();
        }
    }

#else

    #if (Accelero_SCB_MODE_I2C_CONST_CFG && Accelero_I2C_WAKE_ENABLE_CONST)
        Accelero_I2CSaveConfig();

    #elif (Accelero_SCB_MODE_EZI2C_CONST_CFG && Accelero_EZI2C_WAKE_ENABLE_CONST)
        Accelero_EzI2CSaveConfig();

    #elif (Accelero_SCB_MODE_SPI_CONST_CFG && Accelero_SPI_WAKE_ENABLE_CONST)
        Accelero_SpiSaveConfig();

    #elif (Accelero_SCB_MODE_UART_CONST_CFG && Accelero_UART_WAKE_ENABLE_CONST)
        Accelero_UartSaveConfig();

    #else

        Accelero_backup.enableState = (uint8) Accelero_GET_CTRL_ENABLED;

        if(0u != Accelero_backup.enableState)
        {
            Accelero_Stop();
        }

    #endif /* defined (Accelero_SCB_MODE_I2C_CONST_CFG) && (Accelero_I2C_WAKE_ENABLE_CONST) */

#endif /* (Accelero_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Accelero_Wakeup
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
void Accelero_Wakeup(void)
{
#if(Accelero_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Accelero_SCB_WAKE_ENABLE_CHECK)
    {
        if(Accelero_SCB_MODE_I2C_RUNTM_CFG)
        {
            Accelero_I2CRestoreConfig();
        }
        else if(Accelero_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Accelero_EzI2CRestoreConfig();
        }
    #if(!Accelero_CY_SCBIP_V1)
        else if(Accelero_SCB_MODE_SPI_RUNTM_CFG)
        {
            Accelero_SpiRestoreConfig();
        }
        else if(Accelero_SCB_MODE_UART_RUNTM_CFG)
        {
            Accelero_UartRestoreConfig();
        }
    #endif /* (!Accelero_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Accelero_backup.enableState)
        {
            Accelero_Enable();
        }
    }

#else

    #if (Accelero_SCB_MODE_I2C_CONST_CFG  && Accelero_I2C_WAKE_ENABLE_CONST)
        Accelero_I2CRestoreConfig();

    #elif (Accelero_SCB_MODE_EZI2C_CONST_CFG && Accelero_EZI2C_WAKE_ENABLE_CONST)
        Accelero_EzI2CRestoreConfig();

    #elif (Accelero_SCB_MODE_SPI_CONST_CFG && Accelero_SPI_WAKE_ENABLE_CONST)
        Accelero_SpiRestoreConfig();

    #elif (Accelero_SCB_MODE_UART_CONST_CFG && Accelero_UART_WAKE_ENABLE_CONST)
        Accelero_UartRestoreConfig();

    #else

        if(0u != Accelero_backup.enableState)
        {
            Accelero_Enable();
        }

    #endif /* (Accelero_I2C_WAKE_ENABLE_CONST) */

#endif /* (Accelero_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
