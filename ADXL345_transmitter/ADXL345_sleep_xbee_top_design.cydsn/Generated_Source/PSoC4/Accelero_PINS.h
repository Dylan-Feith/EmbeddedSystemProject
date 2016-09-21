/*******************************************************************************
* File Name: Accelero_PINS.h
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

#if !defined(CY_SCB_PINS_Accelero_H)
#define CY_SCB_PINS_Accelero_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define Accelero_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define Accelero_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define Accelero_REMOVE_TX_SDA_MISO_PIN      (1u)
#define Accelero_REMOVE_SCLK_PIN      (1u)
#define Accelero_REMOVE_SS0_PIN      (1u)
#define Accelero_REMOVE_SS1_PIN                 (1u)
#define Accelero_REMOVE_SS2_PIN                 (1u)
#define Accelero_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define Accelero_REMOVE_I2C_PINS                (0u)
#define Accelero_REMOVE_SPI_MASTER_PINS         (1u)
#define Accelero_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define Accelero_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define Accelero_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define Accelero_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define Accelero_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define Accelero_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define Accelero_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define Accelero_REMOVE_SPI_SLAVE_PINS          (1u)
#define Accelero_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define Accelero_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define Accelero_REMOVE_UART_TX_PIN             (1u)
#define Accelero_REMOVE_UART_RX_TX_PIN          (1u)
#define Accelero_REMOVE_UART_RX_PIN             (1u)
#define Accelero_REMOVE_UART_RX_WAKE_PIN        (1u)
#define Accelero_REMOVE_UART_RTS_PIN            (1u)
#define Accelero_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define Accelero_RX_WAKE_SCL_MOSI_PIN (0u == Accelero_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define Accelero_RX_SCL_MOSI_PIN     (0u == Accelero_REMOVE_RX_SCL_MOSI_PIN)
#define Accelero_TX_SDA_MISO_PIN     (0u == Accelero_REMOVE_TX_SDA_MISO_PIN)
#define Accelero_SCLK_PIN     (0u == Accelero_REMOVE_SCLK_PIN)
#define Accelero_SS0_PIN     (0u == Accelero_REMOVE_SS0_PIN)
#define Accelero_SS1_PIN                (0u == Accelero_REMOVE_SS1_PIN)
#define Accelero_SS2_PIN                (0u == Accelero_REMOVE_SS2_PIN)
#define Accelero_SS3_PIN                (0u == Accelero_REMOVE_SS3_PIN)

/* Mode defined pins */
#define Accelero_I2C_PINS               (0u == Accelero_REMOVE_I2C_PINS)
#define Accelero_SPI_MASTER_PINS        (0u == Accelero_REMOVE_SPI_MASTER_PINS)
#define Accelero_SPI_MASTER_SCLK_PIN    (0u == Accelero_REMOVE_SPI_MASTER_SCLK_PIN)
#define Accelero_SPI_MASTER_MOSI_PIN    (0u == Accelero_REMOVE_SPI_MASTER_MOSI_PIN)
#define Accelero_SPI_MASTER_MISO_PIN    (0u == Accelero_REMOVE_SPI_MASTER_MISO_PIN)
#define Accelero_SPI_MASTER_SS0_PIN     (0u == Accelero_REMOVE_SPI_MASTER_SS0_PIN)
#define Accelero_SPI_MASTER_SS1_PIN     (0u == Accelero_REMOVE_SPI_MASTER_SS1_PIN)
#define Accelero_SPI_MASTER_SS2_PIN     (0u == Accelero_REMOVE_SPI_MASTER_SS2_PIN)
#define Accelero_SPI_MASTER_SS3_PIN     (0u == Accelero_REMOVE_SPI_MASTER_SS3_PIN)
#define Accelero_SPI_SLAVE_PINS         (0u == Accelero_REMOVE_SPI_SLAVE_PINS)
#define Accelero_SPI_SLAVE_MOSI_PIN     (0u == Accelero_REMOVE_SPI_SLAVE_MOSI_PIN)
#define Accelero_SPI_SLAVE_MISO_PIN     (0u == Accelero_REMOVE_SPI_SLAVE_MISO_PIN)
#define Accelero_UART_TX_PIN            (0u == Accelero_REMOVE_UART_TX_PIN)
#define Accelero_UART_RX_TX_PIN         (0u == Accelero_REMOVE_UART_RX_TX_PIN)
#define Accelero_UART_RX_PIN            (0u == Accelero_REMOVE_UART_RX_PIN)
#define Accelero_UART_RX_WAKE_PIN       (0u == Accelero_REMOVE_UART_RX_WAKE_PIN)
#define Accelero_UART_RTS_PIN           (0u == Accelero_REMOVE_UART_RTS_PIN)
#define Accelero_UART_CTS_PIN           (0u == Accelero_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (Accelero_RX_WAKE_SCL_MOSI_PIN)
    #include "Accelero_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (Accelero_RX_SCL_MOSI) */

