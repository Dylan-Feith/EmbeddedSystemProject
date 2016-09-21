#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice_trm.h"

/* Pin_tx */
#define Pin_tx__0__DM__MASK 0x38000u
#define Pin_tx__0__DM__SHIFT 15
#define Pin_tx__0__DR CYREG_PRT0_DR
#define Pin_tx__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define Pin_tx__0__HSIOM_MASK 0x00F00000u
#define Pin_tx__0__HSIOM_SHIFT 20u
#define Pin_tx__0__INTCFG CYREG_PRT0_INTCFG
#define Pin_tx__0__INTSTAT CYREG_PRT0_INTSTAT
#define Pin_tx__0__MASK 0x20u
#define Pin_tx__0__OUT_SEL CYREG_UDB_PA0_CFG10
#define Pin_tx__0__OUT_SEL_SHIFT 10u
#define Pin_tx__0__OUT_SEL_VAL 1u
#define Pin_tx__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define Pin_tx__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define Pin_tx__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define Pin_tx__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define Pin_tx__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define Pin_tx__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define Pin_tx__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define Pin_tx__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define Pin_tx__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define Pin_tx__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define Pin_tx__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define Pin_tx__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define Pin_tx__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define Pin_tx__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define Pin_tx__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define Pin_tx__0__PC CYREG_PRT0_PC
#define Pin_tx__0__PC2 CYREG_PRT0_PC2
#define Pin_tx__0__PORT 0u
#define Pin_tx__0__PS CYREG_PRT0_PS
#define Pin_tx__0__SHIFT 5
#define Pin_tx__DR CYREG_PRT0_DR
#define Pin_tx__INTCFG CYREG_PRT0_INTCFG
#define Pin_tx__INTSTAT CYREG_PRT0_INTSTAT
#define Pin_tx__MASK 0x20u
#define Pin_tx__PA__CFG0 CYREG_UDB_PA0_CFG0
#define Pin_tx__PA__CFG1 CYREG_UDB_PA0_CFG1
#define Pin_tx__PA__CFG10 CYREG_UDB_PA0_CFG10
#define Pin_tx__PA__CFG11 CYREG_UDB_PA0_CFG11
#define Pin_tx__PA__CFG12 CYREG_UDB_PA0_CFG12
#define Pin_tx__PA__CFG13 CYREG_UDB_PA0_CFG13
#define Pin_tx__PA__CFG14 CYREG_UDB_PA0_CFG14
#define Pin_tx__PA__CFG2 CYREG_UDB_PA0_CFG2
#define Pin_tx__PA__CFG3 CYREG_UDB_PA0_CFG3
#define Pin_tx__PA__CFG4 CYREG_UDB_PA0_CFG4
#define Pin_tx__PA__CFG5 CYREG_UDB_PA0_CFG5
#define Pin_tx__PA__CFG6 CYREG_UDB_PA0_CFG6
#define Pin_tx__PA__CFG7 CYREG_UDB_PA0_CFG7
#define Pin_tx__PA__CFG8 CYREG_UDB_PA0_CFG8
#define Pin_tx__PA__CFG9 CYREG_UDB_PA0_CFG9
#define Pin_tx__PC CYREG_PRT0_PC
#define Pin_tx__PC2 CYREG_PRT0_PC2
#define Pin_tx__PORT 0u
#define Pin_tx__PS CYREG_PRT0_PS
#define Pin_tx__SHIFT 5

/* WdtIsr */
#define WdtIsr__INTC_CLR_EN_REG CYREG_CM0_ICER
#define WdtIsr__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define WdtIsr__INTC_MASK 0x200u
#define WdtIsr__INTC_NUMBER 9u
#define WdtIsr__INTC_PRIOR_MASK 0xC000u
#define WdtIsr__INTC_PRIOR_NUM 3u
#define WdtIsr__INTC_PRIOR_REG CYREG_CM0_IPR2
#define WdtIsr__INTC_SET_EN_REG CYREG_CM0_ISER
#define WdtIsr__INTC_SET_PD_REG CYREG_CM0_ISPR

