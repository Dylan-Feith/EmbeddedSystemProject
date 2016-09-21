/*******************************************************************************
* File Name: Accelero_I2C.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
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


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 Accelero_state;  /* Current state of I2C FSM */

#if(Accelero_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const Accelero_I2C_INIT_STRUCT Accelero_configI2C =
    {
        Accelero_I2C_MODE,
        Accelero_I2C_OVS_FACTOR_LOW,
        Accelero_I2C_OVS_FACTOR_HIGH,
        Accelero_I2C_MEDIAN_FILTER_ENABLE,
        Accelero_I2C_SLAVE_ADDRESS,
        Accelero_I2C_SLAVE_ADDRESS_MASK,
        Accelero_I2C_ACCEPT_ADDRESS,
        Accelero_I2C_WAKE_ENABLE,
        Accelero_I2C_BYTE_MODE_ENABLE,
        Accelero_I2C_DATA_RATE,
        Accelero_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: Accelero_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Accelero_I2CInit(const Accelero_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            Accelero_SetPins(Accelero_SCB_MODE_I2C, Accelero_DUMMY_PARAM,
                                     Accelero_DUMMY_PARAM);

            /* Store internal configuration */
            Accelero_scbMode       = (uint8) Accelero_SCB_MODE_I2C;
            Accelero_scbEnableWake = (uint8) config->enableWake;
            Accelero_scbEnableIntr = (uint8) Accelero_SCB_IRQ_INTERNAL;

            Accelero_mode          = (uint8) config->mode;
            Accelero_acceptAddr    = (uint8) config->acceptAddr;

        #if (Accelero_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            Accelero_SET_I2C_CFG_SDA_FILT_TRIM(Accelero_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (Accelero_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((Accelero_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= Accelero_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (Accelero_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                Accelero_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = Accelero_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                Accelero_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = Accelero_DIGITAL_FILTER_ENABLE;
            }

        #if (!Accelero_CY_SCBIP_V0)
            locEnableWake = (Accelero_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!Accelero_CY_SCBIP_V0) */

            /* Configure I2C interface */
            Accelero_CTRL_REG     = Accelero_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            Accelero_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            Accelero_GET_CTRL_EC_AM_MODE (locEnableWake);

            Accelero_I2C_CTRL_REG = Accelero_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    Accelero_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    Accelero_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    Accelero_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            Accelero_RX_CTRL_REG      = Accelero_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                Accelero_I2C_RX_CTRL;
            Accelero_RX_FIFO_CTRL_REG = Accelero_CLEAR_REG;

            /* Set default address and mask */
            Accelero_RX_MATCH_REG    = ((Accelero_I2C_SLAVE) ?
                                                (Accelero_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 Accelero_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (Accelero_CLEAR_REG));


            /* Configure TX direction */
            Accelero_TX_CTRL_REG      = Accelero_I2C_TX_CTRL;
            Accelero_TX_FIFO_CTRL_REG = Accelero_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (Accelero_ISR_NUMBER);
            CyIntSetPriority(Accelero_ISR_NUMBER, Accelero_ISR_PRIORITY);
            (void) CyIntSetVector(Accelero_ISR_NUMBER, &Accelero_I2C_ISR);

            /* Configure interrupt sources */
        #if(!Accelero_CY_SCBIP_V1)
            Accelero_INTR_SPI_EC_MASK_REG = Accelero_NO_INTR_SOURCES;
        #endif /* (!Accelero_CY_SCBIP_V1) */

            Accelero_INTR_I2C_EC_MASK_REG = Accelero_NO_INTR_SOURCES;
            Accelero_INTR_RX_MASK_REG     = Accelero_NO_INTR_SOURCES;
            Accelero_INTR_TX_MASK_REG     = Accelero_NO_INTR_SOURCES;

            Accelero_INTR_SLAVE_MASK_REG  = ((Accelero_I2C_SLAVE) ?
                            (Accelero_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             Accelero_I2C_INTR_SLAVE_MASK) : (Accelero_CLEAR_REG));

            Accelero_INTR_MASTER_MASK_REG = ((Accelero_I2C_MASTER) ?
                                                     (Accelero_I2C_INTR_MASTER_MASK) :
                                                     (Accelero_CLEAR_REG));

            /* Configure global variables */
            Accelero_state = Accelero_I2C_FSM_IDLE;

            /* Internal slave variables */
            Accelero_slStatus        = 0u;
            Accelero_slRdBufIndex    = 0u;
            Accelero_slWrBufIndex    = 0u;
            Accelero_slOverFlowCount = 0u;

            /* Internal master variables */
            Accelero_mstrStatus     = 0u;
            Accelero_mstrRdBufIndex = 0u;
            Accelero_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: Accelero_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Accelero_I2CInit(void)
    {
    #if(Accelero_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        Accelero_SET_I2C_CFG_SDA_FILT_TRIM(Accelero_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (Accelero_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        Accelero_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        Accelero_CTRL_REG     = Accelero_I2C_DEFAULT_CTRL;
        Accelero_I2C_CTRL_REG = Accelero_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        Accelero_RX_CTRL_REG      = Accelero_I2C_DEFAULT_RX_CTRL;
        Accelero_RX_FIFO_CTRL_REG = Accelero_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        Accelero_RX_MATCH_REG     = Accelero_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        Accelero_TX_CTRL_REG      = Accelero_I2C_DEFAULT_TX_CTRL;
        Accelero_TX_FIFO_CTRL_REG = Accelero_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (Accelero_ISR_NUMBER);
        CyIntSetPriority(Accelero_ISR_NUMBER, Accelero_ISR_PRIORITY);
    #if(!Accelero_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(Accelero_ISR_NUMBER, &Accelero_I2C_ISR);
    #endif /* (Accelero_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!Accelero_CY_SCBIP_V1)
        Accelero_INTR_SPI_EC_MASK_REG = Accelero_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!Accelero_CY_SCBIP_V1) */

        Accelero_INTR_I2C_EC_MASK_REG = Accelero_I2C_DEFAULT_INTR_I2C_EC_MASK;
        Accelero_INTR_SLAVE_MASK_REG  = Accelero_I2C_DEFAULT_INTR_SLAVE_MASK;
        Accelero_INTR_MASTER_MASK_REG = Accelero_I2C_DEFAULT_INTR_MASTER_MASK;
        Accelero_INTR_RX_MASK_REG     = Accelero_I2C_DEFAULT_INTR_RX_MASK;
        Accelero_INTR_TX_MASK_REG     = Accelero_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        Accelero_state = Accelero_I2C_FSM_IDLE;

    #if(Accelero_I2C_SLAVE)
        /* Internal slave variable */
        Accelero_slStatus        = 0u;
        Accelero_slRdBufIndex    = 0u;
        Accelero_slWrBufIndex    = 0u;
        Accelero_slOverFlowCount = 0u;
    #endif /* (Accelero_I2C_SLAVE) */

    #if(Accelero_I2C_MASTER)
    /* Internal master variable */
        Accelero_mstrStatus     = 0u;
        Accelero_mstrRdBufIndex = 0u;
        Accelero_mstrWrBufIndex = 0u;
    #endif /* (Accelero_I2C_MASTER) */
    }
#endif /* (Accelero_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: Accelero_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Accelero_I2CStop(void)
{
    Accelero_state = Accelero_I2C_FSM_IDLE;
}


#if(Accelero_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: Accelero_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables Accelero_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Accelero_I2CSaveConfig(void)
    {
    #if (!Accelero_CY_SCBIP_V0)
        #if (Accelero_I2C_MULTI_MASTER_SLAVE_CONST && Accelero_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (Accelero_CTRL_REG & Accelero_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                Accelero_Stop();
                Accelero_CTRL_REG |= Accelero_CTRL_EC_AM_MODE;
                Accelero_Enable();
            }
        #endif /* (Accelero_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (Accelero_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            Accelero_SCBCLK_Stop();
        #endif /* (Accelero_SCB_CLK_INTERNAL) */
    #endif /* (!Accelero_CY_SCBIP_V0) */

        Accelero_SetI2CExtClkInterruptMode(Accelero_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: Accelero_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables Accelero_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Accelero_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        Accelero_SetI2CExtClkInterruptMode(Accelero_NO_INTR_SOURCES);

    #if (!Accelero_CY_SCBIP_V0)
        #if (Accelero_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            Accelero_SCBCLK_Start();
        #endif /* (Accelero_SCB_CLK_INTERNAL) */
    #endif /* (!Accelero_CY_SCBIP_V0) */
    }
#endif /* (Accelero_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
