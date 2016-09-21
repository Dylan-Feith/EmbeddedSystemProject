/*******************************************************************************
* File Name: Accelero_I2C_BOOT.c
* Version 3.0
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component I2C mode.

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
#include "Accelero_I2C_PVT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_I2C_BTLDR_COMM_ENABLED)

/***************************************
*    Private I/O Component Vars
***************************************/

/* Writes to this buffer */
static uint8 Accelero_slReadBuf[Accelero_I2C_BTLDR_SIZEOF_READ_BUFFER];

/* Reads from this buffer */
static uint8 Accelero_slWriteBuf[Accelero_I2C_BTLDR_SIZEOF_WRITE_BUFFER];

/* Flag to release buffer to be read */
static uint32 Accelero_applyBuffer;


/***************************************
*    Private Function Prototypes
***************************************/

static void Accelero_I2CResposeInsert(void);


/*******************************************************************************
* Function Name: Accelero_I2CCyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the I2C component and enables its interrupt.
*  Every incoming I2C write transaction is treated as a command for the
*  bootloader.
*  Every incoming I2C read transaction returns 0xFF until the bootloader
*  provides a response to the executed command.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Accelero_I2CCyBtldrCommStart(void)
{
    Accelero_I2CSlaveInitWriteBuf(Accelero_slWriteBuf, Accelero_I2C_BTLDR_SIZEOF_WRITE_BUFFER);
    Accelero_I2CSlaveInitReadBuf (Accelero_slReadBuf, 0u);

    Accelero_SetCustomInterruptHandler(&Accelero_I2CResposeInsert);
    Accelero_applyBuffer = 0u;

    Accelero_Start();
}


/*******************************************************************************
* Function Name: Accelero_I2CCyBtldrCommStop
********************************************************************************
*
* Summary:
*  Disables the I2C component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Accelero_I2CCyBtldrCommStop(void)
{
    Accelero_Stop();
}


/*******************************************************************************
* Function Name: Accelero_I2CCyBtldrCommReset
********************************************************************************
*
* Summary:
*  Resets read and write I2C buffers to the initial state and resets the slave
*  status.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Refer to functions below for global variables description.
*
*******************************************************************************/
void Accelero_I2CCyBtldrCommReset(void)
{
    /* Make read buffer full */
    Accelero_slRdBufSize = 0u;

    /* Reset write buffer and Read buffer */
    Accelero_slRdBufIndex = 0u;
    Accelero_slWrBufIndex = 0u;

    /* Clear read and write status */
    Accelero_slStatus = 0u;
}


/*******************************************************************************
* Function Name: Accelero_I2CCyBtldrCommRead
********************************************************************************
*
* Summary:
*  Allows the caller to read data from the bootloader host (the host writes the
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
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
*  that best describes the problem. For more information refer to the
*  "Return Codes" section of the System Reference Guide.
*
* Global variables:
*  Accelero_slWriteBuf - used to store received command.
*  Accelero_slWrBufIndex - used to store current index within slave
*  write buffer.
*
*******************************************************************************/
cystatus Accelero_I2CCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    uint32 timeoutMs;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint32) 10u * timeOut); /* Convert from 10mS check to 1mS checks */

        while (0u != timeoutMs)
        {
            /* Check if host complete write */
            if (0u != (Accelero_I2C_SSTAT_WR_CMPLT & Accelero_slStatus))
            {
                /* Copy number of written bytes */
                *count = (uint16) Accelero_slWrBufIndex;

                /* Clear slave status and write index */
                Accelero_slStatus = 0u;
                Accelero_slWrBufIndex = 0u;

                /* Copy command into bootloader buffer */
                (void) memcpy((void *) pData, (const void *) Accelero_slWriteBuf,
                                              Accelero_BYTES_TO_COPY(*count, size));

                status = CYRET_SUCCESS;
                break;
            }

            CyDelay(Accelero_WAIT_1_MS);
            --timeoutMs;
        }
    }

    return(status);
}


/*******************************************************************************
* Function Name: Accelero_I2CCyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the bootloader host (the host reads the
*  data). The function does not use timeout and returns after data has been
*  copied into the slave read buffer. This data is available to be read by the
*  bootloader host until following host data write.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  The timeout is not used by this function. The function returns
*            as soon as data is copied into the slave read buffer.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem. For more information refer to the
*  "Return Codes" section of the System Reference Guide.
*
* Global variables:
*  Accelero_slReadBuf - used to store response.
*
*******************************************************************************/
cystatus Accelero_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    if ((NULL != pData) && (size > 0u))
    {
        /* Copy response into read buffer */
        *count = size;
        (void) memcpy((void *) Accelero_slReadBuf, (const void *) pData, (uint32) size);

        /* Read buffer is ready to be released to host */
        Accelero_applyBuffer = (uint32) size;

        if (0u != timeOut)
        {
            /* Suppress compiler warning */
        }

        status = CYRET_SUCCESS;
    }

    return(status);
}


/*******************************************************************************
* Function Name: Accelero_I2CResposeInsert
********************************************************************************
*
* Summary:
*  Releases the read buffer to be read when a response is copied to the buffer
*  and a new read transaction starts.
*  Closes the read buffer when write transaction is started.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Accelero_slRdBufSize - used to store slave read buffer size.
*  Accelero_slRdBufIndex - used to store the current index within the
*  slave read buffer.
*  Accelero_applyBuffer - the flag to release the buffer with
*  a response to read.
*
*******************************************************************************/
static void Accelero_I2CResposeInsert(void)
{
    if (Accelero_CHECK_INTR_SLAVE_MASKED(Accelero_INTR_SLAVE_I2C_ADDR_MATCH))
    {
        if (Accelero_CHECK_I2C_STATUS(Accelero_I2C_STATUS_S_READ))
        {
            /* Address phase, host reads: release read buffer */
            if (0u != Accelero_applyBuffer)
            {
                Accelero_slRdBufSize  = Accelero_applyBuffer;
                Accelero_slRdBufIndex = 0u;
                Accelero_applyBuffer  = 0u;
            }
        }
        else
        {
            /* Address phase, host writes: close read buffer */
            if (Accelero_slRdBufIndex != Accelero_slRdBufSize)
            {
                Accelero_slRdBufIndex = Accelero_slRdBufSize;
            }
        }
    }
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Accelero_I2C_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
