/*******************************************************************************
* File Name: PC_PINS.h
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

#if !defined(CY_SCB_PINS_PC_H)
#define CY_SCB_PINS_PC_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define PC_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define PC_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define PC_REMOVE_TX_SDA_MISO_PIN      (1u)
#define PC_REMOVE_SCLK_PIN      (1u)
#define PC_REMOVE_SS0_PIN      (1u)
#define PC_REMOVE_SS1_PIN                 (1u)
#define PC_REMOVE_SS2_PIN                 (1u)
#define PC_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define PC_REMOVE_I2C_PINS                (1u)
#define PC_REMOVE_SPI_MASTER_PINS         (1u)
#define PC_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define PC_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define PC_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define PC_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define PC_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define PC_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define PC_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define PC_REMOVE_SPI_SLAVE_PINS          (1u)
#define PC_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define PC_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define PC_REMOVE_UART_TX_PIN             (0u)
#define PC_REMOVE_UART_RX_TX_PIN          (1u)
#define PC_REMOVE_UART_RX_PIN             (0u)
#define PC_REMOVE_UART_RX_WAKE_PIN        (1u)
#define PC_REMOVE_UART_RTS_PIN            (1u)
#define PC_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define PC_RX_WAKE_SCL_MOSI_PIN (0u == PC_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define PC_RX_SCL_MOSI_PIN     (0u == PC_REMOVE_RX_SCL_MOSI_PIN)
#define PC_TX_SDA_MISO_PIN     (0u == PC_REMOVE_TX_SDA_MISO_PIN)
#define PC_SCLK_PIN     (0u == PC_REMOVE_SCLK_PIN)
#define PC_SS0_PIN     (0u == PC_REMOVE_SS0_PIN)
#define PC_SS1_PIN                (0u == PC_REMOVE_SS1_PIN)
#define PC_SS2_PIN                (0u == PC_REMOVE_SS2_PIN)
#define PC_SS3_PIN                (0u == PC_REMOVE_SS3_PIN)

/* Mode defined pins */
#define PC_I2C_PINS               (0u == PC_REMOVE_I2C_PINS)
#define PC_SPI_MASTER_PINS        (0u == PC_REMOVE_SPI_MASTER_PINS)
#define PC_SPI_MASTER_SCLK_PIN    (0u == PC_REMOVE_SPI_MASTER_SCLK_PIN)
#define PC_SPI_MASTER_MOSI_PIN    (0u == PC_REMOVE_SPI_MASTER_MOSI_PIN)
#define PC_SPI_MASTER_MISO_PIN    (0u == PC_REMOVE_SPI_MASTER_MISO_PIN)
#define PC_SPI_MASTER_SS0_PIN     (0u == PC_REMOVE_SPI_MASTER_SS0_PIN)
#define PC_SPI_MASTER_SS1_PIN     (0u == PC_REMOVE_SPI_MASTER_SS1_PIN)
#define PC_SPI_MASTER_SS2_PIN     (0u == PC_REMOVE_SPI_MASTER_SS2_PIN)
#define PC_SPI_MASTER_SS3_PIN     (0u == PC_REMOVE_SPI_MASTER_SS3_PIN)
#define PC_SPI_SLAVE_PINS         (0u == PC_REMOVE_SPI_SLAVE_PINS)
#define PC_SPI_SLAVE_MOSI_PIN     (0u == PC_REMOVE_SPI_SLAVE_MOSI_PIN)
#define PC_SPI_SLAVE_MISO_PIN     (0u == PC_REMOVE_SPI_SLAVE_MISO_PIN)
#define PC_UART_TX_PIN            (0u == PC_REMOVE_UART_TX_PIN)
#define PC_UART_RX_TX_PIN         (0u == PC_REMOVE_UART_RX_TX_PIN)
#define PC_UART_RX_PIN            (0u == PC_REMOVE_UART_RX_PIN)
#define PC_UART_RX_WAKE_PIN       (0u == PC_REMOVE_UART_RX_WAKE_PIN)
#define PC_UART_RTS_PIN           (0u == PC_REMOVE_UART_RTS_PIN)
#define PC_UART_CTS_PIN           (0u == PC_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (PC_RX_WAKE_SCL_MOSI_PIN)
    #include "PC_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (PC_RX_SCL_MOSI) */