/* zigbee_BUART */
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_UDB_W16_A0_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_UDB_W16_A1_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_UDB_W16_D0_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_UDB_W16_D1_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_UDB_W16_ACTL_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_UDB_W16_F0_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_UDB_W16_F1_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_UDB_CAT16_A_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_UDB_W8_A0_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_UDB_W8_A1_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_UDB_CAT16_D_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_UDB_W8_D0_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_UDB_W8_D1_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_UDB_CAT16_F_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_UDB_W8_F0_02
#define zigbee_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_UDB_W8_F1_02
#define zigbee_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_UDB_CAT16_A_03
#define zigbee_BUART_sTX_TxShifter_u0__A0_REG CYREG_UDB_W8_A0_03
#define zigbee_BUART_sTX_TxShifter_u0__A1_REG CYREG_UDB_W8_A1_03
#define zigbee_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_UDB_CAT16_D_03
#define zigbee_BUART_sTX_TxShifter_u0__D0_REG CYREG_UDB_W8_D0_03
#define zigbee_BUART_sTX_TxShifter_u0__D1_REG CYREG_UDB_W8_D1_03
#define zigbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define zigbee_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_UDB_CAT16_F_03
#define zigbee_BUART_sTX_TxShifter_u0__F0_REG CYREG_UDB_W8_F0_03
#define zigbee_BUART_sTX_TxShifter_u0__F1_REG CYREG_UDB_W8_F1_03
#define zigbee_BUART_sTX_TxSts__0__MASK 0x01u
#define zigbee_BUART_sTX_TxSts__0__POS 0
#define zigbee_BUART_sTX_TxSts__1__MASK 0x02u
#define zigbee_BUART_sTX_TxSts__1__POS 1
#define zigbee_BUART_sTX_TxSts__2__MASK 0x04u
#define zigbee_BUART_sTX_TxSts__2__POS 2
#define zigbee_BUART_sTX_TxSts__3__MASK 0x08u
#define zigbee_BUART_sTX_TxSts__3__POS 3
#define zigbee_BUART_sTX_TxSts__MASK 0x0Fu
#define zigbee_BUART_sTX_TxSts__MASK_REG CYREG_UDB_W8_MSK_03
#define zigbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define zigbee_BUART_sTX_TxSts__STATUS_REG CYREG_UDB_W8_ST_03

/* zigbee_IntClock */
#define zigbee_IntClock__DIVIDER_MASK 0x0000FFFFu
#define zigbee_IntClock__ENABLE CYREG_CLK_DIVIDER_B00
#define zigbee_IntClock__ENABLE_MASK 0x80000000u
#define zigbee_IntClock__MASK 0x80000000u
#define zigbee_IntClock__REGISTER CYREG_CLK_DIVIDER_B00

