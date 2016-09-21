/*******************************************************************************
* File Name: XBee_SPI_UART_INT.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "XBee_PVT.h"
#include "XBee_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (XBee_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: XBee_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(XBee_SPI_UART_ISR)
{
#if (XBee_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (XBee_INTERNAL_RX_SW_BUFFER_CONST) */

#if (XBee_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (XBee_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef XBee_SPI_UART_ISR_ENTRY_CALLBACK
    XBee_SPI_UART_ISR_EntryCallback();
#endif /* XBee_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != XBee_customIntrHandler)
    {
        XBee_customIntrHandler();
    }

    #if (XBee_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        XBee_ClearSpiExtClkInterruptSource(XBee_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (XBee_CHECK_RX_SW_BUFFER)
    {
        if (XBee_CHECK_INTR_RX_MASKED(XBee_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (XBee_rxBufferHead + 1u);

                /* Adjust local head index */
                if (XBee_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == XBee_rxBufferTail)
                {
                    #if (XBee_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        XBee_INTR_RX_MASK_REG &= ~XBee_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) XBee_RX_FIFO_RD_REG;
                        XBee_rxBufferOverflow = (uint8) XBee_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    XBee_PutWordInRxBuffer(locHead, XBee_RX_FIFO_RD_REG);

                    /* Move head index */
                    XBee_rxBufferHead = locHead;
                }
            }
            while(0u != XBee_GET_RX_FIFO_ENTRIES);

            XBee_ClearRxInterruptSource(XBee_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (XBee_CHECK_TX_SW_BUFFER)
    {
        if (XBee_CHECK_INTR_TX_MASKED(XBee_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (XBee_txBufferHead != XBee_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (XBee_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (XBee_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    XBee_TX_FIFO_WR_REG = XBee_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    XBee_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    XBee_DISABLE_INTR_TX(XBee_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (XBee_SPI_UART_FIFO_SIZE != XBee_GET_TX_FIFO_ENTRIES);

            XBee_ClearTxInterruptSource(XBee_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef XBee_SPI_UART_ISR_EXIT_CALLBACK
    XBee_SPI_UART_ISR_ExitCallback();
#endif /* XBee_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (XBee_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