#if (Accelero_RX_SCL_MOSI_PIN)
    #include "Accelero_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (Accelero_RX_SCL_MOSI) */

#if (Accelero_TX_SDA_MISO_PIN)
    #include "Accelero_uart_tx_i2c_sda_spi_miso.h"
#endif /* (Accelero_TX_SDA_MISO) */

#if (Accelero_SCLK_PIN)
    #include "Accelero_spi_sclk.h"
#endif /* (Accelero_SCLK) */

#if (Accelero_SS0_PIN)
    #include "Accelero_spi_ss0.h"
#endif /* (Accelero_SS0_PIN) */

#if (Accelero_SS1_PIN)
    #include "Accelero_spi_ss1.h"
#endif /* (Accelero_SS1_PIN) */

#if (Accelero_SS2_PIN)
    #include "Accelero_spi_ss2.h"
#endif /* (Accelero_SS2_PIN) */

#if (Accelero_SS3_PIN)
    #include "Accelero_spi_ss3.h"
#endif /* (Accelero_SS3_PIN) */

#if (Accelero_I2C_PINS)
    #include "Accelero_scl.h"
    #include "Accelero_sda.h"
#endif /* (Accelero_I2C_PINS) */

#if (Accelero_SPI_MASTER_PINS)
#if (Accelero_SPI_MASTER_SCLK_PIN)
    #include "Accelero_sclk_m.h"
#endif /* (Accelero_SPI_MASTER_SCLK_PIN) */

#if (Accelero_SPI_MASTER_MOSI_PIN)
    #include "Accelero_mosi_m.h"
#endif /* (Accelero_SPI_MASTER_MOSI_PIN) */

#if (Accelero_SPI_MASTER_MISO_PIN)
    #include "Accelero_miso_m.h"
#endif /*(Accelero_SPI_MASTER_MISO_PIN) */
#endif /* (Accelero_SPI_MASTER_PINS) */

#if (Accelero_SPI_SLAVE_PINS)
    #include "Accelero_sclk_s.h"
    #include "Accelero_ss_s.h"

#if (Accelero_SPI_SLAVE_MOSI_PIN)
    #include "Accelero_mosi_s.h"
#endif /* (Accelero_SPI_SLAVE_MOSI_PIN) */

#if (Accelero_SPI_SLAVE_MISO_PIN)
    #include "Accelero_miso_s.h"
#endif /*(Accelero_SPI_SLAVE_MISO_PIN) */
#endif /* (Accelero_SPI_SLAVE_PINS) */

#if (Accelero_SPI_MASTER_SS0_PIN)
    #include "Accelero_ss0_m.h"
#endif /* (Accelero_SPI_MASTER_SS0_PIN) */

#if (Accelero_SPI_MASTER_SS1_PIN)
    #include "Accelero_ss1_m.h"