/* Accelero_SCB */
#define Accelero_SCB__BIST_CONTROL CYREG_SCB0_BIST_CONTROL
#define Accelero_SCB__BIST_DATA CYREG_SCB0_BIST_DATA
#define Accelero_SCB__CTRL CYREG_SCB0_CTRL
#define Accelero_SCB__EZ_DATA00 CYREG_SCB0_EZ_DATA00
#define Accelero_SCB__EZ_DATA01 CYREG_SCB0_EZ_DATA01
#define Accelero_SCB__EZ_DATA02 CYREG_SCB0_EZ_DATA02
#define Accelero_SCB__EZ_DATA03 CYREG_SCB0_EZ_DATA03
#define Accelero_SCB__EZ_DATA04 CYREG_SCB0_EZ_DATA04
#define Accelero_SCB__EZ_DATA05 CYREG_SCB0_EZ_DATA05
#define Accelero_SCB__EZ_DATA06 CYREG_SCB0_EZ_DATA06
#define Accelero_SCB__EZ_DATA07 CYREG_SCB0_EZ_DATA07
#define Accelero_SCB__EZ_DATA08 CYREG_SCB0_EZ_DATA08
#define Accelero_SCB__EZ_DATA09 CYREG_SCB0_EZ_DATA09
#define Accelero_SCB__EZ_DATA10 CYREG_SCB0_EZ_DATA10
#define Accelero_SCB__EZ_DATA11 CYREG_SCB0_EZ_DATA11
#define Accelero_SCB__EZ_DATA12 CYREG_SCB0_EZ_DATA12
#define Accelero_SCB__EZ_DATA13 CYREG_SCB0_EZ_DATA13
#define Accelero_SCB__EZ_DATA14 CYREG_SCB0_EZ_DATA14
#define Accelero_SCB__EZ_DATA15 CYREG_SCB0_EZ_DATA15
#define Accelero_SCB__EZ_DATA16 CYREG_SCB0_EZ_DATA16
#define Accelero_SCB__EZ_DATA17 CYREG_SCB0_EZ_DATA17
#define Accelero_SCB__EZ_DATA18 CYREG_SCB0_EZ_DATA18
#define Accelero_SCB__EZ_DATA19 CYREG_SCB0_EZ_DATA19
#define Accelero_SCB__EZ_DATA20 CYREG_SCB0_EZ_DATA20
#define Accelero_SCB__EZ_DATA21 CYREG_SCB0_EZ_DATA21
#define Accelero_SCB__EZ_DATA22 CYREG_SCB0_EZ_DATA22
#define Accelero_SCB__EZ_DATA23 CYREG_SCB0_EZ_DATA23
#define Accelero_SCB__EZ_DATA24 CYREG_SCB0_EZ_DATA24
#define Accelero_SCB__EZ_DATA25 CYREG_SCB0_EZ_DATA25
#define Accelero_SCB__EZ_DATA26 CYREG_SCB0_EZ_DATA26
#define Accelero_SCB__EZ_DATA27 CYREG_SCB0_EZ_DATA27
#define Accelero_SCB__EZ_DATA28 CYREG_SCB0_EZ_DATA28
#define Accelero_SCB__EZ_DATA29 CYREG_SCB0_EZ_DATA29
#define Accelero_SCB__EZ_DATA30 CYREG_SCB0_EZ_DATA30
#define Accelero_SCB__EZ_DATA31 CYREG_SCB0_EZ_DATA31
#define Accelero_SCB__I2C_CFG CYREG_SCB0_I2C_CFG
#define Accelero_SCB__I2C_CTRL CYREG_SCB0_I2C_CTRL
#define Accelero_SCB__I2C_M_CMD CYREG_SCB0_I2C_M_CMD
#define Accelero_SCB__I2C_S_CMD CYREG_SCB0_I2C_S_CMD
#define Accelero_SCB__I2C_STATUS CYREG_SCB0_I2C_STATUS
#define Accelero_SCB__INTR_CAUSE CYREG_SCB0_INTR_CAUSE
#define Accelero_SCB__INTR_I2C_EC CYREG_SCB0_INTR_I2C_EC
#define Accelero_SCB__INTR_I2C_EC_MASK CYREG_SCB0_INTR_I2C_EC_MASK
#define Accelero_SCB__INTR_I2C_EC_MASKED CYREG_SCB0_INTR_I2C_EC_MASKED
#define Accelero_SCB__INTR_M CYREG_SCB0_INTR_M
#define Accelero_SCB__INTR_M_MASK CYREG_SCB0_INTR_M_MASK
#define Accelero_SCB__INTR_M_MASKED CYREG_SCB0_INTR_M_MASKED
#define Accelero_SCB__INTR_M_SET CYREG_SCB0_INTR_M_SET
#define Accelero_SCB__INTR_RX CYREG_SCB0_INTR_RX
#define Accelero_SCB__INTR_RX_MASK CYREG_SCB0_INTR_RX_MASK
#define Accelero_SCB__INTR_RX_MASKED CYREG_SCB0_INTR_RX_MASKED
#define Accelero_SCB__INTR_RX_SET CYREG_SCB0_INTR_RX_SET
#define Accelero_SCB__INTR_S CYREG_SCB0_INTR_S
#define Accelero_SCB__INTR_S_MASK CYREG_SCB0_INTR_S_MASK
#define Accelero_SCB__INTR_S_MASKED CYREG_SCB0_INTR_S_MASKED
#define Accelero_SCB__INTR_S_SET CYREG_SCB0_INTR_S_SET
#define Accelero_SCB__INTR_SPI_EC CYREG_SCB0_INTR_SPI_EC
#define Accelero_SCB__INTR_SPI_EC_MASK CYREG_SCB0_INTR_SPI_EC_MASK
#define Accelero_SCB__INTR_SPI_EC_MASKED CYREG_SCB0_INTR_SPI_EC_MASKED
#define Accelero_SCB__INTR_TX CYREG_SCB0_INTR_TX
#define Accelero_SCB__INTR_TX_MASK CYREG_SCB0_INTR_TX_MASK
#define Accelero_SCB__INTR_TX_MASKED CYREG_SCB0_INTR_TX_MASKED
#define Accelero_SCB__INTR_TX_SET CYREG_SCB0_INTR_TX_SET
#define Accelero_SCB__RX_CTRL CYREG_SCB0_RX_CTRL
#define Accelero_SCB__RX_FIFO_CTRL CYREG_SCB0_RX_FIFO_CTRL
#define Accelero_SCB__RX_FIFO_RD CYREG_SCB0_RX_FIFO_RD
#define Accelero_SCB__RX_FIFO_RD_SILENT CYREG_SCB0_RX_FIFO_RD_SILENT
#define Accelero_SCB__RX_FIFO_STATUS CYREG_SCB0_RX_FIFO_STATUS
#define Accelero_SCB__RX_MATCH CYREG_SCB0_RX_MATCH
#define Accelero_SCB__SPI_CTRL CYREG_SCB0_SPI_CTRL
#define Accelero_SCB__SPI_STATUS CYREG_SCB0_SPI_STATUS
#define Accelero_SCB__SS0_POSISTION 0u
#define Accelero_SCB__SS1_POSISTION 1u
#define Accelero_SCB__SS2_POSISTION 2u
#define Accelero_SCB__SS3_POSISTION 3u
#define Accelero_SCB__STATUS CYREG_SCB0_STATUS
#define Accelero_SCB__TX_CTRL CYREG_SCB0_TX_CTRL
#define Accelero_SCB__TX_FIFO_CTRL CYREG_SCB0_TX_FIFO_CTRL
#define Accelero_SCB__TX_FIFO_STATUS CYREG_SCB0_TX_FIFO_STATUS
#define Accelero_SCB__TX_FIFO_WR CYREG_SCB0_TX_FIFO_WR
#define Accelero_SCB__UART_CTRL CYREG_SCB0_UART_CTRL
#define Accelero_SCB__UART_RX_CTRL CYREG_SCB0_UART_RX_CTRL
#define Accelero_SCB__UART_RX_STATUS CYREG_SCB0_UART_RX_STATUS
#define Accelero_SCB__UART_TX_CTRL CYREG_SCB0_UART_TX_CTRL

