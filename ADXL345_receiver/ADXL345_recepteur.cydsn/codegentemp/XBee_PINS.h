/*******************************************************************************
* File Name: XBee_PINS.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_XBee_H)
#define CY_SCB_PINS_XBee_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define XBee_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define XBee_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define XBee_REMOVE_TX_SDA_MISO_PIN      (1u)
#define XBee_REMOVE_SCLK_PIN      (1u)
#define XBee_REMOVE_SS0_PIN      (1u)
#define XBee_REMOVE_SS1_PIN                 (1u)
#define XBee_REMOVE_SS2_PIN                 (1u)
#define XBee_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define XBee_REMOVE_I2C_PINS                (1u)
#define XBee_REMOVE_SPI_MASTER_PINS         (1u)
#define XBee_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define XBee_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define XBee_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define XBee_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define XBee_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define XBee_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define XBee_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define XBee_REMOVE_SPI_SLAVE_PINS          (1u)
#define XBee_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define XBee_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define XBee_REMOVE_UART_TX_PIN             (0u)
#define XBee_REMOVE_UART_RX_TX_PIN          (1u)
#define XBee_REMOVE_UART_RX_PIN             (0u)
#define XBee_REMOVE_UART_RX_WAKE_PIN        (1u)
#define XBee_REMOVE_UART_RTS_PIN            (1u)
#define XBee_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define XBee_RX_WAKE_SCL_MOSI_PIN (0u == XBee_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define XBee_RX_SCL_MOSI_PIN     (0u == XBee_REMOVE_RX_SCL_MOSI_PIN)
#define XBee_TX_SDA_MISO_PIN     (0u == XBee_REMOVE_TX_SDA_MISO_PIN)
#define XBee_SCLK_PIN     (0u == XBee_REMOVE_SCLK_PIN)
#define XBee_SS0_PIN     (0u == XBee_REMOVE_SS0_PIN)
#define XBee_SS1_PIN                (0u == XBee_REMOVE_SS1_PIN)
#define XBee_SS2_PIN                (0u == XBee_REMOVE_SS2_PIN)
#define XBee_SS3_PIN                (0u == XBee_REMOVE_SS3_PIN)

/* Mode defined pins */
#define XBee_I2C_PINS               (0u == XBee_REMOVE_I2C_PINS)
#define XBee_SPI_MASTER_PINS        (0u == XBee_REMOVE_SPI_MASTER_PINS)
#define XBee_SPI_MASTER_SCLK_PIN    (0u == XBee_REMOVE_SPI_MASTER_SCLK_PIN)
#define XBee_SPI_MASTER_MOSI_PIN    (0u == XBee_REMOVE_SPI_MASTER_MOSI_PIN)
#define XBee_SPI_MASTER_MISO_PIN    (0u == XBee_REMOVE_SPI_MASTER_MISO_PIN)
#define XBee_SPI_MASTER_SS0_PIN     (0u == XBee_REMOVE_SPI_MASTER_SS0_PIN)
#define XBee_SPI_MASTER_SS1_PIN     (0u == XBee_REMOVE_SPI_MASTER_SS1_PIN)
#define XBee_SPI_MASTER_SS2_PIN     (0u == XBee_REMOVE_SPI_MASTER_SS2_PIN)
#define XBee_SPI_MASTER_SS3_PIN     (0u == XBee_REMOVE_SPI_MASTER_SS3_PIN)
#define XBee_SPI_SLAVE_PINS         (0u == XBee_REMOVE_SPI_SLAVE_PINS)
#define XBee_SPI_SLAVE_MOSI_PIN     (0u == XBee_REMOVE_SPI_SLAVE_MOSI_PIN)
#define XBee_SPI_SLAVE_MISO_PIN     (0u == XBee_REMOVE_SPI_SLAVE_MISO_PIN)
#define XBee_UART_TX_PIN            (0u == XBee_REMOVE_UART_TX_PIN)
#define XBee_UART_RX_TX_PIN         (0u == XBee_REMOVE_UART_RX_TX_PIN)
#define XBee_UART_RX_PIN            (0u == XBee_REMOVE_UART_RX_PIN)
#define XBee_UART_RX_WAKE_PIN       (0u == XBee_REMOVE_UART_RX_WAKE_PIN)
#define XBee_UART_RTS_PIN           (0u == XBee_REMOVE_UART_RTS_PIN)
#define XBee_UART_CTS_PIN           (0u == XBee_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (XBee_RX_WAKE_SCL_MOSI_PIN)
    #include "XBee_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (XBee_RX_SCL_MOSI) */