#endif /* (Accelero_SPI_MASTER_SS1_PIN) */

#if (Accelero_SPI_MASTER_SS2_PIN)
    #include "Accelero_ss2_m.h"
#endif /* (Accelero_SPI_MASTER_SS2_PIN) */

#if (Accelero_SPI_MASTER_SS3_PIN)
    #include "Accelero_ss3_m.h"
#endif /* (Accelero_SPI_MASTER_SS3_PIN) */

#if (Accelero_UART_TX_PIN)
    #include "Accelero_tx.h"
#endif /* (Accelero_UART_TX_PIN) */

#if (Accelero_UART_RX_TX_PIN)
    #include "Accelero_rx_tx.h"
#endif /* (Accelero_UART_RX_TX_PIN) */

#if (Accelero_UART_RX_PIN)
    #include "Accelero_rx.h"
#endif /* (Accelero_UART_RX_PIN) */

#if (Accelero_UART_RX_WAKE_PIN)
    #include "Accelero_rx_wake.h"
#endif /* (Accelero_UART_RX_WAKE_PIN) */

#if (Accelero_UART_RTS_PIN)
    #include "Accelero_rts.h"
#endif /* (Accelero_UART_RTS_PIN) */

#if (Accelero_UART_CTS_PIN)
    #include "Accelero_cts.h"
#endif /* (Accelero_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (Accelero_RX_WAKE_SCL_MOSI_PIN)
    #define Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) Accelero_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define Accelero_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) Accelero_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define Accelero_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (Accelero_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Accelero_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (Accelero_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define Accelero_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) Accelero_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Accelero_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) Accelero_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Accelero_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (Accelero_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define Accelero_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) Accelero_INTCFG_TYPE_MASK << \
                                      Accelero_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (Accelero_RX_WAKE_SCL_MOSI_PIN) */

#if (Accelero_RX_SCL_MOSI_PIN)
    #define Accelero_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) Accelero_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define Accelero_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) Accelero_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define Accelero_RX_SCL_MOSI_HSIOM_MASK  (Accelero_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Accelero_RX_SCL_MOSI_HSIOM_POS   (Accelero_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (Accelero_RX_SCL_MOSI_PIN) */

#if (Accelero_TX_SDA_MISO_PIN)
    #define Accelero_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) Accelero_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define Accelero_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) Accelero_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define Accelero_TX_SDA_MISO_HSIOM_MASK  (Accelero_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define Accelero_TX_SDA_MISO_HSIOM_POS   (Accelero_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (Accelero_TX_SDA_MISO_PIN) */

#if (Accelero_SCLK_PIN)
    #define Accelero_SCLK_HSIOM_REG   (*(reg32 *) Accelero_spi_sclk__0__HSIOM)
    #define Accelero_SCLK_HSIOM_PTR   ( (reg32 *) Accelero_spi_sclk__0__HSIOM)
    #define Accelero_SCLK_HSIOM_MASK  (Accelero_spi_sclk__0__HSIOM_MASK)
    #define Accelero_SCLK_HSIOM_POS   (Accelero_spi_sclk__0__HSIOM_SHIFT)
#endif /* (Accelero_SCLK_PIN) */

#if (Accelero_SS0_PIN)
    #define Accelero_SS0_HSIOM_REG   (*(reg32 *) Accelero_spi_ss0__0__HSIOM)
    #define Accelero_SS0_HSIOM_PTR   ( (reg32 *) Accelero_spi_ss0__0__HSIOM)
    #define Accelero_SS0_HSIOM_MASK  (Accelero_spi_ss0__0__HSIOM_MASK)
    #define Accelero_SS0_HSIOM_POS   (Accelero_spi_ss0__0__HSIOM_SHIFT)
#endif /* (Accelero_SS0_PIN) */

