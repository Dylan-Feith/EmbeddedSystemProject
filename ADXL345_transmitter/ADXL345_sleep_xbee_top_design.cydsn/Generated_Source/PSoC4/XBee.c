/*******************************************************************************
* File Name: XBee.c
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

#include "XBee_PVT.h"

#if (XBee_SCB_MODE_I2C_INC)
    #include "XBee_I2C_PVT.h"
#endif /* (XBee_SCB_MODE_I2C_INC) */

#if (XBee_SCB_MODE_EZI2C_INC)
    #include "XBee_EZI2C_PVT.h"
#endif /* (XBee_SCB_MODE_EZI2C_INC) */

#if (XBee_SCB_MODE_SPI_INC || XBee_SCB_MODE_UART_INC)
    #include "XBee_SPI_UART_PVT.h"
#endif /* (XBee_SCB_MODE_SPI_INC || XBee_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 XBee_scbMode = XBee_SCB_MODE_UNCONFIG;
    uint8 XBee_scbEnableWake;
    uint8 XBee_scbEnableIntr;

    /* I2C configuration variables */
    uint8 XBee_mode;
    uint8 XBee_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * XBee_rxBuffer;
    uint8  XBee_rxDataBits;
    uint32 XBee_rxBufferSize;

    volatile uint8 * XBee_txBuffer;
    uint8  XBee_txDataBits;
    uint32 XBee_txBufferSize;

    /* EZI2C configuration variables */
    uint8 XBee_numberOfAddr;
    uint8 XBee_subAddrSize;
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 XBee_initVar = 0u;

#if (XBee_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_XBee_CUSTOM_INTR_HANDLER)
    void (*XBee_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_XBee_CUSTOM_INTR_HANDLER) */