#if (XBee_RX_SCL_MOSI_PIN)
    #include "XBee_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (XBee_RX_SCL_MOSI) */

#if (XBee_TX_SDA_MISO_PIN)
    #include "XBee_uart_tx_i2c_sda_spi_miso.h"
#endif /* (XBee_TX_SDA_MISO) */

#if (XBee_SCLK_PIN)
    #include "XBee_spi_sclk.h"
#endif /* (XBee_SCLK) */

#if (XBee_SS0_PIN)
    #include "XBee_spi_ss0.h"
#endif /* (XBee_SS0_PIN) */

#if (XBee_SS1_PIN)
    #include "XBee_spi_ss1.h"
#endif /* (XBee_SS1_PIN) */

#if (XBee_SS2_PIN)
    #include "XBee_spi_ss2.h"
#endif /* (XBee_SS2_PIN) */

#if (XBee_SS3_PIN)
    #include "XBee_spi_ss3.h"
#endif /* (XBee_SS3_PIN) */

#if (XBee_I2C_PINS)
    #include "XBee_scl.h"
    #include "XBee_sda.h"
#endif /* (XBee_I2C_PINS) */

#if (XBee_SPI_MASTER_PINS)
#if (XBee_SPI_MASTER_SCLK_PIN)
    #include "XBee_sclk_m.h"
#endif /* (XBee_SPI_MASTER_SCLK_PIN) */

#if (XBee_SPI_MASTER_MOSI_PIN)
    #include "XBee_mosi_m.h"
#endif /* (XBee_SPI_MASTER_MOSI_PIN) */

#if (XBee_SPI_MASTER_MISO_PIN)
    #include "XBee_miso_m.h"
#endif /*(XBee_SPI_MASTER_MISO_PIN) */
#endif /* (XBee_SPI_MASTER_PINS) */

#if (XBee_SPI_SLAVE_PINS)
    #include "XBee_sclk_s.h"
    #include "XBee_ss_s.h"

#if (XBee_SPI_SLAVE_MOSI_PIN)
    #include "XBee_mosi_s.h"
#endif /* (XBee_SPI_SLAVE_MOSI_PIN) */

#if (XBee_SPI_SLAVE_MISO_PIN)
    #include "XBee_miso_s.h"
#endif /*(XBee_SPI_SLAVE_MISO_PIN) */
#endif /* (XBee_SPI_SLAVE_PINS) */

#if (XBee_SPI_MASTER_SS0_PIN)
    #include "XBee_ss0_m.h"
#endif /* (XBee_SPI_MASTER_SS0_PIN) */

#if (XBee_SPI_MASTER_SS1_PIN)
    #include "XBee_ss1_m.h"
#endif /* (XBee_SPI_MASTER_SS1_PIN) */

#if (XBee_SPI_MASTER_SS2_PIN)
    #include "XBee_ss2_m.h"
#endif /* (XBee_SPI_MASTER_SS2_PIN) */

#if (XBee_SPI_MASTER_SS3_PIN)
    #include "XBee_ss3_m.h"
#endif /* (XBee_SPI_MASTER_SS3_PIN) */

#if (XBee_UART_TX_PIN)
    #include "XBee_tx.h"
#endif /* (XBee_UART_TX_PIN) */

#if (XBee_UART_RX_TX_PIN)
    #include "XBee_rx_tx.h"
#endif /* (XBee_UART_RX_TX_PIN) */

#if (XBee_UART_RX_PIN)
    #include "XBee_rx.h"
#endif /* (XBee_UART_RX_PIN) */

#if (XBee_UART_RX_WAKE_PIN)
    #include "XBee_rx_wake.h"
#endif /* (XBee_UART_RX_WAKE_PIN) */

#if (XBee_UART_RTS_PIN)
    #include "XBee_rts.h"
#endif /* (XBee_UART_RTS_PIN) */