/* Accelero_SCB_IRQ */
#define Accelero_SCB_IRQ__INTC_CLR_EN_REG CYREG_CM0_ICER
#define Accelero_SCB_IRQ__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define Accelero_SCB_IRQ__INTC_MASK 0x400u
#define Accelero_SCB_IRQ__INTC_NUMBER 10u
#define Accelero_SCB_IRQ__INTC_PRIOR_MASK 0xC00000u
#define Accelero_SCB_IRQ__INTC_PRIOR_NUM 3u
#define Accelero_SCB_IRQ__INTC_PRIOR_REG CYREG_CM0_IPR2
#define Accelero_SCB_IRQ__INTC_SET_EN_REG CYREG_CM0_ISER
#define Accelero_SCB_IRQ__INTC_SET_PD_REG CYREG_CM0_ISPR

/* Accelero_SCBCLK */
#define Accelero_SCBCLK__DIVIDER_MASK 0x0000FFFFu
#define Accelero_SCBCLK__ENABLE CYREG_CLK_DIVIDER_A00
#define Accelero_SCBCLK__ENABLE_MASK 0x80000000u
#define Accelero_SCBCLK__MASK 0x80000000u
#define Accelero_SCBCLK__REGISTER CYREG_CLK_DIVIDER_A00

/* Accelero_scl */
#define Accelero_scl__0__DM__MASK 0x07u
#define Accelero_scl__0__DM__SHIFT 0
#define Accelero_scl__0__DR CYREG_PRT4_DR
#define Accelero_scl__0__HSIOM CYREG_HSIOM_PORT_SEL4
#define Accelero_scl__0__HSIOM_MASK 0x0000000Fu
#define Accelero_scl__0__HSIOM_SHIFT 0u
#define Accelero_scl__0__INTCFG CYREG_PRT4_INTCFG
#define Accelero_scl__0__INTSTAT CYREG_PRT4_INTSTAT
#define Accelero_scl__0__MASK 0x01u
#define Accelero_scl__0__PC CYREG_PRT4_PC
#define Accelero_scl__0__PC2 CYREG_PRT4_PC2
#define Accelero_scl__0__PORT 4u
#define Accelero_scl__0__PS CYREG_PRT4_PS
#define Accelero_scl__0__SHIFT 0
#define Accelero_scl__DR CYREG_PRT4_DR
#define Accelero_scl__INTCFG CYREG_PRT4_INTCFG
#define Accelero_scl__INTSTAT CYREG_PRT4_INTSTAT
#define Accelero_scl__MASK 0x01u
#define Accelero_scl__PC CYREG_PRT4_PC
#define Accelero_scl__PC2 CYREG_PRT4_PC2
#define Accelero_scl__PORT 4u
#define Accelero_scl__PS CYREG_PRT4_PS
#define Accelero_scl__SHIFT 0

