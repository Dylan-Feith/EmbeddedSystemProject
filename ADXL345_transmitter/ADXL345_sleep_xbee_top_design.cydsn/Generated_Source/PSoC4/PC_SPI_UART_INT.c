/*******************************************************************************
* File Name: PC_SPI_UART_INT.c
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

#include "PC_PVT.h"
#include "PC_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (PC_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: PC_SPI_UART_ISR
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
CY_ISR(PC_SPI_UART_ISR)
{
#if (PC_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (PC_INTERNAL_RX_SW_BUFFER_CONST) */

#if (PC_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (PC_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef PC_SPI_UART_ISR_ENTRY_CALLBACK
    PC_SPI_UART_ISR_EntryCallback();
#endif /* PC_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != PC_customIntrHandler)
    {
        PC_customIntrHandler();
    }

    #if (PC_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        PC_ClearSpiExtClkInterruptSource(PC_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (PC_CHECK_RX_SW_BUFFER)
    {
        if (PC_CHECK_INTR_RX_MASKED(PC_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (PC_rxBufferHead + 1u);

                /* Adjust local head index */
                if (PC_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == PC_rxBufferTail)
                {
                    #if (PC_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        PC_INTR_RX_MASK_REG &= ~PC_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) PC_RX_FIFO_RD_REG;
                        PC_rxBufferOverflow = (uint8) PC_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    PC_PutWordInRxBuffer(locHead, PC_RX_FIFO_RD_REG);

                    /* Move head index */
                    PC_rxBufferHead = locHead;
                }
            }
            while(0u != PC_GET_RX_FIFO_ENTRIES);

            PC_ClearRxInterruptSource(PC_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (PC_CHECK_TX_SW_BUFFER)
    {
        if (PC_CHECK_INTR_TX_MASKED(PC_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (PC_txBufferHead != PC_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (PC_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (PC_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    PC_TX_FIFO_WR_REG = PC_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    PC_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    PC_DISABLE_INTR_TX(PC_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (PC_SPI_UART_FIFO_SIZE != PC_GET_TX_FIFO_ENTRIES);

            PC_ClearTxInterruptSource(PC_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef PC_SPI_UART_ISR_EXIT_CALLBACK
    PC_SPI_UART_ISR_ExitCallback();
#endif /* PC_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (PC_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
