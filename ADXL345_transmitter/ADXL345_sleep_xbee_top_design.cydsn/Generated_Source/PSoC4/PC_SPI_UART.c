/*******************************************************************************
* File Name: PC_SPI_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PC_PVT.h"
#include "PC_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(PC_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 PC_rxBufferHead;
    volatile uint32 PC_rxBufferTail;
    volatile uint8  PC_rxBufferOverflow;
#endif /* (PC_INTERNAL_RX_SW_BUFFER_CONST) */

#if(PC_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 PC_txBufferHead;
    volatile uint32 PC_txBufferTail;
#endif /* (PC_INTERNAL_TX_SW_BUFFER_CONST) */

#if(PC_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 PC_rxBufferInternal[PC_INTERNAL_RX_BUFFER_SIZE];
#endif /* (PC_INTERNAL_RX_SW_BUFFER) */

#if(PC_INTERNAL_TX_SW_BUFFER)
    volatile uint8 PC_txBufferInternal[PC_TX_BUFFER_SIZE];
#endif /* (PC_INTERNAL_TX_SW_BUFFER) */


#if(PC_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: PC_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into PC_SpiInit for description.
    *
    *******************************************************************************/
    uint32 PC_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (PC_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (PC_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (PC_CHECK_RX_SW_BUFFER)
        {
            if (PC_rxBufferHead != PC_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (PC_rxBufferTail + 1u);

                if (PC_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = PC_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                PC_rxBufferTail = locTail;

                #if (PC_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (PC_INTR_RX_MASK_REG & PC_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        PC_INTR_RX_MASK_REG |= PC_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = PC_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: PC_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 PC_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (PC_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (PC_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (PC_CHECK_RX_SW_BUFFER)
        {
            locHead = PC_rxBufferHead;

            if(locHead >= PC_rxBufferTail)
            {
                size = (locHead - PC_rxBufferTail);
            }
            else
            {
                size = (locHead + (PC_INTERNAL_RX_BUFFER_SIZE - PC_rxBufferTail));
            }
        }
        #else
        {
            size = PC_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: PC_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_SpiUartClearRxBuffer(void)
    {
        #if (PC_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            PC_DisableInt();

            /* Flush RX software buffer */
            PC_rxBufferHead = PC_rxBufferTail;
            PC_rxBufferOverflow = 0u;

            PC_CLEAR_RX_FIFO;
            PC_ClearRxInterruptSource(PC_INTR_RX_ALL);

            #if (PC_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                PC_INTR_RX_MASK_REG |= PC_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            PC_EnableInt();
        }
        #else
        {
            PC_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (PC_RX_DIRECTION) */


#if(PC_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: PC_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_SpiUartWriteTxData(uint32 txData)
    {
    #if (PC_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (PC_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (PC_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((PC_txBufferHead == PC_txBufferTail) &&
                (PC_SPI_UART_FIFO_SIZE != PC_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                PC_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (PC_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (PC_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == PC_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                PC_ClearTxInterruptSource(PC_INTR_TX_NOT_FULL);

                PC_PutWordInTxBuffer(locHead, txData);

                PC_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (PC_INTR_TX_MASK_REG & PC_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    PC_INTR_TX_MASK_REG |= (uint32) PC_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (PC_SPI_UART_FIFO_SIZE == PC_GET_TX_FIFO_ENTRIES)
            {
            }

            PC_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: PC_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            PC_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: PC_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 PC_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (PC_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (PC_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (PC_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = PC_txBufferTail;

            if (PC_txBufferHead >= locTail)
            {
                size = (PC_txBufferHead - locTail);
            }
            else
            {
                size = (PC_txBufferHead + (PC_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = PC_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: PC_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_SpiUartClearTxBuffer(void)
    {
        #if (PC_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            PC_DisableInt();

            /* Flush TX software buffer */
            PC_txBufferHead = PC_txBufferTail;

            PC_INTR_TX_MASK_REG &= (uint32) ~PC_INTR_TX_NOT_FULL;
            PC_CLEAR_TX_FIFO;
            PC_ClearTxInterruptSource(PC_INTR_TX_ALL);

            /* Release lock */
            PC_EnableInt();
        }
        #else
        {
            PC_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (PC_TX_DIRECTION) */


/*******************************************************************************
* Function Name: PC_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 PC_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = PC_GetRxInterruptMode();

    PC_SetRxInterruptMode(PC_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: PC_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 PC_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = PC_GetTxInterruptMode();

    PC_SetTxInterruptMode(PC_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(PC_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: PC_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (PC_ONE_BYTE_WIDTH == PC_rxDataBits)
        {
            PC_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            PC_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            PC_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: PC_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 PC_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (PC_ONE_BYTE_WIDTH == PC_rxDataBits)
        {
            value = PC_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) PC_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)PC_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: PC_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (PC_ONE_BYTE_WIDTH == PC_txDataBits)
        {
            PC_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            PC_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            PC_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: PC_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 PC_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (PC_ONE_BYTE_WIDTH == PC_txDataBits)
        {
            value = (uint32) PC_txBuffer[idx];
        }
        else
        {
            value  = (uint32) PC_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) PC_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
