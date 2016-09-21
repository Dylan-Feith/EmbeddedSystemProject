/*******************************************************************************
* File Name: PC.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if (PC_SCB_MODE_I2C_INC)
    #include "PC_I2C_PVT.h"
#endif /* (PC_SCB_MODE_I2C_INC) */

#if (PC_SCB_MODE_EZI2C_INC)
    #include "PC_EZI2C_PVT.h"
#endif /* (PC_SCB_MODE_EZI2C_INC) */

#if (PC_SCB_MODE_SPI_INC || PC_SCB_MODE_UART_INC)
    #include "PC_SPI_UART_PVT.h"
#endif /* (PC_SCB_MODE_SPI_INC || PC_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (PC_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 PC_scbMode = PC_SCB_MODE_UNCONFIG;
    uint8 PC_scbEnableWake;
    uint8 PC_scbEnableIntr;

    /* I2C configuration variables */
    uint8 PC_mode;
    uint8 PC_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * PC_rxBuffer;
    uint8  PC_rxDataBits;
    uint32 PC_rxBufferSize;

    volatile uint8 * PC_txBuffer;
    uint8  PC_txDataBits;
    uint32 PC_txBufferSize;

    /* EZI2C configuration variables */
    uint8 PC_numberOfAddr;
    uint8 PC_subAddrSize;
#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 PC_initVar = 0u;

#if (PC_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_PC_CUSTOM_INTR_HANDLER)
    void (*PC_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_PC_CUSTOM_INTR_HANDLER) */
#endif /* (PC_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void PC_ScbEnableIntr(void);
static void PC_ScbModeStop(void);
static void PC_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: PC_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PC_Init(void)
{
#if (PC_SCB_MODE_UNCONFIG_CONST_CFG)
    if (PC_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        PC_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (PC_SCB_MODE_I2C_CONST_CFG)
    PC_I2CInit();

#elif (PC_SCB_MODE_SPI_CONST_CFG)
    PC_SpiInit();

#elif (PC_SCB_MODE_UART_CONST_CFG)
    PC_UartInit();

#elif (PC_SCB_MODE_EZI2C_CONST_CFG)
    PC_EzI2CInit();

#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: PC_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PC_Enable(void)
{
#if (PC_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!PC_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        PC_CTRL_REG |= PC_CTRL_ENABLED;

        PC_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        PC_ScbModePostEnable();
    }
#else
    PC_CTRL_REG |= PC_CTRL_ENABLED;

    PC_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    PC_ScbModePostEnable();
#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: PC_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PC_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void PC_Start(void)
{
    if (0u == PC_initVar)
    {
        PC_Init();
        PC_initVar = 1u; /* Component was initialized */
    }

    PC_Enable();
}


/*******************************************************************************
* Function Name: PC_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void PC_Stop(void)
{
#if (PC_SCB_IRQ_INTERNAL)
    PC_DisableInt();
#endif /* (PC_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    PC_ScbModeStop();

    /* Disable SCB IP */
    PC_CTRL_REG &= (uint32) ~PC_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    PC_SetTxInterruptMode(PC_NO_INTR_SOURCES);

#if (PC_SCB_IRQ_INTERNAL)
    PC_ClearPendingInt();
#endif /* (PC_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: PC_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void PC_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = PC_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~PC_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (PC_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    PC_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: PC_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void PC_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = PC_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~PC_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (PC_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    PC_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (PC_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: PC_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_PC_CUSTOM_INTR_HANDLER)
        PC_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_PC_CUSTOM_INTR_HANDLER) */
    }