#if (XBee_UART_CTS_PIN)
    #include "XBee_cts.h"
#endif /* (XBee_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (XBee_RX_WAKE_SCL_MOSI_PIN)
    #define XBee_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) XBee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define XBee_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) XBee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define XBee_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (XBee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define XBee_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (XBee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define XBee_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) XBee_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define XBee_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) XBee_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define XBee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (XBee_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define XBee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) XBee_INTCFG_TYPE_MASK << \
                                      XBee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (XBee_RX_WAKE_SCL_MOSI_PIN) */

#if (XBee_RX_SCL_MOSI_PIN)
    #define XBee_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) XBee_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define XBee_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) XBee_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define XBee_RX_SCL_MOSI_HSIOM_MASK  (XBee_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define XBee_RX_SCL_MOSI_HSIOM_POS   (XBee_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (XBee_RX_SCL_MOSI_PIN) */

#if (XBee_TX_SDA_MISO_PIN)
    #define XBee_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) XBee_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define XBee_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) XBee_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define XBee_TX_SDA_MISO_HSIOM_MASK  (XBee_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define XBee_TX_SDA_MISO_HSIOM_POS   (XBee_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (XBee_TX_SDA_MISO_PIN) */

#if (XBee_SCLK_PIN)
    #define XBee_SCLK_HSIOM_REG   (*(reg32 *) XBee_spi_sclk__0__HSIOM)
    #define XBee_SCLK_HSIOM_PTR   ( (reg32 *) XBee_spi_sclk__0__HSIOM)
    #define XBee_SCLK_HSIOM_MASK  (XBee_spi_sclk__0__HSIOM_MASK)
    #define XBee_SCLK_HSIOM_POS   (XBee_spi_sclk__0__HSIOM_SHIFT)
#endif /* (XBee_SCLK_PIN) */

#if (XBee_SS0_PIN)
    #define XBee_SS0_HSIOM_REG   (*(reg32 *) XBee_spi_ss0__0__HSIOM)
    #define XBee_SS0_HSIOM_PTR   ( (reg32 *) XBee_spi_ss0__0__HSIOM)
    #define XBee_SS0_HSIOM_MASK  (XBee_spi_ss0__0__HSIOM_MASK)
    #define XBee_SS0_HSIOM_POS   (XBee_spi_ss0__0__HSIOM_SHIFT)
#endif /* (XBee_SS0_PIN) */

#if (XBee_SS1_PIN)
    #define XBee_SS1_HSIOM_REG      (*(reg32 *) XBee_spi_ss1__0__HSIOM)
    #define XBee_SS1_HSIOM_PTR      ( (reg32 *) XBee_spi_ss1__0__HSIOM)
    #define XBee_SS1_HSIOM_MASK     (XBee_spi_ss1__0__HSIOM_MASK)
    #define XBee_SS1_HSIOM_POS      (XBee_spi_ss1__0__HSIOM_SHIFT)
#endif /* (XBee_SS1_PIN) */

#if (XBee_SS2_PIN)
    #define XBee_SS2_HSIOM_REG     (*(reg32 *) XBee_spi_ss2__0__HSIOM)
    #define XBee_SS2_HSIOM_PTR     ( (reg32 *) XBee_spi_ss2__0__HSIOM)
    #define XBee_SS2_HSIOM_MASK    (XBee_spi_ss2__0__HSIOM_MASK)
    #define XBee_SS2_HSIOM_POS     (XBee_spi_ss2__0__HSIOM_SHIFT)
#endif /* (XBee_SS2_PIN) */

#if (XBee_SS3_PIN)
    #define XBee_SS3_HSIOM_REG     (*(reg32 *) XBee_spi_ss3__0__HSIOM)
    #define XBee_SS3_HSIOM_PTR     ( (reg32 *) XBee_spi_ss3__0__HSIOM)
    #define XBee_SS3_HSIOM_MASK    (XBee_spi_ss3__0__HSIOM_MASK)
    #define XBee_SS3_HSIOM_POS     (XBee_spi_ss3__0__HSIOM_SHIFT)
#endif /* (XBee_SS3_PIN) */