#if (Accelero_SS1_PIN)
    #define Accelero_SS1_HSIOM_REG      (*(reg32 *) Accelero_spi_ss1__0__HSIOM)
    #define Accelero_SS1_HSIOM_PTR      ( (reg32 *) Accelero_spi_ss1__0__HSIOM)
    #define Accelero_SS1_HSIOM_MASK     (Accelero_spi_ss1__0__HSIOM_MASK)
    #define Accelero_SS1_HSIOM_POS      (Accelero_spi_ss1__0__HSIOM_SHIFT)
#endif /* (Accelero_SS1_PIN) */

#if (Accelero_SS2_PIN)
    #define Accelero_SS2_HSIOM_REG     (*(reg32 *) Accelero_spi_ss2__0__HSIOM)
    #define Accelero_SS2_HSIOM_PTR     ( (reg32 *) Accelero_spi_ss2__0__HSIOM)
    #define Accelero_SS2_HSIOM_MASK    (Accelero_spi_ss2__0__HSIOM_MASK)
    #define Accelero_SS2_HSIOM_POS     (Accelero_spi_ss2__0__HSIOM_SHIFT)
#endif /* (Accelero_SS2_PIN) */

#if (Accelero_SS3_PIN)
    #define Accelero_SS3_HSIOM_REG     (*(reg32 *) Accelero_spi_ss3__0__HSIOM)
    #define Accelero_SS3_HSIOM_PTR     ( (reg32 *) Accelero_spi_ss3__0__HSIOM)
    #define Accelero_SS3_HSIOM_MASK    (Accelero_spi_ss3__0__HSIOM_MASK)
    #define Accelero_SS3_HSIOM_POS     (Accelero_spi_ss3__0__HSIOM_SHIFT)
#endif /* (Accelero_SS3_PIN) */

#if (Accelero_I2C_PINS)
    #define Accelero_SCL_HSIOM_REG     (*(reg32 *) Accelero_scl__0__HSIOM)
    #define Accelero_SCL_HSIOM_PTR     ( (reg32 *) Accelero_scl__0__HSIOM)
    #define Accelero_SCL_HSIOM_MASK    (Accelero_scl__0__HSIOM_MASK)
    #define Accelero_SCL_HSIOM_POS     (Accelero_scl__0__HSIOM_SHIFT)

    #define Accelero_SDA_HSIOM_REG     (*(reg32 *) Accelero_sda__0__HSIOM)
    #define Accelero_SDA_HSIOM_PTR     ( (reg32 *) Accelero_sda__0__HSIOM)
    #define Accelero_SDA_HSIOM_MASK    (Accelero_sda__0__HSIOM_MASK)
    #define Accelero_SDA_HSIOM_POS     (Accelero_sda__0__HSIOM_SHIFT)
#endif /* (Accelero_I2C_PINS) */

#if (Accelero_SPI_MASTER_SCLK_PIN)
    #define Accelero_SCLK_M_HSIOM_REG   (*(reg32 *) Accelero_sclk_m__0__HSIOM)
    #define Accelero_SCLK_M_HSIOM_PTR   ( (reg32 *) Accelero_sclk_m__0__HSIOM)
    #define Accelero_SCLK_M_HSIOM_MASK  (Accelero_sclk_m__0__HSIOM_MASK)
    #define Accelero_SCLK_M_HSIOM_POS   (Accelero_sclk_m__0__HSIOM_SHIFT)
#endif /* (Accelero_SPI_MASTER_SCLK_PIN) */

#if (Accelero_SPI_MASTER_SS0_PIN)
    #define Accelero_SS0_M_HSIOM_REG    (*(reg32 *) Accelero_ss0_m__0__HSIOM)
    #define Accelero_SS0_M_HSIOM_PTR    ( (reg32 *) Accelero_ss0_m__0__HSIOM)
    #define Accelero_SS0_M_HSIOM_MASK   (Accelero_ss0_m__0__HSIOM_MASK)
    #define Accelero_SS0_M_HSIOM_POS    (Accelero_ss0_m__0__HSIOM_SHIFT)
