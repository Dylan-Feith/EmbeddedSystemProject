/*******************************************************************************
* File Name: zigbeeINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "zigbee.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (zigbee_RX_INTERRUPT_ENABLED && (zigbee_RX_ENABLED || zigbee_HD_ENABLED))
    /*******************************************************************************
    * Function Name: zigbee_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  zigbee_rxBuffer - RAM buffer pointer for save received data.
    *  zigbee_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  zigbee_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  zigbee_rxBufferOverflow - software overflow flag. Set to one
    *     when zigbee_rxBufferWrite index overtakes
    *     zigbee_rxBufferRead index.
    *  zigbee_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when zigbee_rxBufferWrite is equal to
    *    zigbee_rxBufferRead
    *  zigbee_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  zigbee_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(zigbee_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef zigbee_RXISR_ENTRY_CALLBACK
        zigbee_RXISR_EntryCallback();
    #endif /* zigbee_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START zigbee_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = zigbee_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in zigbee_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (zigbee_RX_STS_BREAK | 
                            zigbee_RX_STS_PAR_ERROR |
                            zigbee_RX_STS_STOP_ERROR | 
                            zigbee_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                zigbee_errorStatus |= readStatus & ( zigbee_RX_STS_BREAK | 
                                                            zigbee_RX_STS_PAR_ERROR | 
                                                            zigbee_RX_STS_STOP_ERROR | 
                                                            zigbee_RX_STS_OVERRUN);
                /* `#START zigbee_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef zigbee_RXISR_ERROR_CALLBACK
                zigbee_RXISR_ERROR_Callback();
            #endif /* zigbee_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & zigbee_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = zigbee_RXDATA_REG;
            #if (zigbee_RXHW_ADDRESS_ENABLED)
                if(zigbee_rxAddressMode == (uint8)zigbee__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & zigbee_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & zigbee_RX_STS_ADDR_MATCH) != 0u)
                        {
                            zigbee_rxAddressDetected = 1u;
                        }
                        else
                        {
                            zigbee_rxAddressDetected = 0u;
                        }
                    }
                    if(zigbee_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        zigbee_rxBuffer[zigbee_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    zigbee_rxBuffer[zigbee_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                zigbee_rxBuffer[zigbee_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (zigbee_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(zigbee_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        zigbee_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    zigbee_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(zigbee_rxBufferWrite >= zigbee_RX_BUFFER_SIZE)
                    {
                        zigbee_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(zigbee_rxBufferWrite == zigbee_rxBufferRead)
                    {
                        zigbee_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (zigbee_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            zigbee_RXSTATUS_MASK_REG  &= (uint8)~zigbee_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(zigbee_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (zigbee_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & zigbee_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START zigbee_RXISR_END` */

        /* `#END` */

    #ifdef zigbee_RXISR_EXIT_CALLBACK
        zigbee_RXISR_ExitCallback();
    #endif /* zigbee_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (zigbee_RX_INTERRUPT_ENABLED && (zigbee_RX_ENABLED || zigbee_HD_ENABLED)) */


#if (zigbee_TX_INTERRUPT_ENABLED && zigbee_TX_ENABLED)
    /*******************************************************************************
    * Function Name: zigbee_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  zigbee_txBuffer - RAM buffer pointer for transmit data from.
    *  zigbee_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  zigbee_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(zigbee_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef zigbee_TXISR_ENTRY_CALLBACK
        zigbee_TXISR_EntryCallback();
    #endif /* zigbee_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START zigbee_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((zigbee_txBufferRead != zigbee_txBufferWrite) &&
             ((zigbee_TXSTATUS_REG & zigbee_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(zigbee_txBufferRead >= zigbee_TX_BUFFER_SIZE)
            {
                zigbee_txBufferRead = 0u;
            }

            zigbee_TXDATA_REG = zigbee_txBuffer[zigbee_txBufferRead];

            /* Set next pointer */
            zigbee_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START zigbee_TXISR_END` */

        /* `#END` */

    #ifdef zigbee_TXISR_EXIT_CALLBACK
        zigbee_TXISR_ExitCallback();
    #endif /* zigbee_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (zigbee_TX_INTERRUPT_ENABLED && zigbee_TX_ENABLED) */


/* [] END OF FILE */