#endif /* (XBee_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void XBee_ScbEnableIntr(void);
static void XBee_ScbModeStop(void);
static void XBee_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: XBee_Init
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
void XBee_Init(void)
{
#if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    if (XBee_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        XBee_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (XBee_SCB_MODE_I2C_CONST_CFG)
    XBee_I2CInit();

#elif (XBee_SCB_MODE_SPI_CONST_CFG)
    XBee_SpiInit();

#elif (XBee_SCB_MODE_UART_CONST_CFG)
    XBee_UartInit();

#elif (XBee_SCB_MODE_EZI2C_CONST_CFG)
    XBee_EzI2CInit();

#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: XBee_Enable
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
void XBee_Enable(void)
{
#if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!XBee_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        XBee_CTRL_REG |= XBee_CTRL_ENABLED;

        XBee_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        XBee_ScbModePostEnable();
    }
#else
    XBee_CTRL_REG |= XBee_CTRL_ENABLED;

    XBee_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    XBee_ScbModePostEnable();
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: XBee_Start
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
*  XBee_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void XBee_Start(void)
{
    if (0u == XBee_initVar)
    {
        XBee_Init();
        XBee_initVar = 1u; /* Component was initialized */
    }

    XBee_Enable();
}


/*******************************************************************************
* Function Name: XBee_Stop
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
void XBee_Stop(void)
{
#if (XBee_SCB_IRQ_INTERNAL)
    XBee_DisableInt();
#endif /* (XBee_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    XBee_ScbModeStop();

    /* Disable SCB IP */
    XBee_CTRL_REG &= (uint32) ~XBee_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    XBee_SetTxInterruptMode(XBee_NO_INTR_SOURCES);

#if (XBee_SCB_IRQ_INTERNAL)
    XBee_ClearPendingInt();
#endif /* (XBee_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: XBee_SetRxFifoLevel
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
void XBee_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = XBee_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~XBee_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (XBee_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    XBee_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: XBee_SetTxFifoLevel
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
void XBee_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = XBee_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~XBee_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (XBee_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    XBee_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (XBee_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: XBee_SetCustomInterruptHandler
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
    void XBee_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_XBee_CUSTOM_INTR_HANDLER)
        XBee_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_XBee_CUSTOM_INTR_HANDLER) */
    }
#endif /* (XBee_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: XBee_ScbModeEnableIntr
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
static void XBee_ScbEnableIntr(void)
{
#if (XBee_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != XBee_scbEnableIntr)
        {
            XBee_EnableInt();
        }

    #else
        XBee_EnableInt();

    #endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (XBee_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: XBee_ScbModePostEnable
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
static void XBee_ScbModePostEnable(void)
{
#if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!XBee_CY_SCBIP_V1)
    if (XBee_SCB_MODE_SPI_RUNTM_CFG)
    {
        XBee_SpiPostEnable();
    }
    else if (XBee_SCB_MODE_UART_RUNTM_CFG)
    {
        XBee_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!XBee_CY_SCBIP_V1) */

#elif (XBee_SCB_MODE_SPI_CONST_CFG)
    XBee_SpiPostEnable();

#elif (XBee_SCB_MODE_UART_CONST_CFG)
    XBee_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: XBee_ScbModeStop
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
static void XBee_ScbModeStop(void)
{
#if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    if (XBee_SCB_MODE_I2C_RUNTM_CFG)
    {
        XBee_I2CStop();
    }
    else if (XBee_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        XBee_EzI2CStop();
    }
#if (!XBee_CY_SCBIP_V1)
    else if (XBee_SCB_MODE_SPI_RUNTM_CFG)
    {
        XBee_SpiStop();
    }
    else if (XBee_SCB_MODE_UART_RUNTM_CFG)
    {
        XBee_UartStop();
    }
#endif /* (!XBee_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (XBee_SCB_MODE_I2C_CONST_CFG)
    XBee_I2CStop();

#elif (XBee_SCB_MODE_EZI2C_CONST_CFG)
    XBee_EzI2CStop();

#elif (XBee_SCB_MODE_SPI_CONST_CFG)
    XBee_SpiStop();

#elif (XBee_SCB_MODE_UART_CONST_CFG)
    XBee_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (XBee_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: XBee_SetPins
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
    void XBee_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [XBee_SCB_PINS_NUMBER];
        uint32 pinsDm   [XBee_SCB_PINS_NUMBER];

    #if (!XBee_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!XBee_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < XBee_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = XBee_HSIOM_DEF_SEL;
            pinsDm[i]    = XBee_PIN_DM_ALG_HIZ;
        }

        if ((XBee_SCB_MODE_I2C   == mode) ||
           (XBee_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[XBee_RX_SCL_MOSI_PIN_INDEX] = XBee_HSIOM_I2C_SEL;
            hsiomSel[XBee_TX_SDA_MISO_PIN_INDEX] = XBee_HSIOM_I2C_SEL;

            pinsDm[XBee_RX_SCL_MOSI_PIN_INDEX] = XBee_PIN_DM_OD_LO;
            pinsDm[XBee_TX_SDA_MISO_PIN_INDEX] = XBee_PIN_DM_OD_LO;
        }
    #if (!XBee_CY_SCBIP_V1)
        else if (XBee_SCB_MODE_SPI == mode)
        {
            hsiomSel[XBee_RX_SCL_MOSI_PIN_INDEX] = XBee_HSIOM_SPI_SEL;
            hsiomSel[XBee_TX_SDA_MISO_PIN_INDEX] = XBee_HSIOM_SPI_SEL;
            hsiomSel[XBee_SCLK_PIN_INDEX] = XBee_HSIOM_SPI_SEL;

            if (XBee_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[XBee_RX_SCL_MOSI_PIN_INDEX] = XBee_PIN_DM_DIG_HIZ;
                pinsDm[XBee_TX_SDA_MISO_PIN_INDEX] = XBee_PIN_DM_STRONG;
                pinsDm[XBee_SCLK_PIN_INDEX] = XBee_PIN_DM_DIG_HIZ;

            #if (XBee_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[XBee_SS0_PIN_INDEX] = XBee_HSIOM_SPI_SEL;
                pinsDm  [XBee_SS0_PIN_INDEX] = XBee_PIN_DM_DIG_HIZ;
            #endif /* (XBee_SS0_PIN) */

            #if (XBee_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= XBee_TX_SDA_MISO_PIN_MASK;
            #endif /* (XBee_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[XBee_RX_SCL_MOSI_PIN_INDEX] = XBee_PIN_DM_STRONG;
                pinsDm[XBee_TX_SDA_MISO_PIN_INDEX] = XBee_PIN_DM_DIG_HIZ;
                pinsDm[XBee_SCLK_PIN_INDEX] = XBee_PIN_DM_STRONG;

            #if (XBee_SS0_PIN)
                hsiomSel [XBee_SS0_PIN_INDEX] = XBee_HSIOM_SPI_SEL;
                pinsDm   [XBee_SS0_PIN_INDEX] = XBee_PIN_DM_STRONG;
                pinsInBuf |= XBee_SS0_PIN_MASK;
            #endif /* (XBee_SS0_PIN) */

            #if (XBee_SS1_PIN)
                hsiomSel [XBee_SS1_PIN_INDEX] = XBee_HSIOM_SPI_SEL;
                pinsDm   [XBee_SS1_PIN_INDEX] = XBee_PIN_DM_STRONG;
                pinsInBuf |= XBee_SS1_PIN_MASK;
            #endif /* (XBee_SS1_PIN) */

            #if (XBee_SS2_PIN)
                hsiomSel [XBee_SS2_PIN_INDEX] = XBee_HSIOM_SPI_SEL;
                pinsDm   [XBee_SS2_PIN_INDEX] = XBee_PIN_DM_STRONG;
                pinsInBuf |= XBee_SS2_PIN_MASK;
            #endif /* (XBee_SS2_PIN) */

            #if (XBee_SS3_PIN)
                hsiomSel [XBee_SS3_PIN_INDEX] = XBee_HSIOM_SPI_SEL;
                pinsDm   [XBee_SS3_PIN_INDEX] = XBee_PIN_DM_STRONG;
                pinsInBuf |= XBee_SS3_PIN_MASK;
            #endif /* (XBee_SS3_PIN) */

                /* Disable input buffers */
            #if (XBee_RX_SCL_MOSI_PIN)
                pinsInBuf |= XBee_RX_SCL_MOSI_PIN_MASK;
            #endif /* (XBee_RX_SCL_MOSI_PIN) */

             #if (XBee_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= XBee_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (XBee_RX_WAKE_SCL_MOSI_PIN) */

            #if (XBee_SCLK_PIN)
                pinsInBuf |= XBee_SCLK_PIN_MASK;
            #endif /* (XBee_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (XBee_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[XBee_TX_SDA_MISO_PIN_INDEX] = XBee_HSIOM_UART_SEL;
                pinsDm  [XBee_TX_SDA_MISO_PIN_INDEX] = XBee_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (XBee_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[XBee_RX_SCL_MOSI_PIN_INDEX] = XBee_HSIOM_UART_SEL;
                    pinsDm  [XBee_RX_SCL_MOSI_PIN_INDEX] = XBee_PIN_DM_DIG_HIZ;
                }

                if (0u != (XBee_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[XBee_TX_SDA_MISO_PIN_INDEX] = XBee_HSIOM_UART_SEL;
                    pinsDm  [XBee_TX_SDA_MISO_PIN_INDEX] = XBee_PIN_DM_STRONG;

                #if (XBee_TX_SDA_MISO_PIN)
                     pinsInBuf |= XBee_TX_SDA_MISO_PIN_MASK;
                #endif /* (XBee_TX_SDA_MISO_PIN) */
                }

            #if !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
                if (XBee_UART_MODE_STD == subMode)
                {
                    if (0u != (XBee_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[XBee_SCLK_PIN_INDEX] = XBee_HSIOM_UART_SEL;
                        pinsDm  [XBee_SCLK_PIN_INDEX] = XBee_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (XBee_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[XBee_SS0_PIN_INDEX] = XBee_HSIOM_UART_SEL;
                        pinsDm  [XBee_SS0_PIN_INDEX] = XBee_PIN_DM_STRONG;

                    #if (XBee_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= XBee_SS0_PIN_MASK;
                    #endif /* (XBee_SS0_PIN) */
                    }
                }
            #endif /* !(XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */
            }
        }
    #endif /* (!XBee_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (XBee_RX_WAKE_SCL_MOSI_PIN)
        XBee_SET_HSIOM_SEL(XBee_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       XBee_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       XBee_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[XBee_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        XBee_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[XBee_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        XBee_SET_INP_DIS(XBee_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     XBee_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & XBee_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        XBee_SET_INCFG_TYPE(XBee_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        XBee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        XBee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        XBee_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (XBee_RX_WAKE_SCL_MOSI_PIN) */

    #if (XBee_RX_SCL_MOSI_PIN)
        XBee_SET_HSIOM_SEL(XBee_RX_SCL_MOSI_HSIOM_REG,
                                       XBee_RX_SCL_MOSI_HSIOM_MASK,
                                       XBee_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[XBee_RX_SCL_MOSI_PIN_INDEX]);

        XBee_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[XBee_RX_SCL_MOSI_PIN_INDEX]);

    #if (!XBee_CY_SCBIP_V1)
        XBee_SET_INP_DIS(XBee_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     XBee_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & XBee_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!XBee_CY_SCBIP_V1) */
    #endif /* (XBee_RX_SCL_MOSI_PIN) */

    #if (XBee_TX_SDA_MISO_PIN)
        XBee_SET_HSIOM_SEL(XBee_TX_SDA_MISO_HSIOM_REG,
                                       XBee_TX_SDA_MISO_HSIOM_MASK,
                                       XBee_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[XBee_TX_SDA_MISO_PIN_INDEX]);

        XBee_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[XBee_TX_SDA_MISO_PIN_INDEX]);

    #if (!XBee_CY_SCBIP_V1)
        XBee_SET_INP_DIS(XBee_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     XBee_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & XBee_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!XBee_CY_SCBIP_V1) */
    #endif /* (XBee_RX_SCL_MOSI_PIN) */

    #if (XBee_SCLK_PIN)
        XBee_SET_HSIOM_SEL(XBee_SCLK_HSIOM_REG,
                                       XBee_SCLK_HSIOM_MASK,
                                       XBee_SCLK_HSIOM_POS,
                                       hsiomSel[XBee_SCLK_PIN_INDEX]);

        XBee_spi_sclk_SetDriveMode((uint8) pinsDm[XBee_SCLK_PIN_INDEX]);

        XBee_SET_INP_DIS(XBee_spi_sclk_INP_DIS,
                                     XBee_spi_sclk_MASK,
                                     (0u != (pinsInBuf & XBee_SCLK_PIN_MASK)));
    #endif /* (XBee_SCLK_PIN) */

    #if (XBee_SS0_PIN)
        XBee_SET_HSIOM_SEL(XBee_SS0_HSIOM_REG,
                                       XBee_SS0_HSIOM_MASK,
                                       XBee_SS0_HSIOM_POS,
                                       hsiomSel[XBee_SS0_PIN_INDEX]);

        XBee_spi_ss0_SetDriveMode((uint8) pinsDm[XBee_SS0_PIN_INDEX]);

        XBee_SET_INP_DIS(XBee_spi_ss0_INP_DIS,
                                     XBee_spi_ss0_MASK,
                                     (0u != (pinsInBuf & XBee_SS0_PIN_MASK)));
    #endif /* (XBee_SS0_PIN) */

    #if (XBee_SS1_PIN)
        XBee_SET_HSIOM_SEL(XBee_SS1_HSIOM_REG,
                                       XBee_SS1_HSIOM_MASK,
                                       XBee_SS1_HSIOM_POS,
                                       hsiomSel[XBee_SS1_PIN_INDEX]);

        XBee_spi_ss1_SetDriveMode((uint8) pinsDm[XBee_SS1_PIN_INDEX]);

        XBee_SET_INP_DIS(XBee_spi_ss1_INP_DIS,
                                     XBee_spi_ss1_MASK,
                                     (0u != (pinsInBuf & XBee_SS1_PIN_MASK)));
    #endif /* (XBee_SS1_PIN) */

    #if (XBee_SS2_PIN)
        XBee_SET_HSIOM_SEL(XBee_SS2_HSIOM_REG,
                                       XBee_SS2_HSIOM_MASK,
                                       XBee_SS2_HSIOM_POS,
                                       hsiomSel[XBee_SS2_PIN_INDEX]);

        XBee_spi_ss2_SetDriveMode((uint8) pinsDm[XBee_SS2_PIN_INDEX]);

        XBee_SET_INP_DIS(XBee_spi_ss2_INP_DIS,
                                     XBee_spi_ss2_MASK,
                                     (0u != (pinsInBuf & XBee_SS2_PIN_MASK)));
    #endif /* (XBee_SS2_PIN) */

    #if (XBee_SS3_PIN)
        XBee_SET_HSIOM_SEL(XBee_SS3_HSIOM_REG,
                                       XBee_SS3_HSIOM_MASK,
                                       XBee_SS3_HSIOM_POS,
                                       hsiomSel[XBee_SS3_PIN_INDEX]);

        XBee_spi_ss3_SetDriveMode((uint8) pinsDm[XBee_SS3_PIN_INDEX]);

        XBee_SET_INP_DIS(XBee_spi_ss3_INP_DIS,
                                     XBee_spi_ss3_MASK,
                                     (0u != (pinsInBuf & XBee_SS3_PIN_MASK)));
    #endif /* (XBee_SS3_PIN) */
    }

#endif /* (XBee_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: XBee_I2CSlaveNackGeneration
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
    void XBee_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (XBee_CTRL_REG & XBee_CTRL_EC_AM_MODE)) &&
            (0u == (XBee_I2C_CTRL_REG & XBee_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            XBee_CTRL_REG &= ~XBee_CTRL_EC_AM_MODE;
            XBee_CTRL_REG |=  XBee_CTRL_EC_AM_MODE;
        }

        XBee_I2C_SLAVE_CMD_REG = XBee_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (XBee_CY_SCBIP_V0 || XBee_CY_SCBIP_V1) */


/* [] END OF FILE */