#if (PC_RX_SCL_MOSI_PIN)
    #include "PC_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (PC_RX_SCL_MOSI) */

#if (PC_TX_SDA_MISO_PIN)
    #include "PC_uart_tx_i2c_sda_spi_miso.h"
#endif /* (PC_TX_SDA_MISO) */

#if (PC_SCLK_PIN)
    #include "PC_spi_sclk.h"
#endif /* (PC_SCLK) */

#if (PC_SS0_PIN)
    #include "PC_spi_ss0.h"
#endif /* (PC_SS0_PIN) */

#if (PC_SS1_PIN)
    #include "PC_spi_ss1.h"
#endif /* (PC_SS1_PIN) */

#if (PC_SS2_PIN)
    #include "PC_spi_ss2.h"
#endif /* (PC_SS2_PIN) */

#if (PC_SS3_PIN)
    #include "PC_spi_ss3.h"
#endif /* (PC_SS3_PIN) */

#if (PC_I2C_PINS)
    #include "PC_scl.h"
    #include "PC_sda.h"
#endif /* (PC_I2C_PINS) */

#if (PC_SPI_MASTER_PINS)
#if (PC_SPI_MASTER_SCLK_PIN)
    #include "PC_sclk_m.h"
#endif /* (PC_SPI_MASTER_SCLK_PIN) */

#if (PC_SPI_MASTER_MOSI_PIN)
    #include "PC_mosi_m.h"
#endif /* (PC_SPI_MASTER_MOSI_PIN) */

#if (PC_SPI_MASTER_MISO_PIN)
    #include "PC_miso_m.h"
#endif /*(PC_SPI_MASTER_MISO_PIN) */
#endif /* (PC_SPI_MASTER_PINS) */

#if (PC_SPI_SLAVE_PINS)
    #include "PC_sclk_s.h"
    #include "PC_ss_s.h"

#if (PC_SPI_SLAVE_MOSI_PIN)
    #include "PC_mosi_s.h"
#endif /* (PC_SPI_SLAVE_MOSI_PIN) */

#if (PC_SPI_SLAVE_MISO_PIN)
    #include "PC_miso_s.h"
#endif /*(PC_SPI_SLAVE_MISO_PIN) */
#endif /* (PC_SPI_SLAVE_PINS) */

#if (PC_SPI_MASTER_SS0_PIN)
    #include "PC_ss0_m.h"
#endif /* (PC_SPI_MASTER_SS0_PIN) */

#if (PC_SPI_MASTER_SS1_PIN)
    #include "PC_ss1_m.h"
#endif /* (PC_SPI_MASTER_SS1_PIN) */

#if (PC_SPI_MASTER_SS2_PIN)
    #include "PC_ss2_m.h"
#endif /* (PC_SPI_MASTER_SS2_PIN) */

#if (PC_SPI_MASTER_SS3_PIN)
    #include "PC_ss3_m.h"
#endif /* (PC_SPI_MASTER_SS3_PIN) */

#if (PC_UART_TX_PIN)
    #include "PC_tx.h"
#endif /* (PC_UART_TX_PIN) */

#if (PC_UART_RX_TX_PIN)
    #include "PC_rx_tx.h"
#endif /* (PC_UART_RX_TX_PIN) */

#if (PC_UART_RX_PIN)
    #include "PC_rx.h"
#endif /* (PC_UART_RX_PIN) */

#if (PC_UART_RX_WAKE_PIN)
    #include "PC_rx_wake.h"
#endif /* (PC_UART_RX_WAKE_PIN) */

#if (PC_UART_RTS_PIN)
    #include "PC_rts.h"
#endif /* (PC_UART_RTS_PIN) */

#if (PC_UART_CTS_PIN)
    #include "PC_cts.h"