/* Accelero_sda */
#define Accelero_sda__0__DM__MASK 0x38u
#define Accelero_sda__0__DM__SHIFT 3
#define Accelero_sda__0__DR CYREG_PRT4_DR
#define Accelero_sda__0__HSIOM CYREG_HSIOM_PORT_SEL4
#define Accelero_sda__0__HSIOM_MASK 0x000000F0u
#define Accelero_sda__0__HSIOM_SHIFT 4u
#define Accelero_sda__0__INTCFG CYREG_PRT4_INTCFG
#define Accelero_sda__0__INTSTAT CYREG_PRT4_INTSTAT
#define Accelero_sda__0__MASK 0x02u
#define Accelero_sda__0__PC CYREG_PRT4_PC
#define Accelero_sda__0__PC2 CYREG_PRT4_PC2
#define Accelero_sda__0__PORT 4u
#define Accelero_sda__0__PS CYREG_PRT4_PS
#define Accelero_sda__0__SHIFT 1
#define Accelero_sda__DR CYREG_PRT4_DR
#define Accelero_sda__INTCFG CYREG_PRT4_INTCFG
#define Accelero_sda__INTSTAT CYREG_PRT4_INTSTAT
#define Accelero_sda__MASK 0x02u
#define Accelero_sda__PC CYREG_PRT4_PC
#define Accelero_sda__PC2 CYREG_PRT4_PC2
#define Accelero_sda__PORT 4u
#define Accelero_sda__PS CYREG_PRT4_PS
#define Accelero_sda__SHIFT 1

