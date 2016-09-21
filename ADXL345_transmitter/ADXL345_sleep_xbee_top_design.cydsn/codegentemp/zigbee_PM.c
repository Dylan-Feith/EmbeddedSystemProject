/*******************************************************************************
* File Name: zigbee_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "zigbee.h"


/***************************************
* Local data allocation
***************************************/

static zigbee_BACKUP_STRUCT  zigbee_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: zigbee_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the zigbee_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  zigbee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void zigbee_SaveConfig(void)
{
    #if(zigbee_CONTROL_REG_REMOVED == 0u)
        zigbee_backup.cr = zigbee_CONTROL_REG;
    #endif /* End zigbee_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: zigbee_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  zigbee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling zigbee_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void zigbee_RestoreConfig(void)
{
    #if(zigbee_CONTROL_REG_REMOVED == 0u)
        zigbee_CONTROL_REG = zigbee_backup.cr;
    #endif /* End zigbee_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: zigbee_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The zigbee_Sleep() API saves the current component state. Then it
*  calls the zigbee_Stop() function and calls 
*  zigbee_SaveConfig() to save the hardware configuration.
*  Call the zigbee_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  zigbee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void zigbee_Sleep(void)
{
    #if(zigbee_RX_ENABLED || zigbee_HD_ENABLED)
        if((zigbee_RXSTATUS_ACTL_REG  & zigbee_INT_ENABLE) != 0u)
        {
            zigbee_backup.enableState = 1u;
        }
        else
        {
            zigbee_backup.enableState = 0u;
        }
    #else
        if((zigbee_TXSTATUS_ACTL_REG  & zigbee_INT_ENABLE) !=0u)
        {
            zigbee_backup.enableState = 1u;
        }
        else
        {
            zigbee_backup.enableState = 0u;
        }
    #endif /* End zigbee_RX_ENABLED || zigbee_HD_ENABLED*/

    zigbee_Stop();
    zigbee_SaveConfig();
}


/*******************************************************************************
* Function Name: zigbee_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  zigbee_Sleep() was called. The zigbee_Wakeup() function
*  calls the zigbee_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  zigbee_Sleep() function was called, the zigbee_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  zigbee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void zigbee_Wakeup(void)
{
    zigbee_RestoreConfig();
    #if( (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) )
        zigbee_ClearRxBuffer();
    #endif /* End (zigbee_RX_ENABLED) || (zigbee_HD_ENABLED) */
    #if(zigbee_TX_ENABLED || zigbee_HD_ENABLED)
        zigbee_ClearTxBuffer();
    #endif /* End zigbee_TX_ENABLED || zigbee_HD_ENABLED */

    if(zigbee_backup.enableState != 0u)
    {
        zigbee_Enable();
    }
}


/* [] END OF FILE */