#endif /* (PC_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (PC_RX_WAKE_SCL_MOSI_PIN)
    #define PC_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) PC_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define PC_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) PC_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define PC_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (PC_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define PC_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (PC_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define PC_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) PC_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define PC_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) PC_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define PC_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (PC_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define PC_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) PC_INTCFG_TYPE_MASK << \
                                      PC_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (PC_RX_WAKE_SCL_MOSI_PIN) */

#if (PC_RX_SCL_MOSI_PIN)
    #define PC_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) PC_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define PC_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) PC_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define PC_RX_SCL_MOSI_HSIOM_MASK  (PC_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define PC_RX_SCL_MOSI_HSIOM_POS   (PC_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (PC_RX_SCL_MOSI_PIN) */

#if (PC_TX_SDA_MISO_PIN)
    #define PC_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) PC_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define PC_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) PC_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define PC_TX_SDA_MISO_HSIOM_MASK  (PC_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define PC_TX_SDA_MISO_HSIOM_POS   (PC_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (PC_TX_SDA_MISO_PIN) */

#if (PC_SCLK_PIN)
    #define PC_SCLK_HSIOM_REG   (*(reg32 *) PC_spi_sclk__0__HSIOM)
    #define PC_SCLK_HSIOM_PTR   ( (reg32 *) PC_spi_sclk__0__HSIOM)
    #define PC_SCLK_HSIOM_MASK  (PC_spi_sclk__0__HSIOM_MASK)
    #define PC_SCLK_HSIOM_POS   (PC_spi_sclk__0__HSIOM_SHIFT)
#endif /* (PC_SCLK_PIN) */

#if (PC_SS0_PIN)
    #define PC_SS0_HSIOM_REG   (*(reg32 *) PC_spi_ss0__0__HSIOM)
    #define PC_SS0_HSIOM_PTR   ( (reg32 *) PC_spi_ss0__0__HSIOM)
    #define PC_SS0_HSIOM_MASK  (PC_spi_ss0__0__HSIOM_MASK)
    #define PC_SS0_HSIOM_POS   (PC_spi_ss0__0__HSIOM_SHIFT)
#endif /* (PC_SS0_PIN) */

#if (PC_SS1_PIN)
    #define PC_SS1_HSIOM_REG      (*(reg32 *) PC_spi_ss1__0__HSIOM)
    #define PC_SS1_HSIOM_PTR      ( (reg32 *) PC_spi_ss1__0__HSIOM)
    #define PC_SS1_HSIOM_MASK     (PC_spi_ss1__0__HSIOM_MASK)
    #define PC_SS1_HSIOM_POS      (PC_spi_ss1__0__HSIOM_SHIFT)
#endif /* (PC_SS1_PIN) */

#if (PC_SS2_PIN)
    #define PC_SS2_HSIOM_REG     (*(reg32 *) PC_spi_ss2__0__HSIOM)
    #define PC_SS2_HSIOM_PTR     ( (reg32 *) PC_spi_ss2__0__HSIOM)
    #define PC_SS2_HSIOM_MASK    (PC_spi_ss2__0__HSIOM_MASK)
    #define PC_SS2_HSIOM_POS     (PC_spi_ss2__0__HSIOM_SHIFT)
#endif /* (PC_SS2_PIN) */

#if (PC_SS3_PIN)
    #define PC_SS3_HSIOM_REG     (*(reg32 *) PC_spi_ss3__0__HSIOM)
    #define PC_SS3_HSIOM_PTR     ( (reg32 *) PC_spi_ss3__0__HSIOM)
    #define PC_SS3_HSIOM_MASK    (PC_spi_ss3__0__HSIOM_MASK)
    #define PC_SS3_HSIOM_POS     (PC_spi_ss3__0__HSIOM_SHIFT)
#endif /* (PC_SS3_PIN) */