#if (XBee_I2C_PINS)
    #define XBee_SCL_HSIOM_REG     (*(reg32 *) XBee_scl__0__HSIOM)
    #define XBee_SCL_HSIOM_PTR     ( (reg32 *) XBee_scl__0__HSIOM)
    #define XBee_SCL_HSIOM_MASK    (XBee_scl__0__HSIOM_MASK)
    #define XBee_SCL_HSIOM_POS     (XBee_scl__0__HSIOM_SHIFT)

    #define XBee_SDA_HSIOM_REG     (*(reg32 *) XBee_sda__0__HSIOM)
    #define XBee_SDA_HSIOM_PTR     ( (reg32 *) XBee_sda__0__HSIOM)
    #define XBee_SDA_HSIOM_MASK    (XBee_sda__0__HSIOM_MASK)
    #define XBee_SDA_HSIOM_POS     (XBee_sda__0__HSIOM_SHIFT)
#endif /* (XBee_I2C_PINS) */

#if (XBee_SPI_MASTER_SCLK_PIN)
    #define XBee_SCLK_M_HSIOM_REG   (*(reg32 *) XBee_sclk_m__0__HSIOM)
    #define XBee_SCLK_M_HSIOM_PTR   ( (reg32 *) XBee_sclk_m__0__HSIOM)
    #define XBee_SCLK_M_HSIOM_MASK  (XBee_sclk_m__0__HSIOM_MASK)
    #define XBee_SCLK_M_HSIOM_POS   (XBee_sclk_m__0__HSIOM_SHIFT)
#endif /* (XBee_SPI_MASTER_SCLK_PIN) */

#if (XBee_SPI_MASTER_SS0_PIN)
    #define XBee_SS0_M_HSIOM_REG    (*(reg32 *) XBee_ss0_m__0__HSIOM)
    #define XBee_SS0_M_HSIOM_PTR    ( (reg32 *) XBee_ss0_m__0__HSIOM)
    #define XBee_SS0_M_HSIOM_MASK   (XBee_ss0_m__0__HSIOM_MASK)
    #define XBee_SS0_M_HSIOM_POS    (XBee_ss0_m__0__HSIOM_SHIFT)
#endif /* (XBee_SPI_MASTER_SS0_PIN) */

#if (XBee_SPI_MASTER_SS1_PIN)
    #define XBee_SS1_M_HSIOM_REG    (*(reg32 *) XBee_ss1_m__0__HSIOM)
    #define XBee_SS1_M_HSIOM_PTR    ( (reg32 *) XBee_ss1_m__0__HSIOM)
    #define XBee_SS1_M_HSIOM_MASK   (XBee_ss1_m__0__HSIOM_MASK)
    #define XBee_SS1_M_HSIOM_POS    (XBee_ss1_m__0__HSIOM_SHIFT)
#endif /* (XBee_SPI_MASTER_SS1_PIN) */

#if (XBee_SPI_MASTER_SS2_PIN)
    #define XBee_SS2_M_HSIOM_REG    (*(reg32 *) XBee_ss2_m__0__HSIOM)
    #define XBee_SS2_M_HSIOM_PTR    ( (reg32 *) XBee_ss2_m__0__HSIOM)
    #define XBee_SS2_M_HSIOM_MASK   (XBee_ss2_m__0__HSIOM_MASK)
    #define XBee_SS2_M_HSIOM_POS    (XBee_ss2_m__0__HSIOM_SHIFT)
#endif /* (XBee_SPI_MASTER_SS2_PIN) */

#if (XBee_SPI_MASTER_SS3_PIN)
    #define XBee_SS3_M_HSIOM_REG    (*(reg32 *) XBee_ss3_m__0__HSIOM)
    #define XBee_SS3_M_HSIOM_PTR    ( (reg32 *) XBee_ss3_m__0__HSIOM)
    #define XBee_SS3_M_HSIOM_MASK   (XBee_ss3_m__0__HSIOM_MASK)
    #define XBee_SS3_M_HSIOM_POS    (XBee_ss3_m__0__HSIOM_SHIFT)
#endif /* (XBee_SPI_MASTER_SS3_PIN) */