#endif /* (Accelero_SPI_MASTER_SS0_PIN) */

#if (Accelero_SPI_MASTER_SS1_PIN)
    #define Accelero_SS1_M_HSIOM_REG    (*(reg32 *) Accelero_ss1_m__0__HSIOM)
    #define Accelero_SS1_M_HSIOM_PTR    ( (reg32 *) Accelero_ss1_m__0__HSIOM)
    #define Accelero_SS1_M_HSIOM_MASK   (Accelero_ss1_m__0__HSIOM_MASK)
    #define Accelero_SS1_M_HSIOM_POS    (Accelero_ss1_m__0__HSIOM_SHIFT)
#endif /* (Accelero_SPI_MASTER_SS1_PIN) */

#if (Accelero_SPI_MASTER_SS2_PIN)
    #define Accelero_SS2_M_HSIOM_REG    (*(reg32 *) Accelero_ss2_m__0__HSIOM)
    #define Accelero_SS2_M_HSIOM_PTR    ( (reg32 *) Accelero_ss2_m__0__HSIOM)
    #define Accelero_SS2_M_HSIOM_MASK   (Accelero_ss2_m__0__HSIOM_MASK)
    #define Accelero_SS2_M_HSIOM_POS    (Accelero_ss2_m__0__HSIOM_SHIFT)
#endif /* (Accelero_SPI_MASTER_SS2_PIN) */

#if (Accelero_SPI_MASTER_SS3_PIN)
    #define Accelero_SS3_M_HSIOM_REG    (*(reg32 *) Accelero_ss3_m__0__HSIOM)
    #define Accelero_SS3_M_HSIOM_PTR    ( (reg32 *) Accelero_ss3_m__0__HSIOM)
    #define Accelero_SS3_M_HSIOM_MASK   (Accelero_ss3_m__0__HSIOM_MASK)
    #define Accelero_SS3_M_HSIOM_POS    (Accelero_ss3_m__0__HSIOM_SHIFT)
#endif /* (Accelero_SPI_MASTER_SS3_PIN) */

#if (Accelero_UART_TX_PIN)
    #define Accelero_TX_HSIOM_REG   (*(reg32 *) Accelero_tx__0__HSIOM)
    #define Accelero_TX_HSIOM_PTR   ( (reg32 *) Accelero_tx_0__HSIOM)
    #define Accelero_TX_HSIOM_MASK  (Accelero_tx__0__HSIOM_MASK)
    #define Accelero_TX_HSIOM_POS   (Accelero_tx__0__HSIOM_SHIFT)
#endif /* (Accelero_UART_TX_PIN) */

#if (Accelero_UART_RTS_PIN)
    #define Accelero_RTS_HSIOM_REG  (*(reg32 *) Accelero_rts__0__HSIOM)
    #define Accelero_RTS_HSIOM_PTR  ( (reg32 *) Accelero_rts__0__HSIOM)
    #define Accelero_RTS_HSIOM_MASK (Accelero_rts__0__HSIOM_MASK)
    #define Accelero_RTS_HSIOM_POS  (Accelero_rts__0__HSIOM_SHIFT)
#endif /* (Accelero_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define Accelero_HSIOM_DEF_SEL      (0x00u)
#define Accelero_HSIOM_GPIO_SEL     (0x00u)
#define Accelero_HSIOM_UART_SEL     (0x09u)
#define Accelero_HSIOM_I2C_SEL      (0x0Eu)
#define Accelero_HSIOM_SPI_SEL      (0x0Fu)

#define Accelero_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define Accelero_RX_SCL_MOSI_PIN_INDEX       (0u)
#define Accelero_TX_SDA_MISO_PIN_INDEX       (1u)
#define Accelero_SCLK_PIN_INDEX       (2u)
#define Accelero_SS0_PIN_INDEX       (3u)
#define Accelero_SS1_PIN_INDEX                  (4u)
#define Accelero_SS2_PIN_INDEX                  (5u)
#define Accelero_SS3_PIN_INDEX                  (6u)