#endif /* (PC_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: PC_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void PC_ScbEnableIntr(void)
{
#if (PC_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (PC_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != PC_scbEnableIntr)
        {
            PC_EnableInt();
        }

    #else
        PC_EnableInt();

    #endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (PC_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: PC_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void PC_ScbModePostEnable(void)
{
#if (PC_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!PC_CY_SCBIP_V1)
    if (PC_SCB_MODE_SPI_RUNTM_CFG)
    {
        PC_SpiPostEnable();
    }
    else if (PC_SCB_MODE_UART_RUNTM_CFG)
    {
        PC_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!PC_CY_SCBIP_V1) */

#elif (PC_SCB_MODE_SPI_CONST_CFG)
    PC_SpiPostEnable();

#elif (PC_SCB_MODE_UART_CONST_CFG)
    PC_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: PC_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void PC_ScbModeStop(void)
{
#if (PC_SCB_MODE_UNCONFIG_CONST_CFG)
    if (PC_SCB_MODE_I2C_RUNTM_CFG)
    {
        PC_I2CStop();
    }
    else if (PC_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        PC_EzI2CStop();
    }
#if (!PC_CY_SCBIP_V1)
    else if (PC_SCB_MODE_SPI_RUNTM_CFG)
    {
        PC_SpiStop();
    }
    else if (PC_SCB_MODE_UART_RUNTM_CFG)
    {
        PC_UartStop();
    }
#endif /* (!PC_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (PC_SCB_MODE_I2C_CONST_CFG)
    PC_I2CStop();

#elif (PC_SCB_MODE_EZI2C_CONST_CFG)
    PC_EzI2CStop();

#elif (PC_SCB_MODE_SPI_CONST_CFG)
    PC_SpiStop();

#elif (PC_SCB_MODE_UART_CONST_CFG)
    PC_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (PC_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: PC_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [PC_SCB_PINS_NUMBER];
        uint32 pinsDm   [PC_SCB_PINS_NUMBER];

    #if (!PC_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!PC_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < PC_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = PC_HSIOM_DEF_SEL;
            pinsDm[i]    = PC_PIN_DM_ALG_HIZ;
        }

        if ((PC_SCB_MODE_I2C   == mode) ||
           (PC_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[PC_RX_SCL_MOSI_PIN_INDEX] = PC_HSIOM_I2C_SEL;
            hsiomSel[PC_TX_SDA_MISO_PIN_INDEX] = PC_HSIOM_I2C_SEL;

            pinsDm[PC_RX_SCL_MOSI_PIN_INDEX] = PC_PIN_DM_OD_LO;
            pinsDm[PC_TX_SDA_MISO_PIN_INDEX] = PC_PIN_DM_OD_LO;
        }
    #if (!PC_CY_SCBIP_V1)
        else if (PC_SCB_MODE_SPI == mode)
        {
            hsiomSel[PC_RX_SCL_MOSI_PIN_INDEX] = PC_HSIOM_SPI_SEL;
            hsiomSel[PC_TX_SDA_MISO_PIN_INDEX] = PC_HSIOM_SPI_SEL;
            hsiomSel[PC_SCLK_PIN_INDEX] = PC_HSIOM_SPI_SEL;

            if (PC_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[PC_RX_SCL_MOSI_PIN_INDEX] = PC_PIN_DM_DIG_HIZ;
                pinsDm[PC_TX_SDA_MISO_PIN_INDEX] = PC_PIN_DM_STRONG;
                pinsDm[PC_SCLK_PIN_INDEX] = PC_PIN_DM_DIG_HIZ;

            #if (PC_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[PC_SS0_PIN_INDEX] = PC_HSIOM_SPI_SEL;
                pinsDm  [PC_SS0_PIN_INDEX] = PC_PIN_DM_DIG_HIZ;
            #endif /* (PC_SS0_PIN) */

            #if (PC_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= PC_TX_SDA_MISO_PIN_MASK;
            #endif /* (PC_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[PC_RX_SCL_MOSI_PIN_INDEX] = PC_PIN_DM_STRONG;
                pinsDm[PC_TX_SDA_MISO_PIN_INDEX] = PC_PIN_DM_DIG_HIZ;
                pinsDm[PC_SCLK_PIN_INDEX] = PC_PIN_DM_STRONG;

            #if (PC_SS0_PIN)
                hsiomSel [PC_SS0_PIN_INDEX] = PC_HSIOM_SPI_SEL;
                pinsDm   [PC_SS0_PIN_INDEX] = PC_PIN_DM_STRONG;
                pinsInBuf |= PC_SS0_PIN_MASK;
            #endif /* (PC_SS0_PIN) */

            #if (PC_SS1_PIN)
                hsiomSel [PC_SS1_PIN_INDEX] = PC_HSIOM_SPI_SEL;
                pinsDm   [PC_SS1_PIN_INDEX] = PC_PIN_DM_STRONG;
                pinsInBuf |= PC_SS1_PIN_MASK;
            #endif /* (PC_SS1_PIN) */

            #if (PC_SS2_PIN)
                hsiomSel [PC_SS2_PIN_INDEX] = PC_HSIOM_SPI_SEL;
                pinsDm   [PC_SS2_PIN_INDEX] = PC_PIN_DM_STRONG;
                pinsInBuf |= PC_SS2_PIN_MASK;
            #endif /* (PC_SS2_PIN) */

            #if (PC_SS3_PIN)
                hsiomSel [PC_SS3_PIN_INDEX] = PC_HSIOM_SPI_SEL;
                pinsDm   [PC_SS3_PIN_INDEX] = PC_PIN_DM_STRONG;
                pinsInBuf |= PC_SS3_PIN_MASK;
            #endif /* (PC_SS3_PIN) */

                /* Disable input buffers */
            #if (PC_RX_SCL_MOSI_PIN)
                pinsInBuf |= PC_RX_SCL_MOSI_PIN_MASK;
            #endif /* (PC_RX_SCL_MOSI_PIN) */

             #if (PC_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= PC_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (PC_RX_WAKE_SCL_MOSI_PIN) */

            #if (PC_SCLK_PIN)
                pinsInBuf |= PC_SCLK_PIN_MASK;
            #endif /* (PC_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (PC_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[PC_TX_SDA_MISO_PIN_INDEX] = PC_HSIOM_UART_SEL;
                pinsDm  [PC_TX_SDA_MISO_PIN_INDEX] = PC_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (PC_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[PC_RX_SCL_MOSI_PIN_INDEX] = PC_HSIOM_UART_SEL;
                    pinsDm  [PC_RX_SCL_MOSI_PIN_INDEX] = PC_PIN_DM_DIG_HIZ;
                }

                if (0u != (PC_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[PC_TX_SDA_MISO_PIN_INDEX] = PC_HSIOM_UART_SEL;
                    pinsDm  [PC_TX_SDA_MISO_PIN_INDEX] = PC_PIN_DM_STRONG;

                #if (PC_TX_SDA_MISO_PIN)
                     pinsInBuf |= PC_TX_SDA_MISO_PIN_MASK;
                #endif /* (PC_TX_SDA_MISO_PIN) */
                }

            #if !(PC_CY_SCBIP_V0 || PC_CY_SCBIP_V1)
                if (PC_UART_MODE_STD == subMode)
                {
                    if (0u != (PC_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[PC_SCLK_PIN_INDEX] = PC_HSIOM_UART_SEL;
                        pinsDm  [PC_SCLK_PIN_INDEX] = PC_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (PC_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[PC_SS0_PIN_INDEX] = PC_HSIOM_UART_SEL;
                        pinsDm  [PC_SS0_PIN_INDEX] = PC_PIN_DM_STRONG;

                    #if (PC_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= PC_SS0_PIN_MASK;
                    #endif /* (PC_SS0_PIN) */
                    }
                }
            #endif /* !(PC_CY_SCBIP_V0 || PC_CY_SCBIP_V1) */
            }
        }
    #endif /* (!PC_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (PC_RX_WAKE_SCL_MOSI_PIN)
        PC_SET_HSIOM_SEL(PC_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       PC_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       PC_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[PC_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        PC_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[PC_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        PC_SET_INP_DIS(PC_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     PC_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & PC_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        PC_SET_INCFG_TYPE(PC_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        PC_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        PC_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        PC_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (PC_RX_WAKE_SCL_MOSI_PIN) */

    #if (PC_RX_SCL_MOSI_PIN)
        PC_SET_HSIOM_SEL(PC_RX_SCL_MOSI_HSIOM_REG,
                                       PC_RX_SCL_MOSI_HSIOM_MASK,
                                       PC_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[PC_RX_SCL_MOSI_PIN_INDEX]);

        PC_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[PC_RX_SCL_MOSI_PIN_INDEX]);

    #if (!PC_CY_SCBIP_V1)
        PC_SET_INP_DIS(PC_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     PC_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & PC_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!PC_CY_SCBIP_V1) */
    #endif /* (PC_RX_SCL_MOSI_PIN) */

    #if (PC_TX_SDA_MISO_PIN)
        PC_SET_HSIOM_SEL(PC_TX_SDA_MISO_HSIOM_REG,
                                       PC_TX_SDA_MISO_HSIOM_MASK,
                                       PC_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[PC_TX_SDA_MISO_PIN_INDEX]);

        PC_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[PC_TX_SDA_MISO_PIN_INDEX]);

    #if (!PC_CY_SCBIP_V1)
        PC_SET_INP_DIS(PC_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     PC_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & PC_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!PC_CY_SCBIP_V1) */
    #endif /* (PC_RX_SCL_MOSI_PIN) */

    #if (PC_SCLK_PIN)
        PC_SET_HSIOM_SEL(PC_SCLK_HSIOM_REG,
                                       PC_SCLK_HSIOM_MASK,
                                       PC_SCLK_HSIOM_POS,
                                       hsiomSel[PC_SCLK_PIN_INDEX]);

        PC_spi_sclk_SetDriveMode((uint8) pinsDm[PC_SCLK_PIN_INDEX]);

        PC_SET_INP_DIS(PC_spi_sclk_INP_DIS,
                                     PC_spi_sclk_MASK,
                                     (0u != (pinsInBuf & PC_SCLK_PIN_MASK)));
    #endif /* (PC_SCLK_PIN) */

    #if (PC_SS0_PIN)
        PC_SET_HSIOM_SEL(PC_SS0_HSIOM_REG,
                                       PC_SS0_HSIOM_MASK,
                                       PC_SS0_HSIOM_POS,
                                       hsiomSel[PC_SS0_PIN_INDEX]);

        PC_spi_ss0_SetDriveMode((uint8) pinsDm[PC_SS0_PIN_INDEX]);

        PC_SET_INP_DIS(PC_spi_ss0_INP_DIS,
                                     PC_spi_ss0_MASK,
                                     (0u != (pinsInBuf & PC_SS0_PIN_MASK)));
    #endif /* (PC_SS0_PIN) */

    #if (PC_SS1_PIN)
        PC_SET_HSIOM_SEL(PC_SS1_HSIOM_REG,
                                       PC_SS1_HSIOM_MASK,
                                       PC_SS1_HSIOM_POS,
                                       hsiomSel[PC_SS1_PIN_INDEX]);

        PC_spi_ss1_SetDriveMode((uint8) pinsDm[PC_SS1_PIN_INDEX]);

        PC_SET_INP_DIS(PC_spi_ss1_INP_DIS,
                                     PC_spi_ss1_MASK,
                                     (0u != (pinsInBuf & PC_SS1_PIN_MASK)));
    #endif /* (PC_SS1_PIN) */

    #if (PC_SS2_PIN)
        PC_SET_HSIOM_SEL(PC_SS2_HSIOM_REG,
                                       PC_SS2_HSIOM_MASK,
                                       PC_SS2_HSIOM_POS,
                                       hsiomSel[PC_SS2_PIN_INDEX]);

        PC_spi_ss2_SetDriveMode((uint8) pinsDm[PC_SS2_PIN_INDEX]);

        PC_SET_INP_DIS(PC_spi_ss2_INP_DIS,
                                     PC_spi_ss2_MASK,
                                     (0u != (pinsInBuf & PC_SS2_PIN_MASK)));
    #endif /* (PC_SS2_PIN) */

    #if (PC_SS3_PIN)
        PC_SET_HSIOM_SEL(PC_SS3_HSIOM_REG,
                                       PC_SS3_HSIOM_MASK,
                                       PC_SS3_HSIOM_POS,
                                       hsiomSel[PC_SS3_PIN_INDEX]);

        PC_spi_ss3_SetDriveMode((uint8) pinsDm[PC_SS3_PIN_INDEX]);

        PC_SET_INP_DIS(PC_spi_ss3_INP_DIS,
                                     PC_spi_ss3_MASK,
                                     (0u != (pinsInBuf & PC_SS3_PIN_MASK)));
    #endif /* (PC_SS3_PIN) */
    }

#endif /* (PC_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (PC_CY_SCBIP_V0 || PC_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: PC_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (PC_CTRL_REG & PC_CTRL_EC_AM_MODE)) &&
            (0u == (PC_I2C_CTRL_REG & PC_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            PC_CTRL_REG &= ~PC_CTRL_EC_AM_MODE;
            PC_CTRL_REG |=  PC_CTRL_EC_AM_MODE;
        }

        PC_I2C_SLAVE_CMD_REG = PC_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (PC_CY_SCBIP_V0 || PC_CY_SCBIP_V1) */


/* [] END OF FILE */