#if (XBee_UART_TX_PIN)
    #define XBee_TX_HSIOM_REG   (*(reg32 *) XBee_tx__0__HSIOM)
    #define XBee_TX_HSIOM_PTR   ( (reg32 *) XBee_tx_0__HSIOM)
    #define XBee_TX_HSIOM_MASK  (XBee_tx__0__HSIOM_MASK)
    #define XBee_TX_HSIOM_POS   (XBee_tx__0__HSIOM_SHIFT)
#endif /* (XBee_UART_TX_PIN) */

#if (XBee_UART_RTS_PIN)
    #define XBee_RTS_HSIOM_REG  (*(reg32 *) XBee_rts__0__HSIOM)
    #define XBee_RTS_HSIOM_PTR  ( (reg32 *) XBee_rts__0__HSIOM)
    #define XBee_RTS_HSIOM_MASK (XBee_rts__0__HSIOM_MASK)
    #define XBee_RTS_HSIOM_POS  (XBee_rts__0__HSIOM_SHIFT)
#endif /* (XBee_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define XBee_HSIOM_DEF_SEL      (0x00u)
#define XBee_HSIOM_GPIO_SEL     (0x00u)
#define XBee_HSIOM_UART_SEL     (0x09u)
#define XBee_HSIOM_I2C_SEL      (0x0Eu)
#define XBee_HSIOM_SPI_SEL      (0x0Fu)

#define XBee_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define XBee_RX_SCL_MOSI_PIN_INDEX       (0u)
#define XBee_TX_SDA_MISO_PIN_INDEX       (1u)
#define XBee_SCLK_PIN_INDEX       (2u)
#define XBee_SS0_PIN_INDEX       (3u)
#define XBee_SS1_PIN_INDEX                  (4u)
#define XBee_SS2_PIN_INDEX                  (5u)
#define XBee_SS3_PIN_INDEX                  (6u)

#define XBee_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << XBee_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define XBee_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << XBee_RX_SCL_MOSI_PIN_INDEX)
#define XBee_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << XBee_TX_SDA_MISO_PIN_INDEX)
#define XBee_SCLK_PIN_MASK     ((uint32) 0x01u << XBee_SCLK_PIN_INDEX)
#define XBee_SS0_PIN_MASK     ((uint32) 0x01u << XBee_SS0_PIN_INDEX)
#define XBee_SS1_PIN_MASK                ((uint32) 0x01u << XBee_SS1_PIN_INDEX)
#define XBee_SS2_PIN_MASK                ((uint32) 0x01u << XBee_SS2_PIN_INDEX)
#define XBee_SS3_PIN_MASK                ((uint32) 0x01u << XBee_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define XBee_INTCFG_TYPE_MASK           (0x03u)
#define XBee_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define XBee_PIN_DM_ALG_HIZ  (0u)
#define XBee_PIN_DM_DIG_HIZ  (1u)
#define XBee_PIN_DM_OD_LO    (4u)
#define XBee_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define XBee_DM_MASK    (0x7u)
#define XBee_DM_SIZE    (3)
#define XBee_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) XBee_DM_MASK << (XBee_DM_SIZE * (pos)))) >> \
                                                              (XBee_DM_SIZE * (pos)) )

