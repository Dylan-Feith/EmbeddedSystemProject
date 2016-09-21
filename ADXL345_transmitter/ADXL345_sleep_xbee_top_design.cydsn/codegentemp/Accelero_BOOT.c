/*******************************************************************************
* File Name: Accelero_BOOT.c
* Version 3.0
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Accelero_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_BTLDR_COMM_ENABLED) && \
                                (Accelero_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: Accelero_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Accelero_CyBtldrCommStart(void)
{
    if (Accelero_SCB_MODE_I2C_RUNTM_CFG)
    {
        Accelero_I2CCyBtldrCommStart();
    }
    else if (Accelero_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Accelero_EzI2CCyBtldrCommStart();
    }
#if (!Accelero_CY_SCBIP_V1)
    else if (Accelero_SCB_MODE_SPI_RUNTM_CFG)
    {
        Accelero_SpiCyBtldrCommStart();
    }
    else if (Accelero_SCB_MODE_UART_RUNTM_CFG)
    {
        Accelero_UartCyBtldrCommStart();
    }
#endif /* (!Accelero_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: Accelero_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Accelero_CyBtldrCommStop(void)
{
    if (Accelero_SCB_MODE_I2C_RUNTM_CFG)
    {
        Accelero_I2CCyBtldrCommStop();
    }
    else if (Accelero_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Accelero_EzI2CCyBtldrCommStop();
    }
#if (!Accelero_CY_SCBIP_V1)
    else if (Accelero_SCB_MODE_SPI_RUNTM_CFG)
    {
        Accelero_SpiCyBtldrCommStop();
    }
    else if (Accelero_SCB_MODE_UART_RUNTM_CFG)
    {
        Accelero_UartCyBtldrCommStop();
    }
#endif /* (!Accelero_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: Accelero_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Accelero_CyBtldrCommReset(void)
{
    if(Accelero_SCB_MODE_I2C_RUNTM_CFG)
    {
        Accelero_I2CCyBtldrCommReset();
    }
    else if(Accelero_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Accelero_EzI2CCyBtldrCommReset();
    }
#if (!Accelero_CY_SCBIP_V1)
    else if(Accelero_SCB_MODE_SPI_RUNTM_CFG)
    {
        Accelero_SpiCyBtldrCommReset();
    }
    else if(Accelero_SCB_MODE_UART_RUNTM_CFG)
    {
        Accelero_UartCyBtldrCommReset();
    }
#endif /* (!Accelero_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: Accelero_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus Accelero_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(Accelero_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = Accelero_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(Accelero_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = Accelero_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!Accelero_CY_SCBIP_V1)
    else if(Accelero_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = Accelero_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(Accelero_SCB_MODE_UART_RUNTM_CFG)
    {
        status = Accelero_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!Accelero_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: Accelero_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus Accelero_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(Accelero_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = Accelero_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(Accelero_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = Accelero_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!Accelero_CY_SCBIP_V1)
    else if(Accelero_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = Accelero_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(Accelero_SCB_MODE_UART_RUNTM_CFG)
    {
        status = Accelero_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!Accelero_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