#if (PC_I2C_PINS)
    #define PC_SCL_HSIOM_REG     (*(reg32 *) PC_scl__0__HSIOM)
    #define PC_SCL_HSIOM_PTR     ( (reg32 *) PC_scl__0__HSIOM)
    #define PC_SCL_HSIOM_MASK    (PC_scl__0__HSIOM_MASK)
    #define PC_SCL_HSIOM_POS     (PC_scl__0__HSIOM_SHIFT)

    #define PC_SDA_HSIOM_REG     (*(reg32 *) PC_sda__0__HSIOM)
    #define PC_SDA_HSIOM_PTR     ( (reg32 *) PC_sda__0__HSIOM)
    #define PC_SDA_HSIOM_MASK    (PC_sda__0__HSIOM_MASK)
    #define PC_SDA_HSIOM_POS     (PC_sda__0__HSIOM_SHIFT)
#endif /* (PC_I2C_PINS) */

#if (PC_SPI_MASTER_SCLK_PIN)
    #define PC_SCLK_M_HSIOM_REG   (*(reg32 *) PC_sclk_m__0__HSIOM)
    #define PC_SCLK_M_HSIOM_PTR   ( (reg32 *) PC_sclk_m__0__HSIOM)
    #define PC_SCLK_M_HSIOM_MASK  (PC_sclk_m__0__HSIOM_MASK)
    #define PC_SCLK_M_HSIOM_POS   (PC_sclk_m__0__HSIOM_SHIFT)
#endif /* (PC_SPI_MASTER_SCLK_PIN) */

#if (PC_SPI_MASTER_SS0_PIN)
    #define PC_SS0_M_HSIOM_REG    (*(reg32 *) PC_ss0_m__0__HSIOM)
    #define PC_SS0_M_HSIOM_PTR    ( (reg32 *) PC_ss0_m__0__HSIOM)
    #define PC_SS0_M_HSIOM_MASK   (PC_ss0_m__0__HSIOM_MASK)
    #define PC_SS0_M_HSIOM_POS    (PC_ss0_m__0__HSIOM_SHIFT)
#endif /* (PC_SPI_MASTER_SS0_PIN) */

#if (PC_SPI_MASTER_SS1_PIN)
    #define PC_SS1_M_HSIOM_REG    (*(reg32 *) PC_ss1_m__0__HSIOM)
    #define PC_SS1_M_HSIOM_PTR    ( (reg32 *) PC_ss1_m__0__HSIOM)
    #define PC_SS1_M_HSIOM_MASK   (PC_ss1_m__0__HSIOM_MASK)
    #define PC_SS1_M_HSIOM_POS    (PC_ss1_m__0__HSIOM_SHIFT)
#endif /* (PC_SPI_MASTER_SS1_PIN) */

#if (PC_SPI_MASTER_SS2_PIN)
    #define PC_SS2_M_HSIOM_REG    (*(reg32 *) PC_ss2_m__0__HSIOM)
    #define PC_SS2_M_HSIOM_PTR    ( (reg32 *) PC_ss2_m__0__HSIOM)
    #define PC_SS2_M_HSIOM_MASK   (PC_ss2_m__0__HSIOM_MASK)
    #define PC_SS2_M_HSIOM_POS    (PC_ss2_m__0__HSIOM_SHIFT)
#endif /* (PC_SPI_MASTER_SS2_PIN) */

#if (PC_SPI_MASTER_SS3_PIN)
    #define PC_SS3_M_HSIOM_REG    (*(reg32 *) PC_ss3_m__0__HSIOM)
    #define PC_SS3_M_HSIOM_PTR    ( (reg32 *) PC_ss3_m__0__HSIOM)
    #define PC_SS3_M_HSIOM_MASK   (PC_ss3_m__0__HSIOM_MASK)
    #define PC_SS3_M_HSIOM_POS    (PC_ss3_m__0__HSIOM_SHIFT)
#endif /* (PC_SPI_MASTER_SS3_PIN) */

#if (PC_UART_TX_PIN)
    #define PC_TX_HSIOM_REG   (*(reg32 *) PC_tx__0__HSIOM)
    #define PC_TX_HSIOM_PTR   ( (reg32 *) PC_tx_0__HSIOM)
    #define PC_TX_HSIOM_MASK  (PC_tx__0__HSIOM_MASK)
    #define PC_TX_HSIOM_POS   (PC_tx__0__HSIOM_SHIFT)
