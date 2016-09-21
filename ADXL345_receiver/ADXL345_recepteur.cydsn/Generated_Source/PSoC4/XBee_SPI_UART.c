/*******************************************************************************
* File Name: XBee_SPI_UART.c
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

#include "XBee_PVT.h"
#include "XBee_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(XBee_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 XBee_rxBufferHead;
    volatile uint32 XBee_rxBufferTail;
    volatile uint8  XBee_rxBufferOverflow;
#endif /* (XBee_INTERNAL_RX_SW_BUFFER_CONST) */

#if(XBee_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 XBee_txBufferHead;
    volatile uint32 XBee_txBufferTail;
#endif /* (XBee_INTERNAL_TX_SW_BUFFER_CONST) */

#if(XBee_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 XBee_rxBufferInternal[XBee_INTERNAL_RX_BUFFER_SIZE];
#endif /* (XBee_INTERNAL_RX_SW_BUFFER) */

#if(XBee_INTERNAL_TX_SW_BUFFER)
    volatile uint8 XBee_txBufferInternal[XBee_TX_BUFFER_SIZE];
#endif /* (XBee_INTERNAL_TX_SW_BUFFER) */


#if(XBee_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: XBee_SpiUartReadRxData
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
    *  Look into XBee_SpiInit for description.
    *
    *******************************************************************************/
    uint32 XBee_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (XBee_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (XBee_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (XBee_CHECK_RX_SW_BUFFER)
        {
            if (XBee_rxBufferHead != XBee_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (XBee_rxBufferTail + 1u);

                if (XBee_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = XBee_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                XBee_rxBufferTail = locTail;

                #if (XBee_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (XBee_INTR_RX_MASK_REG & XBee_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        XBee_INTR_RX_MASK_REG |= XBee_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = XBee_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: XBee_SpiUartGetRxBufferSize
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
    uint32 XBee_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (XBee_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (XBee_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (XBee_CHECK_RX_SW_BUFFER)
        {
            locHead = XBee_rxBufferHead;

            if(locHead >= XBee_rxBufferTail)
            {
                size = (locHead - XBee_rxBufferTail);
            }
            else
            {
                size = (locHead + (XBee_INTERNAL_RX_BUFFER_SIZE - XBee_rxBufferTail));
            }
        }
        #else
        {
            size = XBee_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: XBee_SpiUartClearRxBuffer
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
    void XBee_SpiUartClearRxBuffer(void)
    {
        #if (XBee_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            XBee_DisableInt();

            /* Flush RX software buffer */
            XBee_rxBufferHead = XBee_rxBufferTail;
            XBee_rxBufferOverflow = 0u;

            XBee_CLEAR_RX_FIFO;
            XBee_ClearRxInterruptSource(XBee_INTR_RX_ALL);

            #if (XBee_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                XBee_INTR_RX_MASK_REG |= XBee_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            XBee_EnableInt();
        }
        #else
        {
            XBee_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (XBee_RX_DIRECTION) */


#if(XBee_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: XBee_SpiUartWriteTxData
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
    void XBee_SpiUartWriteTxData(uint32 txData)
    {
    #if (XBee_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (XBee_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (XBee_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((XBee_txBufferHead == XBee_txBufferTail) &&
                (XBee_SPI_UART_FIFO_SIZE != XBee_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                XBee_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (XBee_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (XBee_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == XBee_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                XBee_ClearTxInterruptSource(XBee_INTR_TX_NOT_FULL);

                XBee_PutWordInTxBuffer(locHead, txData);

                XBee_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (XBee_INTR_TX_MASK_REG & XBee_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    XBee_INTR_TX_MASK_REG |= (uint32) XBee_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (XBee_SPI_UART_FIFO_SIZE == XBee_GET_TX_FIFO_ENTRIES)
            {
            }

            XBee_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: XBee_SpiUartPutArray
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
    void XBee_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            XBee_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: XBee_SpiUartGetTxBufferSize
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
    uint32 XBee_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (XBee_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (XBee_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (XBee_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = XBee_txBufferTail;

            if (XBee_txBufferHead >= locTail)
            {
                size = (XBee_txBufferHead - locTail);
            }
            else
            {
                size = (XBee_txBufferHead + (XBee_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = XBee_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: XBee_SpiUartClearTxBuffer
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
    void XBee_SpiUartClearTxBuffer(void)
    {
        #if (XBee_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            XBee_DisableInt();

            /* Flush TX software buffer */
            XBee_txBufferHead = XBee_txBufferTail;

            XBee_INTR_TX_MASK_REG &= (uint32) ~XBee_INTR_TX_NOT_FULL;
            XBee_CLEAR_TX_FIFO;
            XBee_ClearTxInterruptSource(XBee_INTR_TX_ALL);

            /* Release lock */
            XBee_EnableInt();
        }
        #else
        {
            XBee_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (XBee_TX_DIRECTION) */


/*******************************************************************************
* Function Name: XBee_SpiUartDisableIntRx
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
uint32 XBee_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = XBee_GetRxInterruptMode();

    XBee_SetRxInterruptMode(XBee_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: XBee_SpiUartDisableIntTx
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
uint32 XBee_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = XBee_GetTxInterruptMode();

    XBee_SetTxInterruptMode(XBee_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: XBee_PutWordInRxBuffer
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
    void XBee_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (XBee_ONE_BYTE_WIDTH == XBee_rxDataBits)
        {
            XBee_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            XBee_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            XBee_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: XBee_GetWordFromRxBuffer
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
    uint32 XBee_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (XBee_ONE_BYTE_WIDTH == XBee_rxDataBits)
        {
            value = XBee_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) XBee_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)XBee_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: XBee_PutWordInTxBuffer
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
    void XBee_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (XBee_ONE_BYTE_WIDTH == XBee_txDataBits)
        {
            XBee_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            XBee_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            XBee_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: XBee_GetWordFromTxBuffer
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
    uint32 XBee_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (XBee_ONE_BYTE_WIDTH == XBee_txDataBits)
        {
            value = (uint32) XBee_txBuffer[idx];
        }
        else
        {
            value  = (uint32) XBee_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) XBee_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
