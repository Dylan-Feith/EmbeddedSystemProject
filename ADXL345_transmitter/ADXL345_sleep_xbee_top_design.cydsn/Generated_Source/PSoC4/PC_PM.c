/*******************************************************************************
* File Name: PC_PM.c
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

#include "PC.h"
#include "PC_PVT.h"

#if(PC_SCB_MODE_I2C_INC)
    #include "PC_I2C_PVT.h"
#endif /* (PC_SCB_MODE_I2C_INC) */

#if(PC_SCB_MODE_EZI2C_INC)
    #include "PC_EZI2C_PVT.h"
#endif /* (PC_SCB_MODE_EZI2C_INC) */

#if(PC_SCB_MODE_SPI_INC || PC_SCB_MODE_UART_INC)
    #include "PC_SPI_UART_PVT.h"
#endif /* (PC_SCB_MODE_SPI_INC || PC_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(PC_SCB_MODE_UNCONFIG_CONST_CFG || \
   (PC_SCB_MODE_I2C_CONST_CFG   && (!PC_I2C_WAKE_ENABLE_CONST))   || \
   (PC_SCB_MODE_EZI2C_CONST_CFG && (!PC_EZI2C_WAKE_ENABLE_CONST)) || \
   (PC_SCB_MODE_SPI_CONST_CFG   && (!PC_SPI_WAKE_ENABLE_CONST))   || \
   (PC_SCB_MODE_UART_CONST_CFG  && (!PC_UART_WAKE_ENABLE_CONST)))

    PC_BACKUP_STRUCT PC_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: PC_Sleep
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
void PC_Sleep(void)
{
#if(PC_SCB_MODE_UNCONFIG_CONST_CFG)

    if(PC_SCB_WAKE_ENABLE_CHECK)
    {
        if(PC_SCB_MODE_I2C_RUNTM_CFG)
        {
            PC_I2CSaveConfig();
        }
        else if(PC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            PC_EzI2CSaveConfig();
        }
    #if(!PC_CY_SCBIP_V1)
        else if(PC_SCB_MODE_SPI_RUNTM_CFG)
        {
            PC_SpiSaveConfig();
        }
        else if(PC_SCB_MODE_UART_RUNTM_CFG)
        {
            PC_UartSaveConfig();
        }
    #endif /* (!PC_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        PC_backup.enableState = (uint8) PC_GET_CTRL_ENABLED;

        if(0u != PC_backup.enableState)
        {
            PC_Stop();
        }
    }

#else

    #if (PC_SCB_MODE_I2C_CONST_CFG && PC_I2C_WAKE_ENABLE_CONST)
        PC_I2CSaveConfig();

    #elif (PC_SCB_MODE_EZI2C_CONST_CFG && PC_EZI2C_WAKE_ENABLE_CONST)
        PC_EzI2CSaveConfig();

    #elif (PC_SCB_MODE_SPI_CONST_CFG && PC_SPI_WAKE_ENABLE_CONST)
        PC_SpiSaveConfig();

    #elif (PC_SCB_MODE_UART_CONST_CFG && PC_UART_WAKE_ENABLE_CONST)
        PC_UartSaveConfig();

    #else

        PC_backup.enableState = (uint8) PC_GET_CTRL_ENABLED;

        if(0u != PC_backup.enableState)
        {
            PC_Stop();
        }

    #endif /* defined (PC_SCB_MODE_I2C_CONST_CFG) && (PC_I2C_WAKE_ENABLE_CONST) */

#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: PC_Wakeup
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
void PC_Wakeup(void)
{
#if(PC_SCB_MODE_UNCONFIG_CONST_CFG)

    if(PC_SCB_WAKE_ENABLE_CHECK)
    {
        if(PC_SCB_MODE_I2C_RUNTM_CFG)
        {
            PC_I2CRestoreConfig();
        }
        else if(PC_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            PC_EzI2CRestoreConfig();
        }
    #if(!PC_CY_SCBIP_V1)
        else if(PC_SCB_MODE_SPI_RUNTM_CFG)
        {
            PC_SpiRestoreConfig();
        }
        else if(PC_SCB_MODE_UART_RUNTM_CFG)
        {
            PC_UartRestoreConfig();
        }
    #endif /* (!PC_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != PC_backup.enableState)
        {
            PC_Enable();
        }
    }

#else

    #if (PC_SCB_MODE_I2C_CONST_CFG  && PC_I2C_WAKE_ENABLE_CONST)
        PC_I2CRestoreConfig();

    #elif (PC_SCB_MODE_EZI2C_CONST_CFG && PC_EZI2C_WAKE_ENABLE_CONST)
        PC_EzI2CRestoreConfig();

    #elif (PC_SCB_MODE_SPI_CONST_CFG && PC_SPI_WAKE_ENABLE_CONST)
        PC_SpiRestoreConfig();

    #elif (PC_SCB_MODE_UART_CONST_CFG && PC_UART_WAKE_ENABLE_CONST)
        PC_UartRestoreConfig();

    #else

        if(0u != PC_backup.enableState)
        {
            PC_Enable();
        }

    #endif /* (PC_I2C_WAKE_ENABLE_CONST) */

#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