#define Accelero_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << Accelero_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define Accelero_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << Accelero_RX_SCL_MOSI_PIN_INDEX)
#define Accelero_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << Accelero_TX_SDA_MISO_PIN_INDEX)
#define Accelero_SCLK_PIN_MASK     ((uint32) 0x01u << Accelero_SCLK_PIN_INDEX)
#define Accelero_SS0_PIN_MASK     ((uint32) 0x01u << Accelero_SS0_PIN_INDEX)
#define Accelero_SS1_PIN_MASK                ((uint32) 0x01u << Accelero_SS1_PIN_INDEX)
#define Accelero_SS2_PIN_MASK                ((uint32) 0x01u << Accelero_SS2_PIN_INDEX)
#define Accelero_SS3_PIN_MASK                ((uint32) 0x01u << Accelero_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define Accelero_INTCFG_TYPE_MASK           (0x03u)
#define Accelero_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define Accelero_PIN_DM_ALG_HIZ  (0u)
#define Accelero_PIN_DM_DIG_HIZ  (1u)
#define Accelero_PIN_DM_OD_LO    (4u)
#define Accelero_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define Accelero_DM_MASK    (0x7u)
#define Accelero_DM_SIZE    (3)
#define Accelero_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) Accelero_DM_MASK << (Accelero_DM_SIZE * (pos)))) >> \
                                                              (Accelero_DM_SIZE * (pos)) )