#if (XBee_TX_SDA_MISO_PIN)
    #define XBee_CHECK_TX_SDA_MISO_PIN_USED \
                (XBee_PIN_DM_ALG_HIZ != \
                    XBee_GET_P4_PIN_DM(XBee_uart_tx_i2c_sda_spi_miso_PC, \
                                                   XBee_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (XBee_TX_SDA_MISO_PIN) */

#if (XBee_SS0_PIN)
    #define XBee_CHECK_SS0_PIN_USED \
                (XBee_PIN_DM_ALG_HIZ != \
                    XBee_GET_P4_PIN_DM(XBee_spi_ss0_PC, \
                                                   XBee_spi_ss0_SHIFT))
#endif /* (XBee_SS0_PIN) */

/* Set bits-mask in register */
#define XBee_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define XBee_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define XBee_SET_HSIOM_SEL(reg, mask, pos, sel) XBee_SET_REGISTER_BITS(reg, mask, pos, sel)
#define XBee_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        XBee_SET_REGISTER_BITS(reg, mask, pos, intType)
#define XBee_SET_INP_DIS(reg, mask, val) XBee_SET_REGISTER_BIT(reg, mask, val)

/* XBee_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  XBee_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (XBee_CY_SCBIP_V0)
#if (XBee_I2C_PINS)
    #define XBee_SET_I2C_SCL_DR(val) XBee_scl_Write(val)

    #define XBee_SET_I2C_SCL_HSIOM_SEL(sel) \
                          XBee_SET_HSIOM_SEL(XBee_SCL_HSIOM_REG,  \
                                                         XBee_SCL_HSIOM_MASK, \
                                                         XBee_SCL_HSIOM_POS,  \
                                                         (sel))
    #define XBee_WAIT_SCL_SET_HIGH  (0u == XBee_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (XBee_RX_WAKE_SCL_MOSI_PIN)
    #define XBee_SET_I2C_SCL_DR(val) \
                            XBee_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define XBee_SET_I2C_SCL_HSIOM_SEL(sel) \
                    XBee_SET_HSIOM_SEL(XBee_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   XBee_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   XBee_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define XBee_WAIT_SCL_SET_HIGH  (0u == XBee_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (XBee_RX_SCL_MOSI_PIN)
    #define XBee_SET_I2C_SCL_DR(val) \
                            XBee_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define XBee_SET_I2C_SCL_HSIOM_SEL(sel) \
                            XBee_SET_HSIOM_SEL(XBee_RX_SCL_MOSI_HSIOM_REG,  \
                                                           XBee_RX_SCL_MOSI_HSIOM_MASK, \
                                                           XBee_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define XBee_WAIT_SCL_SET_HIGH  (0u == XBee_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define XBee_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define XBee_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define XBee_WAIT_SCL_SET_HIGH  (0u)
#endif /* (XBee_I2C_PINS) */

/* SCB I2C: sda signal */
#if (XBee_I2C_PINS)
    #define XBee_WAIT_SDA_SET_HIGH  (0u == XBee_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (XBee_TX_SDA_MISO_PIN)
    #define XBee_WAIT_SDA_SET_HIGH  (0u == XBee_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define XBee_WAIT_SDA_SET_HIGH  (0u)
#endif /* (XBee_MOSI_SCL_RX_PIN) */
#endif /* (XBee_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define XBee_REMOVE_MOSI_SCL_RX_WAKE_PIN    XBee_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define XBee_REMOVE_MOSI_SCL_RX_PIN         XBee_REMOVE_RX_SCL_MOSI_PIN
#define XBee_REMOVE_MISO_SDA_TX_PIN         XBee_REMOVE_TX_SDA_MISO_PIN
#ifndef XBee_REMOVE_SCLK_PIN
#define XBee_REMOVE_SCLK_PIN                XBee_REMOVE_SCLK_PIN
#endif /* XBee_REMOVE_SCLK_PIN */
#ifndef XBee_REMOVE_SS0_PIN
#define XBee_REMOVE_SS0_PIN                 XBee_REMOVE_SS0_PIN
#endif /* XBee_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define XBee_MOSI_SCL_RX_WAKE_PIN   XBee_RX_WAKE_SCL_MOSI_PIN
#define XBee_MOSI_SCL_RX_PIN        XBee_RX_SCL_MOSI_PIN
#define XBee_MISO_SDA_TX_PIN        XBee_TX_SDA_MISO_PIN
#ifndef XBee_SCLK_PIN
#define XBee_SCLK_PIN               XBee_SCLK_PIN
#endif /* XBee_SCLK_PIN */
#ifndef XBee_SS0_PIN
#define XBee_SS0_PIN                XBee_SS0_PIN
#endif /* XBee_SS0_PIN */

#if (XBee_MOSI_SCL_RX_WAKE_PIN)
    #define XBee_MOSI_SCL_RX_WAKE_HSIOM_REG     XBee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define XBee_MOSI_SCL_RX_WAKE_HSIOM_PTR     XBee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define XBee_MOSI_SCL_RX_WAKE_HSIOM_MASK    XBee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define XBee_MOSI_SCL_RX_WAKE_HSIOM_POS     XBee_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define XBee_MOSI_SCL_RX_WAKE_INTCFG_REG    XBee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define XBee_MOSI_SCL_RX_WAKE_INTCFG_PTR    XBee_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define XBee_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   XBee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define XBee_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  XBee_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (XBee_RX_WAKE_SCL_MOSI_PIN) */

#if (XBee_MOSI_SCL_RX_PIN)
    #define XBee_MOSI_SCL_RX_HSIOM_REG      XBee_RX_SCL_MOSI_HSIOM_REG
    #define XBee_MOSI_SCL_RX_HSIOM_PTR      XBee_RX_SCL_MOSI_HSIOM_PTR
    #define XBee_MOSI_SCL_RX_HSIOM_MASK     XBee_RX_SCL_MOSI_HSIOM_MASK
    #define XBee_MOSI_SCL_RX_HSIOM_POS      XBee_RX_SCL_MOSI_HSIOM_POS
#endif /* (XBee_MOSI_SCL_RX_PIN) */

#if (XBee_MISO_SDA_TX_PIN)
    #define XBee_MISO_SDA_TX_HSIOM_REG      XBee_TX_SDA_MISO_HSIOM_REG
    #define XBee_MISO_SDA_TX_HSIOM_PTR      XBee_TX_SDA_MISO_HSIOM_REG
    #define XBee_MISO_SDA_TX_HSIOM_MASK     XBee_TX_SDA_MISO_HSIOM_REG
    #define XBee_MISO_SDA_TX_HSIOM_POS      XBee_TX_SDA_MISO_HSIOM_REG
#endif /* (XBee_MISO_SDA_TX_PIN_PIN) */

#if (XBee_SCLK_PIN)
    #ifndef XBee_SCLK_HSIOM_REG
    #define XBee_SCLK_HSIOM_REG     XBee_SCLK_HSIOM_REG
    #define XBee_SCLK_HSIOM_PTR     XBee_SCLK_HSIOM_PTR
    #define XBee_SCLK_HSIOM_MASK    XBee_SCLK_HSIOM_MASK
    #define XBee_SCLK_HSIOM_POS     XBee_SCLK_HSIOM_POS
    #endif /* XBee_SCLK_HSIOM_REG */
#endif /* (XBee_SCLK_PIN) */

#if (XBee_SS0_PIN)
    #ifndef XBee_SS0_HSIOM_REG
    #define XBee_SS0_HSIOM_REG      XBee_SS0_HSIOM_REG
    #define XBee_SS0_HSIOM_PTR      XBee_SS0_HSIOM_PTR
    #define XBee_SS0_HSIOM_MASK     XBee_SS0_HSIOM_MASK
    #define XBee_SS0_HSIOM_POS      XBee_SS0_HSIOM_POS
    #endif /* XBee_SS0_HSIOM_REG */
#endif /* (XBee_SS0_PIN) */

#define XBee_MOSI_SCL_RX_WAKE_PIN_INDEX XBee_RX_WAKE_SCL_MOSI_PIN_INDEX
#define XBee_MOSI_SCL_RX_PIN_INDEX      XBee_RX_SCL_MOSI_PIN_INDEX
#define XBee_MISO_SDA_TX_PIN_INDEX      XBee_TX_SDA_MISO_PIN_INDEX
#ifndef XBee_SCLK_PIN_INDEX
#define XBee_SCLK_PIN_INDEX             XBee_SCLK_PIN_INDEX
#endif /* XBee_SCLK_PIN_INDEX */
#ifndef XBee_SS0_PIN_INDEX
#define XBee_SS0_PIN_INDEX              XBee_SS0_PIN_INDEX
#endif /* XBee_SS0_PIN_INDEX */

#define XBee_MOSI_SCL_RX_WAKE_PIN_MASK XBee_RX_WAKE_SCL_MOSI_PIN_MASK
#define XBee_MOSI_SCL_RX_PIN_MASK      XBee_RX_SCL_MOSI_PIN_MASK
#define XBee_MISO_SDA_TX_PIN_MASK      XBee_TX_SDA_MISO_PIN_MASK
#ifndef XBee_SCLK_PIN_MASK
#define XBee_SCLK_PIN_MASK             XBee_SCLK_PIN_MASK
#endif /* XBee_SCLK_PIN_MASK */
#ifndef XBee_SS0_PIN_MASK
#define XBee_SS0_PIN_MASK              XBee_SS0_PIN_MASK
#endif /* XBee_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_XBee_H) */


/* [] END OF FILE */