#endif /* (PC_UART_TX_PIN) */

#if (PC_UART_RTS_PIN)
    #define PC_RTS_HSIOM_REG  (*(reg32 *) PC_rts__0__HSIOM)
    #define PC_RTS_HSIOM_PTR  ( (reg32 *) PC_rts__0__HSIOM)
    #define PC_RTS_HSIOM_MASK (PC_rts__0__HSIOM_MASK)
    #define PC_RTS_HSIOM_POS  (PC_rts__0__HSIOM_SHIFT)
#endif /* (PC_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define PC_HSIOM_DEF_SEL      (0x00u)
#define PC_HSIOM_GPIO_SEL     (0x00u)
#define PC_HSIOM_UART_SEL     (0x09u)
#define PC_HSIOM_I2C_SEL      (0x0Eu)
#define PC_HSIOM_SPI_SEL      (0x0Fu)

#define PC_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define PC_RX_SCL_MOSI_PIN_INDEX       (0u)
#define PC_TX_SDA_MISO_PIN_INDEX       (1u)
#define PC_SCLK_PIN_INDEX       (2u)
#define PC_SS0_PIN_INDEX       (3u)
#define PC_SS1_PIN_INDEX                  (4u)
#define PC_SS2_PIN_INDEX                  (5u)
#define PC_SS3_PIN_INDEX                  (6u)

#define PC_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << PC_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define PC_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << PC_RX_SCL_MOSI_PIN_INDEX)
#define PC_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << PC_TX_SDA_MISO_PIN_INDEX)
#define PC_SCLK_PIN_MASK     ((uint32) 0x01u << PC_SCLK_PIN_INDEX)
#define PC_SS0_PIN_MASK     ((uint32) 0x01u << PC_SS0_PIN_INDEX)
#define PC_SS1_PIN_MASK                ((uint32) 0x01u << PC_SS1_PIN_INDEX)
#define PC_SS2_PIN_MASK                ((uint32) 0x01u << PC_SS2_PIN_INDEX)
#define PC_SS3_PIN_MASK                ((uint32) 0x01u << PC_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define PC_INTCFG_TYPE_MASK           (0x03u)
#define PC_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define PC_PIN_DM_ALG_HIZ  (0u)
#define PC_PIN_DM_DIG_HIZ  (1u)
#define PC_PIN_DM_OD_LO    (4u)
#define PC_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define PC_DM_MASK    (0x7u)
#define PC_DM_SIZE    (3)
#define PC_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) PC_DM_MASK << (PC_DM_SIZE * (pos)))) >> \
                                                              (PC_DM_SIZE * (pos)) )