#if (Accelero_TX_SDA_MISO_PIN)
    #define Accelero_CHECK_TX_SDA_MISO_PIN_USED \
                (Accelero_PIN_DM_ALG_HIZ != \
                    Accelero_GET_P4_PIN_DM(Accelero_uart_tx_i2c_sda_spi_miso_PC, \
                                                   Accelero_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (Accelero_TX_SDA_MISO_PIN) */

#if (Accelero_SS0_PIN)
    #define Accelero_CHECK_SS0_PIN_USED \
                (Accelero_PIN_DM_ALG_HIZ != \
                    Accelero_GET_P4_PIN_DM(Accelero_spi_ss0_PC, \
                                                   Accelero_spi_ss0_SHIFT))
#endif /* (Accelero_SS0_PIN) */

/* Set bits-mask in register */
#define Accelero_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define Accelero_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define Accelero_SET_HSIOM_SEL(reg, mask, pos, sel) Accelero_SET_REGISTER_BITS(reg, mask, pos, sel)
#define Accelero_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        Accelero_SET_REGISTER_BITS(reg, mask, pos, intType)
#define Accelero_SET_INP_DIS(reg, mask, val) Accelero_SET_REGISTER_BIT(reg, mask, val)

/* Accelero_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  Accelero_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (Accelero_CY_SCBIP_V0)
#if (Accelero_I2C_PINS)
    #define Accelero_SET_I2C_SCL_DR(val) Accelero_scl_Write(val)

    #define Accelero_SET_I2C_SCL_HSIOM_SEL(sel) \
                          Accelero_SET_HSIOM_SEL(Accelero_SCL_HSIOM_REG,  \
                                                         Accelero_SCL_HSIOM_MASK, \
                                                         Accelero_SCL_HSIOM_POS,  \
                                                         (sel))
    #define Accelero_WAIT_SCL_SET_HIGH  (0u == Accelero_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (Accelero_RX_WAKE_SCL_MOSI_PIN)
    #define Accelero_SET_I2C_SCL_DR(val) \
                            Accelero_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define Accelero_SET_I2C_SCL_HSIOM_SEL(sel) \
                    Accelero_SET_HSIOM_SEL(Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   Accelero_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   Accelero_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define Accelero_WAIT_SCL_SET_HIGH  (0u == Accelero_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (Accelero_RX_SCL_MOSI_PIN)
    #define Accelero_SET_I2C_SCL_DR(val) \
                            Accelero_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define Accelero_SET_I2C_SCL_HSIOM_SEL(sel) \
                            Accelero_SET_HSIOM_SEL(Accelero_RX_SCL_MOSI_HSIOM_REG,  \
                                                           Accelero_RX_SCL_MOSI_HSIOM_MASK, \
                                                           Accelero_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define Accelero_WAIT_SCL_SET_HIGH  (0u == Accelero_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define Accelero_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define Accelero_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define Accelero_WAIT_SCL_SET_HIGH  (0u)
#endif /* (Accelero_I2C_PINS) */

/* SCB I2C: sda signal */
#if (Accelero_I2C_PINS)
    #define Accelero_WAIT_SDA_SET_HIGH  (0u == Accelero_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (Accelero_TX_SDA_MISO_PIN)
    #define Accelero_WAIT_SDA_SET_HIGH  (0u == Accelero_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define Accelero_WAIT_SDA_SET_HIGH  (0u)
#endif /* (Accelero_MOSI_SCL_RX_PIN) */
#endif /* (Accelero_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define Accelero_REMOVE_MOSI_SCL_RX_WAKE_PIN    Accelero_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define Accelero_REMOVE_MOSI_SCL_RX_PIN         Accelero_REMOVE_RX_SCL_MOSI_PIN
#define Accelero_REMOVE_MISO_SDA_TX_PIN         Accelero_REMOVE_TX_SDA_MISO_PIN
#ifndef Accelero_REMOVE_SCLK_PIN
#define Accelero_REMOVE_SCLK_PIN                Accelero_REMOVE_SCLK_PIN
#endif /* Accelero_REMOVE_SCLK_PIN */
#ifndef Accelero_REMOVE_SS0_PIN
#define Accelero_REMOVE_SS0_PIN                 Accelero_REMOVE_SS0_PIN
#endif /* Accelero_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define Accelero_MOSI_SCL_RX_WAKE_PIN   Accelero_RX_WAKE_SCL_MOSI_PIN
#define Accelero_MOSI_SCL_RX_PIN        Accelero_RX_SCL_MOSI_PIN
#define Accelero_MISO_SDA_TX_PIN        Accelero_TX_SDA_MISO_PIN
#ifndef Accelero_SCLK_PIN
#define Accelero_SCLK_PIN               Accelero_SCLK_PIN
#endif /* Accelero_SCLK_PIN */
#ifndef Accelero_SS0_PIN
#define Accelero_SS0_PIN                Accelero_SS0_PIN
#endif /* Accelero_SS0_PIN */

#if (Accelero_MOSI_SCL_RX_WAKE_PIN)
    #define Accelero_MOSI_SCL_RX_WAKE_HSIOM_REG     Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Accelero_MOSI_SCL_RX_WAKE_HSIOM_PTR     Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Accelero_MOSI_SCL_RX_WAKE_HSIOM_MASK    Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Accelero_MOSI_SCL_RX_WAKE_HSIOM_POS     Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Accelero_MOSI_SCL_RX_WAKE_INTCFG_REG    Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Accelero_MOSI_SCL_RX_WAKE_INTCFG_PTR    Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Accelero_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Accelero_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  Accelero_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (Accelero_RX_WAKE_SCL_MOSI_PIN) */

#if (Accelero_MOSI_SCL_RX_PIN)
    #define Accelero_MOSI_SCL_RX_HSIOM_REG      Accelero_RX_SCL_MOSI_HSIOM_REG
    #define Accelero_MOSI_SCL_RX_HSIOM_PTR      Accelero_RX_SCL_MOSI_HSIOM_PTR
    #define Accelero_MOSI_SCL_RX_HSIOM_MASK     Accelero_RX_SCL_MOSI_HSIOM_MASK
    #define Accelero_MOSI_SCL_RX_HSIOM_POS      Accelero_RX_SCL_MOSI_HSIOM_POS
#endif /* (Accelero_MOSI_SCL_RX_PIN) */

#if (Accelero_MISO_SDA_TX_PIN)
    #define Accelero_MISO_SDA_TX_HSIOM_REG      Accelero_TX_SDA_MISO_HSIOM_REG
    #define Accelero_MISO_SDA_TX_HSIOM_PTR      Accelero_TX_SDA_MISO_HSIOM_REG
    #define Accelero_MISO_SDA_TX_HSIOM_MASK     Accelero_TX_SDA_MISO_HSIOM_REG
    #define Accelero_MISO_SDA_TX_HSIOM_POS      Accelero_TX_SDA_MISO_HSIOM_REG
#endif /* (Accelero_MISO_SDA_TX_PIN_PIN) */

#if (Accelero_SCLK_PIN)
    #ifndef Accelero_SCLK_HSIOM_REG
    #define Accelero_SCLK_HSIOM_REG     Accelero_SCLK_HSIOM_REG
    #define Accelero_SCLK_HSIOM_PTR     Accelero_SCLK_HSIOM_PTR
    #define Accelero_SCLK_HSIOM_MASK    Accelero_SCLK_HSIOM_MASK
    #define Accelero_SCLK_HSIOM_POS     Accelero_SCLK_HSIOM_POS
    #endif /* Accelero_SCLK_HSIOM_REG */
#endif /* (Accelero_SCLK_PIN) */

#if (Accelero_SS0_PIN)
    #ifndef Accelero_SS0_HSIOM_REG
    #define Accelero_SS0_HSIOM_REG      Accelero_SS0_HSIOM_REG
    #define Accelero_SS0_HSIOM_PTR      Accelero_SS0_HSIOM_PTR
    #define Accelero_SS0_HSIOM_MASK     Accelero_SS0_HSIOM_MASK
    #define Accelero_SS0_HSIOM_POS      Accelero_SS0_HSIOM_POS
    #endif /* Accelero_SS0_HSIOM_REG */
#endif /* (Accelero_SS0_PIN) */

#define Accelero_MOSI_SCL_RX_WAKE_PIN_INDEX Accelero_RX_WAKE_SCL_MOSI_PIN_INDEX
#define Accelero_MOSI_SCL_RX_PIN_INDEX      Accelero_RX_SCL_MOSI_PIN_INDEX
#define Accelero_MISO_SDA_TX_PIN_INDEX      Accelero_TX_SDA_MISO_PIN_INDEX
#ifndef Accelero_SCLK_PIN_INDEX
#define Accelero_SCLK_PIN_INDEX             Accelero_SCLK_PIN_INDEX
#endif /* Accelero_SCLK_PIN_INDEX */
#ifndef Accelero_SS0_PIN_INDEX
#define Accelero_SS0_PIN_INDEX              Accelero_SS0_PIN_INDEX
#endif /* Accelero_SS0_PIN_INDEX */

#define Accelero_MOSI_SCL_RX_WAKE_PIN_MASK Accelero_RX_WAKE_SCL_MOSI_PIN_MASK
#define Accelero_MOSI_SCL_RX_PIN_MASK      Accelero_RX_SCL_MOSI_PIN_MASK
#define Accelero_MISO_SDA_TX_PIN_MASK      Accelero_TX_SDA_MISO_PIN_MASK
#ifndef Accelero_SCLK_PIN_MASK
#define Accelero_SCLK_PIN_MASK             Accelero_SCLK_PIN_MASK
#endif /* Accelero_SCLK_PIN_MASK */
#ifndef Accelero_SS0_PIN_MASK
#define Accelero_SS0_PIN_MASK              Accelero_SS0_PIN_MASK
#endif /* Accelero_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_Accelero_H) */


/* [] END OF FILE */
