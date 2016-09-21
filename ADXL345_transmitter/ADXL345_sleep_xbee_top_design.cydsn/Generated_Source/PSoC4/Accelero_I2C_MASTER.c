/*******************************************************************************
* File Name: Accelero_I2C_MASTER.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C Master mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Accelero_PVT.h"
#include "Accelero_I2C_PVT.h"

#if(Accelero_I2C_MASTER_CONST)

/***************************************
*      I2C Master Private Vars
***************************************/

/* Master variables */
volatile uint16 Accelero_mstrStatus;      /* Master Status byte  */
volatile uint8  Accelero_mstrControl;     /* Master Control byte */

/* Receive buffer variables */
volatile uint8 * Accelero_mstrRdBufPtr;   /* Pointer to Master Read buffer */
volatile uint32  Accelero_mstrRdBufSize;  /* Master Read buffer size       */
volatile uint32  Accelero_mstrRdBufIndex; /* Master Read buffer Index      */

/* Transmit buffer variables */
volatile uint8 * Accelero_mstrWrBufPtr;   /* Pointer to Master Write buffer */
volatile uint32  Accelero_mstrWrBufSize;  /* Master Write buffer size       */
volatile uint32  Accelero_mstrWrBufIndex; /* Master Write buffer Index      */
volatile uint32  Accelero_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */

#if (!Accelero_CY_SCBIP_V0 && \
    Accelero_I2C_MULTI_MASTER_SLAVE_CONST && Accelero_I2C_WAKE_ENABLE_CONST)
    static void Accelero_I2CMasterDisableEcAm(void);
#endif /* (!Accelero_CY_SCBIP_V0) */


/*******************************************************************************
* Function Name: Accelero_I2CMasterWriteBuf
********************************************************************************
*
* Summary:
* Automatically writes an entire buffer of data to a slave device.
* Once the data transfer is initiated by this function, further data transfer
* is handled by the included ISR.
* Enables the I2C interrupt and clears SCB_ I2C_MSTAT_WR_CMPLT status.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer of data to be sent.
*  cnt:       Size of buffer to send.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Error status.
*
* Global variables:
*  Accelero_mstrStatus  - used to store current status of I2C Master.
*  Accelero_state       - used to store current state of software FSM.
*  Accelero_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  Accelero_mstrWrBufPtr - used to store pointer to master write buffer.
*  Accelero_mstrWrBufIndex - used to current index within master write
*  buffer.
*  Accelero_mstrWrBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 Accelero_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = Accelero_I2C_MSTR_NOT_READY;

    if(NULL != wrData)  /* Check buffer pointer */
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(Accelero_CHECK_I2C_FSM_IDLE)
        {
            Accelero_DisableInt();  /* Lock from interruption */

            /* Check bus state */
            errStatus = Accelero_CHECK_I2C_STATUS(Accelero_I2C_STATUS_BUS_BUSY) ?
                            Accelero_I2C_MSTR_BUS_BUSY : Accelero_I2C_MSTR_NO_ERROR;
        }
        else if(Accelero_CHECK_I2C_FSM_HALT)
        {
            Accelero_mstrStatus &= (uint16) ~Accelero_I2C_MSTAT_XFER_HALT;
                              errStatus  = Accelero_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check if master is ready to start  */
    if(Accelero_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
    #if (!Accelero_CY_SCBIP_V0 && \
        Accelero_I2C_MULTI_MASTER_SLAVE_CONST && Accelero_I2C_WAKE_ENABLE_CONST)
            Accelero_I2CMasterDisableEcAm();
    #endif /* (!Accelero_CY_SCBIP_V0) */

        /* Set up write transaction */
        Accelero_state = Accelero_I2C_FSM_MSTR_WR_ADDR;
        Accelero_mstrWrBufIndexTmp = 0u;
        Accelero_mstrWrBufIndex    = 0u;
        Accelero_mstrWrBufSize     = cnt;
        Accelero_mstrWrBufPtr      = (volatile uint8 *) wrData;
        Accelero_mstrControl       = (uint8) mode;

        slaveAddress = Accelero_GET_I2C_8BIT_ADDRESS(slaveAddress);

        Accelero_mstrStatus &= (uint16) ~Accelero_I2C_MSTAT_WR_CMPLT;

        Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_ALL);
        Accelero_ClearTxInterruptSource(Accelero_INTR_TX_UNDERFLOW);

        /* The TX and RX FIFO have to be EMPTY */

        /* Enable interrupt source to catch when address is sent */
        Accelero_SetTxInterruptMode(Accelero_INTR_TX_UNDERFLOW);

        /* Generate Start or ReStart */
        if(Accelero_CHECK_I2C_MODE_RESTART(mode))
        {
            Accelero_I2C_MASTER_GENERATE_RESTART;
            Accelero_TX_FIFO_WR_REG = slaveAddress;
        }
        else
        {
            Accelero_TX_FIFO_WR_REG = slaveAddress;
            Accelero_I2C_MASTER_GENERATE_START;
        }
    }

    Accelero_EnableInt();   /* Release lock */

    return(errStatus);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterReadBuf
********************************************************************************
*
* Summary:
*  Automatically reads an entire buffer of data from a slave device.
*  Once the data transfer is initiated by this function, further data transfer
*  is handled by the included ISR.
* Enables the I2C interrupt and clears SCB_ I2C_MSTAT_RD_CMPLT status.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer where to put data from slave.
*  cnt:       Size of buffer to read.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Error status.
*
* Global variables:
*  Accelero_mstrStatus  - used to store current status of I2C Master.
*  Accelero_state       - used to store current state of software FSM.
*  Accelero_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  Accelero_mstrRdBufPtr - used to store pointer to master write buffer.
*  Accelero_mstrRdBufIndex - used to current index within master write
*  buffer.
*  Accelero_mstrRdBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 Accelero_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = Accelero_I2C_MSTR_NOT_READY;

    if(NULL != rdData)
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(Accelero_CHECK_I2C_FSM_IDLE)
        {
            Accelero_DisableInt();  /* Lock from interruption */

            /* Check bus state */
            errStatus = Accelero_CHECK_I2C_STATUS(Accelero_I2C_STATUS_BUS_BUSY) ?
                            Accelero_I2C_MSTR_BUS_BUSY : Accelero_I2C_MSTR_NO_ERROR;
        }
        else if(Accelero_CHECK_I2C_FSM_HALT)
        {
            Accelero_mstrStatus &= (uint16) ~Accelero_I2C_MSTAT_XFER_HALT;
                              errStatus  =  Accelero_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check master ready to proceed */
    if(Accelero_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
        #if (!Accelero_CY_SCBIP_V0 && \
        Accelero_I2C_MULTI_MASTER_SLAVE_CONST && Accelero_I2C_WAKE_ENABLE_CONST)
            Accelero_I2CMasterDisableEcAm();
        #endif /* (!Accelero_CY_SCBIP_V0) */

        /* Set up read transaction */
        Accelero_state = Accelero_I2C_FSM_MSTR_RD_ADDR;
        Accelero_mstrRdBufIndex = 0u;
        Accelero_mstrRdBufSize  = cnt;
        Accelero_mstrRdBufPtr   = (volatile uint8 *) rdData;
        Accelero_mstrControl    = (uint8) mode;

        slaveAddress = (Accelero_GET_I2C_8BIT_ADDRESS(slaveAddress) | Accelero_I2C_READ_FLAG);

        Accelero_mstrStatus &= (uint16) ~Accelero_I2C_MSTAT_RD_CMPLT;

        Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_ALL);

        /* TX and RX FIFO have to be EMPTY */

        /* Prepare reading */
        if(Accelero_mstrRdBufSize < Accelero_I2C_FIFO_SIZE)
        {
            /* Reading byte-by-byte */
            Accelero_SetRxInterruptMode(Accelero_INTR_RX_NOT_EMPTY);
        }
        else
        {
            /* Receive RX FIFO chunks */
            Accelero_ENABLE_MASTER_AUTO_DATA_ACK;
            Accelero_SetRxInterruptMode(Accelero_INTR_RX_FULL);
        }

        /* Generate Start or ReStart */
        if(Accelero_CHECK_I2C_MODE_RESTART(mode))
        {
            Accelero_I2C_MASTER_GENERATE_RESTART;
            Accelero_TX_FIFO_WR_REG = (slaveAddress);
        }
        else
        {
            Accelero_TX_FIFO_WR_REG = (slaveAddress);
            Accelero_I2C_MASTER_GENERATE_START;
        }
    }

    Accelero_EnableInt();   /* Release lock */

    return(errStatus);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterSendStart
********************************************************************************
*
* Summary:
*  Generates Start condition and sends slave address with read/write bit.
*  Disables the I2C interrupt.
*  This function is blocking and does not return until start condition and
*  address byte are sent and ACK/NACK response is received or errors occurred.
*
* Parameters:
*  slaveAddress: Right justified 7-bit Slave address (valid range 8 to 120).
*  bitRnW:       Direction of the following transfer. It is defined by
*                read/write bit within address byte.
*
* Return:
*  Error status.
*
* Global variables:
*  Accelero_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 Accelero_I2CMasterSendStart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32  resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = Accelero_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Start condition */
    if(Accelero_CHECK_I2C_FSM_IDLE)
    {
        /* If bus is free, generate Start condition */
        if(Accelero_CHECK_I2C_STATUS(Accelero_I2C_STATUS_BUS_BUSY))
        {
            errStatus = Accelero_I2C_MSTR_BUS_BUSY;
        }
        else
        {
            Accelero_DisableInt();  /* Lock from interruption */

        #if (!Accelero_CY_SCBIP_V0 && \
            Accelero_I2C_MULTI_MASTER_SLAVE_CONST && Accelero_I2C_WAKE_ENABLE_CONST)
            Accelero_I2CMasterDisableEcAm();
        #endif /* (!Accelero_CY_SCBIP_V0) */

            slaveAddress = Accelero_GET_I2C_8BIT_ADDRESS(slaveAddress);

            if(0u == bitRnW) /* Write direction */
            {
                Accelero_state = Accelero_I2C_FSM_MSTR_WR_DATA;
            }
            else /* Read direction */
            {
                Accelero_state = Accelero_I2C_FSM_MSTR_RD_DATA;
                         slaveAddress |= Accelero_I2C_READ_FLAG;
            }

            /* TX and RX FIFO have to be EMPTY */

            Accelero_TX_FIFO_WR_REG = slaveAddress; /* Put address in TX FIFO */
            Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_ALL);

            Accelero_I2C_MASTER_GENERATE_START;


            while(!Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ACK      |
                                                      Accelero_INTR_MASTER_I2C_NACK     |
                                                      Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                      Accelero_INTR_MASTER_I2C_BUS_ERROR))
            {
                /*
                * Write: wait until address has been transferred
                * Read : wait until address has been transferred, data byte is going to RX FIFO as well.
                */
            }

            /* Check the results of the address phase */
            if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ACK))
            {
                errStatus = Accelero_I2C_MSTR_NO_ERROR;
            }
            else if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_NACK))
            {
                errStatus = Accelero_I2C_MSTR_ERR_LB_NAK;
            }
            else if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ARB_LOST))
            {
                Accelero_state = Accelero_I2C_FSM_IDLE;
                             errStatus = Accelero_I2C_MSTR_ERR_ARB_LOST;
                             resetIp   = Accelero_I2C_RESET_ERROR;
            }
            else /* Accelero_INTR_MASTER_I2C_BUS_ERROR set is else condition */
            {
                Accelero_state = Accelero_I2C_FSM_IDLE;
                             errStatus = Accelero_I2C_MSTR_ERR_BUS_ERR;
                             resetIp   = Accelero_I2C_RESET_ERROR;
            }

            Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_I2C_ACK      |
                                                        Accelero_INTR_MASTER_I2C_NACK     |
                                                        Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                        Accelero_INTR_MASTER_I2C_BUS_ERROR);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            if(0u != resetIp)
            {
                Accelero_SCB_SW_RESET;
            }
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterSendRestart
********************************************************************************
*
* Summary:
*  Generates Restart condition and sends slave address with read/write bit.
*  This function is blocking and does not return until start condition and
*  address are sent and ACK/NACK response is received or errors occurred.
*
* Parameters:
*  slaveAddress: Right justified 7-bit Slave address (valid range 8 to 120).
*  bitRnW:       Direction of the following transfer. It is defined by
*                read/write bit within address byte.
*
* Return:
*  Error status
*
*
* Global variables:
*  Accelero_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 Accelero_I2CMasterSendRestart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = Accelero_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating ReStart condition */
    if(Accelero_CHECK_I2C_MASTER_ACTIVE)
    {
        slaveAddress = Accelero_GET_I2C_8BIT_ADDRESS(slaveAddress);

        if(0u == bitRnW) /* Write direction */
        {
            Accelero_state = Accelero_I2C_FSM_MSTR_WR_DATA;
        }
        else  /* Read direction */
        {
            Accelero_state  = Accelero_I2C_FSM_MSTR_RD_DATA;
                      slaveAddress |= Accelero_I2C_READ_FLAG;
        }

        /* TX and RX FIFO have to be EMPTY */

        /* Clean-up interrupt status */
        Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_ALL);

        /* A proper ReStart sequence is: generate ReStart, then put an address byte in the TX FIFO.
        * Otherwise the master treats the address in the TX FIFO as a data byte if a previous transfer is write.
        * The write transfer continues instead of ReStart.
        */
        Accelero_I2C_MASTER_GENERATE_RESTART;

        while(Accelero_CHECK_I2C_MASTER_CMD(Accelero_I2C_MASTER_CMD_M_START))
        {
            /* Wait until ReStart has been generated */
        }

        /* Put address into TX FIFO */
        Accelero_TX_FIFO_WR_REG = slaveAddress;

        /* Wait for address to be transferred */
        while(!Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ACK      |
                                                  Accelero_INTR_MASTER_I2C_NACK     |
                                                  Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                  Accelero_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until address has been transferred */
        }

        /* Check results of address phase */
        if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ACK))
        {
            errStatus = Accelero_I2C_MSTR_NO_ERROR;
        }
        else if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_NACK))
        {
             errStatus = Accelero_I2C_MSTR_ERR_LB_NAK;
        }
        else if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ARB_LOST))
        {
            Accelero_state = Accelero_I2C_FSM_IDLE;
                         errStatus = Accelero_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = Accelero_I2C_RESET_ERROR;
        }
        else /* Accelero_INTR_MASTER_I2C_BUS_ERROR set is else condition */
        {
            Accelero_state = Accelero_I2C_FSM_IDLE;
                         errStatus = Accelero_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = Accelero_I2C_RESET_ERROR;
        }

        Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_I2C_ACK      |
                                                    Accelero_INTR_MASTER_I2C_NACK     |
                                                    Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                    Accelero_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            Accelero_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterSendStop
********************************************************************************
*
* Summary:
*  Generates Stop condition on the bus.
*  At least one byte has to be read if start or restart condition with read
*  direction was generated before.
*  This function is blocking and does not return until a stop condition
*  is generated or error occurred.
*
* Parameters:
*  None
*
* Return:
*  Error status
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*  For read transfer, at least one byte has to be read before Stop generation.
*
* Global variables:
*  Accelero_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 Accelero_I2CMasterSendStop(void)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = Accelero_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Stop condition */
    if(Accelero_CHECK_I2C_MASTER_ACTIVE)
    {
        /*
        * Write direction: generates Stop
        * Read  direction: generates NACK and Stop
        */
        Accelero_I2C_MASTER_GENERATE_STOP;

        while(!Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_STOP     |
                                                  Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                  Accelero_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until Stop has been generated */
        }

        /* Check Stop generation */
        if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_STOP))
        {
            errStatus = Accelero_I2C_MSTR_NO_ERROR;
        }
        else if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ARB_LOST))
        {
            errStatus = Accelero_I2C_MSTR_ERR_ARB_LOST;
            resetIp   = Accelero_I2C_RESET_ERROR;
        }
        else /* Accelero_INTR_MASTER_I2C_BUS_ERROR is set */
        {
            errStatus = Accelero_I2C_MSTR_ERR_BUS_ERR;
            resetIp   = Accelero_I2C_RESET_ERROR;
        }

        Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_I2C_STOP     |
                                                    Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                    Accelero_INTR_MASTER_I2C_BUS_ERROR);

        Accelero_state = Accelero_I2C_FSM_IDLE;

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            Accelero_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterWriteByte
********************************************************************************
*
* Summary:
*  Sends one byte to a slave.
*  This function is blocking and does not return until byte is transmitted
*  or error occurred.
*
* Parameters:
*  data: The data byte to send to the slave.
*
* Return:
*  Error status
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*
* Global variables:
*  Accelero_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 Accelero_I2CMasterWriteByte(uint32 theByte)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = Accelero_I2C_MSTR_NOT_READY;

    /* Check FSM state before write byte */
    if(Accelero_CHECK_I2C_MASTER_ACTIVE)
    {
        Accelero_TX_FIFO_WR_REG = theByte;

        while(!Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ACK      |
                                                  Accelero_INTR_MASTER_I2C_NACK     |
                                                  Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                  Accelero_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until byte has been transferred */
        }

        /* Check results after byte was sent */
        if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ACK))
        {
            Accelero_state = Accelero_I2C_FSM_MSTR_HALT;
                         errStatus = Accelero_I2C_MSTR_NO_ERROR;
        }
        else if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_NACK))
        {
            Accelero_state = Accelero_I2C_FSM_MSTR_HALT;
                         errStatus = Accelero_I2C_MSTR_ERR_LB_NAK;
        }
        else if(Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ARB_LOST))
        {
            Accelero_state = Accelero_I2C_FSM_IDLE;
                         errStatus = Accelero_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = Accelero_I2C_RESET_ERROR;
        }
        else /* Accelero_INTR_MASTER_I2C_BUS_ERROR set is */
        {
            Accelero_state = Accelero_I2C_FSM_IDLE;
                         errStatus = Accelero_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = Accelero_I2C_RESET_ERROR;
        }

        Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_I2C_ACK      |
                                                    Accelero_INTR_MASTER_I2C_NACK     |
                                                    Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                    Accelero_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            Accelero_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterReadByte
********************************************************************************
*
* Summary:
*  Reads one byte from a slave and ACKs or NAKs received byte.
*  This function does not generate NAK explicitly. The following call
*  SCB_I2CMasterSendStop() or SCB_I2CMasterSendRestart() will generate NAK and
*  Stop or ReStart condition appropriately.
*  This function is blocking and does not return until byte is received
*  or error occurred.
*
* Parameters:
*  ackNack: Response to received byte.
*
* Return:
*  Byte read from the slave. In case of error the MSB of returned data
*  is set to 1.
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling this
*  function. This function does nothing and returns invalid byte value
*  if Start or ReStart conditions failed before this function was called.
*
* Global variables:
*  Accelero_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 Accelero_I2CMasterReadByte(uint32 ackNack)
{
    uint32 theByte;

    /* Return invalid byte in case BUS_ERR happen during receiving */
    theByte = Accelero_I2C_INVALID_BYTE;

    /* Check FSM state before read byte */
    if(Accelero_CHECK_I2C_MASTER_ACTIVE)
    {
        while((!Accelero_CHECK_INTR_RX(Accelero_INTR_RX_NOT_EMPTY)) &&
              (!Accelero_CHECK_INTR_MASTER(Accelero_INTR_MASTER_I2C_ARB_LOST |
                                                  Accelero_INTR_MASTER_I2C_BUS_ERROR)))
        {
            /* Wait until byte has been received */
        }

        /* Check the results after the byte was sent */
        if(Accelero_CHECK_INTR_RX(Accelero_INTR_RX_NOT_EMPTY))
        {
            theByte = Accelero_RX_FIFO_RD_REG;

            Accelero_ClearRxInterruptSource(Accelero_INTR_RX_NOT_EMPTY);

            if(0u == ackNack)
            {
                Accelero_I2C_MASTER_GENERATE_ACK;
            }
            else
            {
                /* NACK is generated by Stop or ReStart command */
                Accelero_state = Accelero_I2C_FSM_MSTR_HALT;
            }
        }
        else
        {
            Accelero_ClearMasterInterruptSource(Accelero_INTR_MASTER_ALL);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            Accelero_SCB_SW_RESET;
        }
    }

    return(theByte);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterGetReadBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes that has been transferred with an
*  SCB_I2CMasterReadBuf() function.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it returns
*  the byte count transferred so far.
*
* Side Effects:
*  This function returns not valid value if SCB_I2C_MSTAT_ERR_ARB_LOST
*  or SCB_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* Global variables:
*  Accelero_mstrRdBufIndex - used to current index within master read
*  buffer.
*
*******************************************************************************/
uint32 Accelero_I2CMasterGetReadBufSize(void)
{
    return(Accelero_mstrRdBufIndex);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterGetWriteBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes that have been transferred with an
*  SCB_I2CMasterWriteBuf() function.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it returns
*  zero unit transfer completion.
*
* Side Effects:
*  This function returns not valid value if SCB_I2C_MSTAT_ERR_ARB_LOST
*  or SCB_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* Global variables:
*  Accelero_mstrWrBufIndex - used to current index within master write
*  buffer.
*
*******************************************************************************/
uint32 Accelero_I2CMasterGetWriteBufSize(void)
{
    return(Accelero_mstrWrBufIndex);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterClearReadBuf
********************************************************************************
*
* Summary:
*  Resets the read buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Accelero_mstrRdBufIndex - used to current index within master read
*   buffer.
*  Accelero_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void Accelero_I2CMasterClearReadBuf(void)
{
    Accelero_DisableInt();  /* Lock from interruption */

    Accelero_mstrRdBufIndex = 0u;
    Accelero_mstrStatus    &= (uint16) ~Accelero_I2C_MSTAT_RD_CMPLT;

    Accelero_EnableInt();   /* Release lock */
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterClearWriteBuf
********************************************************************************
*
* Summary:
*  Resets the write buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Accelero_mstrRdBufIndex - used to current index within master read
*   buffer.
*  Accelero_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void Accelero_I2CMasterClearWriteBuf(void)
{
    Accelero_DisableInt();  /* Lock from interruption */

    Accelero_mstrWrBufIndex = 0u;
    Accelero_mstrStatus    &= (uint16) ~Accelero_I2C_MSTAT_WR_CMPLT;

    Accelero_EnableInt();   /* Release lock */
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterStatus
********************************************************************************
*
* Summary:
*  Returns the master's communication status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  Accelero_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 Accelero_I2CMasterStatus(void)
{
    uint32 status;

    Accelero_DisableInt();  /* Lock from interruption */

    status = (uint32) Accelero_mstrStatus;

    if (Accelero_CHECK_I2C_MASTER_ACTIVE)
    {
        /* Add status of master pending transaction: MSTAT_XFER_INP */
        status |= (uint32) Accelero_I2C_MSTAT_XFER_INP;
    }

    Accelero_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: Accelero_I2CMasterClearStatus
********************************************************************************
*
* Summary:
*  Clears all status flags and returns the master status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  Accelero_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 Accelero_I2CMasterClearStatus(void)
{
    uint32 status;

    Accelero_DisableInt();  /* Lock from interruption */

    /* Read and clear master status */
    status = (uint32) Accelero_mstrStatus;
    Accelero_mstrStatus = Accelero_I2C_MSTAT_CLEAR;

    Accelero_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: Accelero_I2CReStartGeneration
********************************************************************************
*
* Summary:
*  Generates a ReStart condition:
*  SCB IP V1 and later: Generates ReStart using the scb IP functionality
*    Sets the I2C_MASTER_CMD_M_START and I2C_MASTER_CMD_M_NACK (if the previous
*    transaction was read) bits in the SCB.I2C_MASTER_CMD register.
*    This combination forces the master to generate ReStart.
*
*  SCB IP V0: Generates Restart using the GPIO and scb IP functionality.
*   After the master completes write or read, the SCL is stretched.
*   The master waits until SDA line is released by the slave. Then the GPIO
*   function is enabled and the scb IP disabled as it already does not drive
*   the bus. In case of the previous transfer was read, the NACK is generated
*   by the GPIO. The delay of tLOW is added to manage the hold time.
*   Set I2C_M_CMD.START and enable the scb IP. The ReStart generation
*   is started after the I2C function is enabled for the SCL.
*   Note1: the scb IP due re-enable generates Start but on the I2C bus it
*          appears as ReStart.
*   Note2: the I2C_M_CMD.START is queued if scb IP is disabled.
*   Note3: the I2C_STATUS_M_READ is cleared is address was NACKed before.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  SCB IP V0: The NACK generation by the GPIO may cause a greater SCL period
*             than expected for the selected master data rate.
*
*******************************************************************************/
void Accelero_I2CReStartGeneration(void)
{
#if(Accelero_CY_SCBIP_V0)
    /* Generates Restart use GPIO and scb IP functionality. Ticket ID#143715,
    ID#145238 and ID#173656 */
    uint32 status = Accelero_I2C_STATUS_REG;

    while(Accelero_WAIT_SDA_SET_HIGH)
    {
        /* Wait when slave release SDA line: SCL tHIGH is complete */
    }

    /* Prepare DR register to drive SCL line */
    Accelero_SET_I2C_SCL_DR(Accelero_I2C_SCL_LOW);

    /* Switch HSIOM to GPIO: SCL goes low */
    Accelero_SET_I2C_SCL_HSIOM_SEL(Accelero_HSIOM_GPIO_SEL);

    /* Disable SCB block */
    Accelero_CTRL_REG &= (uint32) ~Accelero_CTRL_ENABLED;

    if(0u != (status & Accelero_I2C_STATUS_M_READ))
    {
        /* Generate NACK use GPIO functionality */
        Accelero_SET_I2C_SCL_DR(Accelero_I2C_SCL_LOW);
        CyDelayUs(Accelero_I2C_TLOW_TIME); /* Count tLOW */

        Accelero_SET_I2C_SCL_DR(Accelero_I2C_SCL_HIGH);
        while(Accelero_WAIT_SCL_SET_HIGH)
        {
            /* Wait until slave releases SCL in case if it stretches */
        }
        CyDelayUs(Accelero_I2C_THIGH_TIME); /* Count tHIGH */
    }

    /* Count tLOW as hold time for write and read */
    Accelero_SET_I2C_SCL_DR(Accelero_I2C_SCL_LOW);
    CyDelayUs(Accelero_I2C_TLOW_TIME); /* Count tLOW */

    /* Set command for Start generation: it will appear */
    Accelero_I2C_MASTER_CMD_REG = Accelero_I2C_MASTER_CMD_M_START;

    /* Enable SCB block */
    Accelero_CTRL_REG |= (uint32) Accelero_CTRL_ENABLED;

    /* Switch HSIOM to I2C: */
    Accelero_SET_I2C_SCL_HSIOM_SEL(Accelero_HSIOM_I2C_SEL);

    /* Revert SCL DR register */
    Accelero_SET_I2C_SCL_DR(Accelero_I2C_SCL_HIGH);
#else
    uint32 cmd;

    /* Generates ReStart use scb IP functionality */
    cmd  = Accelero_I2C_MASTER_CMD_M_START;
    cmd |= Accelero_CHECK_I2C_STATUS(Accelero_I2C_STATUS_M_READ) ?
                (Accelero_I2C_MASTER_CMD_M_NACK) : (0u);

    Accelero_I2C_MASTER_CMD_REG = cmd;
#endif /* (Accelero_CY_SCBIP_V1) */
}

#endif /* (Accelero_I2C_MASTER_CONST) */


#if (!Accelero_CY_SCBIP_V0 && \
    Accelero_I2C_MULTI_MASTER_SLAVE_CONST && Accelero_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: Accelero_I2CMasterDisableEcAm
    ********************************************************************************
    *
    * Summary:
    *  Disables externally clocked address match to enable master operation
    *  in active mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    static void Accelero_I2CMasterDisableEcAm(void)
    {
        /* Disables externally clocked address match to enable master operation in active mode.
        * This applicable only for Multi-Master-Slave with wakeup enabled. Ticket ID#192742 */
        if (0u != (Accelero_CTRL_REG & Accelero_CTRL_EC_AM_MODE))
        {
            /* Enable external address match logic */
            Accelero_Stop();
            Accelero_CTRL_REG &= (uint32) ~Accelero_CTRL_EC_AM_MODE;
            Accelero_Enable();
        }
    }
#endif /* (!Accelero_CY_SCBIP_V0) */


/* [] END OF FILE */