#if (PC_TX_SDA_MISO_PIN)
    #define PC_CHECK_TX_SDA_MISO_PIN_USED \
                (PC_PIN_DM_ALG_HIZ != \
                    PC_GET_P4_PIN_DM(PC_uart_tx_i2c_sda_spi_miso_PC, \
                                                   PC_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (PC_TX_SDA_MISO_PIN) */

#if (PC_SS0_PIN)
    #define PC_CHECK_SS0_PIN_USED \
                (PC_PIN_DM_ALG_HIZ != \
                    PC_GET_P4_PIN_DM(PC_spi_ss0_PC, \
                                                   PC_spi_ss0_SHIFT))
#endif /* (PC_SS0_PIN) */

/* Set bits-mask in register */
#define PC_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define PC_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define PC_SET_HSIOM_SEL(reg, mask, pos, sel) PC_SET_REGISTER_BITS(reg, mask, pos, sel)
#define PC_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        PC_SET_REGISTER_BITS(reg, mask, pos, intType)
#define PC_SET_INP_DIS(reg, mask, val) PC_SET_REGISTER_BIT(reg, mask, val)

/* PC_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  PC_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (PC_CY_SCBIP_V0)
#if (PC_I2C_PINS)
    #define PC_SET_I2C_SCL_DR(val) PC_scl_Write(val)

    #define PC_SET_I2C_SCL_HSIOM_SEL(sel) \
                          PC_SET_HSIOM_SEL(PC_SCL_HSIOM_REG,  \
                                                         PC_SCL_HSIOM_MASK, \
                                                         PC_SCL_HSIOM_POS,  \
                                                         (sel))
    #define PC_WAIT_SCL_SET_HIGH  (0u == PC_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (PC_RX_WAKE_SCL_MOSI_PIN)
    #define PC_SET_I2C_SCL_DR(val) \
                            PC_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define PC_SET_I2C_SCL_HSIOM_SEL(sel) \
                    PC_SET_HSIOM_SEL(PC_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   PC_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   PC_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define PC_WAIT_SCL_SET_HIGH  (0u == PC_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (PC_RX_SCL_MOSI_PIN)
    #define PC_SET_I2C_SCL_DR(val) \
                            PC_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define PC_SET_I2C_SCL_HSIOM_SEL(sel) \
                            PC_SET_HSIOM_SEL(PC_RX_SCL_MOSI_HSIOM_REG,  \
                                                           PC_RX_SCL_MOSI_HSIOM_MASK, \
                                                           PC_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define PC_WAIT_SCL_SET_HIGH  (0u == PC_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define PC_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define PC_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define PC_WAIT_SCL_SET_HIGH  (0u)
#endif /* (PC_I2C_PINS) */

/* SCB I2C: sda signal */
#if (PC_I2C_PINS)
    #define PC_WAIT_SDA_SET_HIGH  (0u == PC_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (PC_TX_SDA_MISO_PIN)
    #define PC_WAIT_SDA_SET_HIGH  (0u == PC_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define PC_WAIT_SDA_SET_HIGH  (0u)
#endif /* (PC_MOSI_SCL_RX_PIN) */
#endif /* (PC_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define PC_REMOVE_MOSI_SCL_RX_WAKE_PIN    PC_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define PC_REMOVE_MOSI_SCL_RX_PIN         PC_REMOVE_RX_SCL_MOSI_PIN
#define PC_REMOVE_MISO_SDA_TX_PIN         PC_REMOVE_TX_SDA_MISO_PIN
#ifndef PC_REMOVE_SCLK_PIN
#define PC_REMOVE_SCLK_PIN                PC_REMOVE_SCLK_PIN
#endif /* PC_REMOVE_SCLK_PIN */
#ifndef PC_REMOVE_SS0_PIN
#define PC_REMOVE_SS0_PIN                 PC_REMOVE_SS0_PIN
#endif /* PC_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define PC_MOSI_SCL_RX_WAKE_PIN   PC_RX_WAKE_SCL_MOSI_PIN
#define PC_MOSI_SCL_RX_PIN        PC_RX_SCL_MOSI_PIN
#define PC_MISO_SDA_TX_PIN        PC_TX_SDA_MISO_PIN
#ifndef PC_SCLK_PIN
#define PC_SCLK_PIN               PC_SCLK_PIN
#endif /* PC_SCLK_PIN */
#ifndef PC_SS0_PIN
#define PC_SS0_PIN                PC_SS0_PIN
#endif /* PC_SS0_PIN */

#if (PC_MOSI_SCL_RX_WAKE_PIN)
    #define PC_MOSI_SCL_RX_WAKE_HSIOM_REG     PC_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define PC_MOSI_SCL_RX_WAKE_HSIOM_PTR     PC_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define PC_MOSI_SCL_RX_WAKE_HSIOM_MASK    PC_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define PC_MOSI_SCL_RX_WAKE_HSIOM_POS     PC_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define PC_MOSI_SCL_RX_WAKE_INTCFG_REG    PC_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define PC_MOSI_SCL_RX_WAKE_INTCFG_PTR    PC_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define PC_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   PC_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define PC_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  PC_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (PC_RX_WAKE_SCL_MOSI_PIN) */

#if (PC_MOSI_SCL_RX_PIN)
    #define PC_MOSI_SCL_RX_HSIOM_REG      PC_RX_SCL_MOSI_HSIOM_REG
    #define PC_MOSI_SCL_RX_HSIOM_PTR      PC_RX_SCL_MOSI_HSIOM_PTR
    #define PC_MOSI_SCL_RX_HSIOM_MASK     PC_RX_SCL_MOSI_HSIOM_MASK
    #define PC_MOSI_SCL_RX_HSIOM_POS      PC_RX_SCL_MOSI_HSIOM_POS
#endif /* (PC_MOSI_SCL_RX_PIN) */

#if (PC_MISO_SDA_TX_PIN)
    #define PC_MISO_SDA_TX_HSIOM_REG      PC_TX_SDA_MISO_HSIOM_REG
    #define PC_MISO_SDA_TX_HSIOM_PTR      PC_TX_SDA_MISO_HSIOM_REG
    #define PC_MISO_SDA_TX_HSIOM_MASK     PC_TX_SDA_MISO_HSIOM_REG
    #define PC_MISO_SDA_TX_HSIOM_POS      PC_TX_SDA_MISO_HSIOM_REG
#endif /* (PC_MISO_SDA_TX_PIN_PIN) */

#if (PC_SCLK_PIN)
    #ifndef PC_SCLK_HSIOM_REG
    #define PC_SCLK_HSIOM_REG     PC_SCLK_HSIOM_REG
    #define PC_SCLK_HSIOM_PTR     PC_SCLK_HSIOM_PTR
    #define PC_SCLK_HSIOM_MASK    PC_SCLK_HSIOM_MASK
    #define PC_SCLK_HSIOM_POS     PC_SCLK_HSIOM_POS
    #endif /* PC_SCLK_HSIOM_REG */
#endif /* (PC_SCLK_PIN) */

#if (PC_SS0_PIN)
    #ifndef PC_SS0_HSIOM_REG
    #define PC_SS0_HSIOM_REG      PC_SS0_HSIOM_REG
    #define PC_SS0_HSIOM_PTR      PC_SS0_HSIOM_PTR
    #define PC_SS0_HSIOM_MASK     PC_SS0_HSIOM_MASK
    #define PC_SS0_HSIOM_POS      PC_SS0_HSIOM_POS
    #endif /* PC_SS0_HSIOM_REG */
#endif /* (PC_SS0_PIN) */

#define PC_MOSI_SCL_RX_WAKE_PIN_INDEX PC_RX_WAKE_SCL_MOSI_PIN_INDEX
#define PC_MOSI_SCL_RX_PIN_INDEX      PC_RX_SCL_MOSI_PIN_INDEX
#define PC_MISO_SDA_TX_PIN_INDEX      PC_TX_SDA_MISO_PIN_INDEX
#ifndef PC_SCLK_PIN_INDEX
#define PC_SCLK_PIN_INDEX             PC_SCLK_PIN_INDEX
#endif /* PC_SCLK_PIN_INDEX */
#ifndef PC_SS0_PIN_INDEX
#define PC_SS0_PIN_INDEX              PC_SS0_PIN_INDEX
#endif /* PC_SS0_PIN_INDEX */

#define PC_MOSI_SCL_RX_WAKE_PIN_MASK PC_RX_WAKE_SCL_MOSI_PIN_MASK
#define PC_MOSI_SCL_RX_PIN_MASK      PC_RX_SCL_MOSI_PIN_MASK
#define PC_MISO_SDA_TX_PIN_MASK      PC_TX_SDA_MISO_PIN_MASK
#ifndef PC_SCLK_PIN_MASK
#define PC_SCLK_PIN_MASK             PC_SCLK_PIN_MASK
#endif /* PC_SCLK_PIN_MASK */
#ifndef PC_SS0_PIN_MASK
#define PC_SS0_PIN_MASK              PC_SS0_PIN_MASK
#endif /* PC_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_PC_H) */


/* [] END OF FILE */