/* Pin_gestion_sleep_xbee */
#define Pin_gestion_sleep_xbee__0__DM__MASK 0x38000u
#define Pin_gestion_sleep_xbee__0__DM__SHIFT 15
#define Pin_gestion_sleep_xbee__0__DR CYREG_PRT3_DR
#define Pin_gestion_sleep_xbee__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define Pin_gestion_sleep_xbee__0__HSIOM_MASK 0x00F00000u
#define Pin_gestion_sleep_xbee__0__HSIOM_SHIFT 20u
#define Pin_gestion_sleep_xbee__0__INTCFG CYREG_PRT3_INTCFG
#define Pin_gestion_sleep_xbee__0__INTSTAT CYREG_PRT3_INTSTAT
#define Pin_gestion_sleep_xbee__0__MASK 0x20u
#define Pin_gestion_sleep_xbee__0__PA__CFG0 CYREG_UDB_PA3_CFG0
#define Pin_gestion_sleep_xbee__0__PA__CFG1 CYREG_UDB_PA3_CFG1
#define Pin_gestion_sleep_xbee__0__PA__CFG10 CYREG_UDB_PA3_CFG10
#define Pin_gestion_sleep_xbee__0__PA__CFG11 CYREG_UDB_PA3_CFG11
#define Pin_gestion_sleep_xbee__0__PA__CFG12 CYREG_UDB_PA3_CFG12
#define Pin_gestion_sleep_xbee__0__PA__CFG13 CYREG_UDB_PA3_CFG13
#define Pin_gestion_sleep_xbee__0__PA__CFG14 CYREG_UDB_PA3_CFG14
#define Pin_gestion_sleep_xbee__0__PA__CFG2 CYREG_UDB_PA3_CFG2
#define Pin_gestion_sleep_xbee__0__PA__CFG3 CYREG_UDB_PA3_CFG3
#define Pin_gestion_sleep_xbee__0__PA__CFG4 CYREG_UDB_PA3_CFG4
#define Pin_gestion_sleep_xbee__0__PA__CFG5 CYREG_UDB_PA3_CFG5
#define Pin_gestion_sleep_xbee__0__PA__CFG6 CYREG_UDB_PA3_CFG6
#define Pin_gestion_sleep_xbee__0__PA__CFG7 CYREG_UDB_PA3_CFG7
#define Pin_gestion_sleep_xbee__0__PA__CFG8 CYREG_UDB_PA3_CFG8
#define Pin_gestion_sleep_xbee__0__PA__CFG9 CYREG_UDB_PA3_CFG9
#define Pin_gestion_sleep_xbee__0__PC CYREG_PRT3_PC
#define Pin_gestion_sleep_xbee__0__PC2 CYREG_PRT3_PC2
#define Pin_gestion_sleep_xbee__0__PORT 3u
#define Pin_gestion_sleep_xbee__0__PS CYREG_PRT3_PS
#define Pin_gestion_sleep_xbee__0__SHIFT 5
#define Pin_gestion_sleep_xbee__DR CYREG_PRT3_DR
#define Pin_gestion_sleep_xbee__INTCFG CYREG_PRT3_INTCFG
#define Pin_gestion_sleep_xbee__INTSTAT CYREG_PRT3_INTSTAT
#define Pin_gestion_sleep_xbee__MASK 0x20u
#define Pin_gestion_sleep_xbee__PA__CFG0 CYREG_UDB_PA3_CFG0
#define Pin_gestion_sleep_xbee__PA__CFG1 CYREG_UDB_PA3_CFG1
#define Pin_gestion_sleep_xbee__PA__CFG10 CYREG_UDB_PA3_CFG10
#define Pin_gestion_sleep_xbee__PA__CFG11 CYREG_UDB_PA3_CFG11
#define Pin_gestion_sleep_xbee__PA__CFG12 CYREG_UDB_PA3_CFG12
#define Pin_gestion_sleep_xbee__PA__CFG13 CYREG_UDB_PA3_CFG13
#define Pin_gestion_sleep_xbee__PA__CFG14 CYREG_UDB_PA3_CFG14
#define Pin_gestion_sleep_xbee__PA__CFG2 CYREG_UDB_PA3_CFG2
#define Pin_gestion_sleep_xbee__PA__CFG3 CYREG_UDB_PA3_CFG3
#define Pin_gestion_sleep_xbee__PA__CFG4 CYREG_UDB_PA3_CFG4
#define Pin_gestion_sleep_xbee__PA__CFG5 CYREG_UDB_PA3_CFG5
#define Pin_gestion_sleep_xbee__PA__CFG6 CYREG_UDB_PA3_CFG6
#define Pin_gestion_sleep_xbee__PA__CFG7 CYREG_UDB_PA3_CFG7
#define Pin_gestion_sleep_xbee__PA__CFG8 CYREG_UDB_PA3_CFG8
#define Pin_gestion_sleep_xbee__PA__CFG9 CYREG_UDB_PA3_CFG9
#define Pin_gestion_sleep_xbee__PC CYREG_PRT3_PC
#define Pin_gestion_sleep_xbee__PC2 CYREG_PRT3_PC2
#define Pin_gestion_sleep_xbee__PORT 3u
#define Pin_gestion_sleep_xbee__PS CYREG_PRT3_PS
#define Pin_gestion_sleep_xbee__SHIFT 5

/* Miscellaneous */
#define CY_PROJECT_NAME "ADXL345_sleep_xbee"
#define CY_VERSION "PSoC Creator  3.3 SP1"
#define CYDEV_BCLK__HFCLK__HZ 4000000U
#define CYDEV_BCLK__HFCLK__KHZ 4000U
#define CYDEV_BCLK__HFCLK__MHZ 4U
#define CYDEV_BCLK__SYSCLK__HZ 2000000U
#define CYDEV_BCLK__SYSCLK__KHZ 2000U
#define CYDEV_BCLK__SYSCLK__MHZ 2U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 18u
#define CYDEV_CHIP_DIE_PSOC4A 10u
#define CYDEV_CHIP_DIE_PSOC5LP 17u
#define CYDEV_CHIP_DIE_TMA4 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x04C81193u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 10u
#define CYDEV_CHIP_MEMBER_4C 15u
#define CYDEV_CHIP_MEMBER_4D 6u
#define CYDEV_CHIP_MEMBER_4E 4u
#define CYDEV_CHIP_MEMBER_4F 11u
#define CYDEV_CHIP_MEMBER_4G 2u
#define CYDEV_CHIP_MEMBER_4H 9u
#define CYDEV_CHIP_MEMBER_4I 14u
#define CYDEV_CHIP_MEMBER_4J 7u
#define CYDEV_CHIP_MEMBER_4K 8u
#define CYDEV_CHIP_MEMBER_4L 13u
#define CYDEV_CHIP_MEMBER_4M 12u
#define CYDEV_CHIP_MEMBER_4N 5u
#define CYDEV_CHIP_MEMBER_4U 3u
#define CYDEV_CHIP_MEMBER_5A 17u
#define CYDEV_CHIP_MEMBER_5B 16u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4A
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4C_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DFT_SELECT_CLK0 1u
#define CYDEV_DFT_SELECT_CLK1 2u
#define CYDEV_HEAP_SIZE 0x200
#define CYDEV_IMO_TRIMMED_BY_USB 0u
#define CYDEV_IMO_TRIMMED_BY_WCO 0u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0800
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDDA 3.3
#define CYDEV_VDDA_MV 3300
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYDEV_WDT_GENERATE_ISR 0u
#define CYIPBLOCK_M0S8_CTBM_VERSION 0
#define CYIPBLOCK_m0s8cpuss_VERSION 0
#define CYIPBLOCK_m0s8csd_VERSION 0
#define CYIPBLOCK_m0s8gpio2_VERSION 0
#define CYIPBLOCK_m0s8hsiom4a_VERSION 0
#define CYIPBLOCK_m0s8lcd_VERSION 0
#define CYIPBLOCK_m0s8lpcomp_VERSION 0
#define CYIPBLOCK_m0s8pclk_VERSION 0
#define CYIPBLOCK_m0s8sar_VERSION 0
#define CYIPBLOCK_m0s8scb_VERSION 0
#define CYIPBLOCK_m0s8srssv2_VERSION 1
#define CYIPBLOCK_m0s8tcpwm_VERSION 0
#define CYIPBLOCK_m0s8udbif_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 2
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
